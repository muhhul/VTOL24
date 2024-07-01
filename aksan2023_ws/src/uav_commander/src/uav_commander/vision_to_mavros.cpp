#include <ros/ros.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf2_ros/transform_listener.h>
#include <tf2/LinearMath/Quaternion.h>    // for tf2::Quaternion
#include <tf2/LinearMath/Transform.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>    // for tf2::fromMsg
#include <tf2/buffer_core.h>
#include <string>

double gammaWorld = -1.5707963;
double outputRate = 30;

int main(int argc, char **argv) {
    ros::init(argc, argv, "vision_to_mavros");
    ros::NodeHandle nh;

    tf2_ros::Buffer tfBuffer;
    tf2_ros::TransformListener tfListener(tfBuffer);

    ros::Publisher pub = nh.advertise<geometry_msgs::PoseStamped>("/mavros/vision_pose/pose", 10);
    geometry_msgs::PoseStamped pubMsg;

    ros::Rate rate(outputRate);
    ros::Time lastTime = ros::Time::now();
    geometry_msgs::TransformStamped tfToOdomStamped, tfToMapStamped, transformStamped;
    tf2::Vector3 posOrigin;
    tf2::Quaternion quatCam, quatBody;
    tf2::Stamped<tf2::Transform> transformST;
    // tf2::Transform tfToOdom, tfToMap, transform;

    tfToMapStamped = tfBuffer.lookupTransform(
        "map", "realsense_odom_frame", ros::Time(0), ros::Duration(60));
    tf2::BufferCore bufCore;
    bufCore.setTransform(tfToMapStamped, "default_authority", true);
    bufCore.setTransform(tfToOdomStamped, "default_authority", false);

    while (ros::ok()) {
        try {
            tfToOdomStamped = tfBuffer.lookupTransform(
                "realsense_odom_frame", "realsense_link", ros::Time(0));
            bufCore.setTransform(tfToOdomStamped, "default_authority", false);
            // bool bisa = bufCore.canTransform("map", "realsense_link", ros::Time(0));
            // if (bisa) ROS_DEBUG("OKE");
            // else ROS_DEBUG("GA");
            transformStamped = bufCore.lookupTransform(
                "map", "realsense_link", ros::Time(0));
            tf2::fromMsg(transformStamped, transformST);
        }
        catch (tf2::TransformException &e) {
            ROS_WARN_STREAM_THROTTLE(1, e.what());
            continue;
        }
        // ROS_DEBUG_STREAM(tfToOdomStamped.transform.translation.x << ", " <<
        //     tfToOdomStamped.transform.translation.y << ", " << 
        //     tfToOdomStamped.transform.translation.z);


        if (lastTime < tfToOdomStamped.header.stamp) {
            lastTime = tfToOdomStamped.header.stamp;
            pubMsg.header.stamp = tfToOdomStamped.header.stamp;
            pubMsg.header.frame_id = "vision_pose";

            posOrigin = transformST.getOrigin();
            quatCam = transformST.getRotation();

            pubMsg.pose.position.x = cos(gammaWorld) * posOrigin.getX() + 
                sin(gammaWorld) * posOrigin.getY();
            pubMsg.pose.position.y = -sin(gammaWorld) * posOrigin.getX() + 
                cos(gammaWorld) * posOrigin.getY();
            pubMsg.pose.position.z = posOrigin.getZ();

            quatBody.setRPY(0, 0, -gammaWorld);
            quatBody = quatBody * quatCam;
            pubMsg.pose.orientation.x = quatBody.getX();
            pubMsg.pose.orientation.y = quatBody.getY();
            pubMsg.pose.orientation.z = quatBody.getZ();
            pubMsg.pose.orientation.w = quatBody.getW();

            pub.publish(pubMsg);
        }

        rate.sleep();
    }
}