# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/karol/.local/lib/python3.8/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/karol/.local/lib/python3.8/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/karol/Aksantara/VTOL24/aksan2023_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/karol/Aksantara/VTOL24/aksan2023_ws/build

# Include any dependencies generated for this target.
include uav_teleop/CMakeFiles/keyboard.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include uav_teleop/CMakeFiles/keyboard.dir/compiler_depend.make

# Include the progress variables for this target.
include uav_teleop/CMakeFiles/keyboard.dir/progress.make

# Include the compile flags for this target's objects.
include uav_teleop/CMakeFiles/keyboard.dir/flags.make

uav_teleop/CMakeFiles/keyboard.dir/src/main.cpp.o: uav_teleop/CMakeFiles/keyboard.dir/flags.make
uav_teleop/CMakeFiles/keyboard.dir/src/main.cpp.o: /home/karol/Aksantara/VTOL24/aksan2023_ws/src/uav_teleop/src/main.cpp
uav_teleop/CMakeFiles/keyboard.dir/src/main.cpp.o: uav_teleop/CMakeFiles/keyboard.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/karol/Aksantara/VTOL24/aksan2023_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object uav_teleop/CMakeFiles/keyboard.dir/src/main.cpp.o"
	cd /home/karol/Aksantara/VTOL24/aksan2023_ws/build/uav_teleop && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT uav_teleop/CMakeFiles/keyboard.dir/src/main.cpp.o -MF CMakeFiles/keyboard.dir/src/main.cpp.o.d -o CMakeFiles/keyboard.dir/src/main.cpp.o -c /home/karol/Aksantara/VTOL24/aksan2023_ws/src/uav_teleop/src/main.cpp

uav_teleop/CMakeFiles/keyboard.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/keyboard.dir/src/main.cpp.i"
	cd /home/karol/Aksantara/VTOL24/aksan2023_ws/build/uav_teleop && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/karol/Aksantara/VTOL24/aksan2023_ws/src/uav_teleop/src/main.cpp > CMakeFiles/keyboard.dir/src/main.cpp.i

uav_teleop/CMakeFiles/keyboard.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/keyboard.dir/src/main.cpp.s"
	cd /home/karol/Aksantara/VTOL24/aksan2023_ws/build/uav_teleop && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/karol/Aksantara/VTOL24/aksan2023_ws/src/uav_teleop/src/main.cpp -o CMakeFiles/keyboard.dir/src/main.cpp.s

uav_teleop/CMakeFiles/keyboard.dir/src/keyboard.cpp.o: uav_teleop/CMakeFiles/keyboard.dir/flags.make
uav_teleop/CMakeFiles/keyboard.dir/src/keyboard.cpp.o: /home/karol/Aksantara/VTOL24/aksan2023_ws/src/uav_teleop/src/keyboard.cpp
uav_teleop/CMakeFiles/keyboard.dir/src/keyboard.cpp.o: uav_teleop/CMakeFiles/keyboard.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/karol/Aksantara/VTOL24/aksan2023_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object uav_teleop/CMakeFiles/keyboard.dir/src/keyboard.cpp.o"
	cd /home/karol/Aksantara/VTOL24/aksan2023_ws/build/uav_teleop && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT uav_teleop/CMakeFiles/keyboard.dir/src/keyboard.cpp.o -MF CMakeFiles/keyboard.dir/src/keyboard.cpp.o.d -o CMakeFiles/keyboard.dir/src/keyboard.cpp.o -c /home/karol/Aksantara/VTOL24/aksan2023_ws/src/uav_teleop/src/keyboard.cpp

uav_teleop/CMakeFiles/keyboard.dir/src/keyboard.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/keyboard.dir/src/keyboard.cpp.i"
	cd /home/karol/Aksantara/VTOL24/aksan2023_ws/build/uav_teleop && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/karol/Aksantara/VTOL24/aksan2023_ws/src/uav_teleop/src/keyboard.cpp > CMakeFiles/keyboard.dir/src/keyboard.cpp.i

uav_teleop/CMakeFiles/keyboard.dir/src/keyboard.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/keyboard.dir/src/keyboard.cpp.s"
	cd /home/karol/Aksantara/VTOL24/aksan2023_ws/build/uav_teleop && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/karol/Aksantara/VTOL24/aksan2023_ws/src/uav_teleop/src/keyboard.cpp -o CMakeFiles/keyboard.dir/src/keyboard.cpp.s

# Object files for target keyboard
keyboard_OBJECTS = \
"CMakeFiles/keyboard.dir/src/main.cpp.o" \
"CMakeFiles/keyboard.dir/src/keyboard.cpp.o"

# External object files for target keyboard
keyboard_EXTERNAL_OBJECTS =

/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/uav_teleop/keyboard: uav_teleop/CMakeFiles/keyboard.dir/src/main.cpp.o
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/uav_teleop/keyboard: uav_teleop/CMakeFiles/keyboard.dir/src/keyboard.cpp.o
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/uav_teleop/keyboard: uav_teleop/CMakeFiles/keyboard.dir/build.make
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/uav_teleop/keyboard: /usr/lib/x86_64-linux-gnu/libSDLmain.a
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/uav_teleop/keyboard: /usr/lib/x86_64-linux-gnu/libSDL.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/uav_teleop/keyboard: /opt/ros/noetic/lib/libroscpp.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/uav_teleop/keyboard: /usr/lib/x86_64-linux-gnu/libpthread.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/uav_teleop/keyboard: /usr/lib/x86_64-linux-gnu/libboost_chrono.so.1.71.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/uav_teleop/keyboard: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.71.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/uav_teleop/keyboard: /opt/ros/noetic/lib/librosconsole.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/uav_teleop/keyboard: /opt/ros/noetic/lib/librosconsole_log4cxx.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/uav_teleop/keyboard: /opt/ros/noetic/lib/librosconsole_backend_interface.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/uav_teleop/keyboard: /usr/lib/x86_64-linux-gnu/liblog4cxx.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/uav_teleop/keyboard: /usr/lib/x86_64-linux-gnu/libboost_regex.so.1.71.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/uav_teleop/keyboard: /opt/ros/noetic/lib/libxmlrpcpp.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/uav_teleop/keyboard: /opt/ros/noetic/lib/libroscpp_serialization.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/uav_teleop/keyboard: /opt/ros/noetic/lib/librostime.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/uav_teleop/keyboard: /usr/lib/x86_64-linux-gnu/libboost_date_time.so.1.71.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/uav_teleop/keyboard: /opt/ros/noetic/lib/libcpp_common.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/uav_teleop/keyboard: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.71.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/uav_teleop/keyboard: /usr/lib/x86_64-linux-gnu/libboost_thread.so.1.71.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/uav_teleop/keyboard: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so.0.4
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/uav_teleop/keyboard: uav_teleop/CMakeFiles/keyboard.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/karol/Aksantara/VTOL24/aksan2023_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable /home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/uav_teleop/keyboard"
	cd /home/karol/Aksantara/VTOL24/aksan2023_ws/build/uav_teleop && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/keyboard.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
uav_teleop/CMakeFiles/keyboard.dir/build: /home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/uav_teleop/keyboard
.PHONY : uav_teleop/CMakeFiles/keyboard.dir/build

uav_teleop/CMakeFiles/keyboard.dir/clean:
	cd /home/karol/Aksantara/VTOL24/aksan2023_ws/build/uav_teleop && $(CMAKE_COMMAND) -P CMakeFiles/keyboard.dir/cmake_clean.cmake
.PHONY : uav_teleop/CMakeFiles/keyboard.dir/clean

uav_teleop/CMakeFiles/keyboard.dir/depend:
	cd /home/karol/Aksantara/VTOL24/aksan2023_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/karol/Aksantara/VTOL24/aksan2023_ws/src /home/karol/Aksantara/VTOL24/aksan2023_ws/src/uav_teleop /home/karol/Aksantara/VTOL24/aksan2023_ws/build /home/karol/Aksantara/VTOL24/aksan2023_ws/build/uav_teleop /home/karol/Aksantara/VTOL24/aksan2023_ws/build/uav_teleop/CMakeFiles/keyboard.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : uav_teleop/CMakeFiles/keyboard.dir/depend

