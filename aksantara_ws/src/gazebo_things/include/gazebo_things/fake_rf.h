#include <ros/ros.h>
#include <sensor_msgs/Range.h>
#include <geometry_msgs/Pose.h>
#include <vector>

class rangefinder {
    public:
        rangefinder(ros::NodeHandle* nh);
        void publishOnce();
    private:
        ros::NodeHandle nh_;
        ros::Subscriber sub_;
        void callback(const geometry_msgs::Pose &);
        std::vector<double> real_pose_;
        bool rf_depan_, rf_bawah_, test_rf_, rf_atas_;
        ros::Publisher rf_depan_pub_, rf_bawah_pub_, test_pub_, atas_pub_;
        double tembok_y_;
        std::string depan_topic_, bawah_topic_, test_topic_, atas_topic_;
};