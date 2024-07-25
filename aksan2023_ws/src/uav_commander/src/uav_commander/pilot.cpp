#include <uav_commander/pilot.hpp>

namespace uav_commander{

	pilot::pilot(ros::NodeHandle *nh): nh_(*nh)
	{
		// Temporary solution. Fungsi-fungsinya masih sedikit
		// Dibikin kayak gini supaya bisa panggil fungsi dari string.
		// Misalnya std::string f = "armThrottle"; uav_funcs[f](m, nh_);
		uav_funcs.emplace("armThrottle", &armThrottle);
		uav_funcs.emplace("disarmThrottle", &disarmThrottle);
		uav_funcs.emplace("takeoff", &takeoff);
		uav_funcs.emplace("land", &land);
		uav_funcs.emplace("switchMode", &switchMode);
		uav_funcs.emplace("wait", &wait);
		uav_funcs.emplace("testWASD", &testWASD);
		uav_funcs.emplace("indoorInitialize", &indoorInitialize);
		uav_funcs.emplace("indoorGoTo", &indoorGoTo);
		uav_funcs.emplace("dropPayload", &dropPayload);
		uav_funcs.emplace("goToELP", &goToELP);
		uav_funcs.emplace("precLand", &precLand);
		uav_funcs.emplace("goToDZ", &goToDZ);
		uav_funcs.emplace("setpointTakeoff", &setpointTakeoff);
		uav_funcs.emplace("testVelocityGoTo", &testVelocityGoTo);
		uav_funcs.emplace("loiterDZ", &loiterDZ);
		uav_funcs.emplace("velocity", &velocity);
        	uav_funcs.emplace("setPointPosition", &setPointPosition);
		uav_funcs.emplace("chargeOpengrab", &chargeOpengrab);
		uav_funcs.emplace("dischargeOpengrab", &dischargeOpengrab);
        	uav_funcs.emplace("stop", &stop);
        	uav_funcs.emplace("movingCV", &movingCV);
        	uav_funcs.emplace("setPointLidar", &setPointLidar);
                uav_funcs.emplace("setPointGlobal", &setPointGlobal);
        	uav_funcs.emplace("calculateNewPosition", &calculateNewPosition);
        	uav_funcs.emplace("heading", &heading);
        	uav_funcs.emplace("movingPL", &movingPL);    
        	uav_funcs.emplace("middle", &middle);        	
        	uav_funcs.emplace("loiterLand", &loiterLand);   
        	uav_funcs.emplace("PDM", &PDM);       	        	    	        	        	    	
        	uav_funcs.emplace("neutralOpengrab", &neutralOpengrab);       	        	    	        	        	    	        	
	}

	// Function to parse missions from file. 
	bool pilot::load(std::string pilot_fname, std::string config_fname)
	{
		ROS_WARN("---Loading Missions---");

		// Load the config file
		if (loadConfig(config_fname) != 0) {
			ROS_FATAL("Terminate when loading config");
			return false;
		}
		uav_msgs::MissionParams mp;
		if (indoorPreinitialize(mp, nh_) != 0) {
			ROS_FATAL("Terminate when in indoorPreinitialize");
			return false;
		}
		std::ifstream file(pilot_fname);
		std::string line;
		// Reads line by line until end of file
		while(std::getline(file, line)) {
			// Not empty and not a comment
			if (!line.empty() && line.substr(0, 2) != "//") {
				// Separate a line into "chunks", delimited by delim
				std::string delim = "; ";
				std::size_t start = 0;
				std::size_t end = line.find(delim);
				std::string chunk;
				// Store the line to a buffer. Example, if the line is
				// "someFunc; m 1 strings ABCD; m 2 doubles X Y" then the content of mission:
				// {"someFunc", "1", "strings", "ABCD", "2", "doubles", "X", "Y"}
				std::vector<std::string> mission;
				uint8_t num = 0;    // Number of types specified for m (max 3)
				// Error if the line does not contain delim (at least one!)
				if (end == std::string::npos) { return false; }

				bool done = false, trigger_done = false;

				while (!done) {
				
					chunk = line.substr(start, end - start);

					// Process chunks to mission buffer based on 2 first characters
					if (chunk.substr(0, 2) != "m ") {
						if (chunk.substr(0, 2) != "m;") {
							mission.push_back(chunk);    // Must be functionName
						}
						else break;    // Done for this line
					}

					else {
						num++;
						std::size_t s = 2;
						std::size_t e = chunk.find(" ", s);
						std::string get;
						// Process the params given, separated by space
						while (e != std::string::npos) {
							get = chunk.substr(s, e - s);
							mission.push_back(get);
							s = e + 1;
							e = chunk.find(" ", s);
						}
						get = chunk.substr(s, e);
						if (get.back() == ';') {
							if (!trigger_done) { return false; }    // Slight safety check
							get.pop_back();
						}
						mission.push_back(get);
					}

					if (!trigger_done) {
						start = end + delim.length();
						end = line.find(delim, start);
						if (end == std::string::npos)
							trigger_done = true;	// Terminate by the next loop
					}
					else
						done = true;
				}
				uint8_t args, pos = 1;

				// Push the buffer to real missionParams
				for (uint8_t i = 0; i < num; i++) {

					if (!to_smint(mission[pos], args)) { return false; };    // Another error
					m_types type;
					if (mission[pos+1] == "ints") type = M_INTS;
					else if (mission[pos+1] == "doubles") type = M_DOUBLES;
					else if (mission[pos+1] == "strings") type = M_STRINGS;
					else if (mission[pos+1] == "bools") type = M_BOOLS;
					else return false;    // Error

					for (uint8_t j = 0; j < args; j++) {
						uint8_t idx = pos + j + 2;
						switch (type)
						{
						case M_INTS:
							m.ints.push_back(stoi(mission[idx]));
							break;
						case M_DOUBLES:
							m.doubles.push_back(stod(mission[idx]));
							break;
						case M_STRINGS:
							m.strings.push_back(mission[idx]);
							break;
						case M_BOOLS:
							bool val;
							if (mission[idx] == "true") val = true;
							else if (mission[idx] == "false") val = false;
							else return false;
							m.bools.push_back(val);
							break;
						}
					}
					pos += args + 2;
				}
				// Don't forget to capture by value. Otherwise we might got headache
				// REQUIRE C++14
				missionList.push([this, m=m, mission] () {return uav_funcs.at(mission[0])(m, nh_);});
				clearParams();
				ROS_WARN_STREAM("---Loaded mission: " << mission[0] << "---");
			}
		}
		
		return true;
	}

	// Converts string x with length 1 to small integer
	// Used this instead of stoi() for more strict error throw
	bool pilot::to_smint(std::string &x, uint8_t &n) {
		if (x.length() != 1)
			return false;
		n = x.c_str()[0] - '0';
		// Assume the char is in ascii
		return true;
	}

    void pilot::clearParams()
    {
		m.bools.clear();
    	m.ints.clear();
    	m.strings.clear();
    	m.doubles.clear();
    }

    void pilot::executeMissions(int startFrom)
    {
		int currentNo = 0;
		for (int i = 0; i < startFrom; i++) {
			missionList.pop();
			currentNo++;
		}

		int err = 0;    // Storing return value of current function
		ROS_WARN("---Altigen Kresnala in action---");
		ros::ServiceClient fsClient = nh_.serviceClient<uav_msgs::PilotOverride>("/uav_safety/pilot_override");
		uav_msgs::PilotOverride srv;
		
		ros::Publisher currentPub = nh_.advertise<std_msgs::Int32>("/uav_commander/current", 1, false);
		std_msgs::Int32 currentNoMsg;

		boost::function<void(const ros::TimerEvent &ev)> timerCb = 
		[&] (const ros::TimerEvent &ev) {
			currentNoMsg.data = currentNo;
			currentPub.publish(currentNoMsg);
		};

		ros::Timer timer = nh_.createTimer(ros::Duration(0.1), timerCb);
		ros::AsyncSpinner spinner(1);

		spinner.start();
		
		while (ros::ok())
		{
			if (!missionList.empty())
			{
				err = missionList.front()();
				if (err == 0) {	// NO_ERROR
					missionList.pop();
					currentNo++;
				}
				else {
					ROS_FATAL_STREAM("Pilot died with code " << err);
					ROS_WARN_STREAM("---Initiating failsafe---");
					srv.request.what = config.strings.at("FS_METHOD");    // harusnya misi loadConfig udah.
					if (fsClient.call(srv))
						ROS_WARN_STREAM("---Failsafe completed with code " << (unsigned) srv.response.result << "---");
					else {
						ROS_FATAL("Failsafe service UNRESPONSIVE");
						ROS_FATAL("Check config FS_METHOD. Or is safety_node dead?");
					}
					return;
				}
			}
			else {
				ROS_WARN("---Mission Completed. Congrats!---");
				return;
			}
		}
	}
}
