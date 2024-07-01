#include <uav_commander/pilot.hpp>
#include <std_srvs/Empty.h>
#include <std_srvs/SetBool.h>
#include <uav_msgs/SetCurrent.h>
#include <cstdlib>

bool killPilotCb(std_srvs::Empty::Request &req, std_srvs::Empty::Response &res)
{
  ROS_WARN("---PILOT NODE DIED---");
  ros::shutdown();
  exit(100);  // arbitrary
}

bool startMission = false;
bool toggleStartCb(std_srvs::SetBool::Request &req, std_srvs::SetBool::Response &res)
{
  res.success = false;
  startMission = req.data;
  res.success = true;
  ROS_INFO("Toggle on. Starting mission~");
  return true;
}

int startFrom = 0;
bool setCurrentCb(uav_msgs::SetCurrent::Request &req, uav_msgs::SetCurrent::Response &res)
{
  res.success = false;
  startFrom = req.data;
  res.success = true;
  ROS_INFO_STREAM("Starting from mission no " << startFrom);
  return true;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "pilot_node");
  if (argc != 3) {
    ROS_FATAL_STREAM("pilot_node needs exactly 2 argument. Given " << argc - 1);
    return 1;
  }
	ros::NodeHandle nh;
  ros::ServiceServer killPilot = nh.advertiseService("/uav_commander/killPilot", &killPilotCb);
  ros::ServiceServer toggleStart = nh.advertiseService("/uav_commander/toggleStart", &toggleStartCb);
  ros::ServiceServer setCurrent = nh.advertiseService("/uav_commander/setCurrent", &setCurrentCb);

  ros::AsyncSpinner spinner(1);
  spinner.start();

  uav_commander::pilot pilot(&nh);
  if (pilot.load(argv[1], argv[2])) {
    while (!startMission) ros::Duration(0.1).sleep();
    pilot.executeMissions(startFrom);
    return 0;
  }
  ROS_FATAL("Check again pilot file!");
  return 2;
}
