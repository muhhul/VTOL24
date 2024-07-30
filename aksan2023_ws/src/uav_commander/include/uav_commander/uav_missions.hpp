#ifndef UAV_MISSIONS_
#define UAV_MISSIONS_

#include <uav_commander/uav_missions_config.hpp>
#include <uav_commander/uav_missions_utils.cpp>	// due to templating issue
#include <uav_msgs/PrecLand.h>
#include <uav_msgs/DzPosition.h>
#include <uav_msgs/DetectObject.h>
#include <uav_msgs/DetectQR.h>
#include <uav_teleop/Key.h>
#include <mavros_msgs/Mavlink.h>

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
#include <mavros_msgs/GlobalPositionTarget.h>
#include <std_msgs/Float64.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>
#include <functional>
#include <map>
#include <sensor_msgs/NavSatFix.h>
#include <iostream>
#include <cmath>
#include <iomanip>

namespace uav_commander
{
	int armThrottle         (const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
	int disarmThrottle		(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
	int takeoff				(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
	int land				(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
	int land2				(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
	int switchMode          (const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
	int failsafeLand		(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
	int wait				(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
    	int stop				(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);

	double GPSOriginHeading = 0.0;
	double GPSOriginLat = 0.0;
	double GPSOriginLon = 0.0;

  bool gate_centered = false;
  bool gate_exist = false;

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
	int velocity			(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
	int chargeOpengrab		(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
	int dischargeOpengrab	(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
	int setPointPosition	(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
    	int movingCV			(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
    	int setPointLidar		(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
    	int setPointGlobal		(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
	int calculateNewPosition		(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
	int heading		(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
	int movingPL		(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);	
	int middle		(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
	int loiterLand		(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
	int PDM		(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);	    		    
	int neutralOpengrab		(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);	    		    	
	#endif

  int scanGate(const uav_msgs::MissionParams &m, ros::NodeHandle &nh);
  void gateCallback(const std_msgs::Bool::ConstPtr& msg);
  void gateExistCallback(const std_msgs::Bool::ConstPtr& msg);
}

#endif
