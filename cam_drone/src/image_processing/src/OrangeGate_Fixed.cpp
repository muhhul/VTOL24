#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <geometry_msgs/TwistStamped.h>

static const std::string OPENCV_WINDOW = "Image window";

cv::Mat img, img_resized, blurred, morphed, img_hsv, img_thresholded_l, img_thresholded_r, mask;
int lower_h_l = 0, lower_s_l = 203, lower_v_l = 0;
int upper_h_l = 35, upper_s_l = 255, upper_v_l = 255;
int lower_h_r = 126, lower_s_r = 40, lower_v_r = 97;
int upper_h_r = 179, upper_s_r = 255, upper_v_r = 255;
int minArea = 3713; // Filter shapes with small area
std::vector<std::vector<cv::Point>> contours;
std::vector<cv::Vec4i> hierarchy;
const int crosshair_radius = 15;
const int lateral_alignment_slope_tolerance = 0.02;

class ImageConverter
{
  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;
  image_transport::Publisher image_pub_;
  ros::NodeHandle vel_node; 
  ros::Publisher vel_pub;
  geometry_msgs::TwistStamped vel_msg;

public:
  ImageConverter()
    : it_(nh_)
  { 
    vel_pub= vel_node.advertise<geometry_msgs::TwistStamped>("/mavros/setpoint_velocity/cmd_vel", 10);
    // Subscrive to input video feed and publish output video feed
    image_sub_ = it_.subscribe("/webcam/image_raw", 1,
      &ImageConverter::imageCb, this);
    image_pub_ = it_.advertise("/image_converter/output_video", 1);
        
    // Create a window to display the trackbars
    cv::namedWindow("Trackbars", cv::WINDOW_AUTOSIZE);
    cv::createTrackbar("Lower H Left", "Trackbars", &lower_h_l, 179, on_trackbar);
    cv::createTrackbar("Lower S Left", "Trackbars", &lower_s_l, 255, on_trackbar);
    cv::createTrackbar("Lower V Left", "Trackbars", &lower_v_l, 255, on_trackbar);
    cv::createTrackbar("Upper H Left", "Trackbars", &upper_h_l, 179, on_trackbar);
    cv::createTrackbar("Upper S Left", "Trackbars", &upper_s_l, 255, on_trackbar);
    cv::createTrackbar("Upper V Left", "Trackbars", &upper_v_l, 255, on_trackbar);
    cv::createTrackbar("Lower H Right", "Trackbars", &lower_h_r, 179, on_trackbar);
    cv::createTrackbar("Lower S Right", "Trackbars", &lower_s_r, 255, on_trackbar);
    cv::createTrackbar("Lower V Right", "Trackbars", &lower_v_r, 255, on_trackbar);
    cv::createTrackbar("Upper H Right", "Trackbars", &upper_h_r, 179, on_trackbar);
    cv::createTrackbar("Upper S Right", "Trackbars", &upper_s_r, 255, on_trackbar);
    cv::createTrackbar("Upper V Right", "Trackbars", &upper_v_r, 255, on_trackbar);
    cv::createTrackbar("Min Area", "Trackbars", &minArea, 30000);

    // Initial call to display the image
    on_trackbar(0, 0);

    //cv::namedWindow(OPENCV_WINDOW);

    // Initial Velocity
    vel_msg.header.stamp = ros::Time::now();
    vel_msg.twist.linear.x = 0.0;
    vel_msg.twist.linear.y = 0.0;
    vel_msg.twist.linear.z = 0.0;
    vel_msg.twist.angular.x = 0.0;
    vel_msg.twist.angular.y = 0.0;
    vel_msg.twist.angular.z = 0.0;

  }

  ~ImageConverter()
  {
    cv::destroyWindow(OPENCV_WINDOW);
  }

  // OpenCV Function 
  
  static void on_trackbar(int, void*) {
      if (img_hsv.empty()) return; // Check if img_hsv is empty
      cv::inRange(img_hsv, cv::Scalar(lower_h_l, lower_s_l, lower_v_l), cv::Scalar(upper_h_l, upper_s_l, upper_v_l), img_thresholded_l);
      cv::inRange(img_hsv, cv::Scalar(lower_h_r, lower_s_r, lower_v_r), cv::Scalar(upper_h_r, upper_s_r, upper_v_l), img_thresholded_r);
      mask = img_thresholded_l | img_thresholded_r;
      cv::imshow("Thresholded Image", mask);
  }
  
  double find_slope(int x0, int y0, int x1, int y1){
       return (double) (y1-y0)/(x1-x0);
  }
  
  void fullLine(cv::Mat img, cv::Point a, cv::Point b, cv::Scalar color){
       double slope = find_slope(a.x, a.y, b.x, b.y);
  
       cv::Point p(0,0), q(img.cols,img.rows);
  
       p.y = -(a.x - p.x) * slope + a.y;
       q.y = -(b.x - q.x) * slope + b.y;
  
       line(img,p,q,color,1,8,0);
  }


  int min_point_y_idx(std::vector<cv::Point> points)
  {
      int min_y_idx = 0;
      if (points.size() > 1)
      {
          for (int i = 1; i < points.size(); i++)
              if (points[i].y < points[min_y_idx].y) min_y_idx = i;
      }
      return min_y_idx;
  }
  
  cv::Point find_rect_centroid(cv::Mat img, std::vector<cv::Point> largestRectangle)
  {
      // Draw the diagonal lines
      cv::line(img, largestRectangle[0], largestRectangle[2], cv::Scalar(255, 0, 0), 2);
      cv::line(img, largestRectangle[1], largestRectangle[3], cv::Scalar(255, 0, 0), 2);
  
      // Calculate and return the center point
      cv::Point rectCentroid((largestRectangle[0].x + largestRectangle[2].x) / 2, (largestRectangle[0].y + largestRectangle[2].y) / 2);
  
      // Draw the center point
      cv::circle(img, rectCentroid, 5, cv::Scalar(0, 0, 255), -1);
      std::cout << "Rectangle center: " << rectCentroid << std::endl;
  
      return rectCentroid;
  }
  
  void gate_align_normal(cv::Mat img, cv::Point rectCentroid)
  {
      int img_center_y = img.rows / 2;
      if (rectCentroid.y < img_center_y - crosshair_radius)
      {
        std::cout << "MOVE NORMAL UP" << std::endl;
        vel_msg.twist.linear.z = 0.04;
      }
      else if (rectCentroid.y > img_center_y + crosshair_radius)
      {
        std::cout << "MOVE NORMAL DOWN" << std::endl;
        vel_msg.twist.linear.z = -0.04;
      }
      else 
      {
        std::cout << "NORMAL CENTERED" << std::endl;
        vel_msg.twist.linear.z = 0.0;
      }
  }
  
  void gate_align_yaw(cv::Mat img, cv::Point rectCentroid)
  {
      int img_center_x = img.cols / 2;
      if (rectCentroid.x < img_center_x - crosshair_radius)
      {
          std::cout << "ROTATE YAW LEFT" << std::endl;
          vel_msg.twist.linear.x = -0.04;
      }
      else if (rectCentroid.x > img_center_x + crosshair_radius)
      {
          std::cout << "ROTATE YAW RIGHT" << std::endl;
          vel_msg.twist.linear.x = 0.04;
      }
      else 
      {
          std::cout << "YAW CENTERED" << std::endl;
          vel_msg.twist.linear.x = 0.00;
      }
  }
  
  void gate_align_lateral(cv::Mat img, std::vector<cv::Point> rectangle)
  {
      // Find top and botom points
      cv::Point top_a, top_b;
      top_a = rectangle[min_point_y_idx(rectangle)];
      rectangle.erase(rectangle.begin() + min_point_y_idx(rectangle));
      top_b = rectangle[min_point_y_idx(rectangle)];
      rectangle.erase(rectangle.begin() + min_point_y_idx(rectangle));
  
      // Draw perspective lines
      fullLine(img, top_a, top_b, cv::Scalar(0, 0, 255));
      fullLine(img, rectangle[0], rectangle[1], cv::Scalar(0, 0, 255));
  
      // Find top and bottom line slopes
      double top_slope = find_slope(top_a.x, top_a.y, top_b.x, top_b.y);
      double bottom_slope = find_slope(rectangle[0].x, rectangle[0].y, rectangle[1].x, rectangle[1].y);
      std::cout << "top slope: " << top_slope << std::endl << "bottom slope: " << bottom_slope << std::endl;
  
      // Move in lateral direction
      if (top_slope > lateral_alignment_slope_tolerance && bottom_slope < -lateral_alignment_slope_tolerance)
      {
          std::cout << "MOVE LATERAL LEFT" << std::endl;

      }
      else if (top_slope < -lateral_alignment_slope_tolerance && bottom_slope > lateral_alignment_slope_tolerance)
      {
          std::cout << "MOVE LATERAL RIGHT" << std::endl;
      }
      else 
      {
          std::cout << "LATERAL CENTERED" << std::endl;
      }
  }

  void draw_gridlines(cv::Mat img)
  {
      line(img, cv::Point(0, img.rows / 2), cv::Point(img.cols, img.rows / 2), cv::Scalar(255,255,255));
      line(img, cv::Point(img.cols / 2, 0), cv::Point(img.cols / 2, img.rows), cv::Scalar(255,255,255));
  }
    
  
  // ROS & OPENCV
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
    

    img = cv_ptr->image;

    // Resize the image to a smaller size
    int new_width = img.cols / 1; // Adjust the scaling factor as needed
    int new_height = img.rows / 1; // Adjust the scaling factor as needed
    cv::resize(img, img_resized, cv::Size(new_width, new_height));

    cv::GaussianBlur(img_resized, blurred, cv::Size(7, 7), 2);
    cv::cvtColor(blurred, img_hsv, cv::COLOR_BGR2HSV);

    // Process the image
    on_trackbar(0, 0); // Call the trackbar function to update the thresholded image

    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::morphologyEx(mask, morphed, cv::MORPH_DILATE, kernel, cv::Point(-1, -1), 1);

    // Detect contours
    cv::findContours(morphed, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    // Filter contours to find the rectangle
    std::vector<cv::Point> largestRectangle;
    double maxArea = 0;
    for (size_t i = 0; i < contours.size(); ++i) {
        std::vector<cv::Point> contour_poly;
        cv::approxPolyDP(contours[i], contour_poly, 0.02 * cv::arcLength(contours[i], true), true);

        if (contour_poly.size() == 4 && cv::isContourConvex(contour_poly)) {
            double area = cv::contourArea(contour_poly);
            if (area > maxArea && area > minArea) {
                maxArea = area;
                largestRectangle = contour_poly;
            }
        }
    }

    if (!largestRectangle.empty()) {
        // Draw the rectangle
        for (size_t i = 0; i < largestRectangle.size(); i++) {
            cv::line(img_resized, largestRectangle[i], largestRectangle[(i + 1) % largestRectangle.size()], cv::Scalar(0, 255, 0), 3);
        }

        draw_gridlines(img_resized);
        cv::circle(img_resized, cv::Point(img_resized.cols / 2, img_resized.rows / 2), crosshair_radius, cv::Scalar(255, 255, 255));

        cv::Point rectCentroid = find_rect_centroid(img_resized, largestRectangle);
        gate_align_normal(img_resized, rectCentroid);
        gate_align_yaw(img_resized, rectCentroid);
        gate_align_lateral(img_resized, largestRectangle);

        std::cout << "================" << std::endl;
        
    }

    // Display the result
    cv::Mat gray;
    cv::cvtColor(blurred, gray, cv::COLOR_BGR2GRAY);
    //cv::imshow("Gray", gray);
    cv::imshow("Detected Rectangle", img_resized);

    // Update GUI Window
    //cv::imshow(OPENCV_WINDOW, cv_ptr->image);
    cv::waitKey(3);

    // Output modified video stream
    image_pub_.publish(cv_ptr->toImageMsg());
    vel_pub.publish(vel_msg);
  }
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_converter");
  ImageConverter ic;
  ros::spin();
  return 0;
}
