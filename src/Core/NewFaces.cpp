/*
 * NewFaces.cpp
 *
 *  Created on: Aug 27, 2016
 *      Author: dung
 */

#include "Core/NewFaces.h"

NewFaces::NewFaces() {
	// TODO Auto-generated constructor stub

}
void NewFaces::AddFace(cv::Mat face, double diff, String name){
	// Add face
	newface t;
	t.diff = diff;
	t.face = face;
	t.name = name;
	if (list.size() <= 50){
		if (CheckFace(t)){
				list.push_back(t);
			}

	}

	count++;


}
bool NewFaces::CheckFace(newface t){
	// Check whether new face should or shouldn't add to the array
	// true: can add; false: cannot add;
	bool test = false;
	for (int i = 0; i < list.size(); ++i)
	{
		if (list[i].name == t.name){
			test = true;
			break;
		}
	}
	if (test == true){
		for (int i = 0; i < list.size(); i++){
			if (std::fabs(list[i].diff - t.diff) < Threshold && list[i].name == t.name){
				return false;
			}
		}	
	}
	
	return true;
}
void NewFaces::UpdateData(DataHandler& handler){
	// update new face to database

	std::cout << count << " " << list.size() << std::endl;
	if (list.size() != 0){
		string name;
		namedWindow( "NewFace", WINDOW_AUTOSIZE );
		/*
		waitKey(1000);
		usleep(10000);*/
		int i = 0;
		cv::imshow( "NewFace", list[0].face );
		waitKey(0);
		
		for (; i < list.size() - 1; i++){
			cout << "What's the name " << i << " " << list[i].name << " " << list[i].diff  << " face ?: " ;
			cin >> name; 
			cout << "the name is " << name <<std::endl;
			if (name != "0" ){
				handler.StoreData(list[i].face, name);
			}
			cv::imshow( "NewFace", list[i+1].face );
			waitKey(0);
		}

		cout << "What's the name " << i << "face?: " ;
		cin >> name; 
		cout << "the name is " << name <<std::endl;
		if (name != "0" ){
			handler.StoreData(list[i].face, name);
		}
	}


}


NewFaces::~NewFaces() {
	// TODO Auto-generated destructor stub
}

