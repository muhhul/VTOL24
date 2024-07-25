#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "gate_detection.hpp"

cv::Mat img, img_resized, blurred, morphed, img_hsv, img_thresholded_l, img_thresholded_r, mask, edges, gray;
int lower_h_l = 0, lower_s_l = 203, lower_v_l = 0;
int upper_h_l = 35, upper_s_l = 255, upper_v_l = 255;
int lower_h_r = 126, lower_s_r = 40, lower_v_r = 97;
int upper_h_r = 179, upper_s_r = 255, upper_v_r = 255;
int thresh1 = 0;
int thresh2 = 50;
int minArea = 3713; // Filter shapes with small area
int saturation = 100;
int value = 100;
int vibrance = 100;
int normalize_lower = 0; 
int normalize_upper = 500;

void onChange_HSVMask(int, void*) {
    if (img_hsv.empty()) return; // Check if img_hsv is empty
    cv::inRange(img_hsv, cv::Scalar(lower_h_l, lower_s_l, lower_v_l), cv::Scalar(upper_h_l, upper_s_l, upper_v_l), img_thresholded_l);
    cv::inRange(img_hsv, cv::Scalar(lower_h_r, lower_s_r, lower_v_r), cv::Scalar(upper_h_r, upper_s_r, upper_v_l), img_thresholded_r);
    mask = img_thresholded_l | img_thresholded_r;
    cv::imshow("Masked Image", mask);
}

void onChange_Canny(int, void*) {
    if (gray.empty()) return; // Check if img_hsv is empty
    cv::Canny(gray, edges, thresh1, thresh2, 3, 5);
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::morphologyEx(edges, edges, cv::MORPH_DILATE, kernel, cv::Point(-1,-1), 1);
    cv::imshow("Edges Image", edges);
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

void scaleVibrance(cv::Mat& image, double scale, int redBoundLeft = 10, int redBoundRight = 185) {
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

int main(int, char**){
    // Open video file
    cv::VideoCapture cap("assets/vid_wide_gate.mp4"); // Change to 0 for webcam or provide the path to your video file
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open video file or camera!" << std::endl;
        return -1;
    }

    // Open photo file
    // img = cv::imread("../OrGate.png"); // The image file is in the parent directory
    // if (img.empty()) {
    //     std::cerr << "Error: Image not found!" << std::endl;
    //     return -1;
    // }

    void (*on_trackbar)(int, void*) = onChange_HSVMask;

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
    cv::createTrackbar("Thresh1", "Trackbars", &thresh1, 255, on_trackbar);
    cv::createTrackbar("Thresh2", "Trackbars", &thresh2, 255, on_trackbar);
    cv::createTrackbar("Min Area", "Trackbars", &minArea, 30000);
    cv::createTrackbar("Saturation", "Trackbars", &saturation, 200);
    cv::createTrackbar("Value", "Trackbars", &value, 200);
    cv::createTrackbar("Vibrance", "Trackbars", &vibrance, 200);

    cv::namedWindow("Trackbars 2", cv::WINDOW_AUTOSIZE);
    cv::createTrackbar("normalize lower", "Trackbars 2", &normalize_lower, 500);
    cv::createTrackbar("normalize upper", "Trackbars 2", &normalize_upper, 500);

    // Initial call to display the image
    on_trackbar(0, 0);

    bool playing = true;
    while (playing) {
        // Capture frame-by-frame
        cap >> img; // Read a new frame from the video
        if (img.empty()) {
            // Rewind to the start of the video if the end is reached
            cap.set(cv::CAP_PROP_POS_FRAMES, 0);
            continue; // Skip the empty frame and continue the loop
        }

        // Resize the image to a smaller size
        int new_width = img.cols/6; // Adjust the scaling factor as needed
        int new_height = img.rows/6; // Adjust the scaling factor as needed
        cv::resize(img, img_resized, cv::Size(new_width, new_height));

        // IMAGE PREPROCESSING
        double saturationScale = double(saturation) / 100;
        scaleSaturation(img_resized, saturationScale);
        double valueScale = double(value) / 100;
        scaleValue(img_resized, valueScale);
        double vibranceScale = double(vibrance) / 100;
        scaleVibrance(img_resized, vibranceScale, upper_h_l, lower_h_r);
        cv::GaussianBlur(img_resized, blurred, cv::Size(5, 5), 3);
        // cv::cvtColor(blurred, gray, cv::COLOR_BGR2GRAY);
        cv::imshow("Blur", blurred);
        cv::normalize(blurred, blurred, normalize_lower, normalize_upper, cv::NORM_MINMAX);
        cv::imshow("Normed", blurred);
        cv::cvtColor(blurred, img_hsv, cv::COLOR_BGR2HSV);
        // cv::imshow("Gray", gray);

        on_trackbar(0, 0); // Call the trackbar function to update the thresholded image

        // RECTANGLE (GATE) DETECTION
        std::vector<cv::Point> largestRectangle;
        gate_detection::findLargestRectangle(mask, largestRectangle, minArea);
        
        if (!largestRectangle.empty()) {
            // Draw the rectangle
            for (size_t i = 0; i < largestRectangle.size(); i++) {
                cv::line(img_resized, largestRectangle[i], largestRectangle[(i + 1) % largestRectangle.size()], cv::Scalar(0, 255, 0), 3);
            }

            gate_detection::draw_gridlines(img_resized);
            cv::circle(img_resized, cv::Point(img_resized.cols / 2, img_resized.rows / 2), gate_detection::crosshair_radius, cv::Scalar(255, 255, 255));

            cv::Point rectCentroid = gate_detection::find_rect_centroid(img_resized, largestRectangle);
            gate_detection::gate_align_normal(img_resized, rectCentroid);
            gate_detection::gate_align_yaw(img_resized, rectCentroid);
            gate_detection::gate_align_lateral(img_resized, largestRectangle);

            std::cout << "================" << std::endl;
            
        }

        // Display the result
        cv::imshow("Detected Rectangle", img_resized);

        // Break the loop if the user presses the 'q' key
        gate_detection::keyboard_input(cap.get(cv::CAP_PROP_FPS), playing);
    }

    // Release video capture and close windows
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
