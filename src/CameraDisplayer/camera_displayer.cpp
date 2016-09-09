#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <cv_bridge/cv_bridge.h>
#include <iostream>
#include "robotvision/ImageCusMess.h"

void imageCallback(const robotvision::ImageCusMessConstPtr& msg)
{
  try
  {
    cv::Mat im =  cv_bridge::toCvShare(msg->image, msg, "bgr8")->image;
    cv::imshow(msg->WindowsName, im);
    cv::waitKey(10);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Unhandle msg");
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "CameraDisplayer");
  ros::NodeHandle handler;
  std::cout << "Begin display image" << std::endl;
  ros::Subscriber sub1 = handler.subscribe("camera/FaceDetectImage1", 1, imageCallback);
  ros::spin();

  cv::destroyAllWindows();
}