
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
	//----現画像----
	IplImage *img;
	cvNamedWindow("img");
	img = cvLoadImage("img.png");
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
        //画素(x,y)ごとの処理
        for (int y=0; y<sizeofImage.height; y++) {
            for (int x=0; x<sizeofImage.width; x++) {
                s = cvGet2D(hsv, y, x);
                if ( 10 > s.val[0] && 200 < s.val[1] && 200 < s.val[2]) {
					printf("(%d,%d)\n",x ,y);
				} else{
					s.val[0]=0;
					s.val[1]=0;
					s.val[2]=255;
					cvSet2D(result, y, x, s);
				}
            }
        }
	
	//----RGB変換----
	cvCvtColor(hsv,result, CV_HSV2BGR);

	cvShowImage("img",img);
	//cvShowImage("img2",img);
	cvShowImage("hsv",hsv);
	cvShowImage("result",result);

	cvWaitKey(0);

	cvReleaseImage(&img);
	//cvReleaseImage(&img2);
	cvReleaseImage(&hsv);
	cvReleaseImage(&result);

	cvDestroyAllWindows();

  return 0;
}
