#include "stdafx.h"
void readCameraInformation()
{
	std::cout<<"Press ESC to escape"<<std::endl;
	cvNamedWindow("Play",CV_WINDOW_AUTOSIZE);
	CvCapture *capture = cvCreateCameraCapture(1);
	if(!capture){
		std::cout<<"No camera detected!"<<std::endl;
		exit(0);
	}
	IplImage *frame = cvQueryFrame(capture);
	IplImage *frameOut = cvQueryFrame(capture);
	//double fps = cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
	while((frame = cvQueryFrame(capture)) !=NULL){
		if(!frame)
			break;
		//cvSmooth(frame, frameOut, CV_GAUSSIAN, 9, 9);
		cvShowImage("Play", frameOut);
		char c = cvWaitKey(33);
		if (c == 27)
			break;
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("Play");
}