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
CMAKE_SOURCE_DIR = /home/vtol2022/aksan2023_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vtol2022/aksan2023_ws/build

# Include any dependencies generated for this target.
include uav_commander/CMakeFiles/safety_node.dir/depend.make

# Include the progress variables for this target.
include uav_commander/CMakeFiles/safety_node.dir/progress.make

# Include the compile flags for this target's objects.
include uav_commander/CMakeFiles/safety_node.dir/flags.make

uav_commander/CMakeFiles/safety_node.dir/src/uav_commander/safety_node.cpp.o: uav_commander/CMakeFiles/safety_node.dir/flags.make
uav_commander/CMakeFiles/safety_node.dir/src/uav_commander/safety_node.cpp.o: /home/vtol2022/aksan2023_ws/src/uav_commander/src/uav_commander/safety_node.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vtol2022/aksan2023_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object uav_commander/CMakeFiles/safety_node.dir/src/uav_commander/safety_node.cpp.o"
	cd /home/vtol2022/aksan2023_ws/build/uav_commander && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/safety_node.dir/src/uav_commander/safety_node.cpp.o -c /home/vtol2022/aksan2023_ws/src/uav_commander/src/uav_commander/safety_node.cpp

uav_commander/CMakeFiles/safety_node.dir/src/uav_commander/safety_node.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/safety_node.dir/src/uav_commander/safety_node.cpp.i"
	cd /home/vtol2022/aksan2023_ws/build/uav_commander && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vtol2022/aksan2023_ws/src/uav_commander/src/uav_commander/safety_node.cpp > CMakeFiles/safety_node.dir/src/uav_commander/safety_node.cpp.i

uav_commander/CMakeFiles/safety_node.dir/src/uav_commander/safety_node.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/safety_node.dir/src/uav_commander/safety_node.cpp.s"
	cd /home/vtol2022/aksan2023_ws/build/uav_commander && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vtol2022/aksan2023_ws/src/uav_commander/src/uav_commander/safety_node.cpp -o CMakeFiles/safety_node.dir/src/uav_commander/safety_node.cpp.s

# Object files for target safety_node
safety_node_OBJECTS = \
"CMakeFiles/safety_node.dir/src/uav_commander/safety_node.cpp.o"

# External object files for target safety_node
safety_node_EXTERNAL_OBJECTS =

/home/vtol2022/aksan2023_ws/devel/lib/uav_commander/safety_node: uav_commander/CMakeFiles/safety_node.dir/src/uav_commander/safety_node.cpp.o
/home/vtol2022/aksan2023_ws/devel/lib/uav_commander/safety_node: uav_commander/CMakeFiles/safety_node.dir/build.make
/home/vtol2022/aksan2023_ws/devel/lib/uav_commander/safety_node: /opt/ros/noetic/lib/libtf2_ros.so
/home/vtol2022/aksan2023_ws/devel/lib/uav_commander/safety_node: /opt/ros/noetic/lib/libactionlib.so
/home/vtol2022/aksan2023_ws/devel/lib/uav_commander/safety_node: /opt/ros/noetic/lib/libmessage_filters.so
/home/vtol2022/aksan2023_ws/devel/lib/uav_commander/safety_node: /opt/ros/noetic/lib/libroscpp.so
/home/vtol2022/aksan2023_ws/devel/lib/uav_commander/safety_node: /usr/lib/x86_64-linux-gnu/libpthread.so
/home/vtol2022/aksan2023_ws/devel/lib/uav_commander/safety_node: /usr/lib/x86_64-linux-gnu/libboost_chrono.so.1.71.0
/home/vtol2022/aksan2023_ws/devel/lib/uav_commander/safety_node: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.71.0
/home/vtol2022/aksan2023_ws/devel/lib/uav_commander/safety_node: /opt/ros/noetic/lib/librosconsole.so
/home/vtol2022/aksan2023_ws/devel/lib/uav_commander/safety_node: /opt/ros/noetic/lib/librosconsole_log4cxx.so
/home/vtol2022/aksan2023_ws/devel/lib/uav_commander/safety_node: /opt/ros/noetic/lib/librosconsole_backend_interface.so
/home/vtol2022/aksan2023_ws/devel/lib/uav_commander/safety_node: /usr/lib/x86_64-linux-gnu/liblog4cxx.so
/home/vtol2022/aksan2023_ws/devel/lib/uav_commander/safety_node: /usr/lib/x86_64-linux-gnu/libboost_regex.so.1.71.0
/home/vtol2022/aksan2023_ws/devel/lib/uav_commander/safety_node: /opt/ros/noetic/lib/libxmlrpcpp.so
/home/vtol2022/aksan2023_ws/devel/lib/uav_commander/safety_node: /opt/ros/noetic/lib/libtf2.so
/home/vtol2022/aksan2023_ws/devel/lib/uav_commander/safety_node: /opt/ros/noetic/lib/libroscpp_serialization.so
/home/vtol2022/aksan2023_ws/devel/lib/uav_commander/safety_node: /opt/ros/noetic/lib/librostime.so
/home/vtol2022/aksan2023_ws/devel/lib/uav_commander/safety_node: /usr/lib/x86_64-linux-gnu/libboost_date_time.so.1.71.0
/home/vtol2022/aksan2023_ws/devel/lib/uav_commander/safety_node: /opt/ros/noetic/lib/libcpp_common.so
/home/vtol2022/aksan2023_ws/devel/lib/uav_commander/safety_node: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.71.0
/home/vtol2022/aksan2023_ws/devel/lib/uav_commander/safety_node: /usr/lib/x86_64-linux-gnu/libboost_thread.so.1.71.0
/home/vtol2022/aksan2023_ws/devel/lib/uav_commander/safety_node: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so.0.4
/home/vtol2022/aksan2023_ws/devel/lib/uav_commander/safety_node: uav_commander/CMakeFiles/safety_node.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vtol2022/aksan2023_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/vtol2022/aksan2023_ws/devel/lib/uav_commander/safety_node"
	cd /home/vtol2022/aksan2023_ws/build/uav_commander && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/safety_node.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
uav_commander/CMakeFiles/safety_node.dir/build: /home/vtol2022/aksan2023_ws/devel/lib/uav_commander/safety_node

.PHONY : uav_commander/CMakeFiles/safety_node.dir/build

uav_commander/CMakeFiles/safety_node.dir/clean:
	cd /home/vtol2022/aksan2023_ws/build/uav_commander && $(CMAKE_COMMAND) -P CMakeFiles/safety_node.dir/cmake_clean.cmake
.PHONY : uav_commander/CMakeFiles/safety_node.dir/clean

uav_commander/CMakeFiles/safety_node.dir/depend:
	cd /home/vtol2022/aksan2023_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vtol2022/aksan2023_ws/src /home/vtol2022/aksan2023_ws/src/uav_commander /home/vtol2022/aksan2023_ws/build /home/vtol2022/aksan2023_ws/build/uav_commander /home/vtol2022/aksan2023_ws/build/uav_commander/CMakeFiles/safety_node.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : uav_commander/CMakeFiles/safety_node.dir/depend

