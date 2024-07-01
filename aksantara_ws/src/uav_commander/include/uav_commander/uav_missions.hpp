#ifndef UAV_MISSIONS_
#define UAV_MISSIONS_

#include <uav_commander/uav_missions_config.hpp>
#include <uav_commander/uav_missions_utils.cpp>	// due to templating issue
#include <uav_msgs/PrecLand.h>
#include <uav_msgs/DzPosition.h>
#include <uav_msgs/DetectObject.h>
#include <uav_msgs/DetectQR.h>
#include <uav_teleop/Key.h>

#include <uav_msgs/PrecLoit.h>

#include <ros/ros.h>
#include <boost/algorithm/string.hpp>			// string converting
#include <mavros_msgs/SetMode.h>
#include <geographic_msgs/GeoPointStamped.h>	// for injecting EKF origin
#include <mavros_msgs/State.h>					// for /mavros/state
#include <mavros_msgs/CommandBool.h>			// for /mavros/cmd/arming
#include <mavros_msgs/CommandTOL.h>				// for takeoff
#include <mavros_msgs/CommandLong.h>			// for dropping paylaod
#include <mavros_msgs/LandingTarget.h>
#include <mavros_msgs/AttitudeTarget.h>
#include <mavros_msgs/OverrideRCIn.h>
#include <mavros_msgs/RCIn.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int16.h>
#include <std_msgs/String.h>
#include <functional>
#include <map>

namespace uav_commander
{
	int armThrottle         (const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
	int disarmThrottle		(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
	int takeoff				(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
	int land				(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
	int switchMode          (const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
	int failsafeLand		(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
	int wait				(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);

    #if DEBUG_FUNCS
	int testWASD			(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
    #endif

    #if VTOL21_FUNCS
	int indoorPreinitialize	(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
	int indoorInitialize	(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
	int indoorGoTo			(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
	int dropPayload			(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
	int goToELP				(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
	int precLand			(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
	int goToDZ				(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
	int setpointTakeoff		(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
	int loiterDZ			(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
	#endif
}

#endif
