#include "stdafx.h"

#define MAX_NUM 10000
void initPiexelSegment()
{
	CvCapture *capture = cvCreateCameraCapture(0);
	int max_buffer;
	IplImage* rawImage;
	int r[MAX_NUM], g[MAX_NUM], b[MAX_NUM];
	CvLineIterator iterator;
	cvNamedWindow("test", CV_WINDOW_AUTOSIZE);
	FILE *fptrb = fopen("blines.csv", "w");
	FILE *fptrg = fopen("glines.csv", "w");
	FILE *fptrr = fopen("rlines.csv", "w");

	for(;;){
		if(!cvGrabFrame(capture))
			break;
		rawImage = cvRetrieveFrame(capture);
		cvShowImage("test", rawImage);
		max_buffer = cvInitLineIterator(rawImage, cvPoint(0, 10),cvPoint(720, 10), &iterator, 8, 0);
		for(int j=0; j<max_buffer; j++){

		}
	}
}