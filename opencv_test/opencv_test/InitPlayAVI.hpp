#include "stdafx.h"

static int g_slider_position = 0;
static CvCapture* g_capture = NULL;

void onTrackbarSlide(int pos){
	cvSetCaptureProperty(g_capture, CV_CAP_PROP_POS_FRAMES, pos);
}
void callTrackbarSlide(){
	int frames = (int) cvGetCaptureProperty(g_capture, CV_CAP_PROP_FRAME_COUNT);
	if(frames!=0){
		cvCreateTrackbar(
			"Trackbar",
			"PlayAVI",
			&g_slider_position,
			frames,
			onTrackbarSlide);
	}
}
void initPlayAVI(){
	cvNamedWindow("PlayAVI", CV_WINDOW_AUTOSIZE);
	g_capture = cvCreateFileCapture("test.avi");
	callTrackbarSlide();
	IplImage *frame;
	while(1) {
		frame = cvQueryFrame(g_capture);
		if(!frame)
			break;
		cvShowImage("PlayAVI", frame);
		g_slider_position++;
		callTrackbarSlide();
		char c = cvWaitKey(33);
		if(c == 27)
			break;
	}
	cvReleaseCapture(&g_capture);
	cvDestroyWindow("PlayAVI");
}