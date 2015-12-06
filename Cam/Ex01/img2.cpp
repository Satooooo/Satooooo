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
	CvPoint pt[4];
	CvMemStorage *storage = cvCreateMemStorage (0);
	CvRNG rng = cvRNG (time (NULL));


	int xmin0=0, ymin0=0;

	int xmax1=0, ymin1=0;

	int xmax2=0, ymax2=0;

	int ymax3=0, xmin3=0;


	//----現画像----
	IplImage *img;
	cvNamedWindow("img");
	img = cvLoadImage("img4.png");
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


	 points = cvCreateSeq (CV_SEQ_ELTYPE_POINT, sizeof (CvSeq), sizeof (CvPoint), storage);
			pt[0].x = cvRandInt (&rng) % (img->width / 2);
			pt[0].y = cvRandInt (&rng) % (img->height / 2);
			cvSeqPush (points, &pt[0]);
			cvCircle (img, pt[0], 3, CV_RGB (255, 0, 0), CV_FILLED);

			pt[1].x = cvRandInt (&rng) % (img->width/2) + (img->width/2);
			pt[1].y = cvRandInt (&rng) % (img->height / 2);
			cvSeqPush (points, &pt[1]);
			cvCircle (img, pt[1], 3, CV_RGB (255, 0, 0), CV_FILLED);

			pt[2].x = cvRandInt (&rng) % (img->width/2) + (img->width/2);
			pt[2].y = cvRandInt (&rng) % (img->height/2) + (img->height/2);
			cvSeqPush (points, &pt[2]);
			cvCircle (img, pt[2], 3, CV_RGB (255, 0, 0), CV_FILLED);

			pt[3].x = cvRandInt (&rng) % (img->width/2);
			pt[3].y = cvRandInt (&rng) % (img->height/2) + (img->height/2);
			cvSeqPush (points, &pt[3]);
			cvCircle (img, pt[3], 3, CV_RGB (255, 0, 0), CV_FILLED);
	//----HSV変換----
	
	cvCvtColor(img,hsv,CV_BGR2HSV);

	CvScalar s; 
    for (pt[0].y=0; pt[0].y<sizeofImage.height/2; pt[0].y++) {
		for (pt[0].x=0; pt[0].x<sizeofImage.width/2; pt[0].x++) {
			s = cvGet2D(hsv, pt[0].y, pt[0].x);
            if ( 10 > s.val[0] && 200 < s.val[1] && 200 < s.val[2]) {
				printf("(%d,%d)\n",pt[0].x ,pt[0].y);
				if(xmin0 == 0) xmin0 = pt[0].x;
				if(ymin0 == 0 )ymin0 = pt[0].y;
				if(xmin0 > pt[0].x){
					xmin0 = pt[0].x;
				}
				if(ymin0 > pt[0].y){
					ymin0 = pt[0].y;
				}
			}
        }
	}
	
	printf("///////////////////////////////////\n");
	
	for (pt[1].y=0; pt[1].y<sizeofImage.height/2; pt[1].y++) {
		for (pt[1].x=sizeofImage.width/2; pt[1].x<sizeofImage.width; pt[1].x++) {
			s = cvGet2D(hsv, pt[1].y, pt[1].x);
            if ( 10 > s.val[0] && 200 < s.val[1] && 200 < s.val[2]) {
				printf("(%d,%d)\n",pt[1].x ,pt[1].y);
				if(xmax1 < pt[1].x) xmax1 = pt[1].x;
				if(ymin1 == 0) ymin1 = pt[1].y;
			}
        }
	}
	
	printf("///////////////////////////////////\n");

	for (pt[2].y=sizeofImage.height/2; pt[2].y<sizeofImage.height; pt[2].y++) {
		for (pt[2].x=sizeofImage.width/2; pt[2].x<sizeofImage.width; pt[2].x++) {
			s = cvGet2D(hsv, pt[2].y, pt[2].x);
            if ( 10 > s.val[0] && 200 < s.val[1] && 200 < s.val[2]) {
				printf("(%d,%d)\n",pt[2].x ,pt[2].y);
				if(xmax2 < pt[2].x) xmax2 = pt[2].x;
				if(ymax2 < pt[2].y) ymax2 = pt[2].y;
			}
        }
	}
	
	printf("///////////////////////////////////\n");

	for (pt[3].y=sizeofImage.height/2; pt[3].y<sizeofImage.height; pt[3].y++) {
		for (pt[3].x=0; pt[3].x<sizeofImage.width/2; pt[3].x++) {
			s = cvGet2D(hsv, pt[3].y, pt[3].x);
            if ( 10 > s.val[0] && 200 < s.val[1] && 200 < s.val[2]) {
				printf("(%d,%d)\n",pt[3].x ,pt[3].y);
				if(xmin3 == 0) xmin3 = pt[3].x;
				if(ymax3 < pt[3].y) ymax3 = pt[3].y;
			}
        }
	}
	
	printf("///////////////////////////////////\n");

	printf("座標(%d, %d)\n",xmin0, ymin0);
	printf("座標(%d, %d)\n",xmax1, ymin1);
	printf("座標(%d, %d)\n",xmax2, ymax2);
	printf("座標(%d, %d)\n",xmin3, ymax3);

	cvLine(img, cv::Point(xmin0, ymin0), cv::Point(xmax1, ymin1), cv::Scalar(0,0,200), 1, 1);
	cvLine(img, cv::Point(xmax1, ymin1), cv::Point(xmax2, ymax2), cv::Scalar(0,0,200), 1, 1);
	cvLine(img, cv::Point(xmax2, ymax2), cv::Point(xmin3, ymax3), cv::Scalar(0,0,200), 1, 1);
	cvLine(img, cv::Point(xmin3, ymax3), cv::Point(xmin0, ymin0), cv::Scalar(0,0,200), 1, 1);

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