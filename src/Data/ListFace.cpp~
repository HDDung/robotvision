/*
 * ListFace.cpp
 *
 *  Created on: Aug 22, 2016
 *      Author: dung
 */

#include "Data/ListFace.h"


vector<Mat> ListFace::TakeListFace(){

	vector<Mat> out;

	for (int i = 0; i < this->list_face.size(); i++){
		out.push_back(list_face[i].TakeFace());
	}

	return out;
}

void ListFace::AddFace(Face face){
	list_face.push_back(face);
}

void ListFace::RemoveFace(Face face){
	int i = 0;

	while (face != list_face[i]){
		i++;
	}
	list_face.erase(list_face.begin() + i);
}
Face ListFace::TakeFace(int index){
	return list_face[index];
}
vector<Face> ListFace::TakeList(){
	return list_face;
}

String ListFace::SearchName(Mat face){
	Mat mat1,mat2,dst;
	mat2 = face;
	for (int i = 0; i <list_face.size(); i++){
		mat1 = list_face[i].TakeFace();
		cv::bitwise_and(mat1, mat2, dst);

		if (countNonZero(dst) > 0){
			return list_face[i].TakeName();
		}
	}
	return NULL;
}

vector<Mat> ListFace::SearchFace(String name){
	vector<Mat> output = vector<Mat>(0);
	for (int i = 0; i <list_face.size(); i++){
			if (list_face[i].TakeName() == name){
				output.push_back(list_face[i].TakeFace());
		}
	}
	return output;
}
void ListFace::SortName(){
	for (int i = 0; i < list_face.size() - 1; i++){
		for (int j = i; j < list_face.size(); j++){
			if (list_face[i].TakeName() > list_face[j].TakeName()){
				Face t = list_face[j];
				list_face[j] = list_face[i];
				list_face[i] = t;
			}
		}
	}
}




