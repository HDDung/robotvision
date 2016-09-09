cmake_minimum_required(VERSION 2.8.3)
project(robotvision)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  OpenCV
  cv_bridge
  image_transport
  genmsg
  std_msgs
  message_generation
)

add_message_files( DIRECTORY msg
  FILES ImageCusMess.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
  sensor_msgs
)

catkin_package()

catkin_package(CATKIN_DEPENDS message_runtime)



find_package(OpenCV REQUIRED)
include_directories(include ${OpenCV_INCLUDE_DIRS})

#add the publisher example
add_executable(FaceVision src/FaceDetect.cpp 
    src/Core/DataHandler.cpp
    src/Core/FaceDetector.cpp 
    src/Core/FaceRecognition.cpp 
    src/Core/NewFaces.cpp
    src/Data/Face.cpp
    src/Data/ListFace.cpp)
target_link_libraries(FaceVision ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})


#add the publisher camera
add_executable(CameraHandle src/CameraHandler/camera_handler.cpp)
target_link_libraries(CameraHandle ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})

#add the displayer camera
add_executable(CameraDisplayer src/CameraDisplayer/camera_displayer.cpp)
target_link_libraries(CameraDisplayer ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})






