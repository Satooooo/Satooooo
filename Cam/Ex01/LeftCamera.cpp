
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cv.h>
#include <cxcore.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;
using namespace cv;

#define WIDTH 640
#define HEIGHT 480
#define RADIUS 4
#define POINT 4
#define max_frame 20

CvPoint Lpt[POINT];
int frame=0;//フレーム数
int key = NULL;
int Lpoint_flag = -1;

//プロトタイプ
int LNearPoint(CvPoint mouse_pt);
void Lon_mouse(int event, int x, int y, int flags, void *param);
/*
//メイン
int main(int argc, const char* argv[])
{	

    CvCapture *capture = cvCreateCameraCapture(0);
    
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH,WIDTH);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT,HEIGHT);
    
	if (capture==0) {
		printf("Camera not found\n");
		return 0;
	}
	
	IplImage *frameImage = cvQueryFrame(capture);
	CvSize sizeofImage = cvGetSize(frameImage);
    
    IplImage *hsvImage = cvCreateImage(sizeofImage, IPL_DEPTH_8U, 3);
	
	IplImage *recImage = cvCreateImage(sizeofImage, IPL_DEPTH_8U, 3);

	cvNamedWindow("Result", CV_WINDOW_AUTOSIZE);

	//マウスコールバック関数
	cvSetMouseCallback("Result", on_mouse, NULL);
   
    while (1) {
        
        frameImage = cvQueryFrame(capture);
        if (frameImage == NULL)
            break;
        
		//HSVに変換
        cvCvtColor(frameImage, hsvImage, CV_BGR2HSV);

		//一度画素値を取得したら次に移動する
		bool aEnd = false;
		bool bEnd = false;
		bool cEnd = false;
		bool dEnd = false;

		//max_frameの数だけループ
		if(frame<max_frame){

			CvScalar s; 

			/////画像の操作/////
			//左上

			for (pt[0].y=0; pt[0].y<sizeofImage.height/2; pt[0].y++) {
				for (pt[0].x=0; pt[0].x<sizeofImage.width/2; pt[0].x++) {
					s = cvGet2D(hsvImage, pt[0].y, pt[0].x);
					if ((s.val[0]>95 && s.val[0]<130) && s.val[1]>120 && s.val[2]>70) {
						cvSet2D(hsvImage, pt[0].y, pt[0].x, s);
						aEnd = true;
					}
					if (aEnd) break;
				}
				if(aEnd) break;
			}

			//右上
			for (pt[1].y=0; pt[1].y<sizeofImage.height/2; pt[1].y++) {
				for (pt[1].x=sizeofImage.width/2; pt[1].x<sizeofImage.width; pt[1].x++) {
					s = cvGet2D(hsvImage, pt[1].y, pt[1].x);
					if ((s.val[0]>95 && s.val[0]<130) && s.val[1]>120 && s.val[2]>70) {
						cvSet2D(hsvImage, pt[1].y, pt[1].x, s);
						bEnd = true;
					}
					if (bEnd) break;
				}
				if(bEnd) break;
			}

			//右下
			for (pt[2].y=sizeofImage.height/2; pt[2].y<sizeofImage.height; pt[2].y++) {
				for (pt[2].x=sizeofImage.width/2; pt[2].x<sizeofImage.width; pt[2].x++) {
					s = cvGet2D(hsvImage, pt[2].y, pt[2].x);
					if ((s.val[0]>95 && s.val[0]<130) && s.val[1]>120 && s.val[2]>70) {
						cvSet2D(hsvImage, pt[2].y, pt[2].x, s);
						cEnd = true;
					}
					if (cEnd) break;
				}
				if(cEnd) break;
			}

			//左下
			for (pt[3].y=sizeofImage.height/2; pt[3].y<sizeofImage.height; pt[3].y++) {
				for (pt[3].x=0; pt[3].x<sizeofImage.width/2; pt[3].x++) {
					s = cvGet2D(hsvImage, pt[3].y, pt[3].x);
					if ((s.val[0]>95 && s.val[0]<130) && s.val[1]>120 && s.val[2]>70) {
						cvSet2D(hsvImage, pt[3].y, pt[3].x, s);
						dEnd = true;
					}
					if (dEnd) break;
				}
				if(dEnd) break;
			}
			////////////////////

		}

		//頂点の描画
		for(int i=0;i<4;i++){
			cvCircle(frameImage, pt[i], RADIUS, CV_RGB(255, 147, 0), 2, CV_AA, 0);
		}

		//枠の描画
		cvLine(frameImage, pt[0], pt[1], cv::Scalar(0,0,150), 1, CV_AA);
		cvLine(frameImage, pt[1], pt[2], cv::Scalar(0,0,150), 1, CV_AA);
		cvLine(frameImage, pt[2], pt[3], cv::Scalar(0,0,150), 1, CV_AA);
		cvLine(frameImage, pt[3], pt[0], cv::Scalar(0,0,150), 1, CV_AA);

		//RGBに変換
		cvCvtColor(hsvImage, recImage, CV_HSV2RGB);

		cvShowImage("Result", frameImage);

		if(key == 'c') frame = 0;

        if (key == 'q') break;

		key = cvWaitKey(10);

		//最終の座標を印字
        if(frame<max_frame){ 
			frame++;
		}else{ 
			printf("pt[0]:(%d,%d)\n",pt[0].x ,pt[0].y);
			printf("pt[1]:(%d,%d)\n",pt[1].x ,pt[1].y);
			printf("pt[2]:(%d,%d)\n",pt[2].x ,pt[2].y);
			printf("pt[3]:(%d,%d)\n",pt[3].x ,pt[3].y);
		}
		printf("frame数:%d\n",frame);

    }

	cvWaitKey(0);
	
	cvReleaseCapture(&capture);
	
	cvReleaseImage(&recImage);
	cvReleaseImage(&hsvImage);
	
	cvDestroyAllWindows();

	return 0;
}
*/
//メイン
int main(int argc, const char* argv[])
{	
	cv::VideoCapture Lcapture(0);

	if(!Lcapture.isOpened()){
        return -1;
	}

	Lcapture.set(CV_CAP_PROP_FRAME_WIDTH,WIDTH);
	Lcapture.set(CV_CAP_PROP_FRAME_WIDTH,HEIGHT);
	
	Mat LframeImage = Mat(Size(WIDTH,HEIGHT),CV_8UC3);
    
	Mat LhsvImage = Mat(Size(WIDTH,HEIGHT),CV_8UC3);
	
	Mat LrecImage = Mat(Size(WIDTH,HEIGHT),CV_8UC3);

	Vec3b s = NULL;

	namedWindow("Left", CV_WINDOW_AUTOSIZE);
	moveWindow("Left",0, 100);

	//マウスコールバック関数
	setMouseCallback("Left", Lon_mouse, NULL);

    while (1) {
		        
		Lcapture >> LframeImage;

		//HSVに変換
        cv::cvtColor(LframeImage, LhsvImage, CV_BGR2HSV);

		//一度画素値を取得したら次に移動する
		bool End0 = false;
		bool End1 = false;
		bool End2 = false;
		bool End3 = false;

		//max_frameの数だけループ
		if(frame<max_frame){
			/////画像の操作/////
			//左上
			
			for (Lpt[0].y=0; Lpt[0].y<HEIGHT/2; Lpt[0].y++) {
				for (Lpt[0].x=0; Lpt[0].x<WIDTH/2; Lpt[0].x++) {
					s = LhsvImage.at<Vec3b>(Lpt[0].y, Lpt[0].x);
					if ((s.val[0]>95 && s.val[0]<130) && s.val[1]>120 && s.val[2]>70) {
						LhsvImage.at<Vec3b>(Lpt[0].y, Lpt[0].x) = s;
						End1 = true;
					}
					if (End1) break;
				}
				if(End1) break;
			}
			
			//右上
			for (Lpt[1].y=0; Lpt[1].y<HEIGHT/2; Lpt[1].y++) {
				for (Lpt[1].x=WIDTH/2; Lpt[1].x<WIDTH; Lpt[1].x++) {
					s = LhsvImage.at<Vec3b>(Lpt[1].y, Lpt[1].x);
					if ((s.val[0]>95 && s.val[0]<130) && s.val[1]>120 && s.val[2]>70) {
						LhsvImage.at<Vec3b>(Lpt[1].y, Lpt[1].x) = s;
						End1 = true;
					}
					if (End1) break;
				}
				if(End1) break;
			}

			//右下
			for (Lpt[2].y=HEIGHT/2; Lpt[2].y<HEIGHT; Lpt[2].y++) {
				for (Lpt[2].x=WIDTH/2; Lpt[2].x<WIDTH; Lpt[2].x++) {
					s = LhsvImage.at<Vec3b>(Lpt[2].y, Lpt[2].x);
					if ((s.val[0]>95 && s.val[0]<130) && s.val[1]>120 && s.val[2]>70) {
						LhsvImage.at<Vec3b>(Lpt[2].y, Lpt[2].x) = s;
						End2 = true;
					}
					if (End2) break;
				}
				if(End2) break;
			}

			//左下
			for (Lpt[3].y=HEIGHT/2; Lpt[3].y<HEIGHT; Lpt[3].y++) {
				for (Lpt[3].x=0; Lpt[3].x<WIDTH/2; Lpt[3].x++) {
					s = LhsvImage.at<Vec3b>(Lpt[3].y, Lpt[3].x);
					if ((s.val[0]>95 && s.val[0]<130) && s.val[1]>120 && s.val[2]>70) {
						LhsvImage.at<Vec3b>(Lpt[3].y, Lpt[3].x) = s;
						End3 = true;
					}
					if (End3) break;
				}
				if(End3) break;
			}
			////////////////////

		}

		//頂点の描画
		for(int i=0;i<4;i++){
			circle(LframeImage, Lpt[i], RADIUS, CV_RGB(255, 147, 0), 2, CV_AA, 0);
		}

		//枠の描画
		line(LframeImage, Lpt[0], Lpt[1], Scalar(0,0,150), 1, CV_AA);
		line(LframeImage, Lpt[1], Lpt[2], Scalar(0,0,150), 1, CV_AA);
		line(LframeImage, Lpt[2], Lpt[3], Scalar(0,0,150), 1, CV_AA);
		line(LframeImage, Lpt[3], Lpt[0], Scalar(0,0,150), 1, CV_AA);

		//最終の座標を印字
        if(frame<max_frame){ 
			frame++;
		}else{ 
			printf("Lpt[0]:(%d,%d)\n",Lpt[0].x ,Lpt[0].y);
			printf("Lpt[1]:(%d,%d)\n",Lpt[1].x ,Lpt[1].y);
			printf("Lpt[2]:(%d,%d)\n",Lpt[2].x ,Lpt[2].y);
			printf("Lpt[3]:(%d,%d)\n",Lpt[3].x ,Lpt[3].y);
		}
		printf("frame数:%d\n",frame);

		//RGBに変換
		cv::cvtColor(LhsvImage, LrecImage, CV_HSV2RGB);

		cv::imshow("Left", LframeImage);

		if(key == 'c') frame = 0;

        if (key == 'q') break;

		key = cvWaitKey(10);

    }
	cv::waitKey(0);
	
	return 0;
}

//近傍点取得関数
int LNearPoint(CvPoint mouse_pt)
{
    int nx, ny;
    float radius, min_radius = RADIUS;
    int ret = -1;
    
    for(int i=0; i<POINT; i++){
        nx = mouse_pt.x - Lpt[i].x;
        ny = mouse_pt.y - Lpt[i].y;
        radius = sqrt((float)(nx*nx + ny*ny));
        if(radius < min_radius){
            min_radius = radius;
            ret = i;
        }
    }
    return ret;
}

//マウスイベント取得関数
void Lon_mouse(int event, int x, int y, int flags, void *param)

{
    CvPoint push_pt = cvPoint(x,y);

    //左クリック時に一番近い点を取得
	if(event == CV_EVENT_LBUTTONDOWN){
        Lpoint_flag = LNearPoint(push_pt);
	}

	//左クリック時に移動で頂点移動
    if((event == CV_EVENT_MOUSEMOVE)&&(flags == CV_EVENT_FLAG_LBUTTON)){
		Lpt[Lpoint_flag] = cvPoint(x, y);
    }
}