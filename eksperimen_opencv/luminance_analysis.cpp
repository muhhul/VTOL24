#include <opencv2/opencv.hpp>
#include <iostream>
#include "gate_detection.hpp"

int main(int argc, char const *argv[])
{
    cv::VideoCapture cap1("assets/gate_asrama_lorong.mp4");
    cv::VideoCapture cap2("assets/gate_asrama_tengah.mp4");
    cv::VideoCapture cap3("assets/gate_gor.mp4");
    cv::VideoCapture cap4("assets/gate_lapbol_samping.mp4");
    cv::VideoCapture cap5("assets/gate_lapbol_utara.mp4");
    cv::VideoCapture cap6("assets/vid_gate.mp4");
    cv::VideoCapture cap7("assets/vid_wide_gate.mp4");

    // Check if video can be opened
    // if (!cap.isOpened()) {
    //     std::cerr << "Error: Could not open video file or camera!" << std::endl;
    //     return -1;
    // }

    bool playing = true;
    while (playing)
    {
        cv::Mat img1, img2, img3, img4, img5, img6, img7;
        cap1 >> img1; 
        cap2 >> img2; 
        cap3 >> img3; 
        cap4 >> img4;
        cap5 >> img5;
        cap6 >> img6;
        cap7 >> img7;

        // Create image stack
        std::vector<cv::Mat> img_stack;
        img_stack.push_back(img1);
        img_stack.push_back(img2);
        img_stack.push_back(img3);
        img_stack.push_back(img4);
        img_stack.push_back(img5);
        img_stack.push_back(img6);
        img_stack.push_back(img7);

        int hstack = 3;
        int vstack = (img_stack.size() + hstack - 1) / hstack;
        int frameWidth = img1.cols / 4;
        int frameHeight = img1.rows / 4;
        gate_detection::stackAndShowImages(img_stack, hstack * frameWidth, vstack*frameHeight, hstack, vstack);
        gate_detection::keyboard_input(cap1.get(cv::CAP_PROP_FPS), playing);
        
    }
    
    return 0;
}
