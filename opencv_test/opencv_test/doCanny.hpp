#include "stdafx.h"

IplImage *doPyrDown(IplImage* in, int filter = IPL_GAUSSIAN_5x5)
{
	IplImage *out = cvCreateImage(
		cvSize(in->width/2, in->height/2),
		in->depth,
		in->nChannels = 1);
	cvPyrDown(in, out);
	return out;
}

IplImage* doCanny(IplImage* in, double lowThresh, double highThresh, double aperture)
{
	if( in ->nChannels !=1)
		return 0;
	IplImage* out = cvCreateImage(cvSize(in->width, in->height),IPL_DEPTH_8U,1);
	cvCanny(in, out, lowThresh, highThresh,aperture);
	return out;
}

void initCanny()
{
	IplImage *in = cvLoadImage("File/test.jpg");
	cvNamedWindow("Canny", CV_WINDOW_AUTOSIZE);
	IplImage *out;
	out = doPyrDown(in, IPL_GAUSSIAN_5x5);
	out = doPyrDown(out, IPL_GAUSSIAN_5x5);
	out = doCanny(out, 10, 100, 3);
	cvShowImage("Canny",out);
	cvWaitKey(0);
	cvReleaseImage(&out);
}