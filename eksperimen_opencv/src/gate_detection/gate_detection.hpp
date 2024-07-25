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

void findLargestRectangle       (cv::Mat img, std::vector<cv::Point> &largestRectangle, int minArea=0);
void fullLine                   (cv::Mat img, cv::Point a, cv::Point b, cv::Scalar color);
void draw_gridlines             (cv::Mat img);
void gate_align_normal          (cv::Mat img, cv::Point rectCentroid);
void gate_align_yaw             (cv::Mat img, cv::Point rectCentroid);
void gate_align_lateral         (cv::Mat img, std::vector<cv::Point> rectangle);
void keyboard_input             (int fps, bool &playing);

}

#endif