#include <map>
#include <string>
#include <list>
#include <functional>
#include <ros/ros.h>
#include <boost/shared_ptr.hpp>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <geometry_msgs/PoseStamped.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Bool.h>
#include <geometry_msgs/Point.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/aruco.hpp>
#include <uav_msgs/DetectQR.h>
#include <uav_msgs/DetectObject.h>
#include <uav_msgs/PrecLand.h>
#include <uav_msgs/DzPosition.h>
#include <zbar.h>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iomanip>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/core/types.hpp>
#include <sensor_msgs/Range.h>
//#include "env_percept/ImageProcessor_config.hpp"
#include <uav_msgs/PrecLoit.h>
#include <geometry_msgs/TwistStamped.h>

#define DEBUG_FUNCS     1

namespace env_percept{

struct ColorRanges{
	int lowVal;
	int highVal;
};

class ImageProcessor
{
	ros::NodeHandle nh_;
	image_transport::ImageTransport it_;

	image_transport::Subscriber front_image_sub_;
    image_transport::Subscriber down_image_sub_;
	image_transport::Publisher front_image_pub_;
    image_transport::Publisher down_image_pub_;
	ros::Subscriber local_position_sub;
	ros::Subscriber rf_sub;
	ros::Publisher precland_pub_;
	image_transport::Publisher precland_display_;
	ros::Publisher qr_pub_;
	ros::ServiceServer detectQRServer;
	ros::ServiceServer detectObjectServer;
	ros::Publisher detectDz_pub_;
	ros::Publisher qrPos_pub_;
	ros::Publisher distX_pub_;
  ros::Publisher vel_pub;
  image_transport::Publisher detectGate_pub_;

	static const std::map<std::string,ColorRanges> calibratedColors;

	const int minimumArea = 50;
	const int cam_x_size = 640;
	const int cam_y_size = 480;
	const cv::Point cam_center = cv::Point(0.5*cam_x_size, 0.5*cam_y_size);
	const double DFOV = 1.891325149 ;     // 120 deg
	const double HFOV = 2 * atan(tan(DFOV/2)*cos(atan((double)cam_y_size/cam_x_size)));
	const double VFOV = 2 * atan(tan(DFOV/2)*sin(atan((double)cam_y_size/cam_x_size)));
	//Reference: http://www.therandomlab.com/2013/03/logitech-c920-and-c910-fields-of-view.html

	cv::Mat frontHandledImage;
	cv::Mat downHandledImage;

	bool toggleQR = false;
	bool toggleELP = false;
	bool toggleDZ = false;
	bool togglePilot = false;
	bool toggleDistX = false;
  bool toggleGate = false;

	double pose_x;
	double pose_y;
	double pose_z;
	double rf_alt;

	void frontImageCb(const sensor_msgs::ImageConstPtr& msg);
	void downImageCb(const sensor_msgs::ImageConstPtr& msg);
	void localPosCb(const geometry_msgs::PoseStamped& msg);
	// void rfCb(const sensor_msgs::Range& msg);
	void rfCb(const sensor_msgs::Range& msg);


  cv::Mat img, img_resized, blurred, morphed, img_hsv, img_thresholded_l, img_thresholded_r, mask;
  const int lower_h_l = 0, lower_s_l = 203, lower_v_l = 0;
  const int upper_h_l = 35, upper_s_l = 255, upper_v_l = 255;
  const int lower_h_r = 126, lower_s_r = 40, lower_v_r = 97;
  const int upper_h_r = 179, upper_s_r = 255, upper_v_r = 255;
  const int minArea = 3713; // Filter shapes with small area
  std::vector<std::vector<cv::Point>> contours;
  std::vector<cv::Vec4i> hierarchy;
  const int crosshair_radius = 15;
  const int lateral_alignment_slope_tolerance = 0.02;

	public:
	ImageProcessor();
	~ImageProcessor();
	void publishAll();

	typedef struct
	{
		std::string data;
		std::vector <cv::Point> location;
	}decodedObject;

	std::vector<decodedObject> decodedObjects;
	void decode(cv::Mat &im, std::vector<decodedObject> &decodedObjects);
	#if DEBUG_FUNCS
	void display(cv::Mat &im, std::vector<decodedObject> &decodedObjects);
	#endif

	bool scanQR(uav_msgs::DetectQR::Request &req, uav_msgs::DetectQR::Response &res);
	bool scanObject(uav_msgs::DetectObject::Request &req, uav_msgs::DetectObject::Response &res);

	void scanDZ(cv::Mat& inputImg);
	void scanELP(cv::Mat& inputImg);
  void scanGate(cv::Mat& inputImg);

	std::vector<std::vector<cv::Point>> detectContourELP(cv::Mat inputImg, std::string color);
	std::vector<std::vector<cv::Point>> detectContourDistX(cv::Mat inputImg, std::string color);

	void getQrPos(cv::Mat& inputImg);
	cv::Mat saturate(cv::Mat src);

	void getDistX(cv::Mat& inputImg);
	
	bool isGreen(const cv::Mat image, cv::Rect roi);
	std::vector<cv::Rect> surroundingArea(cv::Mat image, cv::Rect rect);
  
  // VTOL 24 OpenCV 
  void on_trackbar(int, void*);
  double find_slope(int x0, int y0, int x1, int y1);
  void fullLine(cv::Mat img, cv::Point a, cv::Point b, cv::Scalar color);
  int min_point_y_idx(std::vector<cv::Point> points);
  cv::Point find_rect_centroid(cv::Mat img, std::vector<cv::Point> largestRectangle);
  bool gate_align_yaw(cv::Mat img, cv::Point rectCentroid, geometry_msgs::TwistStamped& cmd_vel);
  bool gate_align_normal(cv::Mat img, cv::Point rectCentroid, geometry_msgs::TwistStamped& cmd_vel);
  bool gate_align_lateral(cv::Mat img, std::vector<cv::Point> rectangle, geometry_msgs::TwistStamped& cmd_vel);
  void draw_gridlines(cv::Mat img);

};

}
