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
        void sendBroadcast();
    private:
        ros::NodeHandle nh_;
        ros::Subscriber sub_;
        std::string link_name_, frame_name_;
        bool noise_;
        double noise_max_, scale_max_, noise_z_max_, scale_z_max_;
        double noise_x_ = 0.0, noise_y_ = 0.0, noise_z_ = 0.0;
        double scale_x_ = 1.0, scale_y_ = 1.0, scale_z_ = 0.0;

        gazebo_msgs::LinkStates link_states_;
        tf::TransformBroadcaster br_;
        tf::Transform tf_;
        void cb(const gazebo_msgs::LinkStates &link_states);
        
        geometry_msgs::Pose t265_pose_;
        ros::Publisher real_pub_;
};

#endif