#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#ifdef ROS_NOETIC
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#else 
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#endif

const int minimumArea = 200;
const int cam_x_size = 640;
const int cam_y_size = 480;
const cv::Point cam_center = cv::Point(0.5*cam_x_size, 0.5*cam_y_size);
const double DFOV = 1.3089 ;     // 75 deg
const double HFOV = 2 * atan(tan(DFOV/2)*cos(atan((double)cam_y_size/cam_x_size)));
const double VFOV = 2 * atan(tan(DFOV/2)*sin(atan((double)cam_y_size/cam_x_size)));


class ImageConverter
{
  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;
  image_transport::Publisher image_pub_;

public:
  ImageConverter()
    : it_(nh_)
  {
    // Subscrive to input video feed and publish output video feed
    image_sub_ = it_.subscribe("/down_cam/image_rect_color", 1,
      &ImageConverter::imageCb, this);
    image_pub_ = it_.advertise("/image_converter/output_video_tres", 1);

  }

  ~ImageConverter()
  {}

  void imageCb(const sensor_msgs::ImageConstPtr& msg)
  {
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }

    // Run Canny edge detector on image
    cv::Mat inputImg = cv_ptr->image;
    cv::Mat inputHsv, inputBnw, inputThresh, inputThresh1, inputThresh2;
    cv::cvtColor(inputImg, inputHsv, cv::COLOR_BGR2HSV);
    cv::inRange(inputHsv, cv::Scalar(0, 50, 50), cv::Scalar(15, 255, 255), inputThresh1);
    cv::inRange(inputHsv, cv::Scalar(165, 50, 50), cv::Scalar(180, 255, 255), inputThresh2);
    inputThresh = inputThresh1 + inputThresh2;
    

    sensor_msgs::ImagePtr msg_out = cv_bridge::CvImage(std_msgs::Header(), "mono8", inputThresh).toImageMsg();
    // Output modified video stream
    image_pub_.publish(msg_out);
  }
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_converter");
  ImageConverter ic;
  ros::spin();
  return 0;
}
