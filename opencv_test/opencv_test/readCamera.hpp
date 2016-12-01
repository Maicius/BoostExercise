#include "stdafx.h"
void readCamera(int argc, char **argv)
{
	CvCapture *capture;
	if(argc ==1){
		capture = cvCreateCameraCapture(1);
	} else {
		capture = cvCreateFileCapture(argv[1]);
	}
	assert(capture !=NULL);
	cvNamedWindow("Play", CV_WINDOW_AUTOSIZE);
	IplImage *frame = cvQueryFrame(capture);
	double fps = cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
	CvSize size  = cvSize(
		(int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH),
		(int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT));
	CvVideoWriter *writer = cvCreateVideoWriter(
		"test2.avi", CV_FOURCC('M','J','P', 'G'),
		fps,
		size);
	char stop;
	while(true) {
		frame = cvQueryFrame(capture);
		//fps = cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
		//std::cout<<fps<<std::endl;
		//logpolar_frame->nChannels = 1;
		cvWriteFrame(writer, frame);
		cvShowImage("Play", frame);
		stop = cvWaitKey(33);
		if(stop ==27)
			break;
	}
	cvReleaseVideoWriter(&writer);
	cvReleaseImage(&frame);
	cvReleaseCapture(&capture);
	cvDestroyWindow("Play");
	std::cout<<"finished!"<<std::endl;
}