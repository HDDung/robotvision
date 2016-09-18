/*
 * NewFaces.h
 *
 *  Created on: Aug 27, 2016
 *      Author: dung
 */

#ifndef CORE_NEWFACES_H_
#define CORE_NEWFACES_H_

#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

#include "DataHandler.h"

#include <unistd.h>
#include <iostream>
#include <iostream>
#include <string>
#include <cmath>


/* This class deal with new faces
 * 	It has an array (called list) to hold new face and runs a update function at the end of main program.
 *	It will update whenever the difference between a new face and all face in list are large (>> threshold).
 * */
class NewFaces {
public:
	NewFaces();
	struct newface {
			cv::Mat face;
			double diff;
			String name;
	};
	void AddFace(cv::Mat, double, String); // Add face and its difference
	bool CheckFace(newface); // Check whether new face should or shouldn't add to the array
	void UpdateData(DataHandler&); // update new face to database

	virtual ~NewFaces();
private:
	std::vector<newface> list;
	int count = 0;
	
};
static double Threshold=600.0;

#endif /* CORE_NEWFACES_H_ */
