#ifndef PILOT_SAFETY_
#define PILOT_SAFETY_

// Never include uav_commander/uav_missions.hpp!
#include <ros/ros.h>
#include <uav_teleop/Key.h>
#include <uav_msgs/PilotOverride.h>
#include <boost/shared_ptr.hpp>
#include <cctype>       // maybe safer than boost::algorithm::to_lower
#include <string>
#include <vector>       // maybe udah ter-include oleh yang lain tapi yaudah
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <sensor_msgs/Range.h>
#include <mavros_msgs/RCIn.h>
#include <geometry_msgs/PoseStamped.h>
#include <std_srvs/Empty.h>
#include <std_msgs/Bool.h>
#include <stdexcept>
#include <uav_msgs/SetCurrent.h>
#include <std_msgs/Int32.h>
#include <std_srvs/SetBool.h>
#include <mavros_msgs/PositionTarget.h>

#define FS_ALT_CHECK    1
#define RC_CHECK        1

// 1 for local_position, 2 for rangefinder
#define FS_ALT_SOURCE   2

const double KEY_HOLD_DUR           {0.5};
const double LANDSERV_RETRY_DUR     {0.5};
const uint8_t LANDSERV_RETRY_N      {10};
const double LANDSERV_PANIC_RATE    {3};
const double WAIT_MSG_TIMEOUT       {1.0};
const double CHGMODE_RETRY_DUR      {1.0};
const double CHGMODE_RETRY_N        {3};    // before escalating to failsafe
const double FS_MAX_ALT             {3.6};
const double FS_DONE_ALT            {3.0};
const int RC_N_LAND                 {7};
const std::string RC_LAND_PWM       {"HIGH"};
const int RC_N_STAB                 {5};
const std::string RC_STAB_PWM       {"LOW"};

enum safetyErrors {
    OKAY,
    SERVICE_ERROR,
    LOST_MESSAGE,
    NO_PILOT
};

struct keyPress {
    bool isPressed = false;    // Only one key allowed to be pressed at a time
    uint16_t keyDown;
    double keyDown_when;
};

keyPress globKeyPress;

ros::NodeHandle *nh;
bool panic_land = false;

std::string toUpcase(const std::string &str);
void spamLand();
uint8_t landSrv();
uint8_t changeMode(const std::string &mode);
bool pilotOverride(uav_msgs::PilotOverride::Request &req, uav_msgs::PilotOverride::Response &res);
void keyDownCb(const uav_teleop::Key &msg);
void keyUpCb(const uav_teleop::Key &msg);
bool fsTrigger();
bool rcPWM(int val, std::string &want);
int rcTrigger();
bool checkPilot();
bool mundurCb(std_srvs::SetBool::Request &req, std_srvs::SetBool::Response &res);
void mundurTimerCb(const ros::TimerEvent &ev);
bool spamLandCb(std_srvs::Empty::Request &req, std_srvs::Empty::Response &res);

#endif
