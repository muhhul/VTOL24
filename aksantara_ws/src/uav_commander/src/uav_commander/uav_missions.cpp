#include <uav_commander/uav_missions.hpp>

namespace uav_commander
{

int armThrottle(const uav_msgs::MissionParams &m, ros::NodeHandle &nh)
{
	ROS_WARN("---Arming---");

	ros::ServiceClient client { nh.serviceClient<mavros_msgs::CommandBool>("/mavros/cmd/arming") };
	mavros_msgs::CommandBool srv;
	mavros_msgs::State curr_state;
	ros::Duration dur(config.doubles.at("SERVICE_RETRY_DUR"));
	srv.request.value = true;

	// The only way to exit this loop with no error is when curr_state.armed = true
	uint8_t count = 0;
	do {
		count++;
		if (count > config.ints.at("SERVICE_RETRY_N")) {
			ROS_FATAL("---Arming failed---");
			return (int) Errors::UNRESPONSIVE_SERVICE;
		}

		if (!client.call(srv)) {
			ROS_WARN("---Arming failed, retrying...---");
		}
		dur.sleep();

		int gotTopic = getTopicValue(curr_state, "/mavros/state", config.doubles.at("WAIT_MSG_TIMEOUT"));
		if (gotTopic != 0) {
			ROS_FATAL_STREAM("Terminate in func " << __func__);
			return gotTopic;
		}
	} while (!curr_state.armed);

	ROS_WARN("---Armed---");
	return (int) Errors::NO_ERROR;
}

int disarmThrottle(const uav_msgs::MissionParams &m, ros::NodeHandle &nh)
{
	ROS_INFO("---Disarming---");

	ros::ServiceClient client { nh.serviceClient<mavros_msgs::CommandBool>("/mavros/cmd/arming") };
	mavros_msgs::CommandBool srv;
	mavros_msgs::State curr_state;
	ros::Duration dur(config.doubles.at("SERVICE_RETRY_DUR"));
	srv.request.value = false;

	// The only way to exit this loop with no error is when curr_state.armed = false
	uint8_t count = 0;
	do {
		count++;
		if (count > config.ints.at("SERVICE_RETRY_N")) {
			ROS_FATAL("---Disarming failed---");
			return (int) Errors::UNRESPONSIVE_SERVICE;
		}
		
		if (!client.call(srv)) {
			ROS_WARN("---Disarming failed, retrying...---");
		}
		dur.sleep();

		int gotTopic = getTopicValue(curr_state, "/mavros/state", config.doubles.at("WAIT_MSG_TIMEOUT"));
		if (gotTopic != 0) {
			ROS_FATAL_STREAM("Terminate in func " << __func__);
			return gotTopic;
		}
	} while (curr_state.armed);

	ROS_WARN("---Disarmed---");
	return (int) Errors::NO_ERROR;
}

int takeoff(const uav_msgs::MissionParams &m, ros::NodeHandle &nh)
{
	if (!checkArgs(m, M_DOUBLES, 1)) return (int) Errors::INVALID_ARGUMENT;

	ROS_WARN("---Take off initiated---");

	ros::ServiceClient client{ nh.serviceClient<mavros_msgs::CommandTOL>("/mavros/cmd/takeoff") };
	mavros_msgs::CommandTOL srv;
	srv.request.yaw = 0.0;
	srv.request.altitude = m.doubles[0];
	bool takeoffStarted = false;
	double relAlt = 0.0;
	sensor_msgs::Range initialAlt;
	ros::Duration dur(config.doubles.at("TAKEOFF_RETRY_DUR"));

	uint8_t version = config.ints.at("TAKEOFF_VER");
	if (version == 2) {
		if (config.strings.at("TOL_ALT_SRC") != "rangefinder") {
			ROS_ERROR("Takeoff ver 2 can only use rangefinder!");
			return (int) Errors::CONFIG_ERROR;
		}		

		std::string topicName = config.strings.at("RF_BAWAH_SRC");
		int gotInitial = getTopicValue(initialAlt, topicName, config.doubles.at("WAIT_MSG_TO_LONG"));
		if (gotInitial != 0) {
			ROS_FATAL_STREAM("Terminate in function " << __func__);
			return gotInitial;
		}
	}

	if (version != 1 && version != 2) {
		ROS_FATAL("Check config file!");
		return (int) Errors::CONFIG_ERROR;
	}

	uint8_t count = 0;
	do {
		count++;
		if (count > config.ints.at("SERVICE_RETRY_N")) {
			ROS_FATAL("---Takeoff failed---");
			return (int) Errors::UNRESPONSIVE_SERVICE;
		}

		if (!client.call(srv)) {
			ROS_WARN("---Takeoff failed, retrying...---");
			dur.sleep();
			continue;	// If mavros failed to send MAV_CMD_TAKEOFF, no need check alt
		}
		dur.sleep();

		int gotAlt = getAltitude(relAlt, config.strings.at("TOL_ALT_SRC"));
		if (gotAlt != 0) {
			ROS_FATAL_STREAM("Terminate in function " << __func__);
			return gotAlt;
		}

		if (version == 1) {
			if (relAlt > 0.5) takeoffStarted = true;
		}
		else {
			if (relAlt - initialAlt.range > 0.3) {
				takeoffStarted = true;
				ROS_DEBUG_STREAM_ONCE("Kickstart takeoff done coz alt = " << relAlt);
			}
			else
				ROS_DEBUG_STREAM_THROTTLE(1, "Kickstarting takeoff... alt = " << relAlt);
		}
	} while (!takeoffStarted);
	// So you have 3*dur seconds to check if altitude has passed 0.5

	if (version == 1)
		return waitAltitude(m.doubles[0], config.strings.at("TOL_ALT_SRC"));
	else {
		uav_msgs::MissionParams mp;
		mp.doubles.push_back(0.0);
		mp.doubles.push_back(0.0);
		mp.doubles.push_back(m.doubles[0]);
		mp.doubles.push_back(0.0);
		mp.doubles.push_back(0.0);
		mp.doubles.push_back(-0.7);
		mp.doubles.push_back(-0.7);
		return indoorGoTo(mp, nh);
	}
}

int land(const uav_msgs::MissionParams &m, ros::NodeHandle &nh)
{
    ROS_WARN("---Landing initiated.---");

    uav_msgs::MissionParams mp;
    mp.strings.push_back("LAND");
	int switched = switchMode(mp, nh);
	if (switched != 0) {
		ROS_FATAL_STREAM("Terminate in function " << __func__);
		return switched;
	}

	// Wait until landed
	mp.strings.clear();
	mp.doubles.push_back(0.0);
	return waitAltitude(0.5, config.strings.at("TOL_ALT_SRC"));
}

// List of available modes: http://wiki.ros.org/mavros/CustomModes#APM:Copter
int switchMode(const uav_msgs::MissionParams &m, ros::NodeHandle &nh)
{
	if (!checkArgs(m, M_STRINGS, 1)) return (int) Errors::INVALID_ARGUMENT;

	ROS_WARN_STREAM("---Changing mode to " << m.strings[0] << "---" );

	ros::ServiceClient client{ nh.serviceClient<mavros_msgs::SetMode>("/mavros/set_mode") };
	mavros_msgs::SetMode srv;
	mavros_msgs::State curr_state;
	ros::Duration dur(config.doubles.at("SERVICE_RETRY_DUR"));

	srv.request.base_mode 	= 0;
	srv.request.custom_mode = m.strings[0];

	bool toGuided = false;
	if (m.strings[0] == "GUIDED" or m.strings[0] == "guided")
		toGuided = true;
	bool guidedWithVel = config.bools.at("GUIDED_WITH_VEL");

	ros::Publisher velPub;
	mavros_msgs::PositionTarget velMsg;
	ros::Timer timer;
	boost::function<void(const ros::TimerEvent &)> timerCb;
	ros::AsyncSpinner spinner(1);

	if (toGuided && guidedWithVel) {
		ROS_DEBUG("Changing to guided with velocity");
		velPub = nh.advertise<mavros_msgs::PositionTarget>("/mavros/setpoint_raw/local",
			1, true);
		velMsg.type_mask = 2503;
		velMsg.coordinate_frame = 1;
		velMsg.velocity.x = 0.0;
		velMsg.velocity.y = 0.0;
		velMsg.velocity.z = 0.0;
		velMsg.yaw = 1.5708;

		timerCb = [&] (const ros::TimerEvent &ev) {
			velPub.publish(velMsg);
			ROS_DEBUG_STREAM("Publishing vel 0 while switching Guided");
		};

		timer = nh.createTimer(ros::Duration(0.1), timerCb);
		spinner.start();
		ros::Duration(0.5).sleep();
	}

	// The only way to exit this loop with no error is when desired mode is reached
	uint8_t count = 0;
	do {
		count++;
		if (count > config.ints.at("SERVICE_RETRY_N")) {
			ROS_FATAL("---Mode changing failed. Terminate.---");
			return (int) Errors::UNRESPONSIVE_SERVICE;
		}

		if (!client.call(srv)) {
			ROS_WARN("---Mode changing failed, retrying...---");
		}
		dur.sleep();

		int gotTopic = getTopicValue(curr_state, "/mavros/state", config.doubles.at("WAIT_MSG_TIMEOUT"));
		if (gotTopic != 0) {
			ROS_FATAL_STREAM("Terminate in func " << __func__);
			return gotTopic;
		}
	} while (boost::algorithm::to_lower_copy(curr_state.mode) !=
			boost::algorithm::to_lower_copy(m.strings[0]));

	ROS_WARN_STREAM("---Mode successfully changed to " << m.strings[0] << "---");
	
	if (toGuided && guidedWithVel)
		ros::Duration(1.0).sleep();

	return (int) Errors::NO_ERROR;
}

// Simply wait for m.doubles[0] seconds.
int wait(const uav_msgs::MissionParams &m, ros::NodeHandle &nh)
{
	if (!checkArgs(m, M_DOUBLES, 1)) return (int) Errors::INVALID_ARGUMENT;

	ROS_WARN_STREAM("---Waiting for " << m.doubles[0] << " seconds.");

	double initialTime, currTime;
	do {
		initialTime = ros::Time::now().toSec();
	} while (initialTime < 1.0);    // Always need this.

	ros::Rate rate(20);    // Arbitrary
	ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/mavros/setpoint_velocity/cmd_vel_unstamped",
		1, true);
	geometry_msgs::Twist msg;
	msg.linear.x = 0;
	msg.linear.y = 0;
	msg.linear.z = 0;

	do {
		currTime = ros::Time::now().toSec();
		pub.publish(msg);
		rate.sleep();
	} while (currTime - initialTime < m.doubles[0]);

	return (int) Errors::NO_ERROR;
}

#if DEBUG_FUNCS


int testWASD(const uav_msgs::MissionParams &m, ros::NodeHandle &nh)
{
	ROS_WARN("---WASD Testing---");

    bool controlling	{ true }; 
	bool w				{ false };
	bool a				{ false };
	bool s				{ false };
	bool d				{ false };
	bool i				{ false };
	bool k				{ false };
	bool q				{ false };
	bool e				{ false };

	// Keyboard callback
	// Use type boost:function, coz nh.subscribe does not support usual lambda func
	boost::function<void(const uav_teleop::Key&)> keyDownCb= [&](const uav_teleop::Key &msg){
		switch(msg.code){
			case uav_teleop::Key::KEY_w:
				w = true;
				ROS_WARN("Moving forward");
				break;
			case uav_teleop::Key::KEY_a:
				a = true;
				ROS_WARN("Moving left");
				break;
			case uav_teleop::Key::KEY_s:
				ROS_WARN("Moving backward");
				s = true;
				break;
			case uav_teleop::Key::KEY_d:
				ROS_WARN("Moving right");
				d = true;
				break;
			case uav_teleop::Key::KEY_i:
				ROS_WARN("Moving up");
				i = true;
				break;
			case uav_teleop::Key::KEY_k:
				ROS_WARN("Moving down");
				k = true;
				break;
			case uav_teleop::Key::KEY_q:
				ROS_WARN("Yawing CCW");
				q = true;
				break;
			case uav_teleop::Key::KEY_e:
				ROS_WARN("Yawing CW");
				e = true;
				break;
			case uav_teleop::Key::KEY_ESCAPE:
				ROS_WARN("Stopping...");
				controlling = false;
				break;
		}
	};
	boost::function<void(const uav_teleop::Key&)> keyUpCb= [&](const uav_teleop::Key &msg){
		switch(msg.code){
			case uav_teleop::Key::KEY_w:
				w = false;
				break;
			case uav_teleop::Key::KEY_a:
				a = false;
				break;
			case uav_teleop::Key::KEY_s:
				s = false;
				break;
			case uav_teleop::Key::KEY_d:
				d = false;
				break;
			case uav_teleop::Key::KEY_i:
				i = false;
				break;
			case uav_teleop::Key::KEY_k:
				k = false;
				break;
			case uav_teleop::Key::KEY_q:
				q = false;
				break;
			case uav_teleop::Key::KEY_e:
				e = false;
				break;
		}
	};

	// Initialize key subscribers
	ros::Subscriber keyUp { nh.subscribe<uav_teleop::Key>("/keyboard/keyup", 1, keyUpCb) };
	ros::Subscriber keyDown { nh.subscribe<uav_teleop::Key>("/keyboard/keydown", 1, keyDownCb) };

	// So that the buffer won't overload, but still reasonably snappy
	ros::Rate rate(20);
	
	// Initialize setpoint velocity publisher
	ros::Publisher setpointVelPub 	{ nh.advertise<geometry_msgs::Twist>("/mavros/setpoint_velocity/cmd_vel_unstamped", 1, true) };
	
	geometry_msgs::Twist velocity_msg; // used to store setpoint msgsb
	constexpr double velocity		{ 0.50 }; // Intended final absolute velocity in m/s // INGAT DIGANTI!!!
	constexpr double angularv		{ 0.20 };

	// Read values and update control accordingly
	double vy;
	double vx;
	double vz;
	double rv; //omega
	double abs_v;
	while(controlling) {
		// Handle control values for each axis, + 0 to prevent NaN.
		vx = (a*-1) + (d*1) + 0;
		vy = (s*-1) + (w*1) + 0;
		vz = (k*-1) + (i*1) + 0;

		rv = ((e*-1) + (q*1) + 0) * angularv;

		if (w || a || s || d || i || k){
			// Can't normalize if all is zero. Amirite?
			abs_v = sqrt( (vy*vy) + (vx*vx) + (vz*vz) );

			vy = (vy/abs_v) * velocity;
			vx = (vx/abs_v) * velocity;
			vz = (vz/abs_v) * velocity;
		}

		velocity_msg.linear.z = vz;
		velocity_msg.linear.y = vy;
		velocity_msg.linear.x = vx;
		velocity_msg.angular.z = rv;

		// Publishing message
		if ( setpointVelPub.getNumSubscribers() > 0 ){
			setpointVelPub.publish(velocity_msg);
		}

		rate.sleep();
		ros::spinOnce();
	}
	
    // If it reached this point, then testing finished
	ROS_WARN("---Testing WASD finished---");
	return (int) Errors::NO_ERROR;
}


#endif


#if VTOL21_FUNCS

int indoorPreinitialize(const uav_msgs::MissionParams &m, ros::NodeHandle &nh) {
	// Check some pid params
	// Note: lower_limit must = -upper_limit
	// if (!nh.hasParam("/pid/vel_x_long/pid_velxl/upper_limit") ||
	// 	!nh.hasParam("/pid/vel_y_long/pid_velyl/upper_limit") ||
	// 	!nh.hasParam("/pid/vel_z_long/pid_velzl/upper_limit") ||
	// 	!nh.hasParam("/pid/vel_x_short/pid_velxs/upper_limit") ||
	// 	!nh.hasParam("/pid/vel_y_short/pid_velys/upper_limit") ||
	// 	!nh.hasParam("/pid/vel_z_short/pid_velzs/upper_limit")) {
	// 	ROS_FATAL("PID limits not retrieved.");
	// 	ROS_FATAL_STREAM("Terminate in function " << __func__);
	// 	return (int) Errors::CONFIG_ERROR;
	// }
	// double velXLUplim, velYLUplim, velZLUplim;
	// double velXSUplim, velYSUplim, velZSUplim;
	// nh.getParam("/pid/vel_x_long/pid_velxl/upper_limit", velXLUplim);
	// nh.getParam("/pid/vel_y_long/pid_velyl/upper_limit", velYLUplim);
	// nh.getParam("/pid/vel_z_long/pid_velzl/upper_limit", velZLUplim);
	// nh.getParam("/pid/vel_x_short/pid_velxs/upper_limit", velXSUplim);
	// nh.getParam("/pid/vel_y_short/pid_velys/upper_limit", velYSUplim);
	// nh.getParam("/pid/vel_z_short/pid_velzs/upper_limit", velZSUplim);
	// ROS_INFO_STREAM("velXLUplim = " << velXLUplim << ", velYLUplim = " << velYLUplim
	// 	<< ", velZLUplim = " << velZLUplim);
	// ROS_INFO_STREAM("velXSUplim = " << velXSUplim << ", velYSUplim = " << velYSUplim
	// 	<< ", velZSUplim = " << velZSUplim);
	// config.doubles.emplace("PID_VEL_XL_LIM", velXLUplim);
	// config.doubles.emplace("PID_VEL_YL_LIM", velYLUplim);
	// config.doubles.emplace("PID_VEL_ZL_LIM", velZLUplim);
	// config.doubles.emplace("PID_VEL_XS_LIM", velXSUplim);
	// config.doubles.emplace("PID_VEL_YS_LIM", velYSUplim);
	// config.doubles.emplace("PID_VEL_ZS_LIM", velZSUplim);

	// std_msgs::Bool togglePID;
	// togglePID.data = false;
	// waitAndPublish(togglePID, "/pid/vel_x_long/pid_enable", nh);
	// waitAndPublish(togglePID, "/pid/vel_y_long/pid_enable", nh);
	// waitAndPublish(togglePID, "/pid/vel_z_long/pid_enable", nh);
	// waitAndPublish(togglePID, "/pid/vel_x_short/pid_enable", nh);
	// waitAndPublish(togglePID, "/pid/vel_y_short/pid_enable", nh);
	// waitAndPublish(togglePID, "/pid/vel_z_short/pid_enable", nh);

	return (int) Errors::NO_ERROR;	
}

int indoorInitialize(const uav_msgs::MissionParams &m, ros::NodeHandle &nh)
{
    // Koordinat atap Sabuga
    constexpr float gpsOriginLat	{ -6.886783 };
    constexpr float gpsOriginLong	{ 107.608365 };
//    constexpr float gpsOriginAlt	{ 764.00 };

	ROS_WARN("---Injecting GPS Origin...");
	geographic_msgs::GeoPointStamped GPSOrigin;
	// Message header
	GPSOrigin.header.stamp			= ros::Time::now();
	GPSOrigin.header.frame_id		= "ekf_origin";
	GPSOrigin.position.latitude 	= gpsOriginLat;
	GPSOrigin.position.longitude 	= gpsOriginLong;
//	GPSOrigin.position.altitude 	= gpsOriginAlt;

	int published = waitAndPublish(GPSOrigin, "/mavros/global_position/set_gp_origin", nh);
	if (published != 0) {
		ROS_FATAL_STREAM("Terminate in function: " << __func__);
		return published;
	}
	ROS_WARN("---GPS Origin Injected---");    // !! Can be safer by checking global_position/gp_origin

	ros::ServiceClient setServoClient = nh.serviceClient<mavros_msgs::CommandLong>("/mavros/cmd/command");
	mavros_msgs::CommandLong setServoSrv;
	int loadPWM = config.ints.at("LOAD_PAYLOAD_PWM");
	std::vector<int> servoNums {config.ints.at("SERVO_A"), config.ints.at("SERVO_B"), config.ints.at("SERVO_C")};
	
	for (int nums : servoNums) {
		setServoSrv.request.command = 183;
		setServoSrv.request.param1 = nums;
		setServoSrv.request.param2 = loadPWM;
		// No need feedback check lah ya...
		setServoClient.call(setServoSrv);
		ROS_WARN_STREAM("---Payload servo " << nums << " successfully set up---");
	}

	// For reading pressed key
	boost::shared_ptr<const uav_teleop::Key> keyPtr;
	bool startMission = false;

	boost::function<void(const uav_teleop::Key&)> keyCb = [&] (const uav_teleop::Key &keyPress) {
		if (keyPress.code == uav_teleop::Key::KEY_f) {
			ROS_WARN("---Starting mission---");
			startMission = true;
		}
	};

	ROS_WARN("---Press f to start mission---");
	ros::Subscriber sub = nh.subscribe<uav_teleop::Key>("/keyboard/keydown", 10, keyCb);
	while (!startMission) {
		ros::spinOnce();
	}

	return (int) Errors::NO_ERROR;
}

int indoorGoTo(const uav_msgs::MissionParams &m, ros::NodeHandle &nh)
{
	// ONLY used for ROUGH go-to

	bool useLabel;
	uint8_t nArgs = 0;
	if (checkArgs(m, M_STRINGS, 1, false))
		useLabel = true;
	else if (checkArgs(m, M_STRINGS, 0, false)) {
		useLabel = false;
		if (checkArgs(m, M_DOUBLES, 1, false))
			nArgs = 1;
		else if (checkArgs(m, M_DOUBLES, 2, false))
			nArgs = 2;
		else if (checkArgs(m, M_DOUBLES, 3, false))
			nArgs = 3;
		else if (checkArgs(m, M_DOUBLES, 7, true))
			nArgs = 7;  // if use velocity, orientation is ignored
		else return (int) Errors::INVALID_ARGUMENT;
	}
	else return (int) Errors::INVALID_ARGUMENT;

	ros::Publisher setpointPub, offsetPub;
	ros::Subscriber stateSub, stateZSub, stateYSub;
	const std::string setpointTopic = "/uav_commander/cmd_vel/setpoint";
	const std::string offsetTopic = "/uav_commander/cmd_vel/abs_offset";
	double offX, offY, offZ;
	geometry_msgs::Pose setpointMsg;
	bool rigidMove = config.bools.at("RIGID_MOVE");
	bool fullRf, halfRigid;
	if (checkArgs(m, M_BOOLS, 0, false)) {
		fullRf = false;
		halfRigid = false;
	}
	else if (checkArgs(m, M_BOOLS, 1, false)) {
		fullRf = m.bools.at(0);
	}
	else if (checkArgs(m, M_BOOLS, 2, true)) {
		fullRf = m.bools.at(0);
		halfRigid = m.bools.at(1);
	}
	else {
		ROS_FATAL_STREAM("Terminate in function " << __func__);
		return (int) Errors::INVALID_ARGUMENT;
	}

	bool usePosition;
	if (config.strings.at("INDOORGOTO_METHOD") == "position")
		usePosition = true;
	else {
		usePosition = false;
		setpointPub = nh.advertise<geometry_msgs::Pose>(setpointTopic, 1, false);
		offsetPub = nh.advertise<std_msgs::Float64>(offsetTopic, 1, false);

		sensor_msgs::Range currAlt;
		boost::function<void(const sensor_msgs::Range &)> stateZCb = 
			[&] (const sensor_msgs::Range &msg) {
			currAlt.range = msg.range;
		};
		stateZSub = nh.subscribe<sensor_msgs::Range>(
			config.strings.at("RF_BAWAH_SRC"), 1, stateZCb);

		sensor_msgs::Range currY;
		boost::function<void(const sensor_msgs::Range &)> stateYCb =
			[&] (const sensor_msgs::Range &msg) {
			if (msg.range >= 0.3 && msg.range <= 12.0) {
				currY.range = msg.range;
				// A question:
				// tried to use currY = msg. The program can't run afterward. why?
			}
		};
		stateYSub = nh.subscribe<sensor_msgs::Range>(
			config.strings.at("RF_DEPAN_SRC"), 1, stateYCb);

		double maxY = config.doubles.at("ARENA_MAX_Y");
		boost::function<void(const geometry_msgs::PoseStamped &)> stateCb =
			[&] (const geometry_msgs::PoseStamped &msg) {
			offX = setpointMsg.position.x - msg.pose.position.x;
			if (!fullRf)
				offY = setpointMsg.position.y - msg.pose.position.y;
			else
				offY = setpointMsg.position.y - (maxY - currY.range);
			offZ = setpointMsg.position.z - currAlt.range;
			std_msgs::Float64 offsetMsg;
			offsetMsg.data = sqrt(pow(offX, 2) + pow(offY, 2) + pow(offZ, 2));
			setpointPub.publish(setpointMsg);
			offsetPub.publish(offsetMsg);
		};
		stateSub = nh.subscribe<geometry_msgs::PoseStamped>("/mavros/vision_pose/pose", 1, stateCb);

		ros::AsyncSpinner spinner(2);
		spinner.start();
	}

	std::vector<double> coord;
	if (useLabel) {
		std::string gedung = m.strings[0];
		std::string offsetName = "DZ_" + gedung + "_OFF_";  // HURUF KAPITAL
		if (gedung == "B") {
			offsetName += std::to_string(config.ints.at("GEDUNG_B_ORD"));
		}
		coord.push_back(config.doubles.at("GEDUNG_" + gedung + "_X"));
		coord.push_back(config.doubles.at("GEDUNG_" + gedung + "_Y")
			+ config.doubles.at(offsetName + "Y"));
		coord.push_back(config.doubles.at("PRECISE_" + gedung + "_Z")
			+ config.doubles.at(offsetName + "Z") +
			+ config.doubles.at("GLOB_Z_OFFSET"));
	}
	else {
		for (uint8_t i = 0; i < nArgs; i++) {
			coord.push_back(m.doubles[i]);
		}
	}
	// inspired by an accident
	// weird code but yaudah lah ya
	geometry_msgs::PoseStamped initialPose;
	int gotPose = getTopicValue(initialPose, "/mavros/vision_pose/pose",
		config.doubles.at("WAIT_MSG_TO_LONG"));
	if (gotPose != 0) {
		ROS_FATAL_STREAM("Terminate in function " << __func__);
		return gotPose;
	}
	bool consistent = true;
	for (uint8_t i = 0; i < 3; i++) {
		ros::Duration(0.1).sleep();
		geometry_msgs::PoseStamped tempPose;
		gotPose = getTopicValue(tempPose, "/mavros/vision_pose/pose",
			config.doubles.at("WAIT_MSG_TO_LONG"));
		if (gotPose != 0) {
			ROS_FATAL_STREAM("Terminate in function " << __func__);
			return gotPose;
		}
		if (fabs(initialPose.pose.position.x - tempPose.pose.position.x) > 0.6 ||
			fabs(initialPose.pose.position.y - tempPose.pose.position.y) > 0.6)
			consistent = false;
	}
	if (!consistent) {
		ROS_ERROR("Initial pose not consistent!!!\n");
		ROS_FATAL_STREAM("Terminate in function " << __func__);
		return (int) Errors::PARTIALLY_SUCCEEDED;
	}
	ROS_DEBUG_STREAM("nArgs = " << (unsigned) nArgs);
	double relAlt;
	int gotAlt = getAltitude(relAlt, "rangefinder");
	if (gotAlt != 0) {
		ROS_FATAL_STREAM("Terminate in function " << __func__);
		return gotAlt;
	}	
	if (nArgs == 1) {
		coord.push_back(0);
		coord.push_back(0);
		coord.at(2) = coord.at(0);
		coord.at(0) = initialPose.pose.position.x;
		coord.at(1) = initialPose.pose.position.y;
	}
	else if (nArgs == 2)
		coord.push_back(relAlt);
	// NOW coord.size() is guaranteed >= 3

	bool oneDim = false;  // only along z?
	if (fabs(coord[0] - initialPose.pose.position.x) < 0.4 &&
		fabs(coord[1] - initialPose.pose.position.y) < 0.4)
		oneDim = true;

	bool precise = useLabel;

	if (rigidMove && !oneDim) {
		double wantAlt = config.doubles.at("MISSION_ALT");
		wantAlt = std::max(relAlt, wantAlt);

		if (!halfRigid) {
		// step 1
		if (fabs(relAlt - wantAlt) > 0.3) {
			std::vector<double> intermediate;
			intermediate.push_back(initialPose.pose.position.x);
			intermediate.push_back(initialPose.pose.position.y);
			intermediate.push_back(wantAlt);
			if (nArgs == 7) {
				intermediate.push_back(coord.at(3));
				intermediate.push_back(coord.at(4));
				intermediate.push_back(coord.at(5));
				intermediate.push_back(coord.at(6));
			}
			int success;
			if (usePosition)
				success = positionGoTo(intermediate, nh, false);
			else {
				setpointMsg.position.x = intermediate.at(0);
				setpointMsg.position.y = intermediate.at(1);
				setpointMsg.position.z = intermediate.at(2);
				ROS_WARN_STREAM("---Going to (" << intermediate.at(0) << ", "
					<< intermediate.at(1) << ", " << intermediate.at(2) << ").---");
				success = velocityGoTo(setpointTopic, offsetTopic, nh, false, false,
					config.doubles.at("ROUGHER_ADD"), fullRf);
			}
			if (success != 0) {
				ROS_FATAL_STREAM("Terminate in function " << __func__);
				return success;
			}
		}
		}

		// step 2
		std::vector<double> intermediate2(coord);
		intermediate2[2] = wantAlt;

		int success;
		if (usePosition)
			success = positionGoTo(intermediate2, nh, false);
		else {
			setpointMsg.position.x = intermediate2.at(0);
			setpointMsg.position.y = intermediate2.at(1);
			setpointMsg.position.z = intermediate2.at(2);
			ROS_WARN_STREAM("---Going to (" << intermediate2.at(0) << ", "
				<< intermediate2.at(1) << ", " << intermediate2.at(2) << ").---");
			success = velocityGoTo(setpointTopic, offsetTopic, nh, false, false,
				config.doubles.at("ROUGHER_ADD"), fullRf);
		}			
		if (success != 0) {
			ROS_FATAL_STREAM("Terminate in function " << __func__);
			return success;
		}

		// step 3
		gotAlt = getAltitude(relAlt, "rangefinder");
		if (gotAlt != 0) {
			ROS_FATAL_STREAM("Terminate in function " << __func__);
			return gotAlt;
		}

		if (fabs(relAlt - coord[2]) > 0.3) {
			if (usePosition)
				return positionGoTo(coord, nh, false);
			else {
				setpointMsg.position.x = coord.at(0);
				setpointMsg.position.y = coord.at(1);
				setpointMsg.position.z = coord.at(2);
				ROS_WARN_STREAM("---Going to (" << coord.at(0) << ", "
					<< coord.at(1) << ", " << coord.at(2) << ").---");
				return velocityGoTo(setpointTopic, offsetTopic, nh, false, precise, 0.0, fullRf);
			}
		}
	}
	
	else {
		if (usePosition)
			return positionGoTo(coord, nh, false);
		else {
			setpointMsg.position.x = coord.at(0);
			setpointMsg.position.y = coord.at(1);
			setpointMsg.position.z = coord.at(2);
			ROS_WARN_STREAM("---Going to (" << coord.at(0) << ", "
				<< coord.at(1) << ", " << coord.at(2) << ").---");
			return velocityGoTo(setpointTopic, offsetTopic, nh, false, precise, 0.0, fullRf);
		}			
	}

	return (int) Errors::NO_ERROR;
}

// Takes one int: the servo instance number
int dropPayload(const uav_msgs::MissionParams &m, ros::NodeHandle &nh)
{
	if (!checkArgs(m, M_INTS, 1)) return (int) Errors::INVALID_ARGUMENT;

	ROS_WARN_STREAM("---Dropping payload " << m.ints[0] << "---");

	ros::ServiceClient client = nh.serviceClient<mavros_msgs::CommandLong>("/mavros/cmd/command");
	mavros_msgs::CommandLong srv;
	srv.request.command = 183;	// See https://mavlink.io/en/messages/common.html#MAV_CMD_DO_SET_SERVO
	srv.request.param1 = m.ints[0];
	srv.request.param2 = config.ints.at("DROP_PAYLOAD_PWM");

	// sensor_msgs::Range lidarDepan;
	// tidak perlu failsafe
	// getTopicValue(lidarDepan, config.strings.at("RF_DEPAN_SRC"), config.doubles.at("WAIT_MSG_TIMEOUT"));
	sensor_msgs::Range lidarBawah;
	getTopicValue(lidarBawah, config.strings.at("RF_BAWAH_SRC"), config.doubles.at("WAIT_MSG_TIMEOUT"));
	//std_msgs::Float64 xOffset;
	//getTopicValue(xOffset, "/odroid/image_percept/distX", config.doubles.at("WAIT_MSG_TIMEOUT"));
	geometry_msgs::PoseStamped nowPose;
	getTopicValue(nowPose, "/mavros/local_position/pose", config.doubles.at("WAIT_MSG_TIMEOUT"));

	ros::Duration dur(config.doubles.at("SERVICE_RETRY_DUR"));
	bool succeed;
	for (uint8_t i = 0, n = config.ints.at("SERVICE_RETRY_N"); i < n; i++) {
		if (i > 0)
			ROS_ERROR("Payload dropping command not responded. Retrying...");
		succeed = client.call(srv);
		if (succeed) {
			ROS_WARN("---Payload dropped---");
			// ROS_INFO_STREAM("Dropped at: x ~ " << xOffset.data <<
			// ", y ~ " << lidarDepan.range << ", z ~ " << lidarBawah.range);
			ROS_INFO_STREAM("Orient: x = " << nowPose.pose.orientation.x
			<< ", y = " << nowPose.pose.orientation.y << ", z = " <<
			nowPose.pose.orientation.z << ", w = " <<
			nowPose.pose.orientation.w);
			return (int) Errors::NO_ERROR;
		}
		dur.sleep();
	}

	ROS_WARN("Payload dropping command not responded!!!");
	return (int) Errors::NO_ERROR;	// No need to failsafe
}

int goToELP(const uav_msgs::MissionParams &m, ros::NodeHandle &nh)
{
	// Assumes 5x5 grid, user inputs (a, b) => a-th square from left, b-th square from bottom
	if (!checkArgs(m, M_INTS, 2)) return (int) Errors::INVALID_ARGUMENT;

	double posX, posY;
	posX = (m.ints[0] - 1) * 2 + 1.0;
	posY = (m.ints[1] - 1) * 2 + 1.0;
	const double origX = 5.0;
	const double origY = 0.5;

	double scanAlt = config.doubles.at("SCAN_ELP_ALT");
	uav_msgs::MissionParams mp;
	mp.doubles.push_back(posX - origX);
	mp.doubles.push_back(posY - origY);
	mp.doubles.push_back(scanAlt);
	mp.bools.push_back(true);
	ROS_INFO("Now will go to ELP");
	return indoorGoTo(mp, nh);
}

int precLand(const uav_msgs::MissionParams &m, ros::NodeHandle &nh)
{
	// Accepts one arg: wanna directly mode land from here?
	if (!checkArgs(m, M_BOOLS, 1)) return (int) Errors::INVALID_ARGUMENT;
	bool doLand = m.bools[0];  // false if for DEBUGGING (using remote)

	ROS_WARN("---Initiating precision landing---");

	// Calling ELP ON service
	ros::ServiceClient envClient = nh.serviceClient<uav_msgs::DetectObject>("/odroid/env_percept/detectObject");
	uav_msgs::DetectObject envSrv;
	envSrv.request.name = "ELP";
	uint8_t count = 0;
	do {
		envClient.call(envSrv);
		count++;
	} while (!envSrv.response.scanELP && count < config.ints.at("ENV_RETRY_N"));
	if (!envSrv.response.scanELP) {
		ROS_FATAL_STREAM("Cannot turn on scanELP Service!");
		return (int) Errors::UNRESPONSIVE_SERVICE;
	}
	
	ros::Publisher mavPrecLand = nh.advertise<mavros_msgs::LandingTarget>("/mavros/landing_target/raw", 1, true);
	mavros_msgs::LandingTarget landingTarget;
	bool called = false;

	boost::function<void(const uav_msgs::PrecLand &)> sendPrecLandCb = [&] (const uav_msgs::PrecLand &msg)
	{
		landingTarget.angle.at(0) = msg.angle_x;
		landingTarget.angle.at(1) = msg.angle_y;
		landingTarget.size.at(0) = msg.size_x;
		landingTarget.size.at(1) = msg.size_y;
		landingTarget.distance = msg.distance;
		mavPrecLand.publish(landingTarget);
		called = true;
	};

	ros::Subscriber sendPrecLand = nh.subscribe<uav_msgs::PrecLand>("/odroid/image_percept/landing_target", 1, sendPrecLandCb);
	ros::AsyncSpinner spinner(1);
	while (!called) {
		spinner.start();
		ros::Duration(0.2).sleep();
	}

	ROS_INFO("Precision landing data sent.");

	if (doLand) {
		uav_msgs::MissionParams mp;
		mp.doubles.push_back(config.doubles.at("PRECLAND_WAIT_TIME"));
		int ret = wait(mp, nh);
		if (ret != 0) {
			ROS_FATAL_STREAM("Terminate in function " << __func__);
			return ret;
		}
		// SYS_ID

		mp.doubles.clear();
		ret = land(mp, nh);
		if (ret != 0) {
			ROS_FATAL_STREAM("Terminal in function " << __func__);
			return ret;
		}
		spinner.stop();
		}

	else {  // for debugging
		ros::waitForShutdown();
	}

	// Calling ELP OFF service
	count = 0;
	do {
		envClient.call(envSrv);
		count++;
	} while (envSrv.response.scanELP && count < config.ints.at("ENV_RETRY_N"));
	if (envSrv.response.scanELP) {
		ROS_FATAL_STREAM("Cannot turn off scanELP Service!");
		return (int) Errors::UNRESPONSIVE_SERVICE;
	}

	return (int) Errors::NO_ERROR;
}

int goToDZ(const uav_msgs::MissionParams &m, ros::NodeHandle &nh)
{
	// Pastiin uda indoorGoTo terlebih dulu !
	if (!checkArgs(m, M_STRINGS, 1))
		return (int) Errors::INVALID_ARGUMENT;
	
	double want_y, want_z;
	std::string gedung = m.strings[0];  // HARUS KAPITAL
	std::string offsetName = "DZ_" + gedung + "_OFF_";
	if (gedung == "B") {
		offsetName += std::to_string(config.ints.at("GEDUNG_B_ORD"));
	}
	want_y = config.doubles.at("PRECISE_" + gedung + "_Y")
		- config.doubles.at(offsetName + "Y");
	want_z = config.doubles.at("PRECISE_" + gedung + "_Z")
		+ config.doubles.at(offsetName + "Z");

	bool called1 = false, called2 = false, called3 = false;
	// set up subscriber callbacks
	double off_x = 0.0, off_y = 0.0, off_z = 0.0;
	/*
	boost::function<void(const std_msgs::Float64 &)> x_cb = [&] (const std_msgs::Float64 &msg) {
		off_x = msg.data;
		called1 = true;
	};
	*/

	boost::function<void(const sensor_msgs::Range &)> y_cb = [&] (const sensor_msgs::Range &msg) {
		off_y = msg.range - want_y;
		called2 = true;
	};
	boost::function<void(const sensor_msgs::Range &)> z_cb = [&] (const sensor_msgs::Range &msg) {
		off_z = want_z - msg.range;
		called3 = true;
	};

	// subscriber 
	// ros::Subscriber x_sub = nh.subscribe<std_msgs::Float64>("/odroid/image_percept/distX", 1, x_cb);
	ros::Subscriber y_sub = nh.subscribe<sensor_msgs::Range>(
		config.strings.at("RF_DEPAN_SRC"), 1, y_cb);
	ros::Subscriber z_sub = nh.subscribe<sensor_msgs::Range>(
		config.strings.at("RF_BAWAH_SRC"), 1, z_cb);

	// Calling DistX ON service 
	ros::ServiceClient envClient = nh.serviceClient<uav_msgs::DetectObject>("/odroid/env_percept/detectObject");
	uav_msgs::DetectObject envSrv;
	envSrv.request.name = "DistX";
	uint8_t count = 0;
	do {
		envClient.call(envSrv);
		count++;
	} while (!envSrv.response.scanDistX && count < config.ints.at("ENV_RETRY_N"));
	if (!envSrv.response.scanDistX) {
		ROS_FATAL_STREAM("Cannot turn on scanDistX Service!");
		return (int) Errors::UNRESPONSIVE_SERVICE;
	}

	ros::AsyncSpinner spinner(4);
	spinner.start();
	while (!called1 || !called2 || !called3)
		ros::Duration(0.2).sleep();

	ROS_WARN_STREAM("---Aligning to precise DZ location---");
	double tol_x = config.doubles.at("PREC_X_TOL");
	double tol_y = config.doubles.at("PREC_Y_TOL");
	double tol_z = config.doubles.at("PREC_Z_TOL");
	std::string method = config.strings.at("GOTO_DZ_METHOD");
	if (method == "position") {
		ROS_INFO_STREAM("Aligning using position method");
		uint8_t iter = 0;
		while (fabs(off_x) > tol_x || fabs(off_y) > tol_y || fabs(off_z) > tol_z) {
			int success = offsetGoTo(std::vector<double>({off_x, off_y, off_z}), nh, true);
			if (success != 0) {
				ROS_FATAL_STREAM("Terminate in function " << __func__);
				return success;
			}
			iter++;
			if (iter > config.ints.at("PRECDZ_MAX_ITER")) {
				ROS_INFO_STREAM("DZ positioning stopped, already iterated: " << (unsigned) count);
				break;
			}
		}
	}
	else if (method == "velocity") {
		ROS_INFO_STREAM("Aligning using velocity method");
		const std::string setpointTopic = "/uav_commander/cmd_vel/setpoint";
		const std::string offsetTopic = "/uav_commander/cmd_vel/abs_offset";
		ros::Publisher posePub = nh.advertise<geometry_msgs::Pose>(setpointTopic, 1, false);
		ros::Publisher offsetPub = nh.advertise<std_msgs::Float64>(offsetTopic, 1, false);
		geometry_msgs::Pose poseMsg;
		std_msgs::Float64 offsetMsg;
		bool fullRf = (config.ints.at("GOTODZ_VER") == 2) ? true : false;
		double maxY = config.doubles.at("ARENA_MAX_Y");

		boost::function<void(const geometry_msgs::PoseStamped &)> callback = 
			[&] (const geometry_msgs::PoseStamped &msg) {
			poseMsg.position.x = msg.pose.position.x + off_x;
			if (!fullRf)
				poseMsg.position.y = msg.pose.position.y + off_y;
			else
				poseMsg.position.y = maxY - want_y;		
			poseMsg.position.z = want_z;
			posePub.publish(poseMsg);
			offsetMsg.data = sqrt(pow(off_x, 2) + pow(off_y, 2) + pow(off_z, 2));
			offsetPub.publish(offsetMsg);
			ROS_DEBUG_STREAM_THROTTLE(0.5, "now offset = " << off_x << ", "
				<< off_y << ", " << off_z);
		};
		// for better frequency
		ros::Subscriber poseSub = nh.subscribe<geometry_msgs::PoseStamped>(
			"/mavros/vision_pose/pose", 1, callback);
		
		spinner.start();

		int success = velocityGoTo(setpointTopic, offsetTopic, nh, true, true, 0.0, fullRf);
		if (success != 0) {
			ROS_FATAL_STREAM("Terminate in function " << __func__);
			return success;
		}
	}
	else return (int) Errors::CONFIG_ERROR;

	ROS_WARN_STREAM("---DZ positioning done.---");
	spinner.stop();

	// Calling DistX OFF service
	count = 0;
	do {
		envClient.call(envSrv);
		count++;
	} while (envSrv.response.scanDistX && count < config.ints.at("ENV_RETRY_N"));
	if (envSrv.response.scanDistX) {
		ROS_FATAL_STREAM("Cannot turn off scanDistX Service!");
		return (int) Errors::UNRESPONSIVE_SERVICE;
	}

	return (int) Errors::NO_ERROR;
}

int setpointTakeoff(const uav_msgs::MissionParams &m, ros::NodeHandle &nh)
{
	if (!checkArgs(m, M_DOUBLES, 1))
		return (int) Errors::INVALID_ARGUMENT;

	double setpoint = m.doubles[0];  // menurut rangefinder

	ros::Publisher statePub = nh.advertise<std_msgs::Float64>("/pid/vel_z_long/state", 1, false);
	ros::Publisher setpointPub = nh.advertise<std_msgs::Float64>("/pid/vel_z_long/setpoint", 1, false);
	ros::Publisher velPub = nh.advertise<mavros_msgs::PositionTarget>(
		"/mavros/setpoint_raw/local", 1, false);

	double effort;
	boost::function<void(const std_msgs::Float64 &)> effortCb = [&] (const std_msgs::Float64 &msg) {
		effort = msg.data;
	};
	ros::Subscriber effortSub = nh.subscribe<std_msgs::Float64>(
		"/pid/vel_z_long/control_effort", 1, effortCb);
	sensor_msgs::Range state;
	boost::function<void(const sensor_msgs::Range &)> stateCb = [&] (const sensor_msgs::Range &msg) {
		state = msg;
	};
	std::string topicName = config.strings.at("RF_BAWAH_SRC");
	ros::Subscriber stateSub = nh.subscribe<sensor_msgs::Range>(topicName, 1, stateCb);

	double maxThrust = config.doubles.at("TAKEOFF_MAX_THRUST");
	double minThrust = config.doubles.at("TAKEOFF_MIN_THRUST");
	ros::Publisher thrustPub = nh.advertise<mavros_msgs::AttitudeTarget>(
		"/mavros/setpoint_raw/attitude", 1, false);
	sensor_msgs::Range initialAlt;
	int gotAlt = getTopicValue(initialAlt, config.strings.at("RF_BAWAH_SRC"),
		config.doubles.at("WAIT_MSG_TO_LONG"));
	if (gotAlt != 0) {
		ROS_FATAL("Cannot fetch initial altitude!");
		ROS_FATAL_STREAM("Terminate in function " << __func__);
		return gotAlt;
	}
	boost::function<void(void)> publishThrust = [&] () {
		ros::spinOnce();
		double endpoint = 0.2, thrust;
		thrust = minThrust + (setpoint - state.range) / setpoint * (maxThrust - minThrust);
		mavros_msgs::AttitudeTarget thrustMsg;
		thrustMsg.type_mask = 7;
		thrustMsg.orientation.x = 0.0;
		thrustMsg.orientation.y = 0.0;
		thrustMsg.orientation.z = -0.7;
		thrustMsg.orientation.w = -0.7;
		thrustMsg.thrust = thrust;
		if (state.range - initialAlt.range < endpoint)
			thrustPub.publish(thrustMsg);
		else
			ROS_DEBUG_STREAM_ONCE("Stops publishing thrust coz alt = " << state.range);
	};

	boost::function<void(void)> publishInputs = [&] () {
		ros::spinOnce();
		std_msgs::Float64 stateMsg, setpointMsg;
		stateMsg.data = state.range;
		setpointMsg.data = setpoint;
		statePub.publish(stateMsg);
		setpointPub.publish(setpointMsg);
	};

	double maxVel = config.doubles.at("PID_MAX_VEL_Z_LONG");
	double sendWhen = config.doubles.at("SEND_VEL_Z_WHEN");
	double pidLimit = config.doubles.at("PID_VEL_ZL_LIM");
	boost::function<void(void)> publishOutputs = [&] () {
		ros::spinOnce();
		double velZ = effort / pidLimit * maxVel;
		mavros_msgs::PositionTarget velMsg;
		velMsg.type_mask = 3527;
		velMsg.velocity.x = 0.0;
		velMsg.velocity.y = 0.0;
		velMsg.velocity.z = velZ;
		velMsg.coordinate_frame = 1;  // LOCAL_NED
		if (state.range - initialAlt.range > sendWhen) {
			velPub.publish(velMsg);
			ROS_DEBUG_STREAM_ONCE("Started sending velZ coz alt = " << state.range);
		}
	};

	std_msgs::Bool togglePID;
	ros::Publisher togglePub = nh.advertise<std_msgs::Bool>("/pid/vel_z_long/pid_enable", 1, false);
	boost::function<void(bool)> publishToggles = [&] (bool toggle) {
		togglePID.data = toggle;
		togglePub.publish(togglePID);
	};

	ROS_WARN("---Takeoff started---");

	double altTol = config.doubles.at("ROUGH_Z_TOL");
	ros::Rate rate(20.0);
	double startTime = ros::Time::now().toSec();
	while (ros::Time::now().toSec() - startTime < 0.5) {
		publishToggles(true);
		publishInputs();
		if (sendWhen < 0)
			publishOutputs();
	}

	while (fabs(state.range - setpoint) > altTol) {
		publishThrust();
		publishToggles(true);
		publishInputs();
		publishOutputs();
		rate.sleep();
		ROS_DEBUG_STREAM_THROTTLE(0.5, "height = " << state.range);
	}

	publishToggles(false);

	ROS_WARN("---Takeoff succeeded---");

	return (int) Errors::NO_ERROR;
}

int loiterDZ(const uav_msgs::MissionParams &m, ros::NodeHandle &nh)
{
	if (!checkArgs(m, M_STRINGS, 1))
		return (int) Errors::INVALID_ARGUMENT;
	bool debug = false;
	if (checkArgs(m, M_BOOLS, 1, false))
		debug = m.bools[0];

	ros::Publisher namaGedung_pub = nh.advertise<std_msgs::String>("/nuc/env_percept/namaGedung", 1, true);
	std::string gedung = m.strings[0];  // HARUS KAPITAL
	
	std_msgs::String namaGedung;
	namaGedung.data = gedung;
	namaGedung_pub.publish(namaGedung);

	bool called1 = false;
	double angle_x, angle_y, size_x, size_y, distance;
	double last_called;
	double now_alt, angle_x_tol, angle_y_tol;
	angle_x_tol = 0.15;
	angle_y_tol = 0.15;

	bool reached = false;
	
	boost::function<void(const uav_msgs::PrecLoit &)> sendPrecLoitCb = [&] (const uav_msgs::PrecLoit &msg)
	{
		angle_x = msg.angle_x;
		angle_y = msg.angle_y;
		size_x = msg.size_x;
		size_y = msg.size_y;
		distance = msg.distance;
		called1 = true; 
		last_called = ros::Time::now().toSec();
//
		if (called1 && fabs(angle_x) < angle_x_tol && fabs(angle_y) < angle_y_tol)
			reached = true; //  Kalo mau test loiter, false in aja biar dronenya ikutin DZ, kalo mau test payload dibikin true, biar berhenti pada sesuai toleransi.
		else reached = false;
//
	};

	// ros::Subscriber sendPrecLoit = nh.subscribe<uav_msgs::PrecLoit>("/odroid/image_percept/distX", 1, sendPrecLoitCb);
	ros::Subscriber sendPrecLoit = nh.subscribe<uav_msgs::PrecLoit>("/odroid/image_percept/distX", 1, sendPrecLoitCb);

	// ros::Subscriber z_sub = nh.subscribe<sensor_msgs::Range>(
	// 	config.strings.at("RF_BAWAH_SRC"), 1, z_cb);

	// Calling DistX ON service
	ros::ServiceClient envClient = nh.serviceClient<uav_msgs::DetectObject>("/odroid/env_percept/detectObject");
	uav_msgs::DetectObject envSrv;
	envSrv.request.name = "DistX";
	uint8_t count = 0;
	do {
		envClient.call(envSrv);
		count++;
	} while (!envSrv.response.scanDistX && count < config.ints.at("ENV_RETRY_N"));
	if (!envSrv.response.scanDistX) {
		ROS_FATAL_STREAM("Cannot turn on scanDistX Service!");
		return (int) Errors::UNRESPONSIVE_SERVICE;
	}
	ros::Duration(config.doubles.at("ENV_SAFETY_SLEEP")).sleep();

	ros::AsyncSpinner spinner(3);
	spinner.start();
	// while (!called1 || !called2)
	while (!called1)
		ros::Duration(0.2).sleep();


	ros::Publisher precLoiterPub = nh.advertise<mavros_msgs::OverrideRCIn>(
		"/mavros/rc/override", 1, true);
	mavros_msgs::OverrideRCIn precLoiterMsg;
	precLoiterMsg.channels[7] = 2000;
	
	ros::Publisher mavPrecLoiter = nh.advertise<mavros_msgs::LandingTarget>(
		"/mavros/landing_target/raw", 1, true);
	mavros_msgs::LandingTarget mavPrecMsg;
	//precLoiterPub.publish(precLoiterMsg);

	uav_msgs::MissionParams mp;
	mp.strings.push_back("LOITER");
	int modeSwitched = switchMode(mp, nh);
	if (modeSwitched != 0) {
	 	ROS_FATAL_STREAM("Terminate in function " << __func__);
	 	return modeSwitched;
	}

/*	mavros_msgs::RCIn rcStatus;
	count = 0;
	do {
		if (count >= config.ints.at("SERVICE_RETRY_N")) {
			ROS_FATAL("Cannot override RC7!");
			ROS_FATAL_STREAM("Terminate in function " << __func__);
			return (int) Errors::UNRESPONSIVE_SERVICE;
		}
		precLoiterPub.publish(precLoiterMsg);
		count++;
		ros::Duration(0.25).sleep();
		int gotStatus = getTopicValue(rcStatus, "/mavros/rc/in", config.doubles.at("WAIT_MSG_TIMEOUT"));
		if (gotStatus != 0) {
			ROS_FATAL_STREAM("Terminate in function " << __func__);
			return gotStatus;
		}
	} while (rcStatus.channels.at(6) != 2100); */

	ROS_WARN_STREAM("---LOITER at DZ location---");

	ros::Rate freq(20);
	double prevTime = ros::Time::now().toSec();
	bool checkData = true;
	while (true) {
		mavPrecMsg.angle.at(0) = angle_x;
		mavPrecMsg.angle.at(1) = angle_y;
		mavPrecMsg.size.at(0) = size_x;
		mavPrecMsg.size.at(1) = size_y;
		mavPrecMsg.distance = distance;
		precLoiterPub.publish(precLoiterMsg);
		mavPrecLoiter.publish(mavPrecMsg);
		
		freq.sleep();
		if (reached) {
			if (ros::Time::now().toSec() - prevTime > 5) // time to wait?
				break;
		}
		else {
			prevTime = ros::Time::now().toSec();
			ROS_DEBUG_THROTTLE(0.3, "Resetting time...");
		}
		// belum bagus

		if (checkData){
			if (ros::Time::now().toSec() - last_called > 1.0 && called1){
				ROS_ERROR_ONCE("Not seeing dropzone");
				sendPrecLoit.shutdown();
				checkData = false;
			}
		}
	}

	ROS_WARN_STREAM("---DZ Positioning done!---");
	spinner.stop();
	
	// Calling DistX OFF service
	count = 0;
	do {
		envClient.call(envSrv);
		count++;
	} while (envSrv.response.scanDistX && count < config.ints.at("ENV_RETRY_N"));
	if (envSrv.response.scanDistX) {
		ROS_FATAL_STREAM("Cannot turn on scanDistX Service!");
		return (int) Errors::UNRESPONSIVE_SERVICE;
	}
	/*
	mp.strings.clear();
	mp.strings.push_back("GUIDED");
	return switchMode(mp, nh);
	*/
	return (int) Errors::NO_ERROR;
}


#endif
}
