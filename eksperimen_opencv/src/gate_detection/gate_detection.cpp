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
    // Calculate and return the center point
    cv::Point rectCentroid((largestRectangle[0].x + largestRectangle[2].x) / 2, (largestRectangle[0].y + largestRectangle[2].y) / 2);
    return rectCentroid;
}

void draw_rect_centroid(cv::Mat &img, std::vector<cv::Point> largestRectangle)
{
    if (largestRectangle.empty())
    {
        return;
    }
    
    // Draw the diagonal lines
    cv::line(img, largestRectangle[0], largestRectangle[2], cv::Scalar(255, 0, 0), 2);
    cv::line(img, largestRectangle[1], largestRectangle[3], cv::Scalar(255, 0, 0), 2);

    // Find centroid
    cv::Point rectCentroid = find_rect_centroid(img, largestRectangle);

     // Draw the center point
    cv::circle(img, rectCentroid, 5, cv::Scalar(0, 0, 255), -1);
    std::cout << "Rectangle center: " << rectCentroid << std::endl;
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

void findLargestRectangle(cv::Mat img_bin, std::vector<cv::Point> &largestRectangle, int minArea)
{
    if (img_bin.empty())
    {
        std::cerr << "Error: image is empty!" << std::endl;
        return;
    }

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    // Detect contours
    cv::findContours(img_bin, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

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

void drawRectangle(cv::Mat img, std::vector<cv::Point> &largestRectangle)
{
    if (!largestRectangle.empty()) {
        // Draw the rectangle
        for (size_t i = 0; i < largestRectangle.size(); i++) {
            cv::line(img, largestRectangle[i], largestRectangle[(i + 1) % largestRectangle.size()], cv::Scalar(0, 255, 0), 3);
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

void stackAndShowImages(const std::vector<cv::Mat>& images, int windowWidth, int windowHeight, int imagesPerRow, int imagesPerColumn) {
    if (images.empty()) {
        std::cerr << "No images to display." << std::endl;
        return;
    }

    int canvasType = images[0].type();
    int singleImageWidth = windowWidth / imagesPerRow;
    int singleImageHeight = windowHeight / imagesPerColumn;

    // Create a blank canvas
    cv::Mat canvas(windowHeight, windowWidth, images[0].type(), cv::Scalar::all(0));

    // Resize and place images on the canvas
    for (size_t i = 0; i < images.size(); ++i) {
        if (i >= imagesPerRow * imagesPerColumn) break;

        int rowIndex = i / imagesPerRow;
        int colIndex = i % imagesPerRow;

        cv::Rect roi(cv::Point(colIndex * singleImageWidth, rowIndex * singleImageHeight), cv::Size(singleImageWidth, singleImageHeight));
        cv::Mat resizedImage;
        cv::resize(images[i], resizedImage, roi.size());

        // Convert the image to the same type as the canvas if needed
        if (resizedImage.type() != canvasType) {
            cv::cvtColor(resizedImage, resizedImage, resizedImage.channels() == 1 ? cv::COLOR_GRAY2BGR : cv::COLOR_BGR2GRAY);
        }
        
        resizedImage.copyTo(canvas(roi));
    }

    // Display the stacked images
    cv::imshow("Stacked Images", canvas);
}

void scaleSaturation(cv::Mat& image, double scale) {
    // Convert the image from BGR to HSV
    cv::Mat hsv;
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

    // Split the HSV channels
    std::vector<cv::Mat> hsvChannels;
    cv::split(hsv, hsvChannels);

    // Increase the saturation channel
    hsvChannels[1] = hsvChannels[1] * scale;

    // Ensure the values are within the valid range [0, 255]
    cv::min(hsvChannels[1], 255, hsvChannels[1]);

    // Merge the HSV channels back
    cv::merge(hsvChannels, hsv);

    // Convert the image back from HSV to BGR
    cv::cvtColor(hsv, image, cv::COLOR_HSV2BGR);
}

void scaleValue(cv::Mat& image, double scale) {
    // Convert the image from BGR to HSV
    cv::Mat hsv;
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

    // Split the HSV channels
    std::vector<cv::Mat> hsvChannels;
    cv::split(hsv, hsvChannels);

    // Increase the saturation channel
    hsvChannels[2] = hsvChannels[2] * scale;

    // Ensure the values are within the valid range [0, 255]
    cv::min(hsvChannels[2], 255, hsvChannels[2]);

    // Merge the HSV channels back
    cv::merge(hsvChannels, hsv);

    // Convert the image back from HSV to BGR
    cv::cvtColor(hsv, image, cv::COLOR_HSV2BGR);
}

void scaleVibrance(cv::Mat& image, double scale) {
    // Convert the image from BGR to HSV
    cv::Mat hsv;
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

    // Split the HSV channels
    std::vector<cv::Mat> hsvChannels;
    cv::split(hsv, hsvChannels);

    // Adjust the saturation channel
    for (int i = 0; i < hsvChannels[1].rows; ++i) {
        for (int j = 0; j < hsvChannels[1].cols; ++j) {
            uchar& hue = hsvChannels[0].at<uchar>(i, j);
            uchar& sat = hsvChannels[1].at<uchar>(i, j);

            // Decrease vibrance more for higher saturation values
            double newSat = sat * (1.0 - (sat / 255.0) * (1.0 - scale));
            sat = static_cast<uchar>(cv::saturate_cast<uchar>(newSat));
        }
    }

    // Merge the HSV channels back
    cv::merge(hsvChannels, hsv);

    // Convert the image back from HSV to BGR
    cv::cvtColor(hsv, image, cv::COLOR_HSV2BGR);
}

void scaleVibranceRedBounded(cv::Mat& image, double scale, int redBoundLeft, int redBoundRight) {
    // Convert the image from BGR to HSV
    cv::Mat hsv;
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

    // Split the HSV channels
    std::vector<cv::Mat> hsvChannels;
    cv::split(hsv, hsvChannels);

    // Adjust the saturation channel
    for (int i = 0; i < hsvChannels[1].rows; ++i) {
        for (int j = 0; j < hsvChannels[1].cols; ++j) {
            uchar& hue = hsvChannels[0].at<uchar>(i, j);
            uchar& sat = hsvChannels[1].at<uchar>(i, j);

            // Check if the pixel is in the orange hue range
            if (hue < redBoundLeft || hue > redBoundRight) {
                // Decrease vibrance more for higher saturation values
                double newSat = sat * (1.0 - (sat / 255.0) * (1.0 - scale));
                sat = static_cast<uchar>(cv::saturate_cast<uchar>(newSat));
            }
        }
    }

    // Merge the HSV channels back
    cv::merge(hsvChannels, hsv);

    // Convert the image back from HSV to BGR
    cv::cvtColor(hsv, image, cv::COLOR_HSV2BGR);
}

const double focal_length = 3.2 / 10.0; // in cm
const double actual_width = 170; // in cm

double find_width(std::vector<cv::Point> rect){
    std::vector<cv::Point> copy_rect = rect;
    int first = min_point_y_idx(rect);
    rect.erase(rect.begin() + first);
    int second = min_point_y_idx(rect);
    return abs(copy_rect[first].x - copy_rect[second].x);
}

double calculate_distance(double width_in_frame){
    return actual_width * focal_length / width_in_frame;
}

void show_distance(std::vector<cv::Point> rect){
    double distance = calculate_distance(find_width(rect));
    std::cout << "Distance: " << distance << "\n";
}

double meanValueChannel(const cv::Mat& img) {
    // Check if the image is empty
    if (img.empty()) {
        std::cerr << "Error: Image is empty!" << std::endl;
        return -1.0; // Return an invalid value to indicate an error
    }

    // Convert the image to HSV color space
    cv::Mat hsv;
    cv::cvtColor(img, hsv, cv::COLOR_BGR2HSV);

    // Split the HSV channels
    std::vector<cv::Mat> hsv_channels;
    cv::split(hsv, hsv_channels);
    cv::Mat value_channel = hsv_channels[2]; // The Value channel

    // Calculate the mean value of the Value channel
    cv::Scalar mean_value = cv::mean(value_channel);

    return mean_value[0]; // Return the mean value as a double
}

LightingCondition determineLightingCondition(const cv::Mat& img) {
    // Calculate the mean brightness value
    cv::Scalar mean_value = meanValueChannel(img);

    // Define thresholds for different lighting conditions
    double minimal_threshold = 50.0;
    double bright_threshold = 200.0;

    if (mean_value[0] < minimal_threshold) {
        return MINIMAL_LIGHTING;
    } else if (mean_value[0] > bright_threshold) {
        return BRIGHT_LIGHTING;
    } else {
        return NORMAL_LIGHTING;
    }
}

double meanValueInRedHueRange(const cv::Mat& img) {
    // Check if the image is empty
    if (img.empty()) {
        std::cerr << "Error: Image is empty!" << std::endl;
        return -1.0; // Return an invalid value to indicate an error
    }

    // Convert the image to HSV color space
    cv::Mat hsv;
    cv::cvtColor(img, hsv, cv::COLOR_BGR2HSV);

    // Define the hue range for red color (you might need to adjust these values)
    int low_hue1 = 0;
    int high_hue1 = 30;
    int low_hue2 = 160;
    int high_hue2 = 180;

    // Create masks for the specified hue ranges
    cv::Mat mask1, mask2, mask;
    cv::inRange(hsv, cv::Scalar(low_hue1, 50, 50), cv::Scalar(high_hue1, 255, 255), mask1);
    cv::inRange(hsv, cv::Scalar(low_hue2, 50, 50), cv::Scalar(high_hue2, 255, 255), mask2);

    // Combine the masks
    mask = mask1 | mask2;

    // Extract the Value channel
    std::vector<cv::Mat> hsv_channels;
    cv::split(hsv, hsv_channels);
    cv::Mat value_channel = hsv_channels[2]; // The Value channel

    // Calculate the mean value of the Value channel within the mask
    cv::Scalar mean_value = cv::mean(value_channel, mask);

    return mean_value[0]; // Return the mean value as a double
}

}