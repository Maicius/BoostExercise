#include "StdAfx.h"
#include "camerads.h"
#include <highgui.h>
#include <stdio.h>
 #include "stdafx.h"  
#include "highgui.h"     
#include "cv.h"     
#include "cxcore.h"     
#include "cvaux.h"     
#include <iostream>     
#include <cstdio>     
#include <cstring>     
#include <cmath>     
#include <algorithm>     
#include <queue>     
#include <vector>     
#include <windows.h>  

#include <highgui.h>
#include <cv.h>
#include <cxcore.h>
#include <iostream>
using namespace std;   
using namespace cv;



	
	IplImage *frame;


	IplImage *Imask_ROI_L=NULL;
	IplImage *Imask_ROI_R=NULL;
	
    IplImage *image_L=NULL;    
    IplImage *image_R=NULL;    

	
	int width;
	int height;

           IplImage* leftImage ;
	       IplImage* rightImage ;
	       IplImage* depthImage ;


	void stere();
	void  stere_BM();
	void stere_SGBM();

    void stere_GC();



int main()
{
	int cam_count;
 
	//仅仅获取摄像头数目
	cam_count = CCameraDS::CameraCount();
	printf("There are %d cameras.\n", cam_count);
 

 //***************************************************************************
	//获取所有摄像头的名称
	for(int i=0; i < cam_count; i++)
	{
		char camera_name[1024];  
		int retval = CCameraDS::CameraName(i, camera_name, sizeof(camera_name) );
 
		if(retval >0)
			printf("Camera #%d's Name is '%s'.\n", i, camera_name);
		else
			printf("Can not get Camera #%d's name.\n", i);
	}
 
 
	if(cam_count==0)
		return -1;
 
	CCameraDS camera;
 
	//打开第一个摄像头
	//if(! camera.OpenCamera(0, true)) //弹出属性选择窗口
	//if(! camera.OpenCamera(1, false,1280 ,720)) //不弹出属性选择窗口，用代码制定图像宽和高
	//if(! camera.OpenCamera(1, false,640 ,480)) 
	if(! camera.OpenCamera(1, false,1600 ,600)) 
	{
		fprintf(stderr, "Can not open camera.\n");
		return -1;
	}
 
 
	//-------------------------------------------------------

	CvVideoWriter *writer_L =cvCreateVideoWriter("D://write-1-L.avi", 4, 30, cvSize(800,600),1);//create writer  

	CvVideoWriter *writer_R =cvCreateVideoWriter("D://write-1-R.avi", 4, 30, cvSize(800,600),1);//create writer  

	CvVideoWriter *writer =cvCreateVideoWriter("D://write-1-double.avi", 4, 30, cvSize(1600,600),1);//create writer  

//*****************************************************************************

	  cvNamedWindow("Imask_ROI_L"); 
	  cvNamedWindow("Imask_ROI_R"); 


	while(1)
	{
		//获取一帧
		frame = camera.QueryFrame();
       
	//double fps=cvGetCaptureProperty(capture, CV_CAP_PROP_FPS ); 
     //------------------转换--------------------------
        
		image_L = cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,3); 
        cvCopy(frame,image_L);


		image_R= cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,3); 
        cvCopy(frame,image_R);

                 //------------------分割-----------------------------
	
                   width  = cvGetSize(frame).width/2;
			       height  = cvGetSize(frame).height;
				 
				  //---------扩展ROI区域-----------------------------
				 
	               CvRect rect_L = cvRect(0,0,width,height);
			
				   cvSetImageROI(image_L,rect_L);
				   Imask_ROI_L=cvCreateImage(cvGetSize(image_L) ,image_L->depth,image_L->nChannels);
                   cvCopy(image_L,Imask_ROI_L);  
      
                 //--------------ROI区域-----------------------------------

				    CvRect rect_R = cvRect(width,0,width,height);
			
				   cvSetImageROI(image_R,rect_R);
				   Imask_ROI_R=cvCreateImage(cvGetSize(image_R) ,image_R->depth,image_R->nChannels);
                   cvCopy(image_R,Imask_ROI_R);  
    
				//-------------写入----------------------------------------------

				        cvWriteFrame(writer_L,Imask_ROI_L);  
						cvWriteFrame(writer_R,Imask_ROI_R);

						cvWriteFrame(writer,frame);
                 
				//----------------------------------------------------------------




     /*  cvLogPolar(frame,frame,cvPoint2D32f(frame->width/2,  
      frame->height/2),40,CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS);  
   
     cvWriteFrame(writer,frame);  */




				    
				      cvShowImage("src",frame);  
				      cvShowImage("Imask_ROI_R",Imask_ROI_R); 
					  cvShowImage("Imask_ROI_L",Imask_ROI_L);
        	         

				   				   
				     cvReleaseImage(&Imask_ROI_R); 
	                 cvReleaseImage(&Imask_ROI_L); 
					 cvReleaseImage(&image_L); 
					  cvReleaseImage(&image_R); 

   //--------------------------------------------------

        char c = cvWaitKey(30);    
        if(c==27)    
            break;    
	        
	}
	
	
	cvReleaseVideoWriter(&writer_R);  
	cvReleaseVideoWriter(&writer_L);  



	 cvDestroyAllWindows(); 
	
     camera.CloseCamera(); //可不调用此函数，CCameraDS析构时会自动关闭摄像头
 
	 return 0;
	
}

