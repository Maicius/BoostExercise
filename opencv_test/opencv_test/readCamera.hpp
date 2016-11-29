#include "stdafx.h"
void readCamera(int argc, char **argv)
{
	CvCapture *capture;
	if(argc ==1){
		capture = cvCreateCameraCapture(0);
	} else {
		capture = cvCreateFileCapture(argv[1]);
	}
	assert(capture !=NULL);

	IplImage *bgr_frame = cvQueryFrame(capture);
	double fps = cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
	CvSize size  = cvSize(
		(int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH),
		(int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT));
	CvVideoWriter *writer = cvCreateVideoWriter(
		argv[2], CV_FOURCC('M','J','P', 'G'),
		fps,
		size);
	IplImage* logpolar_frame = cvCreateImage(
		size,
		IPL_DEPTH_8U,
		3);
	while((bgr_frame = cvQueryFrame(capture)) !=NULL) {
		cvLogPolar( bgr_frame, logpolar_frame,
			cvPoint2D32f(bgr_frame->width/2, bgr_frame->height/2), 
						40, 
						CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS);
		//logpolar_frame->nChannels = 1;
		cvWriteFrame(writer, logpolar_frame);
	}
	cvReleaseVideoWriter(&writer);
	cvReleaseImage(&logpolar_frame);
	cvReleaseCapture(&capture);

	std::cout<<"finished!"<<std::endl;
}