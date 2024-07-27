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