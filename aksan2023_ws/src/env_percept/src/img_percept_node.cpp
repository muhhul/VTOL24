#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <env_percept/ImageProcessor.hpp>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "img_percept_node");
  ros::NodeHandle globalNh();
  env_percept::ImageProcessor imageProcessor;
  ros::Rate rate(25); // SESUAIKAN DENGAN FREKUENSI PUBLISHER IMAGE_PROC 
  
  while (ros::ok()) {
    imageProcessor.publishAll();
    rate.sleep();
    ros::spinOnce();
  }

  return 0;
}