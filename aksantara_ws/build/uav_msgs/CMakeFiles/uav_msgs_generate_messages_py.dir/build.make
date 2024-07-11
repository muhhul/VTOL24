# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vtol2022/aksantara_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vtol2022/aksantara_ws/build

# Utility rule file for uav_msgs_generate_messages_py.

# Include the progress variables for this target.
include uav_msgs/CMakeFiles/uav_msgs_generate_messages_py.dir/progress.make

uav_msgs/CMakeFiles/uav_msgs_generate_messages_py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/_MissionParams.py
uav_msgs/CMakeFiles/uav_msgs_generate_messages_py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/_PrecLand.py
uav_msgs/CMakeFiles/uav_msgs_generate_messages_py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/_DzPosition.py
uav_msgs/CMakeFiles/uav_msgs_generate_messages_py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/_PrecLoit.py
uav_msgs/CMakeFiles/uav_msgs_generate_messages_py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/_PilotOverride.py
uav_msgs/CMakeFiles/uav_msgs_generate_messages_py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/_DetectQR.py
uav_msgs/CMakeFiles/uav_msgs_generate_messages_py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/_DetectObject.py
uav_msgs/CMakeFiles/uav_msgs_generate_messages_py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/_SetCurrent.py
uav_msgs/CMakeFiles/uav_msgs_generate_messages_py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/__init__.py
uav_msgs/CMakeFiles/uav_msgs_generate_messages_py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/__init__.py


/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/_MissionParams.py: /opt/ros/noetic/lib/genpy/genmsg_py.py
/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/_MissionParams.py: /home/vtol2022/aksantara_ws/src/uav_msgs/msg/MissionParams.msg
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/vtol2022/aksantara_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating Python from MSG uav_msgs/MissionParams"
	cd /home/vtol2022/aksantara_ws/build/uav_msgs && ../catkin_generated/env_cached.sh /usr/bin/python3 /opt/ros/noetic/share/genpy/cmake/../../../lib/genpy/genmsg_py.py /home/vtol2022/aksantara_ws/src/uav_msgs/msg/MissionParams.msg -Iuav_msgs:/home/vtol2022/aksantara_ws/src/uav_msgs/msg -Igeographic_msgs:/opt/ros/noetic/share/geographic_msgs/cmake/../msg -Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg -Isensor_msgs:/opt/ros/noetic/share/sensor_msgs/cmake/../msg -Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg -Iuuid_msgs:/opt/ros/noetic/share/uuid_msgs/cmake/../msg -p uav_msgs -o /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg

/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/_PrecLand.py: /opt/ros/noetic/lib/genpy/genmsg_py.py
/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/_PrecLand.py: /home/vtol2022/aksantara_ws/src/uav_msgs/msg/PrecLand.msg
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/vtol2022/aksantara_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating Python from MSG uav_msgs/PrecLand"
	cd /home/vtol2022/aksantara_ws/build/uav_msgs && ../catkin_generated/env_cached.sh /usr/bin/python3 /opt/ros/noetic/share/genpy/cmake/../../../lib/genpy/genmsg_py.py /home/vtol2022/aksantara_ws/src/uav_msgs/msg/PrecLand.msg -Iuav_msgs:/home/vtol2022/aksantara_ws/src/uav_msgs/msg -Igeographic_msgs:/opt/ros/noetic/share/geographic_msgs/cmake/../msg -Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg -Isensor_msgs:/opt/ros/noetic/share/sensor_msgs/cmake/../msg -Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg -Iuuid_msgs:/opt/ros/noetic/share/uuid_msgs/cmake/../msg -p uav_msgs -o /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg

/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/_DzPosition.py: /opt/ros/noetic/lib/genpy/genmsg_py.py
/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/_DzPosition.py: /home/vtol2022/aksantara_ws/src/uav_msgs/msg/DzPosition.msg
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/vtol2022/aksantara_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Generating Python from MSG uav_msgs/DzPosition"
	cd /home/vtol2022/aksantara_ws/build/uav_msgs && ../catkin_generated/env_cached.sh /usr/bin/python3 /opt/ros/noetic/share/genpy/cmake/../../../lib/genpy/genmsg_py.py /home/vtol2022/aksantara_ws/src/uav_msgs/msg/DzPosition.msg -Iuav_msgs:/home/vtol2022/aksantara_ws/src/uav_msgs/msg -Igeographic_msgs:/opt/ros/noetic/share/geographic_msgs/cmake/../msg -Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg -Isensor_msgs:/opt/ros/noetic/share/sensor_msgs/cmake/../msg -Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg -Iuuid_msgs:/opt/ros/noetic/share/uuid_msgs/cmake/../msg -p uav_msgs -o /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg

/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/_PrecLoit.py: /opt/ros/noetic/lib/genpy/genmsg_py.py
/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/_PrecLoit.py: /home/vtol2022/aksantara_ws/src/uav_msgs/msg/PrecLoit.msg
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/vtol2022/aksantara_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Generating Python from MSG uav_msgs/PrecLoit"
	cd /home/vtol2022/aksantara_ws/build/uav_msgs && ../catkin_generated/env_cached.sh /usr/bin/python3 /opt/ros/noetic/share/genpy/cmake/../../../lib/genpy/genmsg_py.py /home/vtol2022/aksantara_ws/src/uav_msgs/msg/PrecLoit.msg -Iuav_msgs:/home/vtol2022/aksantara_ws/src/uav_msgs/msg -Igeographic_msgs:/opt/ros/noetic/share/geographic_msgs/cmake/../msg -Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg -Isensor_msgs:/opt/ros/noetic/share/sensor_msgs/cmake/../msg -Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg -Iuuid_msgs:/opt/ros/noetic/share/uuid_msgs/cmake/../msg -p uav_msgs -o /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg

/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/_PilotOverride.py: /opt/ros/noetic/lib/genpy/gensrv_py.py
/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/_PilotOverride.py: /home/vtol2022/aksantara_ws/src/uav_msgs/srv/PilotOverride.srv
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/vtol2022/aksantara_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Generating Python code from SRV uav_msgs/PilotOverride"
	cd /home/vtol2022/aksantara_ws/build/uav_msgs && ../catkin_generated/env_cached.sh /usr/bin/python3 /opt/ros/noetic/share/genpy/cmake/../../../lib/genpy/gensrv_py.py /home/vtol2022/aksantara_ws/src/uav_msgs/srv/PilotOverride.srv -Iuav_msgs:/home/vtol2022/aksantara_ws/src/uav_msgs/msg -Igeographic_msgs:/opt/ros/noetic/share/geographic_msgs/cmake/../msg -Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg -Isensor_msgs:/opt/ros/noetic/share/sensor_msgs/cmake/../msg -Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg -Iuuid_msgs:/opt/ros/noetic/share/uuid_msgs/cmake/../msg -p uav_msgs -o /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv

/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/_DetectQR.py: /opt/ros/noetic/lib/genpy/gensrv_py.py
/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/_DetectQR.py: /home/vtol2022/aksantara_ws/src/uav_msgs/srv/DetectQR.srv
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/vtol2022/aksantara_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Generating Python code from SRV uav_msgs/DetectQR"
	cd /home/vtol2022/aksantara_ws/build/uav_msgs && ../catkin_generated/env_cached.sh /usr/bin/python3 /opt/ros/noetic/share/genpy/cmake/../../../lib/genpy/gensrv_py.py /home/vtol2022/aksantara_ws/src/uav_msgs/srv/DetectQR.srv -Iuav_msgs:/home/vtol2022/aksantara_ws/src/uav_msgs/msg -Igeographic_msgs:/opt/ros/noetic/share/geographic_msgs/cmake/../msg -Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg -Isensor_msgs:/opt/ros/noetic/share/sensor_msgs/cmake/../msg -Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg -Iuuid_msgs:/opt/ros/noetic/share/uuid_msgs/cmake/../msg -p uav_msgs -o /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv

/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/_DetectObject.py: /opt/ros/noetic/lib/genpy/gensrv_py.py
/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/_DetectObject.py: /home/vtol2022/aksantara_ws/src/uav_msgs/srv/DetectObject.srv
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/vtol2022/aksantara_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Generating Python code from SRV uav_msgs/DetectObject"
	cd /home/vtol2022/aksantara_ws/build/uav_msgs && ../catkin_generated/env_cached.sh /usr/bin/python3 /opt/ros/noetic/share/genpy/cmake/../../../lib/genpy/gensrv_py.py /home/vtol2022/aksantara_ws/src/uav_msgs/srv/DetectObject.srv -Iuav_msgs:/home/vtol2022/aksantara_ws/src/uav_msgs/msg -Igeographic_msgs:/opt/ros/noetic/share/geographic_msgs/cmake/../msg -Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg -Isensor_msgs:/opt/ros/noetic/share/sensor_msgs/cmake/../msg -Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg -Iuuid_msgs:/opt/ros/noetic/share/uuid_msgs/cmake/../msg -p uav_msgs -o /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv

/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/_SetCurrent.py: /opt/ros/noetic/lib/genpy/gensrv_py.py
/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/_SetCurrent.py: /home/vtol2022/aksantara_ws/src/uav_msgs/srv/SetCurrent.srv
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/vtol2022/aksantara_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Generating Python code from SRV uav_msgs/SetCurrent"
	cd /home/vtol2022/aksantara_ws/build/uav_msgs && ../catkin_generated/env_cached.sh /usr/bin/python3 /opt/ros/noetic/share/genpy/cmake/../../../lib/genpy/gensrv_py.py /home/vtol2022/aksantara_ws/src/uav_msgs/srv/SetCurrent.srv -Iuav_msgs:/home/vtol2022/aksantara_ws/src/uav_msgs/msg -Igeographic_msgs:/opt/ros/noetic/share/geographic_msgs/cmake/../msg -Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg -Isensor_msgs:/opt/ros/noetic/share/sensor_msgs/cmake/../msg -Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg -Iuuid_msgs:/opt/ros/noetic/share/uuid_msgs/cmake/../msg -p uav_msgs -o /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv

/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/__init__.py: /opt/ros/noetic/lib/genpy/genmsg_py.py
/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/__init__.py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/_MissionParams.py
/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/__init__.py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/_PrecLand.py
/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/__init__.py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/_DzPosition.py
/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/__init__.py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/_PrecLoit.py
/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/__init__.py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/_PilotOverride.py
/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/__init__.py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/_DetectQR.py
/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/__init__.py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/_DetectObject.py
/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/__init__.py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/_SetCurrent.py
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/vtol2022/aksantara_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Generating Python msg __init__.py for uav_msgs"
	cd /home/vtol2022/aksantara_ws/build/uav_msgs && ../catkin_generated/env_cached.sh /usr/bin/python3 /opt/ros/noetic/share/genpy/cmake/../../../lib/genpy/genmsg_py.py -o /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg --initpy

/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/__init__.py: /opt/ros/noetic/lib/genpy/genmsg_py.py
/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/__init__.py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/_MissionParams.py
/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/__init__.py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/_PrecLand.py
/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/__init__.py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/_DzPosition.py
/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/__init__.py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/_PrecLoit.py
/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/__init__.py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/_PilotOverride.py
/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/__init__.py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/_DetectQR.py
/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/__init__.py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/_DetectObject.py
/home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/__init__.py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/_SetCurrent.py
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/vtol2022/aksantara_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Generating Python srv __init__.py for uav_msgs"
	cd /home/vtol2022/aksantara_ws/build/uav_msgs && ../catkin_generated/env_cached.sh /usr/bin/python3 /opt/ros/noetic/share/genpy/cmake/../../../lib/genpy/genmsg_py.py -o /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv --initpy

uav_msgs_generate_messages_py: uav_msgs/CMakeFiles/uav_msgs_generate_messages_py
uav_msgs_generate_messages_py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/_MissionParams.py
uav_msgs_generate_messages_py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/_PrecLand.py
uav_msgs_generate_messages_py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/_DzPosition.py
uav_msgs_generate_messages_py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/_PrecLoit.py
uav_msgs_generate_messages_py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/_PilotOverride.py
uav_msgs_generate_messages_py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/_DetectQR.py
uav_msgs_generate_messages_py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/_DetectObject.py
uav_msgs_generate_messages_py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/_SetCurrent.py
uav_msgs_generate_messages_py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/msg/__init__.py
uav_msgs_generate_messages_py: /home/vtol2022/aksantara_ws/devel/lib/python3/dist-packages/uav_msgs/srv/__init__.py
uav_msgs_generate_messages_py: uav_msgs/CMakeFiles/uav_msgs_generate_messages_py.dir/build.make

.PHONY : uav_msgs_generate_messages_py

# Rule to build all files generated by this target.
uav_msgs/CMakeFiles/uav_msgs_generate_messages_py.dir/build: uav_msgs_generate_messages_py

.PHONY : uav_msgs/CMakeFiles/uav_msgs_generate_messages_py.dir/build

uav_msgs/CMakeFiles/uav_msgs_generate_messages_py.dir/clean:
	cd /home/vtol2022/aksantara_ws/build/uav_msgs && $(CMAKE_COMMAND) -P CMakeFiles/uav_msgs_generate_messages_py.dir/cmake_clean.cmake
.PHONY : uav_msgs/CMakeFiles/uav_msgs_generate_messages_py.dir/clean

uav_msgs/CMakeFiles/uav_msgs_generate_messages_py.dir/depend:
	cd /home/vtol2022/aksantara_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vtol2022/aksantara_ws/src /home/vtol2022/aksantara_ws/src/uav_msgs /home/vtol2022/aksantara_ws/build /home/vtol2022/aksantara_ws/build/uav_msgs /home/vtol2022/aksantara_ws/build/uav_msgs/CMakeFiles/uav_msgs_generate_messages_py.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : uav_msgs/CMakeFiles/uav_msgs_generate_messages_py.dir/depend
