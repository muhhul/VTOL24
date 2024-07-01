#ifndef UAV_MISSIONS_UTILS_
#define UAV_MISSIONS_UTILS_

#include <ros/ros.h>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <std_msgs/Bool.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/Vector3.h>
#include <sensor_msgs/Range.h>
#include <mavros_msgs/PositionTarget.h>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <uav_msgs/MissionParams.h>
#include <uav_commander/uav_missions_config.hpp>
#include <cmath>

namespace uav_commander
{
	enum m_types {M_BOOLS, M_INTS, M_DOUBLES, M_STRINGS};	// For function checkArgs

	enum class Errors
	{
		NO_ERROR,
		UNKNOWN_ERROR,    // Because error code 1 might be used by non-uav_missions funcs
		MISSING_MESSAGE,
		UNRESPONSIVE_SERVICE,
		NO_SUBSCRIBER,
		INVALID_ARGUMENT,
		PARTIALLY_SUCCEEDED,
		CONFIG_ERROR
	};

	// All constants from config file will be loaded to here
	struct config {
		std::map<std::string, bool> bools;
		std::map<std::string, int> ints;
		std::map<std::string, double> doubles;
		std::map<std::string, std::string> strings;
	} config;

	int loadConfig(const std::string &filename)
	{
		ROS_DEBUG("Loading config file...");
		std::ifstream file(filename);
		std::string line;

		while (std::getline(file, line)) {
			std::istringstream iss(line);
			std::string type, key, value;
			iss >> type >> key >> value;
			if (type == "bool") {
				bool casted_value = (value == "true") ? true : false;
				config.bools.emplace(key, casted_value);    // no safe guard!
				ROS_DEBUG_STREAM("Loaded config " << key << " value " << casted_value);
			}
			else if (type == "int") {
				int casted_value = stoi(value);
				config.ints.emplace(key, casted_value);
				ROS_DEBUG_STREAM("Loaded config " << key << " value " << casted_value);
			}
			else if (type == "double") {
				double casted_value = stod(value);
				config.doubles.emplace(key, casted_value);
				ROS_DEBUG_STREAM("Loaded config " << key << " value " << casted_value);
			}
			else if (type == "string") {
				config.strings.emplace(key, value);
				ROS_DEBUG_STREAM("Loaded config " << key << " value " << value);
			}
		}

		ROS_WARN("---Config file OK.---");    // !! at least plz dump the config to a log file
		return (int) Errors::NO_ERROR;
	}

	bool checkArgs(const uav_msgs::MissionParams &m, m_types type, uint8_t size,
		bool warn = true, std::string func = __func__)
	{
		switch (type) {
			case M_BOOLS:
				if (m.bools.size() == size) return true; else break;
			case M_INTS:
				if (m.ints.size() == size) return true; else break;
			case M_DOUBLES:
				if (m.doubles.size() == size) return true; else break;
			case M_STRINGS:
				if (m.strings.size() == size) return true; else break;
		}
		// if reach here, the arg size is wrong
		if (warn)
			ROS_ERROR_STREAM("---Wrong argument size in " << func << "---");
		return false;
	}

	template <class T>
	int getTopicValue(T &returnVal, const std::string topicName, double retryTimeout) {
		ROS_DEBUG_STREAM_THROTTLE(1, "Waiting for message from " << topicName);

		boost::shared_ptr<const T> returnPtr;
		returnPtr = ros::topic::waitForMessage<T>(topicName, ros::Duration(retryTimeout));

		if (returnPtr == NULL) {
			ROS_FATAL_STREAM("Cannot get message from " << topicName);
			return (int) Errors::MISSING_MESSAGE;
		}

		returnVal = *returnPtr;
		return (int) Errors::NO_ERROR;
	}
	
	template <class T>
	int waitAndPublish(T &msg, const std::string topicName, ros::NodeHandle &nh, double waitTimeout = config.doubles.at("WAIT_SUB_TIMEOUT"))
	{
		ros::Publisher pub = nh.advertise<T>(topicName, 5, true);
		ROS_DEBUG_STREAM("Waiting for subscriber of " << topicName);

		double initialTry, currTry;
		do {
			initialTry = ros::Time::now().toSec();
		} while (initialTry < 1.0);    // Is a MUST when using simulation time
		ros::Rate rate(20);
		
		while (pub.getNumSubscribers() <= 0) {
			currTry = ros::Time::now().toSec();
			if (currTry - initialTry > waitTimeout) {
				ROS_FATAL_STREAM("No subscriber for topic " << topicName);
				ROS_DEBUG_STREAM("Stop waiting for subs coz elapsed: " << 
					currTry - initialTry << " sec.");
				return (int) Errors::NO_SUBSCRIBER;
			}
			rate.sleep();
		}

		pub.publish(msg);
		ROS_INFO_STREAM("Message published to " << topicName);
		return (int) Errors::NO_ERROR;
	}

	int getAltitude(double &relAlt, std::string source) {
		if (source == "local_pose") {
			std::string topicName = "/mavros/local_position/pose";
			geometry_msgs::PoseStamped reading;
			int gotTopic = getTopicValue(reading, topicName, config.doubles.at("WAIT_MSG_TO_LONG"));
			if (gotTopic != 0) {
				ROS_FATAL("Altitude data not fetched");
				ROS_FATAL_STREAM("Terminate in function " << __func__);
				return gotTopic;
			}

			relAlt = reading.pose.position.z;
			ROS_DEBUG_STREAM_THROTTLE(1, "Height: " << relAlt);
			return (int) Errors::NO_ERROR;
		}
		else if (source == "rangefinder") {
			std::string topicName = config.strings.at("RF_BAWAH_SRC");
			sensor_msgs::Range reading;
			int gotTopic = getTopicValue(reading, topicName, config.doubles.at("WAIT_MSG_TO_LONG"));
			if (gotTopic != 0) {
				ROS_FATAL("Altitude data not fetched");
				ROS_FATAL_STREAM("Terminate in function " << __func__);
				return gotTopic;
				ROS_WARN("GOT TOPIC!");
			}

			relAlt = reading.range;
			ROS_DEBUG_STREAM_THROTTLE(1, "Height: " << relAlt);
			return (int) Errors::NO_ERROR;
		}
		else if (source == "rel_alt") {
			std_msgs::Float64 reading;
			int gotTopic = getTopicValue(reading, "/mavros/global_position/rel_alt", 
				config.doubles.at("WAIT_MSG_TO_LONG"));
			if (gotTopic != 0) {
				ROS_FATAL("Altitude data not fetched!");
				ROS_FATAL_STREAM("Terminate in function " << __func__);
				return gotTopic;
			}

			relAlt = reading.data;
			ROS_DEBUG_STREAM_THROTTLE(1, "Height: " << relAlt);
			return (int) Errors::NO_ERROR;
		}

		else return (int) Errors::CONFIG_ERROR;
	}

	int waitAltitude(const double desiredAlt, std::string source)
	{
		ROS_INFO_STREAM("Waiting for relative altitude " << desiredAlt << " meters.");

		double relAlt;
		double altTol = config.doubles.at("ROUGH_Z_TOL");

		do {
			int gotAlt = getAltitude(relAlt, source);
			if (gotAlt != 0) {
				ROS_ERROR_STREAM("Terminate in func " << __func__);
				return gotAlt;
			};
		} while (std::fabs(relAlt - desiredAlt) > altTol);

		ROS_WARN_STREAM("---Altitude " << desiredAlt << "m reached.---");
		return (int) Errors::NO_ERROR;		
	}
	
	int indoorWaitCoord(const uav_msgs::MissionParams &m, ros::NodeHandle &nh, bool &reached,
		bool precise, double timeout = 60.0)
	{
		// Assumes UAV is already moving
		if (!checkArgs(m, M_DOUBLES, 3)) return (int) Errors::INVALID_ARGUMENT;

		double xDestCoord = m.doubles[0];
		double yDestCoord = m.doubles[1];
		double zDestCoord = m.doubles[2];
		double xCurrCoord, yCurrCoord, zCurrCoord;

		ROS_WARN_STREAM("---Waiting for arrival at (" << xDestCoord << ", " <<
			yDestCoord << ", " << zDestCoord << ")---");

		// Needs current position first to be able to evaluate xDestCoord - xCurrCoord, dst.
		geometry_msgs::PoseStamped initialPose;
		int gotTopic = getTopicValue(initialPose, "/mavros/local_position/pose", config.doubles.at("WAIT_MSG_TO_LONG"));
		if (gotTopic != 0) {
			ROS_FATAL_STREAM("Terminate in function " << __func__);
			return gotTopic;
		}

		xCurrCoord = initialPose.pose.position.x;
		yCurrCoord = initialPose.pose.position.y;
		zCurrCoord = initialPose.pose.position.z;

		// Now set up the subscriber
		boost::function<void(const geometry_msgs::PoseStamped&)> poseCb = [&] (const geometry_msgs::PoseStamped &msg) {
			xCurrCoord = msg.pose.position.x;
			yCurrCoord = msg.pose.position.y;
			zCurrCoord = msg.pose.position.z;
		};

		ros::Rate rate(20);    // Arbitrary
		ros::Subscriber sub = nh.subscribe<geometry_msgs::PoseStamped>("/mavros/local_position/pose", 10, poseCb);

		double xCoordTol, yCoordTol, zCoordTol;
		if (precise) {
			xCoordTol = config.doubles.at("PREC_X_TOL");
			yCoordTol = config.doubles.at("PREC_Y_TOL");
			zCoordTol = config.doubles.at("PREC_Z_TOL");
		}
		else {
			xCoordTol = config.doubles.at("ROUGH_X_TOL");
			yCoordTol = config.doubles.at("ROUGH_Y_TOL");
			zCoordTol = config.doubles.at("ROUGH_Z_TOL");
		}
		reached = false;

		double startTime = ros::Time::now().toSec();
		double nowTime;
		do {
			if (std::fabs(xDestCoord - xCurrCoord) < xCoordTol &&
				std::fabs(yDestCoord - yCurrCoord) < yCoordTol &&
				std::fabs(zDestCoord - zCurrCoord) < zCoordTol)
				reached = true;
			rate.sleep();
			ros::spinOnce;
			nowTime = ros::Time::now().toSec();
		} while (!reached && (nowTime - startTime) < timeout);

		if (reached) ROS_WARN("---Arrived at designated coordinate---");
		else ROS_WARN("---Has not yet arrived");
		return (int) Errors::NO_ERROR;
	}

	int positionGoTo(const uav_msgs::MissionParams &m, ros::NodeHandle &nh, bool precise)
	{
		uint8_t nArgs;
		if (checkArgs(m, M_DOUBLES, 1, false)) nArgs = 1;
		else if (checkArgs(m, M_DOUBLES, 2, false)) nArgs = 2;
		else if (checkArgs(m, M_DOUBLES, 3, false)) nArgs = 3;
		else if (checkArgs(m, M_DOUBLES, 7)) nArgs = 7;
		else return (int) Errors::INVALID_ARGUMENT;

		geometry_msgs::PoseStamped initialPose;
		int gotPose = getTopicValue(initialPose, "/mavros/local_position/pose", config.doubles.at("WAIT_MSG_TO_LONG"));
		if (gotPose != 0) {
			ROS_FATAL_STREAM("Terminate in func " << __func__);
			return gotPose;
		}

		double xDestCoord, yDestCoord, zDestCoord;
		double xDestOrient, yDestOrient, zDestOrient, wDestOrient;

		switch (nArgs) {
			case 1:
				xDestCoord = initialPose.pose.position.x;
				yDestCoord = initialPose.pose.position.y;
				zDestCoord = m.doubles[0];
				xDestOrient = initialPose.pose.orientation.x;
				yDestOrient = initialPose.pose.orientation.y;
				zDestOrient = initialPose.pose.orientation.z;
				wDestOrient = initialPose.pose.orientation.w;
				break;
			case 2:
				xDestCoord = m.doubles[0];
				yDestCoord = m.doubles[1];
				zDestCoord = initialPose.pose.position.z;
				xDestOrient = initialPose.pose.orientation.x;
				yDestOrient = initialPose.pose.orientation.y;
				zDestOrient = initialPose.pose.orientation.z;
				wDestOrient = initialPose.pose.orientation.w;
				break;
			case 3:
				xDestCoord = m.doubles[0];
				yDestCoord = m.doubles[1];
				zDestCoord = m.doubles[2];
				xDestOrient = initialPose.pose.orientation.x;
				yDestOrient = initialPose.pose.orientation.y;
				zDestOrient = initialPose.pose.orientation.z;
				wDestOrient = initialPose.pose.orientation.w;
				break;
			case 7:
				xDestCoord = m.doubles[0];
				yDestCoord = m.doubles[1];
				zDestCoord = m.doubles[2];
				xDestOrient = m.doubles[3];
				yDestOrient = m.doubles[4];
				zDestOrient = m.doubles[5];
				wDestOrient = m.doubles[6];
				break;				
		}
		
		ROS_WARN_STREAM("---Going to (" << xDestCoord << ", " << yDestCoord <<
			", " << zDestCoord << ")---");
		ROS_DEBUG_STREAM("Dest orient: " << xDestOrient << ", " << yDestOrient << 
			", " << zDestOrient << ", " << wDestOrient);
		
		geometry_msgs::PoseStamped msg;
		msg.pose.position.x = xDestCoord;
		msg.pose.position.y = yDestCoord;
		msg.pose.position.z = zDestCoord;
		msg.pose.orientation.x = xDestOrient;
		msg.pose.orientation.y = yDestOrient;
		msg.pose.orientation.z = zDestOrient;
		msg.pose.orientation.w = wDestOrient;

		bool feedbackCheck;
		double distance = sqrt(pow(xDestCoord - initialPose.pose.position.x, 2) + 
			pow(yDestCoord - initialPose.pose.position.y, 2) + 
			pow(zDestCoord - initialPose.pose.position.z, 2));
		if (distance < config.doubles.at("GOTO_CHKMOVE_IF"))
			feedbackCheck = false;
		else feedbackCheck = true;

		if (feedbackCheck) {
			bool justMoving = false, hasMoved = false;
			ros::Duration dur(config.doubles.at("GOTO_RETRY_DUR"));

			uint8_t count = 0;
			do {		
				count++;
				// It's okay lah ya, menamakan setpoint_position ini sebuah "service"
				if (count > config.ints.at("SERVICE_RETRY_N")) {
					ROS_FATAL_STREAM("Vehicle doesn't listen to our command!");
					return (int) Errors::UNRESPONSIVE_SERVICE;
				}

				// Publish ENU to mavros, it will send NED to autopilot
				int published = waitAndPublish(msg, "/mavros/setpoint_position/local", nh);
				if (published != 0) {
					ROS_FATAL_STREAM("Terminate in function " << __func__);
					return published;
				}

				geometry_msgs::PoseStamped poseMsg;
				int gotPose = getTopicValue(poseMsg, "/mavros/local_position/pose",
					config.doubles.at("WAIT_MSG_TO_LONG"));
				if (gotPose != 0) {
					ROS_FATAL_STREAM("Terminate in function " << __func__);
					return gotPose;
				}

				double nowDistance = sqrt(pow(poseMsg.pose.position.x - xDestCoord, 2)
					+ pow(poseMsg.pose.position.y - yDestCoord, 2)
					+ pow(poseMsg.pose.position.z - zDestCoord, 2));
				if (2 * nowDistance < distance) {
					hasMoved = true;
					ROS_INFO_STREAM("Vehicle has (almost) arrived.");
				}
				else {
					hasMoved = false;
					ROS_INFO_STREAM("Vehicle has not arrived");
				}

				if (!hasMoved) {
					dur.sleep();
					
					geometry_msgs::TwistStamped velMsg;
					int gotVel = getTopicValue(velMsg, "/mavros/local_position/velocity_local", 
						config.doubles.at("WAIT_MSG_TO_LONG"));
					if (gotVel != 0) {
						ROS_FATAL_STREAM("Terminate in function " << __func__);
						return gotVel;
					}

					double absVelLin, absVelAng;
					absVelLin = sqrt(pow(velMsg.twist.linear.x, 2) + pow(velMsg.twist.linear.y, 2) 
						+ pow(velMsg.twist.linear.z, 2));
					absVelAng = sqrt(pow(velMsg.twist.angular.x, 2) + pow(velMsg.twist.angular.y, 2)
						+ pow(velMsg.twist.angular.z, 2));
					if (absVelLin > config.doubles.at("MOVE_VEL_TOL")
						|| absVelAng > config.doubles.at("MOVE_VELANG_TOL")) {
							justMoving = true;
							ROS_INFO_STREAM("Vehicle is moving with vel " << absVelLin);
							ROS_INFO_STREAM("Vehicle is moving with vel ang " << absVelAng);
						}
					else {
						justMoving = false;
						ROS_INFO_STREAM("Vehicle is not moving yet. Vel = " << absVelLin);
						ROS_INFO_STREAM("Vehicle is not moving yet. Vel ang = " << absVelAng);
					}
				}

			} while (!justMoving && !hasMoved);

			bool reached;
			uav_msgs::MissionParams mp;
			mp.doubles.push_back(xDestCoord);
			mp.doubles.push_back(yDestCoord);
			mp.doubles.push_back(zDestCoord);
			return indoorWaitCoord(mp, nh, reached, precise);
		}			

		else {
			bool reached;
			uav_msgs::MissionParams mp;
			mp.doubles.push_back(xDestCoord);
			mp.doubles.push_back(yDestCoord);
			mp.doubles.push_back(zDestCoord);
			do {
				int published = waitAndPublish(msg, "/mavros/setpoint_position/local", nh);
				if (published != 0) {
					ROS_FATAL_STREAM("Terminate in function " << __func__);
					return published;
				}
				
				int success = indoorWaitCoord(mp, nh, reached, precise, config.doubles.at("GOTO_RETRY_SHORT"));
				if (success != 0) {
					ROS_FATAL_STREAM("Terminate in function " << __func__);
					return success;
				}
			} while (!reached);

		}

		return (int) Errors::NO_ERROR;
	}

	int positionGoTo(const std::vector<double> &coord, ros::NodeHandle &nh, bool precise) {
		uav_msgs::MissionParams mp;
		for (uint8_t i = 0, n = coord.size(); i < n; i++) {
			mp.doubles.push_back(coord.at(i));
		}
		return positionGoTo(mp, nh, precise);
	}

	int offsetGoTo(const std::vector<double> &coord, ros::NodeHandle &nh, bool precise)
	{
		// Legacy (use setpoint position)
		bool onlyXY = false, onlyZ = false, xyz = false;
		if (coord.size() == 3) xyz = true;
		else if (coord.size() == 2) onlyXY = true;
		else if (coord.size() == 1) onlyZ = true;
		else return (int) Errors::INVALID_ARGUMENT;

		geometry_msgs::PoseStamped pose;
		// Wanna add alternative source? Kapan-kapan deh
		int gotPose = getTopicValue(pose, "/mavros/local_position/pose", config.doubles.at("WAIT_MSG_TO_LONG"));
		if (gotPose != 0) {
			ROS_FATAL_STREAM("Terminate in function " << __func__);
			return gotPose;
		}

		uav_msgs::MissionParams mp;
		if (onlyXY) {
			mp.doubles.push_back(pose.pose.position.x + coord[0]);
			mp.doubles.push_back(pose.pose.position.y + coord[1]);
			ROS_INFO_STREAM("Will go to offset-xy: (" << coord[0] << ", " << coord[1] << ")");
		}
		else if (onlyZ) {
			mp.doubles.push_back(pose.pose.position.z + coord[0]);
			ROS_INFO_STREAM("Will go to offset-z: " << coord[0]);
		}
		else if (xyz) {
			mp.doubles.push_back(pose.pose.position.x + coord[0]);
			mp.doubles.push_back(pose.pose.position.y + coord[1]);
			mp.doubles.push_back(pose.pose.position.z + coord[2]);
			ROS_INFO_STREAM("Will go to offset-xyz: (" << coord[0] << ", " <<
				coord[1] << ", " << coord[2] << ")");
		}
		
		return positionGoTo(mp, nh, precise);
	}

	int velocityGoTo(const std::string &setpointTopic, const std::string &offsetTopic, 
		ros::NodeHandle &nh, bool shortRun, bool precise, double tolAdd = 0.0, bool fullRf = false)
	{
		double tolX, tolY, tolZ;
		if (precise) {
			tolX = config.doubles.at("PREC_X_TOL") + tolAdd;
			tolY = config.doubles.at("PREC_Y_TOL") + tolAdd;
			tolZ = config.doubles.at("PREC_Z_TOL") + tolAdd;
		}
		else {
			tolX = config.doubles.at("ROUGH_X_TOL") + tolAdd;
			tolY = config.doubles.at("ROUGH_Y_TOL") + tolAdd;
			tolZ = config.doubles.at("ROUGH_Z_TOL") + tolAdd;
		}
		double absTol = sqrt(pow(tolX, 2) + pow(tolY, 2) + pow(tolZ, 2));

		// Assume setpoint is streaming to topicName (Pose)
		double setpointX, setpointY, setpointZ;
		boost::function<void(const geometry_msgs::Pose &)> setpointCb = [&] (const geometry_msgs::Pose &msg) {
			setpointX = msg.position.x;
			setpointY = msg.position.y;
			setpointZ = msg.position.z;
		};
		ROS_WARN("setpointSub");
		ros::Subscriber setpointSub = nh.subscribe<geometry_msgs::Pose>(setpointTopic, 1, setpointCb);

		double absOffset;
		boost::function<void(const std_msgs::Float64 &)> offsetCb = [&] (const std_msgs::Float64 &msg) {
			absOffset = msg.data;
		};
		ros::Subscriber offsetSub = nh.subscribe<std_msgs::Float64>(offsetTopic, 1, offsetCb);

		// Should construct them somewhere else to optimize performance
		ros::Publisher stateXPub, stateYPub, stateZPub, setpointXPub, setpointYPub, setpointZPub;
		if (shortRun) {
			stateXPub = nh.advertise<std_msgs::Float64>("/pid/vel_x_short/state", 1, false);
			stateYPub = nh.advertise<std_msgs::Float64>("/pid/vel_y_short/state", 1, false);
			stateZPub = nh.advertise<std_msgs::Float64>("/pid/vel_z_short/state", 1, false);
			setpointXPub = nh.advertise<std_msgs::Float64>("/pid/vel_x_short/setpoint", 1, false);
			setpointYPub = nh.advertise<std_msgs::Float64>("/pid/vel_y_short/setpoint", 1, false);
			setpointZPub = nh.advertise<std_msgs::Float64>("/pid/vel_z_short/setpoint", 1, false);
		}
		else {
			stateXPub = nh.advertise<std_msgs::Float64>("/pid/vel_x_long/state", 1, false);
			stateYPub = nh.advertise<std_msgs::Float64>("/pid/vel_y_long/state", 1, false);
			stateZPub = nh.advertise<std_msgs::Float64>("/pid/vel_z_long/state", 1, false);
			setpointXPub = nh.advertise<std_msgs::Float64>("/pid/vel_x_long/setpoint", 1, false);
			setpointYPub = nh.advertise<std_msgs::Float64>("/pid/vel_y_long/setpoint", 1, false);
			setpointZPub = nh.advertise<std_msgs::Float64>("/pid/vel_z_long/setpoint", 1, false);

		}
		ROS_WARN("velocityPub");
		ros::Publisher velocityPub = nh.advertise<mavros_msgs::PositionTarget>(
			"/mavros/setpoint_raw/local", 1, false);

		double effortX, effortY, effortZ;
		boost::function<void(const std_msgs::Float64 &)> effortXCb = [&] (const std_msgs::Float64 &msg) {
			effortX = msg.data;
		};
		boost::function<void(const std_msgs::Float64 &)> effortYCb = [&] (const std_msgs::Float64 &msg) {
			effortY = msg.data;
		};
		boost::function<void(const std_msgs::Float64 &)> effortZCb = [&] (const std_msgs::Float64 &msg) {
			effortZ = msg.data;
		};
		ros::Subscriber effortXSub, effortYSub, effortZSub;
		if (shortRun) {
			effortXSub = nh.subscribe<std_msgs::Float64>(
				"/pid/vel_x_short/control_effort", 1, effortXCb);
			effortYSub = nh.subscribe<std_msgs::Float64>(
				"/pid/vel_y_short/control_effort", 1, effortYCb);
			effortZSub = nh.subscribe<std_msgs::Float64>(
				"/pid/vel_z_short/control_effort", 1, effortZCb);
		}
		else {
			effortXSub = nh.subscribe<std_msgs::Float64>(
				"/pid/vel_x_long/control_effort", 1, effortXCb);
			effortYSub = nh.subscribe<std_msgs::Float64>(
				"/pid/vel_y_long/control_effort", 1, effortYCb);
			effortZSub = nh.subscribe<std_msgs::Float64>(
				"/pid/vel_z_long/control_effort", 1, effortZCb);
		}

		geometry_msgs::PoseStamped currXY;  // for xy
		boost::function<void(const geometry_msgs::PoseStamped &)> stateXYCb =
			[&] (const geometry_msgs::PoseStamped &msg) {
			currXY = msg;
		};
		// for higher rate, use directly from realsense
		ROS_WARN("stateXYSub");
		ros::Subscriber stateXYSub = nh.subscribe<geometry_msgs::PoseStamped>(
			"/mavros/vision_pose/pose", 1, stateXYCb);

		bool zAneh = false;
		sensor_msgs::Range currAlt;  // for z
		boost::function<void(const sensor_msgs::Range &)> stateZCb =
			[&] (const sensor_msgs::Range &msg) {
			if (msg.range - currAlt.range > -1.0)
				currAlt.range = msg.range;
			else {
				zAneh = true;
				tolZ = 0.7;
				ROS_ERROR_STREAM("Z ANEH! Jump = " << currAlt.range - msg.range);
				ROS_ERROR("Now sending vel z = 0.0");
			}
		};

		ros::Subscriber stateZSub = nh.subscribe<sensor_msgs::Range>(
			config.strings.at("RF_BAWAH_SRC"), 1, stateZCb);
		sensor_msgs::Range currY;
		boost::function<void(const sensor_msgs::Range &)> stateYCb = 
			[&] (const sensor_msgs::Range &msg) {
			if (msg.range >= 0.3 && msg.range <= 12.0)
				currY.range = msg.range;
		};
		ros::Subscriber stateYSub = nh.subscribe<sensor_msgs::Range>(
			config.strings.at("RF_DEPAN_SRC"), 1, stateYCb);

		double maxY = config.doubles.at("ARENA_MAX_Y");
		double finalSetpointX, finalSetpointY, finalSetpointZ;
		// DONT CALL WITH TRUE IF FINALSETPOINTS HASN'T BEEN INITIALIZED
		boost::function<void(bool)> publishInputs = [&] (bool final) {
			ros::spinOnce();
			std_msgs::Float64 stateXMsg, stateYMsg, stateZMsg;
			stateXMsg.data = currXY.pose.position.x;
			if (!fullRf)
				stateYMsg.data = currXY.pose.position.y;
			else
				stateYMsg.data = maxY - currY.range;
			stateZMsg.data = currAlt.range;
			std_msgs::Float64 setpointXMsg, setpointYMsg, setpointZMsg;
			if (!final) {
				setpointXMsg.data = setpointX;
				setpointYMsg.data = setpointY;
				setpointZMsg.data = setpointZ;
			}
			else {
				setpointXMsg.data = finalSetpointX;
				setpointYMsg.data = finalSetpointY;
				setpointZMsg.data = finalSetpointZ;
			}

			stateXPub.publish(stateXMsg);
			stateYPub.publish(stateYMsg);
			stateZPub.publish(stateZMsg);
			setpointXPub.publish(setpointXMsg);
			setpointYPub.publish(setpointYMsg);
			setpointZPub.publish(setpointZMsg);
		};

		double maxVelX, maxVelY, maxVelZ;
		if (shortRun) {
			maxVelX = config.doubles.at("PID_MAX_VEL_X_SHORT");
			maxVelY = config.doubles.at("PID_MAX_VEL_Y_SHORT");
			maxVelZ = config.doubles.at("PID_MAX_VEL_Z_SHORT");
		}
		else {
			maxVelX = config.doubles.at("PID_MAX_VEL_X_LONG");
			maxVelY = config.doubles.at("PID_MAX_VEL_Y_LONG");
			maxVelZ = config.doubles.at("PID_MAX_VEL_Z_LONG");
		}
		// These configs is written from indoorInitialize, not config file
		double pidLimitX, pidLimitY, pidLimitZ;
		if (shortRun) {
			pidLimitX = config.doubles.at("PID_VEL_XS_LIM");
			pidLimitY = config.doubles.at("PID_VEL_YS_LIM");
			pidLimitZ = config.doubles.at("PID_VEL_ZS_LIM");
		}
		else {
			pidLimitX = config.doubles.at("PID_VEL_XL_LIM");
			pidLimitY = config.doubles.at("PID_VEL_YL_LIM");
			pidLimitZ = config.doubles.at("PID_VEL_ZL_LIM");
		}
		double distY;
		boost::function<void(const sensor_msgs::Range &)> distYCb= 
			[&] (const sensor_msgs::Range &msg) {
			distY = msg.range;
		};
		ros::Subscriber distYSub = nh.subscribe<sensor_msgs::Range>(
			config.strings.at("RF_DEPAN_SRC"), 1, distYCb);
		double distZAtas = 4.0;
		boost::function<void(const sensor_msgs::Range &)> distZAtasCb = 
			[&]	(const sensor_msgs::Range &msg) {
			if (msg.range > 0.3 && msg.range < 10.0)
				distZAtas = msg.range;
		};
		ROS_WARN("distZAtasSub");
		ros::Subscriber distZAtasSub = nh.subscribe<sensor_msgs::Range>(
			config.strings.at("RF_ATAS_SRC"), 1, distZAtasCb);
		boost::function<void(void)> publishOutputs = [&] () {
			ros::spinOnce();
			double finalVelX, finalVelY, finalVelZ;
			finalVelX = effortX / pidLimitX * maxVelX;
			finalVelY = effortY / pidLimitY * maxVelY;
			if (distY < 1.0 && finalVelY > 0.5) {
				ROS_ERROR_STREAM_THROTTLE(0.3, "Front lidar near obstacle!!!\nDistY is " << distY);
				finalVelY = 0.1;
			}
			if (distY < 0.7) {
				ROS_ERROR_STREAM_THROTTLE(0.3, "Front lidar near obstacle!!!\nDistY is " << distY);
				finalVelY = -0.8;
			}
			finalVelZ = effortZ / pidLimitZ * maxVelZ;
			mavros_msgs::PositionTarget velocityMsg;
			velocityMsg.type_mask = 2503;
			velocityMsg.coordinate_frame = 1;
			velocityMsg.velocity.x = finalVelX;
			velocityMsg.velocity.y = finalVelY;
			if (!zAneh)
				velocityMsg.velocity.z = finalVelZ;
			else
				velocityMsg.velocity.z = 0.0;
			if (distZAtas < 2.3 || currAlt.range > 3.5) {
				velocityMsg.velocity.z = -0.5;
			}
			velocityMsg.yaw = 1.5708;
			velocityPub.publish(velocityMsg);
			ROS_DEBUG_STREAM_THROTTLE(1, "sent vel = " << finalVelX << ", "
				<< finalVelY << ", " << finalVelZ << '\n');
		};

		ROS_WARN("togglePID");
		std_msgs::Bool togglePID; 
		ros::Publisher toggleXPub, toggleYPub, toggleZPub;
		if (shortRun) {
			toggleXPub = nh.advertise<std_msgs::Bool>("/pid/vel_x_short/pid_enable", 1, false);
			toggleYPub = nh.advertise<std_msgs::Bool>("/pid/vel_y_short/pid_enable", 1, false);
			toggleZPub = nh.advertise<std_msgs::Bool>("/pid/vel_z_short/pid_enable", 1, false);
		}
		else {
			toggleXPub = nh.advertise<std_msgs::Bool>("/pid/vel_x_long/pid_enable", 1, false);
			toggleYPub = nh.advertise<std_msgs::Bool>("/pid/vel_y_long/pid_enable", 1, false);
			toggleZPub = nh.advertise<std_msgs::Bool>("/pid/vel_z_long/pid_enable", 1, false);
		}
		boost::function<void(bool)> publishToggles = [&] (bool toggle) {
			togglePID.data = toggle;
			toggleXPub.publish(togglePID);
			toggleYPub.publish(togglePID);
			toggleZPub.publish(togglePID);
		};

		ROS_WARN("---PID in action---");

		std::string freqPrefix;
		if (shortRun)
			freqPrefix = "SHORT_";
		else
			freqPrefix = "LONG_";
		ros::Rate freq(config.ints.at(freqPrefix + "VEL_RATE"));
		double startTime = ros::Time::now().toSec();
		// give some time to start
		while (ros::Time::now().toSec() - startTime < 0.5) {
			publishToggles(true);
			publishInputs(false);
			freq.sleep();
		}

		while (absOffset > absTol || 
			(effortX / pidLimitX + effortY / pidLimitY + effortZ / pidLimitZ > 0.05)) {
			publishToggles(true);
			publishInputs(false);
			publishOutputs();
			freq.sleep();
			if (shortRun)
				ROS_DEBUG_STREAM_THROTTLE(0.5, "absOffset = " << absOffset << ", want " << absTol);
			else
				ROS_DEBUG_STREAM_THROTTLE(1.0, "absOffset = " << absOffset << ", want " << absTol);
		}

		if (precise) {
			ROS_INFO("Final positioning");
			finalSetpointX = setpointX;
			finalSetpointY = setpointY;
			finalSetpointZ = setpointZ;
			startTime = ros::Time::now().toSec();
			double prevTime = ros::Time::now().toSec();
			bool done = false;
			while (!done) {
				publishToggles(true);
				publishInputs(true);
				publishOutputs();
				freq.sleep();
				bool goodPosition;
				if (!fullRf)
					goodPosition = fabs(currXY.pose.position.x - finalSetpointX) < tolX &&
						fabs(currXY.pose.position.y - finalSetpointY) < tolY &&
						fabs(currAlt.range - finalSetpointZ) < tolZ;
				else
					goodPosition = fabs(currXY.pose.position.x - finalSetpointX) < tolX &&
						fabs(currY.range - finalSetpointY) < tolY &&
						fabs(currAlt.range - finalSetpointZ) < tolZ;
				if (goodPosition) {
					double nowTime = ros::Time::now().toSec();
					if (nowTime - prevTime > config.doubles.at("POSITIONING_WAIT"))
						done = true;
				}
				else {
					prevTime = ros::Time::now().toSec();
					ROS_DEBUG_STREAM_THROTTLE(0.3,
						"UAV has not consistently settled. Resettting time...");
				}
			}
		}

		startTime = ros::Time::now().toSec();
		while (ros::Time::now().toSec() - startTime < 1.0) {
			publishToggles(false);
			geometry_msgs::Twist velocityMsg;
			velocityMsg.linear.x = 0;
			velocityMsg.linear.y = 0;
			velocityMsg.linear.z = 0;
			velocityPub.publish(velocityMsg);
			freq.sleep();
		}

		ROS_WARN("---PID setpoint succeed---");

		return (int) Errors::NO_ERROR;
	}

	int testVelocityGoTo(const uav_msgs::MissionParams &m, ros::NodeHandle &nh) {
		return velocityGoTo("/test/setpoint", "/test/offset", nh, 
		m.bools.at(0), m.bools.at(1), 0.0, m.bools.at(2));
	}
}

#endif
