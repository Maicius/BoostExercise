#include "stdafx.h"

using namespace cv;
using namespace std;

void createDemarcate()
{
	Mat frame = imread("3A4.bmp"); // cols*rows = 630*891
	cvNamedWindow("test",CV_WINDOW_AUTOSIZE);
	int nc = frame.channels();
	int nWidthOfROI = 90;
	for (int j=0;j<frame.rows;j++)
	{
		uchar* data= frame.ptr<uchar>(j);
		for(int i=0;i<frame.cols*nc;i+=nc)
		{			
			if( (i/nc/nWidthOfROI + j/nWidthOfROI) % 2)
			{
				data[i/nc*nc + 0] = 255 ;
				data[i/nc*nc + 1] = 255 ;
				data[i/nc*nc + 2] = 255 ;				
			}
		}
	}
	imshow("test",frame);
	waitKey(0);
}