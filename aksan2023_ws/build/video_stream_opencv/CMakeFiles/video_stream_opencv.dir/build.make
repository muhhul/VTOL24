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
include video_stream_opencv/CMakeFiles/video_stream_opencv.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include video_stream_opencv/CMakeFiles/video_stream_opencv.dir/compiler_depend.make

# Include the progress variables for this target.
include video_stream_opencv/CMakeFiles/video_stream_opencv.dir/progress.make

# Include the compile flags for this target's objects.
include video_stream_opencv/CMakeFiles/video_stream_opencv.dir/flags.make

video_stream_opencv/CMakeFiles/video_stream_opencv.dir/src/video_stream.cpp.o: video_stream_opencv/CMakeFiles/video_stream_opencv.dir/flags.make
video_stream_opencv/CMakeFiles/video_stream_opencv.dir/src/video_stream.cpp.o: /home/karol/Aksantara/VTOL24/aksan2023_ws/src/video_stream_opencv/src/video_stream.cpp
video_stream_opencv/CMakeFiles/video_stream_opencv.dir/src/video_stream.cpp.o: video_stream_opencv/CMakeFiles/video_stream_opencv.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/karol/Aksantara/VTOL24/aksan2023_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object video_stream_opencv/CMakeFiles/video_stream_opencv.dir/src/video_stream.cpp.o"
	cd /home/karol/Aksantara/VTOL24/aksan2023_ws/build/video_stream_opencv && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT video_stream_opencv/CMakeFiles/video_stream_opencv.dir/src/video_stream.cpp.o -MF CMakeFiles/video_stream_opencv.dir/src/video_stream.cpp.o.d -o CMakeFiles/video_stream_opencv.dir/src/video_stream.cpp.o -c /home/karol/Aksantara/VTOL24/aksan2023_ws/src/video_stream_opencv/src/video_stream.cpp

video_stream_opencv/CMakeFiles/video_stream_opencv.dir/src/video_stream.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/video_stream_opencv.dir/src/video_stream.cpp.i"
	cd /home/karol/Aksantara/VTOL24/aksan2023_ws/build/video_stream_opencv && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/karol/Aksantara/VTOL24/aksan2023_ws/src/video_stream_opencv/src/video_stream.cpp > CMakeFiles/video_stream_opencv.dir/src/video_stream.cpp.i

video_stream_opencv/CMakeFiles/video_stream_opencv.dir/src/video_stream.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/video_stream_opencv.dir/src/video_stream.cpp.s"
	cd /home/karol/Aksantara/VTOL24/aksan2023_ws/build/video_stream_opencv && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/karol/Aksantara/VTOL24/aksan2023_ws/src/video_stream_opencv/src/video_stream.cpp -o CMakeFiles/video_stream_opencv.dir/src/video_stream.cpp.s

# Object files for target video_stream_opencv
video_stream_opencv_OBJECTS = \
"CMakeFiles/video_stream_opencv.dir/src/video_stream.cpp.o"

# External object files for target video_stream_opencv
video_stream_opencv_EXTERNAL_OBJECTS =

/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: video_stream_opencv/CMakeFiles/video_stream_opencv.dir/src/video_stream.cpp.o
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: video_stream_opencv/CMakeFiles/video_stream_opencv.dir/build.make
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /opt/ros/noetic/lib/libcv_bridge.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_dnn.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_video.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_videoio.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_aruco.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_bgsegm.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_bioinspired.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_ccalib.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_datasets.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_dnn_objdetect.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_dnn_superres.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_dpm.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_face.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_freetype.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_fuzzy.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_hdf.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_hfs.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_img_hash.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_line_descriptor.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_optflow.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_phase_unwrapping.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_plot.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_quality.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_reg.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_rgbd.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_saliency.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_shape.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_stereo.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_structured_light.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_surface_matching.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_text.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_tracking.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_viz.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_ximgproc.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_xobjdetect.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_xphoto.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_core.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_imgcodecs.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /opt/ros/noetic/lib/libimage_transport.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /opt/ros/noetic/lib/libmessage_filters.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /opt/ros/noetic/lib/libcamera_info_manager.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /opt/ros/noetic/lib/libcamera_calibration_parsers.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /opt/ros/noetic/lib/libnodeletlib.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /opt/ros/noetic/lib/libbondcpp.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libuuid.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /opt/ros/noetic/lib/libclass_loader.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libPocoFoundation.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libdl.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /opt/ros/noetic/lib/libroslib.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /opt/ros/noetic/lib/librospack.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libpython3.8.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libboost_program_options.so.1.71.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libtinyxml2.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /opt/ros/noetic/lib/libroscpp.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libpthread.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libboost_chrono.so.1.71.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.71.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /opt/ros/noetic/lib/librosconsole.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /opt/ros/noetic/lib/librosconsole_log4cxx.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /opt/ros/noetic/lib/librosconsole_backend_interface.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/liblog4cxx.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libboost_regex.so.1.71.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /opt/ros/noetic/lib/libxmlrpcpp.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /opt/ros/noetic/lib/libdynamic_reconfigure_config_init_mutex.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /opt/ros/noetic/lib/libroscpp_serialization.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /opt/ros/noetic/lib/librostime.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libboost_date_time.so.1.71.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /opt/ros/noetic/lib/libcpp_common.so
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.71.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libboost_thread.so.1.71.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so.0.4
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_aruco.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_bgsegm.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_bioinspired.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_ccalib.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_dnn_objdetect.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_dnn_superres.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_dpm.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_face.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_freetype.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_fuzzy.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_hdf.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_hfs.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_img_hash.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_line_descriptor.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_quality.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_reg.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_rgbd.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_saliency.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_shape.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_stereo.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_structured_light.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_surface_matching.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_tracking.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_viz.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_xobjdetect.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_xphoto.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_datasets.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_plot.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_text.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_dnn.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_phase_unwrapping.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_optflow.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_ximgproc.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_video.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_videoio.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_imgcodecs.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: /usr/lib/x86_64-linux-gnu/libopencv_core.so.4.2.0
/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so: video_stream_opencv/CMakeFiles/video_stream_opencv.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/karol/Aksantara/VTOL24/aksan2023_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library /home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so"
	cd /home/karol/Aksantara/VTOL24/aksan2023_ws/build/video_stream_opencv && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/video_stream_opencv.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
video_stream_opencv/CMakeFiles/video_stream_opencv.dir/build: /home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/libvideo_stream_opencv.so
.PHONY : video_stream_opencv/CMakeFiles/video_stream_opencv.dir/build

video_stream_opencv/CMakeFiles/video_stream_opencv.dir/clean:
	cd /home/karol/Aksantara/VTOL24/aksan2023_ws/build/video_stream_opencv && $(CMAKE_COMMAND) -P CMakeFiles/video_stream_opencv.dir/cmake_clean.cmake
.PHONY : video_stream_opencv/CMakeFiles/video_stream_opencv.dir/clean

video_stream_opencv/CMakeFiles/video_stream_opencv.dir/depend:
	cd /home/karol/Aksantara/VTOL24/aksan2023_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/karol/Aksantara/VTOL24/aksan2023_ws/src /home/karol/Aksantara/VTOL24/aksan2023_ws/src/video_stream_opencv /home/karol/Aksantara/VTOL24/aksan2023_ws/build /home/karol/Aksantara/VTOL24/aksan2023_ws/build/video_stream_opencv /home/karol/Aksantara/VTOL24/aksan2023_ws/build/video_stream_opencv/CMakeFiles/video_stream_opencv.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : video_stream_opencv/CMakeFiles/video_stream_opencv.dir/depend

