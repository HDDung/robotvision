#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include "robotvision/ImageCusMess.h"


int main(int argc, char** argv)
{
	// Check video source has been passed, if not using defaul camera
	int camera; 
	if (argv[1] == NULL) {
		camera = 0;
	}  else {
		  std::istringstream cameraCmd(argv[1]);

		  if(!(cameraCmd >> camera)) return 1;
	}


	ros::init(argc, argv, "CameraHandler");
  	ros::NodeHandle node;
    /*
  	image_transport::ImageTransport transporter1(node);
  	image_transport::Publisher pub1 = transporter1.advertise("camera/FaceDetectImage1", 1);
  	image_transport::Publisher pub2 = transporter1.advertise("camera/FaceDetectImage2", 1);
    */
    ros::Publisher pub1 = node.advertise<robotvision::ImageCusMess>("camera/FaceDetectImage1", 1);
  	cv::VideoCapture capture(camera);
  	if(!capture.isOpened()) return 1;
  	cv::Mat frame;
  	//sensor_msgs::ImagePtr mess1, mess2;
    robotvision::ImageCusMess mess1;
  	ros::Rate loop_rate(5);
  	while (node.ok()){
  		capture.read(frame);
        if( !frame.empty() )
        {
          mess1.WindowsName = "Hello";
          sensor_msgs::ImagePtr im_msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
        	mess1.image = *im_msg;
          
        	//mess2 = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
  	    	pub1.publish(mess1);
  	    	//pub2.publish(mess2);
  	    	cv::waitKey(1);
      	} else 
      	{
        	printf(" --(!) No captured frame -- Break!\n");
        	break;
	    }
	    int c = cv::waitKey(10);
	    if( (char)c == 27 ) { break; }

	    ros::spinOnce();
	    loop_rate.sleep();
  	}
    std::cout << "Killing camera" << std::endl;

}