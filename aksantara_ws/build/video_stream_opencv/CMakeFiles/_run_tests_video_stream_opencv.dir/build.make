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
CMAKE_SOURCE_DIR = /home/docker/Aksantara/VTOL24/aksantara_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/docker/Aksantara/VTOL24/aksantara_ws/build

# Utility rule file for _run_tests_video_stream_opencv.

# Include the progress variables for this target.
include video_stream_opencv/CMakeFiles/_run_tests_video_stream_opencv.dir/progress.make

_run_tests_video_stream_opencv: video_stream_opencv/CMakeFiles/_run_tests_video_stream_opencv.dir/build.make

.PHONY : _run_tests_video_stream_opencv

# Rule to build all files generated by this target.
video_stream_opencv/CMakeFiles/_run_tests_video_stream_opencv.dir/build: _run_tests_video_stream_opencv

.PHONY : video_stream_opencv/CMakeFiles/_run_tests_video_stream_opencv.dir/build

video_stream_opencv/CMakeFiles/_run_tests_video_stream_opencv.dir/clean:
	cd /home/docker/Aksantara/VTOL24/aksantara_ws/build/video_stream_opencv && $(CMAKE_COMMAND) -P CMakeFiles/_run_tests_video_stream_opencv.dir/cmake_clean.cmake
.PHONY : video_stream_opencv/CMakeFiles/_run_tests_video_stream_opencv.dir/clean

video_stream_opencv/CMakeFiles/_run_tests_video_stream_opencv.dir/depend:
	cd /home/docker/Aksantara/VTOL24/aksantara_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/docker/Aksantara/VTOL24/aksantara_ws/src /home/docker/Aksantara/VTOL24/aksantara_ws/src/video_stream_opencv /home/docker/Aksantara/VTOL24/aksantara_ws/build /home/docker/Aksantara/VTOL24/aksantara_ws/build/video_stream_opencv /home/docker/Aksantara/VTOL24/aksantara_ws/build/video_stream_opencv/CMakeFiles/_run_tests_video_stream_opencv.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : video_stream_opencv/CMakeFiles/_run_tests_video_stream_opencv.dir/depend

