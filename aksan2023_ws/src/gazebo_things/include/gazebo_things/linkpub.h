#ifndef GAZEBO_SENSORS_H_
#define GAZEBO_SENSORS_H_

#include <string>
#include <vector>

#include <ros/ros.h>
#include <gazebo_msgs/LinkStates.h>
#include <geometry_msgs/Pose.h>
#include <boost/shared_ptr.hpp>
#include <tf/transform_broadcaster.h>
#include <stdexcept>
#include <cstdlib>

class t265 {
    public:
        t265(ros::NodeHandle* nh);
        void publishOnce();
    private:
        ros::NodeHandle nh_;
        ros::Subscriber sub_;
        std::string link_name_, frame_name_;

        gazebo_msgs::LinkStates link_states_;
        tf::TransformBroadcaster br_;
        tf::Transform tf_;
        void cb(const gazebo_msgs::LinkStates &link_states);
        
        geometry_msgs::Pose t265_pose_;
        ros::Publisher real_pub_;
};

#endif