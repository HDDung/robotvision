/*
 * FaceRecognition.h
 *
 *  Created on: Aug 5, 2016
 *      Author: dung
 */

#ifndef FACERECOGNITION_H_
#define FACERECOGNITION_H_

#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>

#include "FaceDetector.h"

using namespace std;
using namespace cv;


class FaceRecognition {
public:
	FaceRecognition(Mat);
	void detectAndDisplay(FaceDetector& );
	void DrawnFace(Rect face,  String = "Unknown");
	void DrawnEyes(Rect face, std::vector<Rect> eyes);
	std::vector<Rect> Face();


private:
	Mat frame;
	Mat frame_gray;
	Mat Crop;
	Size textSize;

	int baseline;

	CascadeClassifier face_cascade;
	CascadeClassifier eyes_cascade;


};


static std::string path = ros::package::getPath("robotvision");
static String face_cascade_name = path + "/HaarCascade/haarcascade_frontalface_alt_test.xml";
static String eyes_cascade_name = path + "/HaarCascade/haarcascade_eye_tree_eyeglasses.xml";
static String window_name = "Capture - Face detection";
#endif /* FACERECOGNITION_H_ */
