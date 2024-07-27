cmake_minimum_required(VERSION 3.5.0)
project(eksperimen_opencv VERSION 0.1.0 LANGUAGES C CXX)

find_package( OpenCV REQUIRED )

include_directories( 
    ${OpenCV_INCLUDE_DIRS} 
    src/gate_detection
    )

add_executable(eksperimen_opencv 
    main.cpp
    src/gate_detection/gate_detection.cpp
    )

add_executable(segmentation_experimenting 
    segmentation_experimenting.cpp
    src/gate_detection/gate_detection.cpp
    )

target_link_libraries( eksperimen_opencv ${OpenCV_LIBS} )
target_link_libraries( segmentation_experimenting ${OpenCV_LIBS} )