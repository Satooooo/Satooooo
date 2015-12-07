
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cv.h>
#include <cxcore.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char* argv[])
{
	CvPoint pt[4];

	int x0=0, y0=0;
	int x1=0, y1=0;
	int x2=0, y2=0;
	int y3=0, x3=0;

    CvCapture *capture = cvCreateCameraCapture(0);
    
    cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH,640);
    cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT,480);
    
	if (capture==0) {
		printf("Camera not found\n");
		return 0;
	}
	
	IplImage *frameImage = cvQueryFrame(capture);
	CvSize sizeofImage = cvGetSize(frameImage);
    
    IplImage *hsvImage = cvCreateImage(sizeofImage, IPL_DEPTH_8U, 3);
	
	IplImage *recImage = cvCreateImage(sizeofImage, IPL_DEPTH_8U, 3);

	cvNamedWindow("Result", CV_WINDOW_AUTOSIZE);
    
    while (1) {
        
        frameImage = cvQueryFrame(capture);
        if (frameImage == NULL)
            break;
        
        cvCvtColor(frameImage, hsvImage, CV_BGR2HSV);

		//////
        CvScalar s; 
		bool aEnd = false;
		for (pt[0].y=0; pt[0].y<sizeofImage.height/2; pt[0].y++) {
			for (pt[0].x=0; pt[0].x<sizeofImage.width/2; pt[0].x++) {
				s = cvGet2D(hsvImage, pt[0].y, pt[0].x);
				if ((s.val[0]>95 && s.val[0]<130) && s.val[1]>120 && s.val[2]>70) {
					x0 = pt[0].x;
					y0 = pt[0].y;
					aEnd = true;
				}
				if (aEnd) break;
			}
			if(aEnd) break;
		}
		printf("pt[0]:(%d,%d)\n",pt[0].x ,pt[0].y);
		printf("\n");

		bool bEnd = false;
		for (pt[1].y=0; pt[1].y<sizeofImage.height/2; pt[1].y++) {
			for (pt[1].x=sizeofImage.width/2; pt[1].x<sizeofImage.width; pt[1].x++) {
				s = cvGet2D(hsvImage, pt[1].y, pt[1].x);
				if ((s.val[0]>95 && s.val[0]<130) && s.val[1]>120 && s.val[2]>70) {
					x1 = pt[1].x;
					y1 = pt[1].y;
					bEnd = true;
				}
				if (bEnd) break;
			}
			if(bEnd) break;
		}
		printf("pt[1]:(%d,%d)\n",pt[1].x ,pt[1].y);
		printf("\n");

		bool cEnd = false;
		for (pt[2].y=sizeofImage.height/2; pt[2].y<sizeofImage.height; pt[2].y++) {
			for (pt[2].x=sizeofImage.width/2; pt[2].x<sizeofImage.width; pt[2].x++) {
				s = cvGet2D(hsvImage, pt[2].y, pt[2].x);
				if ((s.val[0]>95 && s.val[0]<130) && s.val[1]>120 && s.val[2]>70) {
					x2 = pt[2].x;
					y2 = pt[2].y;
					cEnd = true;
				}
				if (cEnd) break;
			}
			if(cEnd) break;
		}
		printf("pt[2]:(%d,%d)\n",pt[2].x ,pt[2].y);
		printf("\n");

		bool dEnd = false;
		for (pt[3].y=sizeofImage.height/2; pt[3].y<sizeofImage.height; pt[3].y++) {
			for (pt[3].x=0; pt[3].x<sizeofImage.width/2; pt[3].x++) {
				s = cvGet2D(hsvImage, pt[3].y, pt[3].x);
				if ((s.val[0]>95 && s.val[0]<130) && s.val[1]>120 && s.val[2]>70) {
					x3 = pt[3].x;
					y3 = pt[3].y;
					dEnd = true;
				}
				if (dEnd) break;
			}
			if(dEnd) break;
		}
		printf("pt[3]:(%d,%d)\n",pt[3].x ,pt[3].y);
		printf("\n");
		
		cvLine(frameImage, cv::Point(x0, y0), cv::Point(x1, y1), cv::Scalar(0,0,200), 2, CV_AA);
		cvLine(frameImage, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0,0,200), 2, CV_AA);
		cvLine(frameImage, cv::Point(x2, y2), cv::Point(x3, y3), cv::Scalar(0,0,200), 2, CV_AA);
		cvLine(frameImage, cv::Point(x3, y3), cv::Point(x0, y0), cv::Scalar(0,0,200), 2, CV_AA);

		cvCvtColor(hsvImage, recImage, CV_HSV2RGB);
        
		cvFlip(frameImage, frameImage, 1);

		cvShowImage("Result", frameImage);
        
        int key = cvWaitKey(10);
        if (key == 'q') break;
    }
	
	cvWaitKey(0);
	
	cvReleaseCapture(&capture);
	
	cvReleaseImage(&recImage);
	cvReleaseImage(&hsvImage);
	
	cvDestroyAllWindows();

	return 0;
}
