/*
#include <opencv2/core/core.hpp>        // coreモジュールのヘッダーをインクルード
#include <opencv2/highgui/highgui.hpp>  // highguiモジュールのヘッダーをインクルード
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cv.h>
#include <cxcore.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char* argv[])
{
	CvSeq *points;
	CvPoint pt;
	CvRect rect;
	CvMemStorage *storage = cvCreateMemStorage (0);

	int xmax=0, ymax=0;


	//----現画像----
	IplImage *img;
	cvNamedWindow("img");
	img = cvLoadImage("img2.png");
	CvSize sizeofImage = cvGetSize(img);

	if(img == NULL){
		printf("読み込めません.");

		cvWaitKey(0);
		return -1;
	}
	//----変換用画像----
	IplImage* hsv = cvCreateImage(sizeofImage,IPL_DEPTH_8U,3);
	cvNamedWindow("hsv");
	cvMoveWindow("hsv", 300, 0);

	IplImage* result = cvCreateImage(sizeofImage,IPL_DEPTH_8U,3);
	cvNamedWindow("result");
	cvMoveWindow("result", 500, 0);

	//----HSV変換----
	
	cvCvtColor(img,hsv,CV_BGR2HSV);

	CvScalar s;  
        for (pt.y=0; pt.y<sizeofImage.height; pt.y++) {
            for (pt.x=0; pt.x<sizeofImage.width; pt.x++) {
                s = cvGet2D(hsv, pt.y, pt.x);
                if ( 10 > s.val[0] && 200 < s.val[1] && 200 < s.val[2]) {
					printf("(%d,%d)\n",pt.x ,pt.y);
					if(xmax < pt.x){
						xmax = pt.x;
					}
					if(ymax < pt.y){
						ymax = pt.y;
					}
					
				} else{
					s.val[0]=0;
					s.val[1]=0;
					s.val[2]=255;
					cvSet2D(result, pt.y, pt.x, s);
				}
            }
        }
	printf("xmax:%d,ymax:%d",xmax, ymax);
	points = cvCreateSeq (CV_SEQ_ELTYPE_POINT, sizeof (CvSeq), sizeof (CvPoint), storage);
	rect = cvBoundingRect (points, 0);
	cvRectangle (hsv, cvPoint (rect.x, rect.y),cvPoint (rect.x + xmax, rect.y + ymax), CV_RGB (0, 0, 0), 2);

	//----RGB変換----
	cvCvtColor(hsv,result, CV_HSV2BGR);

	cvShowImage("img",img);
	cvShowImage("hsv",hsv);
	cvShowImage("result",result);

	cvWaitKey(0);

	cvReleaseImage(&img);
	cvReleaseImage(&hsv);
	cvReleaseImage(&result);

	cvDestroyAllWindows();

  return 0;
}
*/