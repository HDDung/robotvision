/*
 * ListFace.h
 *
 *  Created on: Aug 22, 2016
 *      Author: dung
 */

#ifndef LISTFACE_H_
#define LISTFACE_H_
#include "Face.h"

class ListFace {
public:
	void AddFace(Face);
	Face TakeFace(int index);
	vector<Mat> TakeListFace();
	void RemoveFace(Face face);
	String SearchName(Mat);
	vector<Mat> SearchFace(String);
	vector<Face> TakeList();
	void SortName();
private:
	vector<Face> list_face;
};

#endif /* LISTFACE_H_ */
