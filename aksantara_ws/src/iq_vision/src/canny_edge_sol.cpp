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
    image_pub_ = it_.advertise("/image_converter/output_video", 1);

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
    cv::Mat inputThresh, inputThresh1, inputThresh2, inputHsv;
    cv::cvtColor(inputImg, inputHsv, cv::COLOR_BGR2HSV);
    cv::inRange(inputHsv, cv::Scalar(0, 50, 50), cv::Scalar(15, 255, 255), inputThresh1);
    cv::inRange(inputHsv, cv::Scalar(165, 50, 50), cv::Scalar(180, 255, 255), inputThresh2);
    inputThresh = inputThresh1 + inputThresh2;

    std::vector<std::vector<cv::Point>> contours;
  	findContours(inputThresh, contours, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);
	  // contours = detectContourOut(inputImg);
  
	  // for testing 
	  // contours = detectTerang(inputImg);


	  int largestIndex = -1;
	  double largestArea = 0;
	  for (size_t i=0; i<contours.size(); i++)
	  {
      cv::drawContours(inputImg, contours, i, cv::Scalar(0,255,255));
	  	double area = cv::contourArea(contours[i]);
	  	if (area > largestArea)
	  	{
	  		largestArea = area;
	  		largestIndex = i;
	  	}
	  }
	  if (largestArea > minimumArea) { 

	  	cv::Moments M = cv::moments(contours[largestIndex], true);
	  	cv::Point centroid = cv::Point(int(M.m10/M.m00), int(M.m01/M.m00));
  
	  	cv::circle(inputImg, centroid, 4, cv::Scalar(0,255,0), cv::FILLED);
	  	cv::drawContours(inputImg, contours, largestIndex, cv::Scalar(255,0,200));

	  	int imgArea = inputImg.rows * inputImg.cols;
	  	double percent_red = (largestArea * 100) / imgArea;

	  	std::vector<cv::Point> contour_poly;
	  	cv::Point2f center;
	  	float radius;
	  	cv::approxPolyDP(contours[largestIndex], contour_poly, 3, true);
	  	cv::minEnclosingCircle(contour_poly, center, radius);

	  	double halfSide = radius * 0.707107;

	  	centroid.y = centroid.y - (2 * halfSide * 0.2);

	    double size_x = abs( atan((double)((centroid.x - halfSide)- cam_center.x)/(cam_x_size/2) * tan(HFOV/2)) - atan((double)((centroid.x + halfSide) - cam_center.x)/(cam_x_size/2) * tan(HFOV/2)));
	    double size_y = abs( atan((double)((centroid.y + halfSide) - cam_center.y)/(cam_y_size/2) * tan(VFOV/2)) - atan((double)(cam_center.y - (centroid.y - halfSide))/(cam_y_size/2) * tan(VFOV/2)));
	    double angle_x = atan((double)(centroid.x - cam_center.x)/(cam_x_size/2) * tan(HFOV/2));
	    double angle_y = atan((double)(centroid.y - cam_center.y)/(cam_y_size/2) * tan(VFOV/2));
	    //double distance = alt * sqrt(1 + tan(precLandMsg.angle_x) * tan(precLandMsg.angle_x) + tan(precLandMsg.angle_y) * tan(precLandMsg.angle_y));



	  	std::string text = "Angle x: " + std::to_string(angle_x) + " Angle y: " + std::to_string(angle_y);
	  	cv::putText(inputImg, text, cv::Point(25,35), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.0, cv::Scalar(255,255,255), 1, cv:: LINE_AA);
	  	cv::putText(inputImg, std::to_string(largestArea), cv::Point(25,inputImg.size().height - 50), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.0, cv::Scalar(255,255,255), 1, cv:: LINE_AA);
  
	  }

	  else {
	  	cv::putText(inputImg, "Not detected", cv::Point(25,35), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.0, cv::Scalar(255,255,255), 1, cv:: LINE_AA); 
	  	ROS_DEBUG_STREAM_THROTTLE(5, "ELP scanned area = " << largestArea << ". It's < " << minimumArea);
	  }

    sensor_msgs::ImagePtr msg_out = cv_bridge::CvImage(std_msgs::Header(), "bgr8", inputImg).toImageMsg();
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
