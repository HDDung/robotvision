/*
 * Face.cpp
 *
 *  Created on: Aug 15, 2016
 *      Author: dung
 */

#include "Data/Face.h"


Face::Face(String name, Mat face) {
	// TODO Auto-generated constructor stub
	this->name = name;
	this->face = face;
}
void Face::GiveName(String name){
	this->name = name;
}
String Face::TakeName(){
	return this->name;
}
void Face::GiveFace(Mat face){
	this->face = face;
}
Mat Face::TakeFace(){
	return this->face;
}

bool operator==(Face& lhs, Face& rhs)
{
	Mat mat1,mat2,dst;
	mat1 = lhs.TakeFace();
	mat2 = rhs.TakeFace();
	cv::bitwise_and(mat1, mat2, dst);
	if (countNonZero(dst) > 0 && lhs.TakeName() == rhs.TakeName())
		return true;
	return false;
}

bool operator!=( Face& lhs,  Face& rhs)
{
    return !(lhs == rhs);
}

