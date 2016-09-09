/*
 * FaceDetector.h
 *
 *  Created on: Aug 5, 2016
 *      Author: dung
 */

#ifndef FACEDETECTOR_H_
#define FACEDETECTOR_H_

#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"
#include "../Data/ListFace.h"
#include "NewFaces.h"

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>


using namespace std;
using namespace cv;


#define Threshold 8000
#define Random 397

class FaceDetector {
public:
	FaceDetector(ListFace);
	void LoadList(ListFace);
	Mat asRowMatrix(const vector<Mat>& src, int rtype, double = 1, double = 0);
	Mat norm_0_255(const Mat& src);
	void Training();
	String Prediction(Mat Test_Img);
	FaceDetector();
	NewFaces GiveUtor();
	virtual ~FaceDetector();

private:
	Mat mean_g;
	Mat eigenvector_g;
	Mat eigenvalue_g;
	Mat Y;
	PCA pca_g;
	std::vector<Mat> faces;
	ListFace list;
	NewFaces utor;
};

#endif /* FACEDETECTOR_H_ */
