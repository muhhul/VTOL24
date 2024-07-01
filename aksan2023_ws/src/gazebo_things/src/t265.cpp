#include <gazebo_things/t265.h>

t265::t265(ros::NodeHandle* nh): nh_(*nh) {
        nh_.getParam("link_name", link_name_);
        nh_.getParam("frame_name", frame_name_);
        nh_.getParam("noise", noise_);
        nh_.getParam("noise_max", noise_max_);
        nh_.getParam("scale_max", scale_max_);
        nh_.getParam("noise_z_max", noise_z_max_);
        nh_.getParam("scale_z_max", scale_z_max_);

        sub_ = nh_.subscribe("/gazebo/link_states", 1, &t265::cb, this);
        real_pub_ = nh_.advertise<geometry_msgs::Pose>("/gazebo_things/real_pose", 1, true);

        boost::shared_ptr<const gazebo_msgs::LinkStates> link_states_ptr;
        link_states_ptr = ros::topic::waitForMessage<gazebo_msgs::LinkStates>("/gazebo/link_states");
        link_states_ = *link_states_ptr;
        
        if (noise_) {
            noise_x_ = (rand() % (int) (noise_max_*2000) - (noise_max_*1000)) * 0.001;
            noise_y_ = (rand() % (int) (noise_max_*2000) - (noise_max_*1000)) * 0.001;
            noise_z_ = (rand() % (int) (noise_z_max_*2000) - (noise_z_max_*1000)) * 0.001;
            scale_x_ = 1 - (rand() % (int) (scale_max_*1000)) * 0.001;
            scale_y_ = 1 - (rand() % (int) (scale_max_*1000)) * 0.001;
            scale_z_ = 1 - (rand() % (int) (scale_z_max_*1000)) * 0.001;
        }
    }

void t265::cb(const gazebo_msgs::LinkStates &link_states) {
    link_states_ = link_states;
    int idx = 0;
    bool found = false;
    while (!found) {
        if (link_states_.name.at(idx) == link_name_) {
            found = true;
            break;
        }
        idx++;
    }    
    t265_pose_ = link_states_.pose.at(idx);
}

void t265::publishOnce() {
    real_pub_.publish(t265_pose_);
}

void t265::sendBroadcast() {
    tf_.setOrigin(tf::Vector3(t265_pose_.position.x * scale_x_ + noise_x_,
        t265_pose_.position.y * scale_y_ + noise_y_,
        t265_pose_.position.z * scale_z_ + noise_z_));
    tf_.setRotation(tf::Quaternion(t265_pose_.orientation.x, t265_pose_.orientation.y,
        t265_pose_.orientation.z, t265_pose_.orientation.w));
    br_.sendTransform(tf::StampedTransform(tf_, ros::Time::now(), "map", frame_name_));
}
