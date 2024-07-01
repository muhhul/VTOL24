#include <TFmini.h>
#include <std_srvs/SetBool.h>
#include <std_msgs/Float64.h>
#include <deque>
#include <cmath>
#include <mavros_msgs/PositionTarget.h>
#include <std_srvs/Empty.h>

struct dist_and_time {
  float dist;
  double secs;
  dist_and_time(): dist(0.0), secs(0.0) {};
};

const bool VELZ_DEBUG = false;

float pub_rate_val = 100.0;
std::deque<dist_and_time> data_store(50, dist_and_time());    // berarti menyimpan selama satu detik
float threshold = 1.0;  // for redundancy
float err_tol = 0.70;
float last_stable = 0.0;
float is_stable = false;
float last_vel = 0.0;
float vel_thresh_c = 4.0;
float vel_thresh_d = 3.0;

bool do_modify = true;

bool set_modify(std_srvs::SetBool::Request &req, std_srvs::SetBool::Response &res) {
  if (req.data) do_modify = true;
  else do_modify = false;
  res.success = true;
  return true;
}

void update_status() {
  float abs_err = 0.0;
  int n = data_store.size();
  for (int i = 0; i < n - 1;  i++) {
    abs_err += std::fabs(data_store.at(i+1).dist - data_store.at(i).dist);
  }
  if (abs_err < err_tol) {
    if (!is_stable) {
        ROS_DEBUG("Alt reading is now CONSTANT");
        ROS_DEBUG_STREAM("Last stable = " << last_stable);
    }
    is_stable = true;
    last_stable = data_store.back().dist;
  }
  else {
    if (is_stable) ROS_DEBUG("Alt reading is now NOT CONSTANT");
    is_stable = false;
  }

  double last_time_n5 = data_store.at(n - 20).secs;
  if (last_time_n5 > 1.0) {
    double delta_time = data_store.back().secs - last_time_n5;
    if (delta_time < 0.02) {
      ROS_DEBUG_STREAM("Delta time = " << delta_time);
    }
    float delta_z = data_store.back().dist - 
                    data_store.at(n - 20).dist;
    last_vel = (double) delta_z / delta_time;
  }

  return;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "tfmini_ros_node");
  ros::NodeHandle nh("~");
  std::string id = "/mavros/distance_sensor/rangefinder_sub";
  std::string portName;
  int baud_rate;
  benewake::TFmini *tfmini_obj;

  nh.param("serial_port", portName, std::string("/dev/ttyUSB0"));
  nh.param("baud_rate", baud_rate, 115200);

  tfmini_obj = new benewake::TFmini(portName, baud_rate);
  ros::Publisher pub_range = nh.advertise<sensor_msgs::Range>(id, 1, true);
  sensor_msgs::Range TFmini_range;
  TFmini_range.radiation_type = sensor_msgs::Range::INFRARED;
  TFmini_range.field_of_view = 0.04;
  TFmini_range.min_range = 0.3;
  TFmini_range.max_range = 12;
  TFmini_range.header.frame_id = id;
  float dist = 0;
  ROS_WARN_STREAM("Start processing ...");

  bool is_climbing = false, is_above = false;
  float last_dist = 0.3;    // initial val must match RF mounting position
  float temp, obs_height;
  ros::Rate pub_rate(pub_rate_val);

  ros::Publisher raw_pub = nh.advertise<sensor_msgs::Range>("raw_data", 1000, true);
  ros::Publisher vel_pub = nh.advertise<std_msgs::Float64>("vel_data", 100, true);
  sensor_msgs::Range raw_range;
  std_msgs::Float64 vel_msg;

  ros::ServiceServer set_modify_srv = nh.advertiseService("set_modify", &set_modify);
  // good for debugging is_stable
  bool cmdVelConstant = false;
  ros::Subscriber cmdVelSub;
  ros::AsyncSpinner spinner(4);
  if (VELZ_DEBUG) {
    boost::function<void(const mavros_msgs::PositionTarget &)> cmdVelCb =
    [&] (const mavros_msgs::PositionTarget &msg) {
      if (fabs(msg.velocity.z) < 0.4) {
        if (!cmdVelConstant) {
          ROS_DEBUG_STREAM_THROTTLE(0.5, "\nCommand vel now CONSTANT coz vel = " << 
          msg.velocity.z << '\n');
        }
        cmdVelConstant = true;
      }
      else {
        if (cmdVelConstant) {
          ROS_DEBUG_STREAM_THROTTLE(0.5, "\nCommand vel now NOTCONSTANT coz vel = " <<
          msg.velocity.z << '\n');
        }
        cmdVelConstant = false;
      }

      if (cmdVelConstant && !is_stable) {
        ROS_ERROR_STREAM_THROTTLE(1, "Command vel ~0 but is_stable FALSE!" << 
        "\nCmd vel z = " << msg.velocity.z);
      }
    };
    cmdVelSub = nh.subscribe<mavros_msgs::PositionTarget>(
      "/mavros/setpoint_raw/local", 1, cmdVelCb);
    spinner.start();
  }

  ros::ServiceClient safetyClient = nh.serviceClient<std_srvs::SetBool>("/uav_safety/mundur");
  std_srvs::SetBool safetySrv;
  bool alreadyCalling = false;
  boost::function<void(const ros::TimerEvent &)> timerCb =
  [&] (const ros::TimerEvent &ev) {
    if (is_climbing && !is_above) {
      if (!alreadyCalling) {
        //double prevClimbTime = ros::Time::now().toSec();
        alreadyCalling = true;
        ROS_INFO("Mundur monitoring triggered!");
      
        ROS_INFO("Mundur monitoring now watching time~");
        ros::Duration(2.0).sleep();
          // bahaya!
        if (is_climbing && !is_above) {
          ROS_ERROR("2seconds with is_climbing && !is_above. BAD!");
          safetySrv.request.data = true;
          for (int i = 0; i < 3; i++) {
            if (safetyClient.call(safetySrv)) {
              break;
            }
          }
          if (!safetySrv.response.success) {
            // Mau ngapain yah?
            ROS_FATAL("MUNDUR SERVICE NOT RESPONDING!!!");
            ROS_FATAL("TAKE ACTION!!!");
          }
        }
      }
    }
    if (!is_climbing || (is_climbing && is_above)) {
      if (alreadyCalling)
        ROS_INFO("Mundur monitoring reset...");
      alreadyCalling = false;
    }
  };
  ros::Timer timer = nh.createTimer(ros::Duration(0.05), timerCb);
  spinner.start();

  float last_stable_pause = last_stable;

  double last_published = 0.2;
  boost::function<void(const ros::TimerEvent &ev)> publisherTimerCb = 
  [&] (const ros::TimerEvent &ev) {
    sensor_msgs::Range pubMsg = TFmini_range;
    double gonna_publish = pubMsg.range;
    if (gonna_publish - last_published < -0.3 || last_published - last_published > 1.0) {
      ROS_WARN_STREAM_THROTTLE(0.2, "Gonna publish " << gonna_publish << " but last published = " << last_published);
      ROS_WARN_STREAM_THROTTLE(0.2, "Now publishing " << last_published << " instead.");
      gonna_publish = last_published;
    }
    pubMsg.range = gonna_publish;
    pub_range.publish(pubMsg);
    last_published = gonna_publish;
  };
  ros::Timer publisherTimer = nh.createTimer(ros::Duration(0.01), publisherTimerCb);
  spinner.start();

  double climbStarted;
  bool climbReset = true;
  ros::ServiceClient spamLandClient = nh.serviceClient<std_srvs::Empty>("/uav_safety/spam_land");
  boost::function<void(const ros::TimerEvent &ev)> climbSafetyCb =
  [&] (const ros::TimerEvent &ev) {
    if (!climbReset) {
      if (ros::Time::now().toSec() - climbStarted > 1.0) {
        if (is_above) {
          ROS_FATAL("Not detecting height after 1 sec.");
          ROS_FATAL("WILL SPAM LAND SRV!!!");
          std_srvs::Empty spamLandSrv;
          spamLandClient.call(spamLandSrv);
        }
      }
    }
  };
  climbStarted = ros::Time::now().toSec();
  ros::Timer climbSafety = nh.createTimer(ros::Duration(0.05), climbSafetyCb);
  spinner.start();

  while(ros::ok())
  {
    // ros::spinOnce();
    dist = tfmini_obj->getDist();

    if(dist > 0 && dist < TFmini_range.max_range)
    {
      raw_range.range = dist;
      raw_pub.publish(raw_range);
      vel_msg.data = last_vel;
      vel_pub.publish(vel_msg);

      TFmini_range.header.stamp = ros::Time::now();
      dist_and_time newdist;
      newdist.dist = dist;
      newdist.secs = TFmini_range.header.stamp.toSec();
      data_store.push_back(newdist);
      data_store.pop_front();
      update_status();
/*
      if (do_modify) {

		    if (!is_climbing && !is_above) {  // this assumes kotak simpel, ga kayak "tangga"
		      if (last_dist - dist > threshold || last_vel < -vel_thresh_c) {
		        ROS_WARN_STREAM("Obstacle climb detected. " << last_dist << " vs " << dist);
		        ROS_WARN_STREAM("Last vel = " << last_vel);
		        is_climbing = true;
			      is_above = false;
            climbStarted = ros::Time::now().toSec();
            climbReset = false;
            if (!is_stable) {
              for (uint8_t i = 0; i < 10; i++)
                ROS_FATAL("CLIMB BUT HASN'T BEEN STABLE!!!");
            }
            last_stable_pause = last_stable;
		      }
		    }
		    if (dist - last_dist > threshold || last_vel > vel_thresh_d) {
		      ROS_WARN_STREAM("Obstacle descent detected. " << dist << " vs " << last_dist);
		      ROS_WARN_STREAM("Last vel = " << last_vel);
		      is_climbing = false;
		      is_above = false;
          climbReset = true;
		    }

		    if (is_climbing) {
		      if (!is_stable && !is_above) {
		        if (last_stable < 0.1) {
		          // TODO. Panggil pilotOverride
		          ROS_FATAL("last_stable is EMPTY!");
		        }
		        TFmini_range.range = last_stable_pause;
		      }
		      else if (is_stable && !is_above) {
		        obs_height = last_stable_pause - last_stable;
            if (obs_height < 0) ROS_ERROR("Obstacle height negative.");
		        ROS_WARN_STREAM("Obstacle height: " << obs_height);
		        is_above = true;
            climbReset = true;
		      }
		      if (is_above) {
		        TFmini_range.range = dist + obs_height;
		      }
		    }

		    else TFmini_range.range = dist;
			}
*/
			 TFmini_range.range = dist;      

      // pub_range.publish(TFmini_range);
      last_dist = dist;
    }
    else if(dist == -1.0)
    {
      ROS_ERROR_STREAM("Failed to read data. TFmini ros node stopped!");
      break;
    }
    else if(dist == 0.0)
    {
      ROS_ERROR_STREAM("Data validation error!");
    }
//    pub_rate.sleep();
  }

  tfmini_obj->closePort();
}
