#include <uav_commander/uav_missions.hpp>
#include <uav_msgs/PilotOverride.h>

#include <queue>
#include <functional>
#include <map>
#include <fstream>
#include <vector>
#include <std_msgs/Int32.h>

namespace uav_commander{

class pilot
{
  ros::NodeHandle nh_;
  uav_msgs::MissionParams m;
  std::queue<std::function <int(void)>> missionList;
  std::map<std::string, std::function <int(const uav_msgs::MissionParams&, ros::NodeHandle&)>> uav_funcs;

public:
  pilot(ros::NodeHandle*);
  void clearParams();
  bool load(std::string pilot_fname, std::string config_fname);
  bool to_smint(std::string &x, uint8_t &n);
  void executeMissions(int startFrom);
  
};

}
