/*
 * LoadData.cpp
 *
 *  Created on: Aug 22, 2016
 *      Author: dung
 */

#include "Core/DataHandler.h"


DataHandler::DataHandler(char _link[1000]){
	std::cout << "Get link" << std::endl;
	GiveLink(_link);
}

void DataHandler::GiveLink(char _link[1000]){
	strcpy(this->link, _link);
	std::cout << this->link << "this link have been gotten"<< std::endl;
}

ListFace DataHandler::LoadData(){

	ListFace list;
	ifstream fp;
	fp.open(link, ios::in);
	if (!fp.is_open()){
			std::cout << "Error open file" << endl;
	} else {
		cv::Mat List;
		cv::Mat img;
		string line, datapath = this->path + "/Database/Face_Recog/";
		String name, file;
		int cout = 0;


		while (getline( fp, line ).good()){

			std::istringstream iss(line);
			std::string token;
			if (std::getline(iss, token, ' ')){
				file = token;
			}
			if (std::getline(iss, token, ' ')){
				name = token;
			} else {
				name = "Ahihihi hok bik";
			}

			cout++;
			img = imread(datapath + file, IMREAD_GRAYSCALE);
			if (img.empty()) {
				std::cout << "Missing face" <<std::endl;
				break;
			}
			list.AddFace(Face(name, img));
			std::cout << line << " " << cout<< std::endl;
			
		}
		count = cout;
	}
	fp.close();
	return list;
}

void DataHandler::StoreData(cv::Mat face, String name){
	ofstream fp;
	int _cout = count;
	fp.open(link, ios::out | ios::app | ios::ate);
	if (!fp.is_open()){
				std::cout << "Error open file" << endl;
	} else {
		_cout++;
		String datapath, file;
		datapath =  this->path + "/Database/Face_Recog/";
		ostringstream convert; convert << _cout;
		file = "face" + convert.str() + ".bmp"; 
		if (face.empty()){
			std::cout << "empty face" << std::endl;
		} else {
			std::string save = datapath+file;
			imwrite(save, face);
			fp << file + " " + name << std::endl;
			std::cout << "a face has been save in "+datapath << std::endl;
		}
		
	}
	count = _cout;

	fp.close();
}

