#include "stdafx.h"
void simpleChange()
{
	IplImage *image = cvLoadImage("File/test.jpg");
	cvNamedWindow("test-in", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("test-out", CV_WINDOW_AUTOSIZE);
	cvShowImage("test-in", image);
	IplImage *imageOut = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 3);
	cvSmooth(image, imageOut, CV_GAUSSIAN, 9, 9);
	cvShowImage("test-out", imageOut);
	cvWaitKey(0);
	cvReleaseImage(&image);
	cvReleaseImage(&imageOut);
	cvDestroyWindow("test-in");
	cvDestroyWindow("test-out");
}