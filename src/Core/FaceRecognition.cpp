/*
 * FaceRecognition.cpp
 *
 *  Created on: Aug 5, 2016
 *      Author: dung
 */

#include "Core/FaceRecognition.h"

std::vector<Rect> FaceRecognition::Face(){
	std::vector<Rect> faces;
	//-- Detect faces
	    face_cascade.detectMultiScale( frame_gray, faces, 1.05, 9, 0, Size(30, 30) );
	    /* param 4: Change will effect the accuracy.
	     * param 6: Minimum size the faces that can be recognized.
	     *
	     * */

	    /*
	    for (size_t i = 0; i < faces.size(); i++){
	    	frame(faces[i]).copyTo(Crop);

	    	imshow("Faces", Crop);
	    }*/
	    return faces;
}

void FaceRecognition::DrawnFace(Rect face, String text){
	//-- Draw the face
	int thickness = 1;
	int fontFace = FONT_HERSHEY_TRIPLEX;
	double fontScale = 0.5;
	        	baseline = 0;
	            Point center( face.x + face.width/2, face.y + face.height/2 );
	            //ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 0 ), 2, 8, 0 );

	            rectangle(frame, face, Scalar( 255, 0, 0 ), 1, 8, 0);
	            textSize = getTextSize(text, fontFace,
	                                        fontScale, thickness, &baseline);
	            baseline += thickness;

	            Point textOrg((face.x + textSize.width/2),
	                          (face.y - textSize.height/2));
	            rectangle(frame, textOrg + Point(0, baseline),
	                      textOrg + Point(textSize.width, -textSize.height),
	                      Scalar(0,0,255));
	            line(frame, textOrg + Point(0, thickness),
	                 textOrg + Point(textSize.width, thickness),
	                 Scalar(0, 0, 255));
	            putText(frame, text, textOrg, fontFace, fontScale,
	                    Scalar::all(255), thickness, 8);

}
void FaceRecognition::DrawnEyes(Rect face, std::vector<Rect> eyes){
	for( size_t j = 0; j < eyes.size(); j++ )
	            { //-- Draw the eyes
	                Point eye_center( face.x + eyes[j].x + eyes[j].width/2, face.y + eyes[j].y + eyes[j].height/2 );
	                int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
	                circle( frame, eye_center, radius, Scalar( 255, 0, 255 ), 3, 8, 0 );
	            }
}

void FaceRecognition::detectAndDisplay(FaceDetector& dtor)
{

	if( !face_cascade.load( face_cascade_name ) ){
		throw "--(!)Error loading face cascade\n";
	}

	if( !eyes_cascade.load( eyes_cascade_name ) ){
		throw "--(!)Error loading eyes cascade\n";
	}

    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    std::vector<Rect> faces = Face();
    //imwrite(Crop);

    for( size_t i = 0; i < faces.size(); i++ )
    {


        Mat faceROI = frame_gray( faces[i] );
        std::vector<Rect> eyes;

        //-- In each face, detect eyes
        eyes_cascade.detectMultiScale( faceROI, eyes, 1.05, 7, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );
        Mat face;
    	frame(faces[i]).copyTo(face);

    	DrawnFace(faces[i], dtor.Prediction(face));
        if( eyes.size() == 2)
        {
            //-- Draw the face
        	DrawnEyes(faces[i], eyes);

        }

    }
    //*- Show what you got
    imshow( window_name, frame );
    imshow( "Gray", frame_gray);

}


FaceRecognition::FaceRecognition(Mat frame_input) {
	// TODO Auto-generated constructor stub
	this->frame =  frame_input;
}


