#include "stdafx.h"
void initPicture(){
	IplImage* img = cvLoadImage("test.jpg");
	cvNamedWindow("Test1", CV_WINDOW_AUTOSIZE);
	cvShowImage("Test1", img);
	cvWaitKey(0);
	cvReleaseImage(&img);
	cvDestroyWindow("Test1");
}