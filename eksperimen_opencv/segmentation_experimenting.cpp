#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include "gate_detection.hpp"

int saturation = 100;
int value = 100;
int vibrance = 100;

int main(int argc, char const *argv[])
{
    // Open video file
    cv::VideoCapture cap("assets/vid_wide_gate.mp4");

    // Check if video can be opened
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open video file or camera!" << std::endl;
        return -1;
    }
    
    cv::namedWindow("Trackbars", cv::WINDOW_AUTOSIZE);
    cv::createTrackbar("Saturation", "Trackbars", &saturation, 200);
    cv::createTrackbar("Value", "Trackbars", &value, 200);
    cv::createTrackbar("Vibrance", "Trackbars", &vibrance, 200);

    bool playing = true;
    while (playing)
    {
        // Read image from video
        cv::Mat img;
        cap >> img;

        // Check if image is empty
        if (img.empty()) {
            // Rewind to the start of the video if the end is reached
            cap.set(cv::CAP_PROP_POS_FRAMES, 0);
            continue; // Skip the empty frame and continue the loop
        }

        // IMAGE PROCESSING
        // Change values of each HSV channels
        double saturationScale = double(saturation) / 100;
        gate_detection::scaleSaturation(img, saturationScale);
        double valueScale = double(value) / 100;
        gate_detection::scaleValue(img, valueScale);
        double vibranceScale = double(vibrance) / 100;
        gate_detection::scaleVibranceRedBounded(img, vibranceScale);


        // Split HSV channels
        std::vector<cv::Mat> channels;
        cv::split(img, channels);



        // Create image stack
        std::vector<cv::Mat> img_stack;
        img_stack.push_back(img);
        cv::putText(channels[0], "Hue", cv::Point(30, 100), cv::FONT_HERSHEY_PLAIN, 5, cv::Scalar(255,255,255), 5, cv::LINE_AA);
        img_stack.push_back(channels[0]); 
        cv::putText(channels[1], "Saturation", cv::Point(30, 100), cv::FONT_HERSHEY_PLAIN, 5, cv::Scalar(255,255,255), 5, cv::LINE_AA);
        img_stack.push_back(channels[1]);
        cv::putText(channels[2], "Value", cv::Point(30, 100), cv::FONT_HERSHEY_PLAIN, 5, cv::Scalar(255,255,255), 5, cv::LINE_AA);
        img_stack.push_back(channels[2]);
        
        // Show image stack
        int hstack = 3;
        int vstack = std::ceil(img_stack.size() / hstack);
        int frameWidth = img.cols / 6;
        int frameHeight = img.rows / 6;
        gate_detection::stackAndShowImages(img_stack, hstack * frameWidth, vstack*frameHeight, hstack, vstack);
        gate_detection::keyboard_input(cap.get(cv::CAP_PROP_FPS), playing);
    }
    
    return 0;
}
