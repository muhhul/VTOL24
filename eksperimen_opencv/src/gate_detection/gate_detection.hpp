#ifndef GATE_DETECTION_
#define GATE_DETECTION_

#include <opencv2/opencv.hpp>
#include <iostream>

namespace gate_detection
{

const int crosshair_radius                      = 15;
const int lateral_alignment_slope_tolerance     = 0.02;

double find_slope               (int x0, int y0, int x1, int y1);

int min_point_y_idx             (std::vector<cv::Point> points);

cv::Point find_rect_centroid    (cv::Mat img, std::vector<cv::Point> largestRectangle);

void draw_rect_centroid         (cv::Mat &img, std::vector<cv::Point> largestRectangle);
void findLargestRectangle       (cv::Mat img_bin, std::vector<cv::Point> &largestRectangle, int minArea=0);
void drawRectangle              (cv::Mat img, std::vector<cv::Point> &largestRectangle);
void fullLine                   (cv::Mat img, cv::Point a, cv::Point b, cv::Scalar color);
void draw_gridlines             (cv::Mat img);
void gate_align_normal          (cv::Mat img, cv::Point rectCentroid);
void gate_align_yaw             (cv::Mat img, cv::Point rectCentroid);
void gate_align_lateral         (cv::Mat img, std::vector<cv::Point> rectangle);
void keyboard_input             (int fps, bool &playing);
void stackAndShowImages         (const std::vector<cv::Mat>& images, int windowWidth, int windowHeight, int imagesPerRow, int imagesPerColumn);
void scaleSaturation            (cv::Mat& image, double scale);
void scaleValue                 (cv::Mat& image, double scale);
void scaleVibrance              (cv::Mat& image, double scale);
void scaleVibranceRedBounded    (cv::Mat& image, double scale, int redBoundLeft = 10, int redBoundRight = 185);

double find_width               (std::vector<cv::Point> rect);
double calculate_distance       (double width_in_frame);
void show_distance              (std::vector<cv::Point> rect);

enum LightingCondition {
    MINIMAL_LIGHTING,
    NORMAL_LIGHTING,
    BRIGHT_LIGHTING
};

double meanValueChannel                         (const cv::Mat& img);
double meanValueInRedHueRange                   (const cv::Mat& img);
LightingCondition determineLightingCondition    (const cv::Mat& img);


}

#endif