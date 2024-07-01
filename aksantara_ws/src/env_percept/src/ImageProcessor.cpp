#include <env_percept/ImageProcessor.hpp>


namespace env_percept {

//Ganti kalau pake kamera atau settingan kamera baru
const std::map<std::string,ColorRanges> ImageProcessor::calibratedColors
{
        {"Blue", { 100, 130}},
        {"Green", {45, 80}},
        {"Yellow", {20, 40}},
        {"Red1", {0, 15}},
        {"Red2", {165, 180}},
};

ImageProcessor::ImageProcessor() : it_(nh_)
{
	// Subscribe to input video feed and publish output video feed
	// TODO : use output video only for debugging, remove when deploying 
	// WARN : too much global namespace resolution

	front_image_sub_ = it_.subscribe("/front_cam/image_raw", 1, &ImageProcessor::frontImageCb, this);

	down_image_sub_ = it_.subscribe("/down_cam/image_rect_color", 1, &ImageProcessor::downImageCb, this);

	/*
	#if DEBUG_FUNCS
	front_image_sub_ = it_.subscribe("/logitech/webcam/webcam_image_raw", 1, &ImageProcessor::frontImageCb, this); // for gazebo

	down_image_sub_ = it_.subscribe("/logitech/fisheye/fisheye_image_raw", 1, &ImageProcessor::downImageCb, this); // for gazebo
	#endif
	*/

	local_position_sub = nh_.subscribe("/mavros/local_position/pose", 1, &ImageProcessor::localPosCb, this);
	rf_sub = nh_.subscribe("/tfmini_ros_node/raw_data", 1, &ImageProcessor::rfCb, this);
	
	/*
	#if DEBUG_FUNCS
	rf_sub = nh_.subscribe("/gazebo_things/rf_bawah", 1, &ImageProcessor::rfCb, this);
	#endif 
	*/

	front_image_pub_ = it_.advertise("image_percept/front_image/output_video", 1);
	down_image_pub_ = it_.advertise("image_percept/down_image/output_video", 1);

	precland_pub_ = nh_.advertise<uav_msgs::PrecLand>("image_percept/landing_target", 1);
	// precland_display_ = it_.advertise("image_percept/marked_video", 1);

	qr_pub_ = nh_.advertise<std_msgs::String>("image_percept/qr_data", 3);

	detectQRServer = nh_.advertiseService("env_percept/detectQR", &ImageProcessor::scanQR, this);
	detectObjectServer = nh_.advertiseService("env_percept/detectObject", &ImageProcessor::scanObject, this);

	detectDz_pub_ = nh_.advertise<uav_msgs::DzPosition>("image_percept/DzPosition", 1);
	qrPos_pub_ = nh_.advertise<uav_msgs::DzPosition>("image_percept/qr_pos", 1);

	// distX_pub_ = nh_.advertise<std_msgs::Float64>("image_percept/distX", 1);
	distX_pub_ = nh_.advertise<uav_msgs::PrecLoit>("image_percept/distX", 1);

	namaGedung_sub = nh_.subscribe("/nuc/env_percept/namaGedung", 1, &ImageProcessor::gedungCb, this);
}


ImageProcessor::~ImageProcessor(){}


void ImageProcessor::frontImageCb(const sensor_msgs::ImageConstPtr& msg) {
	cv_bridge::CvImagePtr cv_ptr;
	try {
		cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
	}
	catch (cv_bridge::Exception& e) {
		ROS_ERROR("cv_bridge exception: %s", e.what());
		return;
	}

	cv_ptr->image.copyTo(frontHandledImage);

}


void ImageProcessor::downImageCb(const sensor_msgs::ImageConstPtr& msg) {
	cv_bridge::CvImagePtr cv_ptr;
	try {
		cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
	}
	catch (cv_bridge::Exception& e) {
		ROS_ERROR("cv_bridge exception: %s", e.what());
		return;
	}

	cv_ptr->image.copyTo(downHandledImage);

}

void ImageProcessor::localPosCb(const geometry_msgs::PoseStamped& msg) {
	pose_x = msg.pose.position.x;
	pose_y = msg.pose.position.y;
	pose_z = msg.pose.position.z;

	//ROS_DEBUG_STREAM_THROTTLE(1, "Pose: (" << pose_x << ", " << pose_y << ", " << pose_z);
}

void ImageProcessor::rfCb(const sensor_msgs::Range& msg) {
	rf_alt = msg.range;
}

void ImageProcessor::gedungCb(const std_msgs::String& msg) {
	gedung = msg.data;
}

void ImageProcessor::publishAll()
{
	if (downHandledImage.empty()) {
		ROS_WARN_ONCE("downHandledImage is empty");
	}

	if (frontHandledImage.empty()) {
		ROS_WARN_ONCE("frontHandledImage is empty");
	}
	
	if (toggleQR) {
//		ROS_DEBUG("Good, now try to decode");
		decode(frontHandledImage, decodedObjects);
		#if DEBUG_FUNCS
			display(frontHandledImage, decodedObjects);
		#endif
	}

	if (toggleELP) {
		scanELP(downHandledImage);	
	}

	if (toggleDZ) {
		scanDZ(downHandledImage);
	}

	if (togglePilot) {
		getQrPos(frontHandledImage);
	}

	if (toggleDistX) {
		getDistX(downHandledImage);
	}

	sensor_msgs::ImagePtr front_msg_out = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frontHandledImage).toImageMsg();
	front_image_pub_.publish(front_msg_out);

	sensor_msgs::ImagePtr down_msg_out = cv_bridge::CvImage(std_msgs::Header(), "bgr8", downHandledImage).toImageMsg();
	down_image_pub_.publish(down_msg_out);

}


bool ImageProcessor::scanQR(uav_msgs::DetectQR::Request &req, uav_msgs::DetectQR::Response &res)
{
	if(req.name == "pos") {
		if(togglePilot == false) {
			ROS_INFO("Getting Qr position");
			togglePilot = true;
		}
		else {
			ROS_INFO("Done");
			togglePilot = false;
		}
		
	}
	else {
		if (toggleQR == false) {
			ROS_INFO("---Scanning QR Code---");
			toggleQR = true;
			res.scanQR = true;
			
		}
		else {
			ROS_INFO("---Scan QR Code is DONE---");
			toggleQR = false;
			res.scanQR = false;
		}
	}
	
	return true;
}


bool ImageProcessor::scanObject(uav_msgs::DetectObject::Request &req, uav_msgs::DetectObject::Response &res)
{
	if (req.name == "ELP") {
		if (toggleELP == false) {
			ROS_INFO("---Scanning ELP---");
			toggleELP = true;
			res.scanELP = true;
			
		}
		else {
			ROS_INFO("---Scan ELP is DONE---");
			toggleELP = false;
			res.scanELP = false;
		}
	}

	else if (req.name == "DZ") {
		if (toggleDZ == false) {
			ROS_INFO("---Scanning DZ---");
			toggleDZ = true;
			res.scanDZ = true;
		}
		else {
			ROS_INFO("---Scan DZ is DONE---");
			toggleDZ = false;
			res.scanDZ = false;
		}
	}

	else if (req.name == "QRPos") {
		if (togglePilot == false) {
			ROS_INFO("---Scanning QRPos---");
			togglePilot = true;
			res.scanQRPos = true;
		}
		else {
			ROS_INFO("---Scan QRPos is DONE---");
			togglePilot = false;
			res.scanQRPos = false;
		}
	}

	else if (req.name == "DistX") {
		if (toggleDistX == false) {
			ROS_INFO("---Scanning DZ X Pos---");
			toggleDistX = true;
			res.scanDistX = true;

		}
		else {
			ROS_INFO("---Scan DZ X Pos is DONE---");
			toggleDistX = false;
			res.scanDistX = false;
		}
	}
	
	return true;
}


void ImageProcessor::scanDZ(cv::Mat& inputImg)
{
	cv::Point target = cv::Point(inputImg.size().width / 2, inputImg.size().height / 2); //PDM
	cv::circle(inputImg, target, 3, cv::Scalar(255,0,0), cv::FILLED);

	std::vector<std::vector<cv::Point>> contours;
	contours = detectContour(inputImg, "Red");

	int largestIndex = -1;
	double largestArea = 0;
	for (size_t i=0; i<contours.size(); i++)
	{
		double area = cv::contourArea(contours[i]);
		if (area > largestArea)
		{
			largestArea = area;
			largestIndex = i;
		}
	}

	// Tujuan skema cek largestArea > minimumArea untuk menghindari salah pembacaan noise
	// sebagai DZ ketika DZ tidak ditemukan 
	
	// int minimumArea = 200;		// SET MANUAL

	if (largestArea > minimumArea) {
		cv::Moments M = cv::moments(contours[largestIndex], true);
		cv::Point centroid = cv::Point(int(M.m10/M.m00), int(M.m01/M.m00));
		
		cv::circle(inputImg, centroid, 4, cv::Scalar(0,255,0), cv::FILLED);
		cv::drawContours(inputImg, contours, largestIndex, cv::Scalar(0,255,0));

		int imgArea = inputImg.rows * inputImg.cols;
		double percent_red = (largestArea * 100) / imgArea;

		std::vector<cv::Point> contour_poly;
		cv::Point2f center;
		float radius;
		cv::approxPolyDP(contours[largestIndex], contour_poly, 3, true);
		cv::minEnclosingCircle(contour_poly, center, radius);
		// Apa bedanya center dan centroid??? Mirip aja sebenarnya wkwkwk. Tapi di sini pake centroid aja

		// dist_real = sqrt(2) * side_real / diameter_frame * dist_frame
		uav_msgs::DzPosition positionDz;
		positionDz.dist_x = 0.7071 / (2 * radius) * (centroid.x - target.x);	// ke kanan positif
		positionDz.dist_y = 0.7071 / (2 * radius) * (target.y - centroid.y);	// ke atas positif
		detectDz_pub_.publish(positionDz);

		cv::putText(inputImg, std::to_string(percent_red),cv::Point(25,35),cv::FONT_HERSHEY_COMPLEX_SMALL, 1.0, cv::Scalar(255,255,255), 1, cv:: LINE_AA); 

		std::string text = "( " + std::to_string(positionDz.dist_x) + ", " + std::to_string(positionDz.dist_y) + " )";
		cv::putText(inputImg, text,cv::Point(inputImg.size().width - 450,35),cv::FONT_HERSHEY_COMPLEX_SMALL, 1.0, cv::Scalar(255,255,255), 1, cv:: LINE_AA); 

		std::string pose = "Pose: ( " + std::to_string(pose_x) + ", " + std::to_string(pose_y) + ", " + std::to_string(rf_alt) + " }"; 
		cv::putText(inputImg, pose,cv::Point(25,inputImg.size().height - 30),cv::FONT_HERSHEY_COMPLEX_SMALL, 1.0, cv::Scalar(255,255,255), 1, cv:: LINE_AA); 
	} 

	else {
		cv::putText(inputImg, "Not detected",cv::Point(25,35),cv::FONT_HERSHEY_COMPLEX_SMALL, 1.0, cv::Scalar(255,255,255), 1, cv:: LINE_AA); 
	} 
}


void ImageProcessor::scanELP(cv::Mat& inputImg)
{
	std::vector<std::vector<cv::Point>> contours;
	contours = detectContour(inputImg, "Yellow");


	// testing outdoor
	// contours = detectContourOut(inputImg);

	// for testing 
	// contours = detectTerang(inputImg);


	int largestIndex = -1;
	double largestArea = 0;
	for (size_t i=0; i<contours.size(); i++)
	{
		double area = cv::contourArea(contours[i]);
		if (area > largestArea)
		{
			largestArea = area;
			largestIndex = i;
		}
	}

	// int minimumArea = 200;	//SET MANUAL

	if (largestArea > minimumArea) { 
		int i = largestIndex;
		cv::Moments M = cv::moments(contours[largestIndex], true);
		cv::Point centroid = cv::Point(int(M.m10/M.m00), int(M.m01/M.m00));
		cv::circle( inputImg, centroid, 3, cv::Scalar(0,255,0), cv::FILLED );

		cv::drawContours(inputImg, contours, i, cv::Scalar(0,255,0));
		std::vector<cv::Point> contour_poly;
		cv::approxPolyDP(contours[i], contour_poly, 3, true);
		cv::Rect boundRect = cv::boundingRect(contour_poly);
		cv::rectangle(inputImg, boundRect.tl(), boundRect.br(), cv::Scalar(255,255,0), 2 );
	
		/*
		boost::shared_ptr<const geometry_msgs::PoseStamped> posePtr = ros::topic::waitForMessage<geometry_msgs::PoseStamped>("/mavros/local_position/pose", ros::Duration(3.0));
		if (posePtr == NULL) {
			ROS_WARN("Env_percept can't get rangefinder message");
			return;
		}
		*/
		
		centroid.y = centroid.y + ((boundRect.tl().y - boundRect.br().y) * 0.25);
		// Perhitungan dengan geometri 2d sederhana (pake segitiga siku-siku)
		uav_msgs::PrecLand precLandMsg;
		double alt = rf_alt;
		precLandMsg.size_x = abs( atan((double)(boundRect.tl().x - cam_center.x)/(cam_x_size/2) * tan(HFOV/2)) - atan((double)(boundRect.br().x - cam_center.x)/(cam_x_size/2) * tan(HFOV/2)));
		precLandMsg.size_y = abs( atan((double)(boundRect.tl().y - cam_center.y)/(cam_y_size/2) * tan(VFOV/2)) - atan((double)(cam_center.y - boundRect.br().y)/(cam_y_size/2) * tan(VFOV/2)));
		precLandMsg.angle_x = atan((double)(centroid.x - cam_center.x)/(cam_x_size/2) * tan(HFOV/2));
		precLandMsg.angle_y = atan((double)(centroid.y - cam_center.y)/(cam_y_size/2) * tan(VFOV/2));
		precLandMsg.distance = alt * sqrt(1 + tan(precLandMsg.angle_x)*tan(precLandMsg.angle_x) + tan(precLandMsg.angle_y)* tan(precLandMsg.angle_y));
		precland_pub_.publish(precLandMsg);
		
		//sensor_msgs::ImagePtr elp_marked = cv_bridge::CvImage(std_msgs::Header(), "mono8", src).toImageMsg();
		//precland_display_.publish(elp_marked);

		std::string text = "Angle x: " + std::to_string(precLandMsg.angle_x) + " Angle y: " + std::to_string(precLandMsg.angle_y);
		cv::putText(inputImg, text, cv::Point(25,35), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.0, cv::Scalar(255,255,255), 1, cv:: LINE_AA);
		cv::putText(inputImg, std::to_string(largestArea), cv::Point(25,inputImg.size().height - 50), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.0, cv::Scalar(255,255,255), 1, cv:: LINE_AA);
		
	}

	else {
		cv::putText(inputImg, "Not detected", cv::Point(25,35), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.0, cv::Scalar(255,255,255), 1, cv:: LINE_AA); 
		ROS_DEBUG_STREAM_THROTTLE(5, "ELP scanned area = " << largestArea << ". It's < " << minimumArea);
	}

	// cv::imshow("cam", inputImg);
	// cv::waitKey(3);

}

void ImageProcessor::getDistX(cv::Mat& inputImg)
{
/*	
	std::vector<std::vector<cv::Point>> contours;
	contours = detectContour(inputImg, "Red");

	int largestIndex = -1;
	double largestArea = 0;
	int minimumArea = 500;

	cv::Rect largestBoundRect;
	// cv::Point largestCentroid;

	/*
	for (size_t i=0; i<contours.size(); i++)
	{
		double area = cv::contourArea(contours[i]);
		if (area > largestArea)
		{
			largestArea = area;
			largestIndex = i;
		}
	}



	for (size_t i=0; i<contours.size(); i++)
	{
		double area = cv::contourArea(contours[i]);
		if(area > minimumArea) {
            std::vector<cv::Point> contour_poly;
            cv::approxPolyDP(contours[i], contour_poly, 3, true);
            cv::Rect boundRect = cv::boundingRect(contour_poly);

            std::vector<cv::Rect> surrounding = surroundingArea(inputImg, boundRect);
            
            int green = 0;
            for(size_t j = 0; j < surrounding.size(); j++) {
                if(isGreen(inputImg, surrounding[j])) {
                    green++;
                } 
            }

            if(green >= 2 && area > largestArea) {
                largestArea = area;
                largestIndex = i;
				largestBoundRect = boundRect;
			}
			else if(green == 1 && boundRect.width > 0.95 * inputImg.cols && area > largestArea) {
				largestArea = area;
                largestIndex = i;
				largestBoundRect = boundRect;
			}
			else if(area > largestArea && area > inputImg.cols*inputImg.rows*0.7) {
				largestArea = area;
                largestIndex = i;
				largestBoundRect = boundRect;
			}
		}
	}

	std_msgs::Float64 distx;
	if (largestArea > minimumArea)
	{
		std::vector<cv::Point> contour;
		contour = contours[largestIndex];
		cv::Moments M = cv::moments(contour, true);
		int row = M.m01/M.m00; // baris centroid sebagai acuan

		cv::drawContours(inputImg, contours, largestIndex, cv::Scalar(0,255,0));
		// std::vector<cv::Point> contour_poly;
		// cv::approxPolyDP(contours[largestIndex], contour_poly, 3, true);
		// cv::Rect boundRect = cv::boundingRect(contour_poly);
		cv::rectangle(inputImg, largestBoundRect, cv::Scalar(255,255,0), 2 );

		bool found_start = false;
		bool found_end = false;
		cv::Point start, mid, end;
		int i = 0;
		while (i < inputImg.cols && !found_start) {
			if (cv::pointPolygonTest(contour, cv::Point(i,row), false) == 0) {
				found_start = true;
				start = cv::Point(i,row);
			}
			i++;
		}

		while (i < inputImg.cols && cv::pointPolygonTest(contour, cv::Point(i,row), false) == 0) {
			i++;
		} // Skip in case beberapa point ada di edge contour

		while (i < inputImg.cols && !found_end) {
			if (cv::pointPolygonTest(contour, cv::Point(i,row), false) == 0) {
				found_end = true;
				end = cv::Point(i,row);
			}
			i++;
		}

		mid = cv::Point((start.x+end.x)/2, row);
		cv::circle( inputImg, mid, 3, cv::Scalar(0,255,0), cv::FILLED );
		// 
		std::vector<cv::Point> contour_poly;
	  	cv::Point2f centroid;
	  	float radius;
	  	cv::approxPolyDP(contours[largestIndex], contour_poly, 3, true);
	  	cv::minEnclosingCircle(contour_poly, centroid, radius);
	*/

	cv::Point target = cv::Point(inputImg.size().width / 2, inputImg.size().height / 2); //PDM
	cv::circle(inputImg, target, 3, cv::Scalar(255,0,0), cv::FILLED);

	std::vector<std::vector<cv::Point>> contours;
	contours = detectContour(inputImg, "Red");

	int largestIndex = -1;
	double largestArea = 0;
	for (size_t i=0; i<contours.size(); i++)
	{
		double area = cv::contourArea(contours[i]);
		if (area > largestArea)
		{
			largestArea = area;
			largestIndex = i;
		}
	}

	if (largestArea > minimumArea) {
		cv::Moments M = cv::moments(contours[largestIndex], true);
		cv::Point centroid = cv::Point(int(M.m10/M.m00), int(M.m01/M.m00));
		
		cv::circle(inputImg, centroid, 4, cv::Scalar(0,255,0), cv::FILLED);
		cv::drawContours(inputImg, contours, largestIndex, cv::Scalar(0,255,0));

		int imgArea = inputImg.rows * inputImg.cols;
		double percent_red = (largestArea * 100) / imgArea;

		std::vector<cv::Point> contour_poly;
		cv::Point2f center;
		float radius;
		cv::approxPolyDP(contours[largestIndex], contour_poly, 3, true);
		cv::minEnclosingCircle(contour_poly, center, radius);
		double halfSide = radius * 0.707107;
		std::string namaGedung = gedung;
		if (gedung[0] == 'B'){
			if (gedung[1] == '1' || gedung[1] == '2'){
				centroid.y = centroid.y + (2 * halfSide * 0.2);
			}
			else if (gedung[1] == '3' || gedung[1] == '4'){
				centroid.y = centroid.y - (2 * halfSide * 0.1);
			}
		}
		else if (gedung[0] == 'A' || gedung[0] == 'C') {
			centroid.y = centroid.y - (2 * halfSide * 0.2);

		}



		uav_msgs::PrecLoit precLoitMsg;
		double alt = rf_alt;
	  	precLoitMsg.size_x = abs( atan((double)((centroid.x - halfSide) - cam_center.x)/(cam_x_size/2) * tan(HFOV/2)) - atan((double)((centroid.x + halfSide) - cam_center.x)/(cam_x_size/2) * tan(HFOV/2)));
	  	precLoitMsg.size_y = abs( atan((double)((centroid.y + halfSide) - cam_center.y)/(cam_y_size/2) * tan(VFOV/2)) - atan((double)(cam_center.y - (centroid.y - halfSide))/(cam_y_size/2) * tan(VFOV/2)));
	  	precLoitMsg.angle_x = atan((double)(centroid.x - cam_center.x)/(cam_x_size/2) * tan(HFOV/2));
	  	precLoitMsg.angle_y = atan((double)(centroid.y - cam_center.y)/(cam_y_size/2) * tan(VFOV/2));
	  	precLoitMsg.distance = alt * sqrt(1 + tan(precLoitMsg.angle_x) * tan(precLoitMsg.angle_x) + tan(precLoitMsg.angle_y) * tan(precLoitMsg.angle_y));

		distX_pub_.publish(precLoitMsg);
		
		/*
		double square_side = 0.5;
		distx.data = (double) square_side/(end.x-start.x) * (mid.x - inputImg.cols/2);

		distX_pub_.publish(distx);
		// ROS_INFO_STREAM("distx = " << distx.data);
		*/
		// cv::putText(inputImg, std::to_string(distx.data), cv::Point(25,35), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.0, cv::Scalar(255,255,255), 1, cv:: LINE_AA); 
		std::string text = "Angle x: " + std::to_string(precLoitMsg.angle_x) + " Angle y: " + std::to_string(precLoitMsg.angle_y);
		cv::putText(inputImg, text, cv::Point(25,35), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.0, cv::Scalar(255,255,255), 1, cv:: LINE_AA);
		cv::putText(inputImg, std::to_string(largestArea), cv::Point(25,inputImg.size().height - 50), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.0, cv::Scalar(255,255,255), 1, cv:: LINE_AA);
		
	}
	else {
		//distx.data = 0.0;
		cv::putText(inputImg, "Not detected", cv::Point(25,35), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.0, cv::Scalar(255,255,255), 1, cv:: LINE_AA); 
		ROS_DEBUG_STREAM_THROTTLE(5, "DZ scanned area = " << largestArea << ". It's < " << minimumArea);
	}

	cv::imshow("cam", inputImg);
	cv::waitKey(3);
	
	//distX_pub_.publish(distx);
}


void ImageProcessor::decode(cv::Mat &im, std::vector<env_percept::ImageProcessor::decodedObject> &decodedObjects)
{
	// Create zbar scanner
	zbar::ImageScanner scanner;

	// Configure scanner
	scanner.set_config(zbar::ZBAR_QRCODE, zbar::ZBAR_CFG_ENABLE, 1);

	cv::Mat imGray;
	cv::cvtColor(im, imGray,cv::COLOR_BGR2GRAY);

	// Wrap image data in a zbar image
	zbar::Image image(im.cols, im.rows, "Y800", (uchar *)imGray.data, im.cols * im.rows);

	// Scan the image for barcodes and QRCodes
	int n = scanner.scan(image);

	// Print results
	for(zbar::Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol)
	{
		env_percept::ImageProcessor::decodedObject obj;
		obj.data = symbol->get_data();

		for(int i = 0; i< symbol->get_location_size(); i++) 
		{
			obj.location.push_back(cv::Point(symbol->get_location_x(i),symbol->get_location_y(i)));
		}

		//ROS_INFO("DETECTED, %s", obj.data.c_str());
		decodedObjects.push_back(obj);
	}
	//ROS_INFO_STREAM("DETECTED! QR Data: " << decodedObjects[0].data);
//	ROS_DEBUG_STREAM_THROTTLE(3, "Good. Now publishing QR Data");
	std_msgs::String QRData;
	if (decodedObjects.size() > 0) {
		QRData.data = decodedObjects.at(0).data;
		qr_pub_.publish(QRData);
//		ROS_DEBUG_STREAM_THROTTLE(3, "Good. Done publishing");
	}
}


void ImageProcessor::display(cv::Mat &im, std::vector<env_percept::ImageProcessor::decodedObject> &decodedObjects)
{
	if (decodedObjects.size() > 0) 
	{
		cv::putText(im, 
					decodedObjects[0].data,
					cv::Point(25,35), // Coordinates (Bottom-left corner of the text string in the image)
					cv::FONT_HERSHEY_COMPLEX_SMALL, // Font
					1.0, // Scale. 2.0 = 2x bigger
					cv::Scalar(255,255,255), // BGR Color
					1, // Line Thickness (Optional)
					cv::LINE_AA); // Anti-alias (Optional, see version note)
		
		decodedObjects.clear();
	}
	else 
	{
		cv::putText(im, 
					"Not detected",cv::Point(25,35), 
					cv::FONT_HERSHEY_COMPLEX_SMALL, 1.0, 
					cv::Scalar(255,255,255), 1, 
					cv:: LINE_AA); 
	}
}

std::vector<std::vector<cv::Point>> ImageProcessor::detectContour(cv::Mat inputImg, std::string color)
{
	cv::Mat inputHsv, inputBnw, inputThresh1, inputThresh2, inputThresh;

	//cv::GaussianBlur(inputImg, inputImg, cv::Size(7, 7), 0, 0); 
	cv::cvtColor(inputImg, inputHsv, cv::COLOR_BGR2HSV);

	if ( color == "Red" )
	{
		cv::inRange(inputHsv, cv::Scalar(calibratedColors.at("Red1").lowVal,50,50), cv::Scalar(calibratedColors.at("Red1").highVal,255,255), inputThresh1);	// Red+
		cv::inRange(inputHsv, cv::Scalar(calibratedColors.at("Red2").lowVal,50,50), cv::Scalar(calibratedColors.at("Red2").highVal,255,255), inputThresh2); // Red-
		inputThresh = inputThresh1 + inputThresh2;
	}
	else if (color == "Yellow")
	{	
		// Menambahkan Thresh binary dari inputBNW karena Kondisi Outdoor
		cv::cvtColor(inputImg, inputBnw, cv::COLOR_BGR2GRAY);
		cv::threshold(inputBnw, inputThresh1, 130, 255, cv::THRESH_BINARY); 
		// -------
		cv::inRange(inputHsv, cv::Scalar(calibratedColors.at(color).lowVal, 50, 50), cv::Scalar(calibratedColors.at(color).highVal, 255, 255), inputThresh2);
		inputThresh = inputThresh1 + inputThresh2;

	}
	else {
		cv::inRange(inputHsv, cv::Scalar(calibratedColors.at(color).lowVal, 70, 70), cv::Scalar(calibratedColors.at(color).highVal, 255, 255), inputThresh);
	}
	

	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(10,10));
	cv::erode(inputThresh, inputThresh, kernel);
	cv::dilate(inputThresh, inputThresh, kernel);

	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(inputThresh, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

	return contours;	
}

void ImageProcessor::getQrPos(cv::Mat& inputImg) {
	cv::Mat src_roi, src_hsv, src_thresh;

	cv::Rect roi(1, 0.2 * inputImg.rows, inputImg.cols - 1, 0.6 * inputImg.rows);
    src_roi = inputImg(roi);
    //cv::rectangle(inputImg, roi, cv::Scalar(255), 1, 8, 0);
        src_roi = saturate(src_roi);

	//cv::GaussianBlur(inputImg, inputImg, cv::Size(7, 7), 0, 0); 
	//cv::cvtColor(src_roi, src_hsv, cv::COLOR_BGR2HSV);
    //cv::inRange(src_hsv, cv::Scalar(0,0,180), cv::Scalar(180, 63, 255), src_thresh);

	cv::inRange(src_roi, cv::Scalar(150,150,150), cv::Scalar(255,255,255), src_thresh);

	//cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(10,10));
	//cv::erode(src_thresh, src_thresh, kernel);
	//cv::dilate(src_thresh, src_thresh, kernel);

	std::vector<std::vector<cv::Point> > contours;
	cv::findContours(src_thresh, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

	int largestIndex = -1;
	double largestArea = 0;
	for (size_t i=0; i<contours.size(); i++)
	{
		double area = cv::contourArea(contours[i]);
		if (area > largestArea)
		{
			largestArea = area;
			largestIndex = i;
		}
	}
	
	int minimumArea = 200;             //DITENTUKAN SECARA MANUAL !!

	if (largestArea > minimumArea)
	{
		int i = largestIndex;

		cv::drawContours(inputImg, contours, i, cv::Scalar(0,255,0));
		std::vector<cv::Point> contour_poly;
		cv::approxPolyDP(contours[i], contour_poly, 3, true);
		cv::Rect boundRect = cv::boundingRect(contour_poly);
		cv::Rect newBoundRect (boundRect.tl().x, boundRect.tl().y + (0.2 * inputImg.rows), boundRect.br().x - boundRect.tl().x, (boundRect.br().y - boundRect.tl().y) );
        cv::Point paper_center = cv::Point(newBoundRect.x+0.5*newBoundRect.width, newBoundRect.y+0.5*newBoundRect.height);

		cv::rectangle(inputImg, newBoundRect.tl(), newBoundRect.br(), cv::Scalar(255,255,0), 2);
		cv::circle(inputImg, paper_center, 3, cv::Scalar(0,255,0), cv::FILLED);

		// Intinya ini nanti pake titik tengah kameranya, nanti variabelnya bisa diubah
		cv::Point cam_center = cv::Point(inputImg.cols/2, inputImg.rows/2);

		// Just in case cek konsistensi meter per pixel dari dua sumbu kertas
		double x_mpp = 0.21/newBoundRect.width;
		double y_mpp = 0.297/newBoundRect.height;
		float consistency = abs(x_mpp - y_mpp)/y_mpp;
		
		if (consistency > 0.03) 
			ROS_WARN_STREAM("Inconsistent meter/pixel value, css = " << consistency);
		
		
		double x = x_mpp * (paper_center.x - cam_center.x);  // Kalau + maka drone harus bergerak ke kanan
		double y = y_mpp * (-paper_center.y + cam_center.y); // Kalau + maka drone harus bergerak ke bawah
		// dist_meter = meter/pixel * dist_pixel (ukuran kertas A4)
		uav_msgs::DzPosition positionQr;
		positionQr.dist_x = x;
		positionQr.dist_y = y;
		qrPos_pub_.publish(positionQr);

		ROS_INFO_STREAM("x= " << x << ", y = " << y);
	}
	else {
		cv::putText(inputImg, "Not detected", cv::Point(25,35), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.0, cv::Scalar(255,255,255), 1, cv:: LINE_AA); 
	}
}

cv::Mat ImageProcessor::saturate(cv::Mat src)
{
    cv::Mat new_image = cv::Mat::zeros( src.size(), src.type() );
        double alpha = 1.0; /*< Simple contrast control */
        int beta = 80;       /*< Simple brightness control */
        //std::cout << " Basic Linear Transforms " << std::endl;
        //std::cout << "-------------------------" << std::endl;
        //std::cout << "* Enter the alpha value [1.0-3.0]: "; std::cin >> alpha;
        //std::cout << "* Enter the beta value [0-100]: ";    std::cin >> beta;
        for( int y = 0; y < src.rows; y++ ) {
            for( int x = 0; x < src.cols; x++ ) {
                for( int c = 0; c < src.channels(); c++ ) {
                    new_image.at<cv::Vec3b>(y,x)[c] =
                    cv::saturate_cast<uchar>( alpha*src.at<cv::Vec3b>(y,x)[c] + beta );
                }
            }
        }
    return new_image;
}

bool ImageProcessor::isGreen(const cv::Mat image, cv::Rect roi)
{
	cv::Mat handledImage;
	cv::cvtColor(image, handledImage, cv::COLOR_BGR2HSV);
	cv::Scalar mean = cv::mean(handledImage(roi));
	return (mean[0] >= 45 && mean[0] <= 91 && mean[1] > 50 && mean[2] > 50);
}

std::vector<cv::Rect> ImageProcessor::surroundingArea (cv::Mat image, cv::Rect rect) {
    cv::Mat roi = image(rect);

    std::vector<cv::Rect> surrounding;

    cv::Rect left_area((rect.tl().x-(rect.size().width*0.2)),rect.tl().y, rect.size().width*0.2, rect.size().height);
    if(rect.tl().x-(rect.size().width*0.2)>0) {
        surrounding.push_back(left_area);
    }
    
    cv::Rect right_area(rect.br().x, rect.tl().y, rect.size().width*0.2, rect.size().height);
    if(rect.br().x+rect.size().width*0.2 < image.cols) {
        surrounding.push_back(right_area);
    }
    
    cv::Rect top_area(rect.tl().x, rect.tl().y-(rect.size().height*0.2), rect.size().width, rect.size().height*0.2);
    if(rect.tl().y-(rect.size().height*0.2) > 0) {
        surrounding.push_back(top_area);
    }
    
    cv::Rect bottom_area(rect.tl().x, rect.br().y, rect.size().width, rect.size().height*0.2);
    if(rect.br().y+rect.size().height*0.2 < image.rows) {
        surrounding.push_back(bottom_area);
    }
    
    return surrounding;
}



}
