#include "gate_detection.hpp"

namespace gate_detection
{

double find_slope(int x0, int y0, int x1, int y1)
{
    return (double) (y1-y0)/(x1-x0);
}

void fullLine(cv::Mat img, cv::Point a, cv::Point b, cv::Scalar color)
{
    double slope = find_slope(a.x, a.y, b.x, b.y);

    cv::Point p(0,0), q(img.cols,img.rows);

    p.y = -(a.x - p.x) * slope + a.y;
    q.y = -(b.x - q.x) * slope + b.y;

    line(img,p,q,color,1,8,0);
}

void draw_gridlines(cv::Mat img)
{
    line(img, cv::Point(0, img.rows / 2), cv::Point(img.cols, img.rows / 2), cv::Scalar(255,255,255));
    line(img, cv::Point(img.cols / 2, 0), cv::Point(img.cols / 2, img.rows), cv::Scalar(255,255,255));
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
    if (rectCentroid.y < img_center_y - crosshair_radius) std::cout << "MOVE NORMAL UP" << std::endl;
    else if (rectCentroid.y > img_center_y + crosshair_radius) std::cout << "MOVE NORMAL DOWN" << std::endl;
    else std::cout << "NORMAL CENTERED" << std::endl;
}

void gate_align_yaw(cv::Mat img, cv::Point rectCentroid)
{
    int img_center_x = img.cols / 2;
    if (rectCentroid.x < img_center_x - crosshair_radius) std::cout << "ROTATE YAW LEFT" << std::endl;
    else if (rectCentroid.x > img_center_x + crosshair_radius) std::cout << "ROTATE YAW RIGHT" << std::endl;
    else std::cout << "YAW CENTERED" << std::endl;
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
        std::cout << "MOVE LATERAL LEFT" << std::endl;
    else if (top_slope < -lateral_alignment_slope_tolerance && bottom_slope > lateral_alignment_slope_tolerance)
        std::cout << "MOVE LATERAL RIGHT" << std::endl;
    else std::cout << "LATERAL CENTERED" << std::endl;
}

void findLargestRectangle(cv::Mat img, std::vector<cv::Point> &largestRectangle, int minArea)
{
    if (img.empty())
    {
        std::cerr << "Error: image is empty!" << std::endl;
        return;
    }

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    // Detect contours
    cv::findContours(img, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    // Filter contours to find the rectangle
    double maxArea = 0;
    for (size_t i = 0; i < contours.size(); ++i) 
    {
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
}

void keyboard_input(int fps, bool &playing)
{
    switch (cv::waitKey(1000/fps))
    {
        case 'q':
            playing = false;
            std::cout << "q" << std::endl;
            break;
        case 'p':
            while (cv::waitKey(0) != 'p');
            std::cout << "p" << std::endl;
            break;
    } 
}

}