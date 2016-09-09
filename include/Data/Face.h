/*
 * Face.h
 *
 *  Created on: Aug 15, 2016
 *      Author: dung
 */

#ifndef FACE_H_
#define FACE_H_


#include "opencv2/core.hpp"

#include <stdio.h>
#include <string>

using namespace std;
using namespace cv;


class Face {
public:
	Face(String, Mat);
	void GiveName(String);
	String TakeName();
	void GiveFace(Mat);
	Mat TakeFace();
private:
	Mat face;
	String name;
};
bool operator==( Face& lhs,  Face& rhs);

bool operator!=( Face& lhs,  Face& rhs);

#endif /* FACE_H_ */
