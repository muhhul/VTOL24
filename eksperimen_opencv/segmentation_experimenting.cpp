#include <opencv2/opencv.hpp>
#include <iostream>
#include "gate_detection.hpp"

int saturation = 100;
int value = 100;
int vibrance = 100;

cv::Mat segmentImageWithKMeans(const cv::Mat& img, int K)
{
    // Reshape the image to a 2D array of pixels
    cv::Mat data;
    img.convertTo(data, CV_32F);
    data = data.reshape(1, img.total());

    // Define criteria, number of clusters(K) and apply kmeans()
    cv::Mat labels, centers;
    cv::kmeans(data, K, labels, cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER, 10, 1.0), 3, cv::KMEANS_PP_CENTERS, centers);

    // Convert back the data type of centers
    centers = centers.reshape(3, centers.rows);
    centers.convertTo(centers, CV_8UC1);

    // Replace pixel values with their centroid value
    cv::Mat segmented = labels.reshape(1, img.rows);
    segmented.convertTo(segmented, CV_8UC1);
    cv::Mat segmented_image(img.size(), img.type());
    for (int i = 0; i < segmented.rows; ++i) {
        for (int j = 0; j < segmented.cols; ++j) {
            int cluster_idx = segmented.at<uchar>(i, j);
            segmented_image.at<cv::Vec3b>(i, j) = centers.at<cv::Vec3b>(cluster_idx);
        }
    }

    return segmented_image;
}

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

        // Resize image
        int new_width = img.cols / 8;  // Desired width
        int new_height = img.rows / 8; // Desired height
        cv::resize(img, img, cv::Size(new_width, new_height));

        // IMAGE PROCESSING
        // Change values of each HSV channels
        // double saturationScale = double(saturation) / 100;
        // gate_detection::scaleSaturation(img, saturationScale);
        // double valueScale = double(value) / 100;
        // gate_detection::scaleValue(img, valueScale);
        // double vibranceScale = double(vibrance) / 100;
        // gate_detection::scaleVibranceRedBounded(img, vibranceScale);


        // Split HSV channels
        // std::vector<cv::Mat> channels;
        // cv::split(img, channels);

        int K4 = 4;
        cv::Mat segmented_image4 = segmentImageWithKMeans(img, K4);
        int K5 = 5;
        cv::Mat segmented_image5 = segmentImageWithKMeans(img, K5);

        // Create image stack
        std::vector<cv::Mat> img_stack;
        img_stack.push_back(img);
        img_stack.push_back(segmented_image4);
        img_stack.push_back(segmented_image5);
        // cv::putText(channels[0], "Hue", cv::Point(30, 100), cv::FONT_HERSHEY_PLAIN, 5, cv::Scalar(255,255,255), 5, cv::LINE_AA);
        // img_stack.push_back(channels[0]); 
        // cv::putText(channels[1], "Saturation", cv::Point(30, 100), cv::FONT_HERSHEY_PLAIN, 5, cv::Scalar(255,255,255), 5, cv::LINE_AA);
        // img_stack.push_back(channels[1]);
        // cv::putText(channels[2], "Value", cv::Point(30, 100), cv::FONT_HERSHEY_PLAIN, 5, cv::Scalar(255,255,255), 5, cv::LINE_AA);
        // img_stack.push_back(channels[2]);
        
        // Show image stack
        int hstack = 3;
        int vstack = (img_stack.size() + hstack - 1) / hstack;
        int frameWidth = img.cols;
        int frameHeight = img.rows;
        gate_detection::stackAndShowImages(img_stack, hstack * frameWidth, vstack*frameHeight, hstack, vstack);
        gate_detection::keyboard_input(cap.get(cv::CAP_PROP_FPS), playing);
    }
    
    return 0;
}
