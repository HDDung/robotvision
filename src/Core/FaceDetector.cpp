/*
 * FaceDetector.cpp
 *
 *  Created on: Aug 5, 2016
 *      Author: dung
 */

#include "Core/FaceDetector.h"

#define Num_PC 404 // the number of meaningful eigenface needed for checking and prediction (about 95%)


FaceDetector::FaceDetector(ListFace list){
	LoadList(list);
}

void FaceDetector::LoadList(ListFace list){
	this->list = list;
	this->faces = list.TakeListFace();
}

Mat FaceDetector::asRowMatrix(const vector<Mat>& src, int rtype, double alpha, double beta) {
    // Number of samples:
    size_t n = src.size();
    // Return empty matrix if no matrices given:
    if(n == 0)
        return Mat();
    // dimensionality of (reshaped) samples
    size_t d = src[0].total();
    // Create resulting data matrix:
    Mat data(n, d, rtype);
    // Now copy data:
    for(size_t i = 0; i < n; i++) {
        //
        if(src[i].empty()) {
            string error_message = format("Image number %d was empty, please check your input data.", i);
            CV_Error(CV_StsBadArg, error_message);
        }
        // Make sure data can be reshaped, throw a meaningful exception if not!
        if(src[i].total() != d) {
            string error_message = format("Wrong number of elements in matrix #%d! Expected %d was %d.", i, d, src[i].total());
            CV_Error(CV_StsBadArg, error_message);
        }
        // Get a hold of the current row:
        Mat xi = data.row(i);
        // Make reshape happy by cloning for non-continuous matrices:
        if(src[i].isContinuous()) {
            src[i].reshape(1, 1).convertTo(xi, rtype, alpha, beta);
        } else {
            src[i].clone().reshape(1, 1).convertTo(xi, rtype, alpha, beta);
        }
    }
    return data;
}

Mat FaceDetector::norm_0_255(const Mat& src) {
    // Create and return normalized image:
    Mat dst;
    switch(src.channels()) {
    case 1:
        cv::normalize(src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
        break;
    case 3:
        cv::normalize(src, dst, 0, 255, NORM_MINMAX, CV_8UC3);
        break;
    default:
        src.copyTo(dst);
        break;
    }
    return dst;
}

void FaceDetector::Training(){

	std::cout << "Begin Training" << std::endl;
	if (faces.size() > 0){

		unsigned int num;
		num = faces.size();
		std::cout << num << std::endl;


		for (int i = 0; i < num; i++){
			cv::resize(faces[i], faces[i], faces[0].size());
		}


		cv::Mat List_32FC1 = asRowMatrix(faces, CV_32FC1);

		PCA pca(List_32FC1, Mat(), CV_PCA_DATA_AS_ROW);
		Mat mean = pca.mean.clone();
		Mat eigenvector = pca.eigenvectors.clone();
		Mat eigenvalue = pca.eigenvalues.clone();
		this->mean_g = mean; this->eigenvalue_g = eigenvalue; this->eigenvector_g = eigenvector;
		this->pca_g = pca;


		/*
		imshow("avg", norm_0_255(mean.reshape(1, list[0].rows))); // mean face
		imshow("Something0", norm_0_255(pca.eigenvectors.row(0)).reshape(1, list[0].rows));
		imshow("Something1", norm_0_255(pca.eigenvectors.row(1)).reshape(1, list[1].rows));
		imshow("Something2", norm_0_255(pca.eigenvectors.row(2)).reshape(1, list[2].rows));
		imshow("Something3", norm_0_255(pca.eigenvectors.row(3)).reshape(1, list[3].rows));
		imshow("Something4", norm_0_255(pca.eigenvectors.row(79)).reshape(1, list[200].rows));
		imshow("Something5", norm_0_255(pca.eigenvectors.row(39)).reshape(1, list[399].rows));

		waitKey(0);*/

		//Processing ;
		for (unsigned int i = 0; i < num; i++){
			Mat t = List_32FC1.row(i).clone();
			subtract(t, mean.reshape(1,1),t);
			gemm(t,eigenvector, 1.0, Mat(), 0.0, t, GEMM_2_T);
			Y.push_back(t);
		}
		/*Prediction

		link = "Face_Recog/Test_face/";

		while (getline( ft, line ).good()){
			Mat img = imread(link + line, IMREAD_GRAYSCALE);

			cv::resize(img, img, list[0].size());
			String name = Prediction(img);
		}
		*/
	std::cout << "End Training" << std::endl;
	} else {
		std::cout << "List_face was not loaded, Error" << std::endl;
	}

}

String FaceDetector::Prediction(Mat Test_Img){

	double mindist;
	int minclas;

	Mat Test_Img_p;
	mindist = Threshold;


				cv::resize(Test_Img, Test_Img, faces[0].size());
				cv::cvtColor(Test_Img, Test_Img, cv::COLOR_BGR2GRAY);
				Test_Img.reshape(1, 1).convertTo(Test_Img, CV_32FC1, 1, 0);
				subtract(Test_Img, mean_g.reshape(1,1),Test_Img_p);

				gemm(Test_Img_p,eigenvector_g, 1.0, Mat(), 0.0, Test_Img_p, GEMM_2_T);

				/*check all face that is in database (from 1 to Num_PC - # meaningful eigenfaces)*/
				for (size_t i=0; i < faces.size(); i++){
					double dist = norm(Y.row(i), Test_Img_p, NORM_L2);

					if ((dist < mindist) && (dist < Threshold)){
						mindist = dist;
						minclas = i; // The i_th img that matched mostY
					}
				}

				//imshow("Something0", norm_0_255(pca_g.eigenvectors.row(0)).reshape(1, list[0].rows));

				Mat r = Y.row(minclas);
				gemm(r,eigenvector_g, 1.0, Mat(), 0.0, r);
				add(r, mean_g.reshape(1,1),r);
				String Name = "Prediction: ";

				/*Using minclas (i_th img) to feedback the name
				if ((minclas >= 394 && minclas <= 399) || (minclas >= 407 && minclas <= 408)){

					Name = Name + "Ty";
				} else if ((minclas >= 400 && minclas <= 406)){

					Name = Name + "Me de thuong";
				} else {

					Name = Name + "Ahihihi hok bik";
					Mat t = norm_0_255(Test_Img).reshape(1, faces[0].rows);
					this->utor.AddFace(t, mindist);
				}*/

				imshow("Hello", norm_0_255(r).reshape(1, faces[0].rows));
				/*imshow("Input Img", norm_0_255(Test_Img).reshape(1, list[0].rows));

				cv::waitKey(0);*/



				std::cout << mindist << " " << r.size() << std::endl;



				/* if a face appears many time, count it
				 *
				 *
				 *
				 *
				 * */
				if (mindist <= 3700.0){
					return "prediction: " + list.TakeFace(minclas).TakeName();
				} else {
					Mat t = norm_0_255(Test_Img).reshape(1, faces[0].rows);
					this->utor.AddFace(t, mindist);
					return "unknown";
				}


}


NewFaces FaceDetector::GiveUtor(){
	return this->utor;
}


FaceDetector::FaceDetector() {
	// TODO Auto-generated constructor stub

}

FaceDetector::~FaceDetector() {
	// TODO Auto-generated destructor stub
}

