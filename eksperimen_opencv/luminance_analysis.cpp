#include <opencv2/opencv.hpp>
#include <iostream>
#include "gate_detection.hpp"

int lower_h_l = 0, lower_s_l = 154, lower_v_l = 82;
int upper_h_l = 30, upper_s_l = 255, upper_v_l = 255;
int lower_h_r = 126, lower_s_r = 40, lower_v_r = 97;
int upper_h_r = 179, upper_s_r = 255, upper_v_r = 255;

std::vector<std::string> video_paths = {
    "assets/gate_asrama_lorong.mp4",
    "assets/gate_asrama_tengah.mp4",
    "assets/gate_gor.mp4",
    "assets/gate_lapbol_samping.mp4",
    "assets/gate_lapbol_utara.mp4",
    "assets/vid_gate.mp4",
    "assets/vid_wide_gate.mp4"
};

int main(int argc, char const *argv[])
{
    std::vector<cv::VideoCapture> caps;
    for (auto path : video_paths)
    {
        caps.push_back(cv::VideoCapture(path));
    }

    cv::namedWindow("Trackbars", cv::WINDOW_AUTOSIZE);
    cv::createTrackbar("Lower H Left", "Trackbars", &lower_h_l, 179);
    cv::createTrackbar("Lower S Left", "Trackbars", &lower_s_l, 255);
    cv::createTrackbar("Lower V Left", "Trackbars", &lower_v_l, 255);
    cv::createTrackbar("Upper H Left", "Trackbars", &upper_h_l, 179);
    cv::createTrackbar("Upper S Left", "Trackbars", &upper_s_l, 255);
    cv::createTrackbar("Upper V Left", "Trackbars", &upper_v_l, 255);
    cv::createTrackbar("Lower H Right", "Trackbars", &lower_h_r, 179);
    cv::createTrackbar("Lower S Right", "Trackbars", &lower_s_r, 255);
    cv::createTrackbar("Lower V Right", "Trackbars", &lower_v_r, 255);
    cv::createTrackbar("Upper H Right", "Trackbars", &upper_h_r, 179);
    cv::createTrackbar("Upper S Right", "Trackbars", &upper_s_r, 255);
    cv::createTrackbar("Upper V Right", "Trackbars", &upper_v_r, 255);




    bool playing = true;
    while (playing)
    {
        // Create image stack
        std::vector<cv::Mat> img_stack;
        for (auto cap : caps)
        {
            cv::Mat img;
            cap >> img;

            if (img.empty()) {
                // Rewind to the start of the video if the end is reached
                cap.set(cv::CAP_PROP_POS_FRAMES, 0);
                continue; // Skip the empty frame and continue the loop
            }

            cv::resize(img, img, cv::Size(640, 360));
            double meanValRed = gate_detection::meanValueInRedHueRange(img);
            cv::GaussianBlur(img, img, cv::Size(5, 5), 3);

            cv::cvtColor(img, img, cv::COLOR_BGR2HSV);

            cv::Mat img_thresholded_l, img_thresholded_r;
            cv::inRange(img, cv::Scalar(lower_h_l, lower_s_l, lower_v_l), cv::Scalar(upper_h_l, upper_s_l, upper_v_l), img_thresholded_l);
            cv::inRange(img, cv::Scalar(lower_h_r, lower_s_r, lower_v_r), cv::Scalar(upper_h_r, upper_s_r, upper_v_l), img_thresholded_r);
            cv::Mat mask = img_thresholded_l | img_thresholded_r;

            std::vector<cv::Point> largestRectangle;
            gate_detection::findLargestRectangle(mask, largestRectangle, 3000);

            cv::cvtColor(img, img, cv::COLOR_HSV2BGR);
            cv::cvtColor(mask, mask, cv::COLOR_GRAY2BGR);
            gate_detection::drawRectangle(mask, largestRectangle);
            gate_detection::draw_rect_centroid(mask, largestRectangle);

            std::vector<cv::Mat> hsv_channels;
            cv::split(img, hsv_channels);

            cv::putText(mask, std::to_string(meanValRed), cv::Point(10, 20), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(255,255,255), 1, cv::LINE_AA);
            img_stack.push_back(mask);
        }
        
        

        int hstack = 3;
        int vstack = (img_stack.size() + hstack - 1) / hstack;
        int frameWidth = img_stack[0].cols;
        int frameHeight = img_stack[0].rows;
        gate_detection::stackAndShowImages(img_stack, hstack * frameWidth, vstack*frameHeight, hstack, vstack);
        gate_detection::keyboard_input(caps[0].get(cv::CAP_PROP_FPS), playing);
        
    }
    
    return 0;
}
