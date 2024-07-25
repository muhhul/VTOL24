# Install script for directory: /home/karol/Aksantara/VTOL24/aksan2023_ws/src/uav_msgs

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/karol/Aksantara/VTOL24/aksan2023_ws/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/uav_msgs/msg" TYPE FILE FILES
    "/home/karol/Aksantara/VTOL24/aksan2023_ws/src/uav_msgs/msg/MissionParams.msg"
    "/home/karol/Aksantara/VTOL24/aksan2023_ws/src/uav_msgs/msg/PrecLand.msg"
    "/home/karol/Aksantara/VTOL24/aksan2023_ws/src/uav_msgs/msg/DzPosition.msg"
    "/home/karol/Aksantara/VTOL24/aksan2023_ws/src/uav_msgs/msg/PrecLoit.msg"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/uav_msgs/srv" TYPE FILE FILES
    "/home/karol/Aksantara/VTOL24/aksan2023_ws/src/uav_msgs/srv/PilotOverride.srv"
    "/home/karol/Aksantara/VTOL24/aksan2023_ws/src/uav_msgs/srv/DetectQR.srv"
    "/home/karol/Aksantara/VTOL24/aksan2023_ws/src/uav_msgs/srv/DetectObject.srv"
    "/home/karol/Aksantara/VTOL24/aksan2023_ws/src/uav_msgs/srv/SetCurrent.srv"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/uav_msgs/cmake" TYPE FILE FILES "/home/karol/Aksantara/VTOL24/aksan2023_ws/build/uav_msgs/catkin_generated/installspace/uav_msgs-msg-paths.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/include/uav_msgs")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/share/roseus/ros/uav_msgs")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/share/common-lisp/ros/uav_msgs")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/share/gennodejs/ros/uav_msgs")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND "/usr/bin/python3" -m compileall "/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/python3/dist-packages/uav_msgs")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages" TYPE DIRECTORY FILES "/home/karol/Aksantara/VTOL24/aksan2023_ws/devel/lib/python3/dist-packages/uav_msgs")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/karol/Aksantara/VTOL24/aksan2023_ws/build/uav_msgs/catkin_generated/installspace/uav_msgs.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/uav_msgs/cmake" TYPE FILE FILES "/home/karol/Aksantara/VTOL24/aksan2023_ws/build/uav_msgs/catkin_generated/installspace/uav_msgs-msg-extras.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/uav_msgs/cmake" TYPE FILE FILES
    "/home/karol/Aksantara/VTOL24/aksan2023_ws/build/uav_msgs/catkin_generated/installspace/uav_msgsConfig.cmake"
    "/home/karol/Aksantara/VTOL24/aksan2023_ws/build/uav_msgs/catkin_generated/installspace/uav_msgsConfig-version.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/uav_msgs" TYPE FILE FILES "/home/karol/Aksantara/VTOL24/aksan2023_ws/src/uav_msgs/package.xml")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/uav_msgs" TYPE DIRECTORY FILES "/home/karol/Aksantara/VTOL24/aksan2023_ws/src/uav_msgs/include/uav_msgs/" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

