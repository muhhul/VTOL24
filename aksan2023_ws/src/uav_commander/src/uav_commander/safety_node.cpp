// Pilot node may die for whatever reason~
// But this node MUST NEVER DIE!!!!

#include <uav_commander/safety_node.hpp>

std::string toUpcase(const std::string &str)
{
    std::string upper;
    for (uint8_t i = 0, n = str.size(); i < n; i++) {
        upper.push_back(toupper(str[i]));
    }
    return upper;
}


bool connection() {
    
    const int bufferSize = 1024;
    char buffer[bufferSize];

    const char* command = "w -h";
    FILE* pipe = popen(command, "r");

    if (!pipe) {
        std::cerr << "Failed to run command." << std::endl;
        return 1;
    }

    std::string commandOutput = "";
    while (fgets(buffer, bufferSize, pipe) != nullptr) {
        commandOutput += buffer;
    }

    pclose(pipe);

    // std::cout << "Command output: " << std::endl << commandOutput;
    
    // The IP address to search for
    std::string ipAddressToFind = "192.168.0.103";

    // Check if the IP address is present in the text
    if (commandOutput.find(ipAddressToFind) != std::string::npos) {
        return true;
    } else {
        return false;
    }

}
void timerCallback(const ros::TimerEvent& event) {
    // Your code to execute at each timer tick goes here
    ROS_INFO("Timer callback executed.");
}
void spamLand()
{
    ROS_FATAL("Spamming land service. Check the UAV");
    ros::Rate rate(LANDSERV_PANIC_RATE);
    ros::ServiceClient client = nh->serviceClient<mavros_msgs::SetMode>("/mavros/set_mode");
    mavros_msgs::SetMode srv;
    srv.request.custom_mode = "LAND";

    std_srvs::Empty abortSrv;
    ros::ServiceClient abortClient = nh->serviceClient<std_srvs::Empty>("/uav_commander/killPilot");
    boost::function<void(const ros::TimerEvent &)> abortCb = 
    [&] (const ros::TimerEvent &ev) {
        abortClient.call(abortSrv);
    };
    ros::Timer abortTimer = nh->createTimer(ros::Duration(0.01), abortCb, true, true);
    ros::spinOnce();
    for (uint8_t i = 0; i < 200; i++) {
        client.call(srv);
        rate.sleep();
    }
}

uint8_t landSrv()
{
    ROS_WARN("---Changing to LAND mode---");
    ros::ServiceClient client = nh->serviceClient<mavros_msgs::SetMode>("/mavros/set_mode");
    mavros_msgs::SetMode srv;
    mavros_msgs::State curr_state;
    ros::Duration dur(LANDSERV_RETRY_DUR);

    srv.request.custom_mode = "LAND";

    bool state_miss = false;
    uint8_t count = 0;
    do {
        count++;
        if (count > LANDSERV_RETRY_N) {
            ROS_FATAL("LAND SERV NOT RESPONDING!");
            return SERVICE_ERROR;
        }

        if (!client.call(srv)) {
            ROS_WARN("---Mode changing failed. Retrying...---");
        }
        dur.sleep();

        boost::shared_ptr<const mavros_msgs::State> curr_state_ptr;
        curr_state_ptr = ros::topic::waitForMessage<mavros_msgs::State>("/mavros/state", ros::Duration(WAIT_MSG_TIMEOUT));
        if (curr_state_ptr == NULL) {
            ROS_FATAL("CANNOT GET UAV STATE!");
            state_miss = true;
            break;
        }

        curr_state = *curr_state_ptr;
    } while (toUpcase(curr_state.mode) != "LAND");

    if (state_miss) {
        // !! better idea?
        spamLand();
        return LOST_MESSAGE;
    }

    ROS_WARN("---Now landing---");
    return OKAY;
}

// Most probably used using "abort" functionality.
// Mostly same with landSrv(), but now separated to indicate
// that landSrv() is for failsafe, and this is for abort
uint8_t changeMode(const std::string &mode)
{
    ROS_WARN_STREAM("---Changing to " << mode << " mode.---");
    ros::ServiceClient client = nh->serviceClient<mavros_msgs::SetMode>("/mavros/set_mode");
    mavros_msgs::SetMode srv;
    mavros_msgs::State curr_state;
    ros::Duration dur(CHGMODE_RETRY_DUR);

    srv.request.custom_mode = mode;

    bool state_miss = false;
    uint8_t count = 0;
    do {
        count++;
        if (count > CHGMODE_RETRY_N) {
            ROS_FATAL("MAVROS SET MODE NOT RESPONDING!");
            return SERVICE_ERROR;
        }

        if (!client.call(srv)) {
            ROS_WARN("---Mode changing failed. Retrying...---");
        }
        dur.sleep();

        boost::shared_ptr<const mavros_msgs::State> curr_state_ptr;
        curr_state_ptr = ros::topic::waitForMessage<mavros_msgs::State>("/mavros/state", ros::Duration(WAIT_MSG_TIMEOUT));
        if (curr_state_ptr == NULL) {
            ROS_FATAL("CANNOT GET UAV STATE!");
            state_miss = true;
            break;
        }

        curr_state = *curr_state_ptr;
    } while (toUpcase(curr_state.mode) != toUpcase(mode));

    if (state_miss)
        return LOST_MESSAGE;

    ROS_WARN_STREAM("---Mode changed to " << mode << " mode.---");
    return OKAY;
}

bool pilotOverride(uav_msgs::PilotOverride::Request &req, uav_msgs::PilotOverride::Response &res)
{
    // Note: only return false if wrong request or (of course) when this service is unavailable

    std::string whatToDo = toUpcase(req.what);
    ROS_WARN_STREAM("---Calling pilotOverride to " << whatToDo << "---");

    if (whatToDo == "LAND_SERV") {
        uint8_t landed = landSrv();
        if (landed == SERVICE_ERROR) {
            panic_land = true;      // TODO. If mavros land serv failed, must do manual.
        }
        else if (landed == LOST_MESSAGE)
            spamLand();
        res.result = landed;
        return true;
    }

    if (whatToDo == "RTL") {
        uint8_t succeed = changeMode(whatToDo);
        if (succeed != 0) {
            // Try using land serv
            ros::ServiceClient client = nh->serviceClient<uav_msgs::PilotOverride>("/uav_safety/pilot_override");
            uav_msgs::PilotOverride srv;
            srv.request.what = "LAND_SERV";
            client.call(srv);
            res.result = srv.response.result;
            return true;
        }
        res.result = succeed;
        return true;
    }

    return false;   // WRONG REQUEST
}

void keyDownCb(const uav_teleop::Key msg)
{
    if (globKeyPress.isPressed) {
        globKeyPress.isPressed = false;
        globKeyPress.keyDown = 0;
        return;
    }

    globKeyPress.isPressed = true;
    globKeyPress.keyDown = msg.code;
    globKeyPress.keyDown_when = msg.header.stamp.toSec();
    ROS_DEBUG_STREAM("Pressed key: " << msg.code);
}

void keyUpCb(const uav_teleop::Key msg)
{
    globKeyPress.isPressed = false;
    globKeyPress.keyDown_when = 0;    // for safety
    ROS_DEBUG_STREAM("Released key: " << msg.code);
}

bool fsTrigger()
{
//     #if FS_ALT_CHECK

//     double relAlt;
//     double relKanan;

//     #if FS_ALT_SOURCE == 1
//     auto relAltPtr = ros::topic::waitForMessage<geometry_msgs::PoseStamped>(
//         "/mavros/local_position/pose", ros::Duration(WAIT_MSG_TIMEOUT));

//     #elif FS_ALT_SOURCE == 2
//     auto relAltPtr = ros::topic::waitForMessage<sensor_msgs::Range>(
//         "/mavros/distance_sensor/rangefinder_pub", ros::Duration(WAIT_MSG_TIMEOUT));
//     #endif

//     if (relAltPtr == NULL) {
//         ROS_FATAL_STREAM("CANNOT GET ALTITUDE DATA!");
//         return true; 
//     }

//     #if FS_ALT_SOURCE == 1
//     relAlt = relAltPtr->pose.position.z;

//     #elif FS_ALT_SOURCE == 2
//     relAlt = relAltPtr->range;
//     #endif
    
// //    #if GAZEBO_TEST == 1
// //    auto relKananPtr = ros::topic::waitForMessage<sensor_msgs::Range>(
// //        "/gazebo_things/rf_kanan", ros::Duration(WAIT_MSG_TIMEOUT));
// //    relKanan = relKananPtr->range;
// //    #endif

//     if (relAlt > FS_MAX_ALT) {
//         ROS_FATAL_STREAM("Maximum altitude reached. Alt: " << relAlt);
//         return true;
//     }
    
// //    if (relKanan < FS_MAX_KANAN) {
// //        ROS_FATAL_STREAM("Maximum kanan reached. Kanan: " << relKanan);        
// //        return true;
// //    }

//     return false;

//     #endif
    
    return false;
}

bool rcPWM(int val, const std::string &want)
{
    if (want == "HIGH") {
        if (val > 2000) return true;
        else return false;
    }
    else if (want == "LOW") {
        if (val < 1000) return true;
        else return false;
    }   
    else {
        ROS_FATAL("CHECK rcPWM func!");
        throw std::invalid_argument("CHECK rcPWM func!");
    }
}

int rcTrigger()
{
    // #if RC_CHECK == 1
    // auto rcInPtr = ros::topic::waitForMessage<mavros_msgs::RCIn>("/mavros/rc/in", 
    //     ros::Duration(WAIT_MSG_TIMEOUT));
    // if (rcInPtr == NULL) {
    //     ROS_FATAL_STREAM("Is RC connected?");
    //     return 0;
    // }

    // if (rcPWM(rcInPtr->channels.at(RC_N_LAND-1), RC_LAND_PWM)) {
    //     ROS_ERROR("RC LAND TRIGGERED");
    //     return 1;
    // }
    // if (rcPWM(rcInPtr->channels.at(RC_N_STAB-1), RC_STAB_PWM)) {
    //     ROS_ERROR("RC STABILIZE TRIGGERED");
    //     return 2;
    // }
    // if (rcPWM(rcInPtr->channels.at(RC_N_EMERGENCY_STOP_MOTOR-1), RC_STAB_EMERGENCY_STOP_MOTOR)) {
	// ROS_ERROR("RC EMERGENCY STOP MOTOR TRIGGERED");
	// return 3;
    // }    

    // #endif

    // return 0;
}

bool checkPilot()
{
    ROS_DEBUG("Checking if pilot is alive");
    std::vector<std::string> listNodes;
    if (!ros::master::getNodes(listNodes)) {
        // VERY VERY BAD.
        ROS_FATAL("Cannot get list of NODES!!!");
        return false;
    }

    for (auto &item : listNodes) {
        // DOUBLE CHECK dengan launch file
        if (toUpcase(item) == toUpcase("/pilot_node")) {
            ROS_DEBUG("Pilot node found. It's alive.");
            return true;
        }
    }

    ROS_ERROR("Pilot is not alive.");
    return false;
}

bool mundurTriggered = false;
bool mundurCb(std_srvs::SetBool::Request &req, std_srvs::SetBool::Response &res)
{
    res.success = false;
    mundurTriggered = req.data;
    res.success = true;
    ROS_ERROR("Mundur 1m is triggered!");
    return true;
}

bool isMunduring = false;
void mundurTimerCb(const ros::TimerEvent &ev)
{
    if (mundurTriggered && !isMunduring) {
        isMunduring = true;
        ros::Publisher mundurPub = nh->advertise<mavros_msgs::PositionTarget>(
            "/mavros/setpoint_raw/local", 1, false);
        mavros_msgs::PositionTarget mundurMsg;
        mundurMsg.type_mask = 2503;
        mundurMsg.coordinate_frame = 1;
        mundurMsg.velocity.x = 0.0;
        mundurMsg.velocity.y = -0.5;
        mundurMsg.velocity.z = 0.0;
        mundurMsg.yaw = 1.5708;
        ros::Rate freq(10);
        double startTime = ros::Time::now().toSec();
        while (ros::Time::now().toSec() - startTime < 2.0) {
            ROS_DEBUG_THROTTLE(0.3, "Publishing mundur command");
            mundurPub.publish(mundurMsg);
            freq.sleep();
        }
        mundurTriggered = false;
        isMunduring = false;
        ROS_INFO("Munduring done!");
        return;
    }
}

bool spamLandCb(std_srvs::Empty::Request &req, std_srvs::Empty::Response &res)
{
    spamLand();
    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "safety_node");
    ros::NodeHandle nhval;
    nh = &nhval;
    ROS_WARN("1");
    // When using simulation time
    while(ros::Time::now().toSec() < 1.0) {}

    ros::Duration(3.0).sleep();  // wait pilot node
    if (!checkPilot()) {
        ROS_FATAL("Pilot not found");
        return NO_PILOT;
    }
    ROS_WARN("2");
    ros::ServiceClient toggleStartClient = nh->serviceClient<std_srvs::SetBool>("/uav_commander/toggleStart");
    std_srvs::SetBool toggleStartSrv;
    toggleStartSrv.request.data = true;
    for (int i = 0; i < 3; i++) {
        if (toggleStartClient.call(toggleStartSrv))
            break;
    }
    if (!toggleStartSrv.response.success) {
        ROS_FATAL("Cannot toggle start pilot!");
        return SERVICE_ERROR;
    }
    toggleStartClient.shutdown();
    ROS_WARN("3");
    ros::AsyncSpinner spinner(5);

    ros::ServiceServer server = nh->advertiseService("/uav_safety/pilot_override", &pilotOverride);
    ros::ServiceServer mundurServer = nh->advertiseService("/uav_safety/mundur", &mundurCb);
    ros::Subscriber keySubDown = nh->subscribe<uav_teleop::Key>("/keyboard/keydown", 1, &keyDownCb);
    ros::Subscriber keySubUp = nh->subscribe<uav_teleop::Key>("/keyboard/keyup", 1, &keyUpCb);
    ros::ServiceServer spamLandServer = nh->advertiseService("/uav_safety/spam_land", &spamLandCb);
    ROS_WARN("4");
    // A bit waste of resources but let's don't change, just add.
    double distZAtas = 4.0;
    double distZBawah = 0.2;
    boost::function<void(const sensor_msgs::Range &)> distZAtasCb =
    [&] (const sensor_msgs::Range &msg) {
        if (distZAtas > 0.3 && distZAtas < 10.0)
            distZAtas = msg.range;
    };
    boost::function<void(const sensor_msgs::Range &)> distZBawahCb = 
    [&] (const sensor_msgs::Range &msg) {
        if (distZBawah > 0.1 && distZBawah < 10.0)
            distZBawah = msg.range;
    };
    ros::Subscriber distZAtasSub = nh->subscribe<sensor_msgs::Range>(
        "/tfmini_node_atas/TFmini", 1, distZAtasCb);
    ros::Subscriber distZBawahSub = nh->subscribe<sensor_msgs::Range>(
        "/mavros/distance_sensor/rangefinder_pub", 1, distZBawahCb);
    // cek stream data
    auto tesRfAtas = ros::topic::waitForMessage<sensor_msgs::Range>(
        "/tfmini_node_atas/TFmini", ros::Duration(0.5));
//    if (tesRfAtas == NULL) {
//        for (int i = 0; i < 100; i++) {
//        ROS_FATAL("Lidar atas ga hidup?!");
//        }
//        return -1;
//    }
    ROS_WARN("5");
    bool isSpamming = false;
    boost::function<void(const ros::TimerEvent &)> checkAtapCb =
    [&] (const ros::TimerEvent &ev) {
        if (distZBawah > 50) {
            if (!isSpamming) {
            ROS_FATAL_STREAM("Altitude = " << distZBawah);
            isSpamming = true;
            spamLand();
            }
        }
        // if (distZAtas < 1.8) {
        //     if (!isSpamming) {
        //     ROS_FATAL_STREAM("to Atap = " << distZAtas);
        //     isSpamming = true;
        //     spamLand();
        //     }
        // }
    };
    ros::Timer checkAtapTimer = nh->createTimer(ros::Duration(0.1), checkAtapCb);
    ROS_WARN("6");
    ros::Timer mundurTimer = nh->createTimer(ros::Duration(0.05), &mundurTimerCb);
    spinner.start();
    
    ros::ServiceClient client = nh->serviceClient<uav_msgs::PilotOverride>("/uav_safety/pilot_override");
    uav_msgs::PilotOverride srv;

    bool reqValid = false;
    uint8_t err = 0;

    keyPress locKeyPress;    // So that processingnya tidak tiba2 distracted gara2 cb
    double currTime;
    ros::Rate rate(30);    // Arbitrary
    ROS_WARN("6.1");
    while (ros::ok()) {
        bool triggeredFs = fsTrigger(); int triggeredRc = rcTrigger();
      /*          
        if (!connection()){
            double start_time = ros::Time::now().toSec();
            
            while (!connection() && ((ros::Time::now().toSec()-start_time) < 20)){
                ROS_WARN("DISCONNECTED, WAITING TO CONNECT");
            }
            
            if (!connection() && ((ros::Time::now().toSec()-start_time) >= 20)){
                err = landSrv();
            
                if (err == SERVICE_ERROR) {
                    panic_land = true;    // TO DO
                }
            
                if (checkPilot()) {
                    ROS_ERROR("Pilot will be killed");
                    ros::ServiceClient abortClient = nh->serviceClient<std_srvs::Empty>("/uav_commander/killPilot");
                    std_srvs::Empty emptySrv;
                    abortClient.call(emptySrv);
                    //ros::Duration(1.0).sleep();    // for safety (?)
                }
            
            }
        }*/
        
        if (triggeredFs || triggeredRc) {
   	ROS_FATAL_STREAM("Initiating failsafe");
            int currentMission;
            bool dontRestart = false;
            auto currentMissionPtr = ros::topic::waitForMessage<std_msgs::Int32>("/uav_commander/current", 
            ros::Duration(WAIT_MSG_TIMEOUT));
            if (currentMissionPtr == NULL) {
                ROS_FATAL_STREAM("Cannot get current mission number!");
                dontRestart = true;
            }
            else {
                currentMission = currentMissionPtr->data;
            }
            if (checkPilot()) {
                ROS_ERROR("Pilot will be killed");
                ros::ServiceClient abortClient = nh->serviceClient<std_srvs::Empty>("/uav_commander/killPilot");
                std_srvs::Empty emptySrv;
                abortClient.call(emptySrv);
                //ros::Duration(1.0).sleep();    // for safety (?)
            }
	ROS_WARN("6.2");
            if (triggeredFs && !dontRestart) {
                bool waitAltDone = false;
                double prevTime = ros::Time::now().toSec();
                boost::function<void(const sensor_msgs::Range &)> waitAltCb = 
                [&] (const sensor_msgs::Range &msg) {
                    if (msg.range < FS_DONE_ALT) {
                        if (ros::Time::now().toSec() - prevTime > 0.3) {
                            waitAltDone = true;
                            ROS_INFO_STREAM_ONCE("Safety: land to " << FS_DONE_ALT << "m done.");
                        }
                        else {
                            prevTime = ros::Time::now().toSec();
                            ROS_DEBUG("Safety: land not yet settled. Resetting time.");
                        }
                    }
                };
                ros::Subscriber waitAlt = nh->subscribe<sensor_msgs::Range>(
                    "/mavros/distance_sensor/rangefinder_pub", 1, waitAltCb);

                err = landSrv();
                if (err == SERVICE_ERROR) {
                    panic_land = true;    // TO DO
                }

                ros::Rate waitRate(15);
                while (!waitAltDone) {
                    ros::spinOnce();
                    waitRate.sleep();
                }
	ROS_WARN("6.3");
                ros::ServiceClient setCurrentClient = nh->serviceClient<uav_msgs::SetCurrent>(
                    "/uav_commander/setCurrent");
                uav_msgs::SetCurrent setCurrentSrv;

                if (checkPilot()) {
                    setCurrentSrv.request.data = currentMission;
                    for (int i = 0; i < 3; i++) {
                        if (setCurrentClient.call(setCurrentSrv))
                            break;
                    }
                    if (!setCurrentSrv.response.success) {
                        ROS_FATAL("Error when setting current mission no!");
                        dontRestart = true;
                    }
                }
                else {
                    ROS_FATAL("Pilot node not respawning!!");
                    dontRestart = true;
                }

                if (!dontRestart) {
                    ros::ServiceClient toggleStartClient = nh->serviceClient<std_srvs::SetBool>(
                        "/uav_commander/toggleStart");
                    std_srvs::SetBool toggleStartSrv;
                    toggleStartSrv.request.data = true;

                    err = changeMode("GUIDED");
                    if (err != 0) {
                        ROS_FATAL("Safety: cannot change to guided!");
                        dontRestart = true;
                    }

                    if (!dontRestart) {
                        for (int i = 0; i < 3; i++) {
                            if (toggleStartClient.call(toggleStartSrv))
                                break;
                        }
                        if (!toggleStartSrv.response.success) {
                            ROS_FATAL("Error when calling pilot toggleStart!");
                            dontRestart = true;
                        }

                        else ROS_INFO("Safety node done its good job!");
                    }
                }
            }
	    ROS_WARN("7");
            if (triggeredFs && dontRestart) {
                err = landSrv();
                if (err == SERVICE_ERROR) {
                    panic_land = true;    // TO DO
                }
                break;                
            }

            ros::ServiceClient modeClient = nh->serviceClient<mavros_msgs::SetMode>(
            "/mavros/set_mode");
            mavros_msgs::SetMode modeSrv;
            if (triggeredRc == 1)
            modeSrv.request.custom_mode = "LAND";
            else if (triggeredRc == 2)
            modeSrv.request.custom_mode = "STABILIZE";
            if (triggeredRc) {
              double startTime = ros::Time::now().toSec();
              while (ros::Time::now().toSec() - startTime < 1.0) {
                modeClient.call(modeSrv);
                ros::Duration(0.1).sleep();
              }
              break;
            }
        }
	ROS_WARN("8");
        locKeyPress = globKeyPress;
        currTime = ros::Time::now().toSec();
        if (locKeyPress.isPressed && locKeyPress.keyDown_when > 1.0) {
            if (currTime - locKeyPress.keyDown_when > KEY_HOLD_DUR) {
                ROS_WARN("---SAFETY key pressed!---");
                switch (locKeyPress.keyDown) {
                    case uav_teleop::Key::KEY_DELETE:
                        srv.request.what = "LAND_SERV";
                        ROS_DEBUG_STREAM("Requesting land serv...");
                        reqValid = true;
                        break;
                    case uav_teleop::Key::KEY_HOME:
                        srv.request.what = "RTL";
                        reqValid = true;
                        break;
                    default:
                        ROS_ERROR("You pressed the wrong key!");
                }
                if (reqValid) {
                    ROS_WARN("---Mission Aborted---");
                    if (checkPilot()) {
                        ros::ServiceClient abortClient = nh->serviceClient<std_srvs::Empty>("/uav_commander/killPilot");
                        std_srvs::Empty emptySrv;
                        abortClient.call(emptySrv);
                        ros::Duration(1.0).sleep();    // for safety (?)
                    }
                    client.call(srv);
                    err = srv.response.result;
                    break;
                }
            }
        }
        rate.sleep();
    }
    // Tambahin cek fcu connected
    ROS_WARN_STREAM("---Safety node exiting with code " << (unsigned) err << "---");
    return err;
}
