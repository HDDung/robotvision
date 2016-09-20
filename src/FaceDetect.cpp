//============================================================================
// Name        : FaceDetect.cpp
// Author      : KenKoko
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <ros/ros.h>
#include <ros/package.h>
#include <csignal>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>


#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"
#include <iostream>
#include <stdio.h>
#include <string>

#include "Core/DataHandler.h"
#include "Core/FaceRecognition.h"
#include "Core/FaceDetector.h"

#include "robotvision/ImageCusMess.h"
#include <time.h>
#define h 280
#define w 320
using namespace std;
using namespace cv;


//Global variable decleartation
FaceDetector dtor1;
bool stop = false;
time_t start,end;
int counter;
void FaceProgessing(const robotvision::ImageCusMessConstPtr& msg)
{
  try
  {
    cv::Mat frame =  cv_bridge::toCvShare(msg->image, msg, "bgr8")->image;
    if( frame.empty() ) printf(" --(!) No captured frame -- Break!\n") ;
    //cv::imshow("Mi5", frame);
    //-- bail out if escape was pressed
    waitKey(10);

    FaceRecognition recog(frame);
    recog.detectAndDisplay(dtor1);

    time(&end);
    ++counter;
    double sec=difftime(end,start);
    double fps=counter/sec;
    std::cout << "Hello "<<fps << std::endl;
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("There sthg wrong with the msg");
  }
}

int main(int argc, char** argv)
{

	// Iniziall state 
  	ros::init(argc, argv, "FaceProgessing");
  	ros::NodeHandle nodehandle;
   

	//std::signal(SIGINT, sigIntHandler);


    //Get data
    std::string path = ros::package::getPath("robotvision");
    path = path + "/Database/face";
    char link[1024];
    strcpy(link, path.c_str());
    DataHandler handler = DataHandler(link);

    //Training data
    dtor1.LoadList(handler.LoadData());
    dtor1.Training();


    //-- 2. Read the video stream
    time(&start);
    counter=0;
    while (1){
    	ros::Subscriber sub1 = nodehandle.subscribe("camera/FaceDetectImage1", 1, FaceProgessing);

      

    	int c = waitKey(10);
    	if( (char)c == 27 || !nodehandle.ok()) {  
    		std::cout <<"Killing node" << std::endl;
    		destroyAllWindows(); ros::shutdown(); break; 
    	} else {
    		ros::spin();
    	}
   	
    }
    std::cout << "Beging UpdateData" << std::endl;
    dtor1.GiveUtor().UpdateData(handler);

	return 0;
}
