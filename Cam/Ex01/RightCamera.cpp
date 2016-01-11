
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

CvPoint Rpt[POINT];
int Rframe=0;//フレーム数
int Rkey = NULL;
int Rpoint_flag = -1;

//プロトタイプ
int RNearPoint(CvPoint mouse_pt);
void Ron_mouse(int event, int x, int y, int flags, void *param);

//メイン
int main(int argc, const char* argv[])
{	
	cv::VideoCapture Rcapture(1);

	if(!Rcapture.isOpened()){
        return -1;
	}

	Rcapture.set(CV_CAP_PROP_FRAME_WIDTH,WIDTH);
	Rcapture.set(CV_CAP_PROP_FRAME_WIDTH,HEIGHT);
	
	Mat RframeImage = Mat(Size(WIDTH,HEIGHT),CV_8UC3);
    
	Mat RhsvImage = Mat(Size(WIDTH,HEIGHT),CV_8UC3);
	
	Mat RrecImage = Mat(Size(WIDTH,HEIGHT),CV_8UC3);

	Vec3b s = NULL;

	namedWindow("Right", CV_WINDOW_AUTOSIZE);
	moveWindow("Right",620, 100);

	//マウスコールバック関数
	setMouseCallback("Right", Ron_mouse, NULL);

    while (1) {
		        
		Rcapture >> RframeImage;

		//HSVに変換
        cv::cvtColor(RframeImage, RhsvImage, CV_BGR2HSV);

		//一度画素値を取得したら次に移動する
		bool End0 = false;
		bool End1 = false;
		bool End2 = false;
		bool End3 = false;

		//max_frameの数だけループ
		if(Rframe<max_frame){
			/////画像の操作/////
			//左上
			
			for (Rpt[0].y=0; Rpt[0].y<HEIGHT/2; Rpt[0].y++) {
				for (Rpt[0].x=0; Rpt[0].x<WIDTH/2; Rpt[0].x++) {
					s = RhsvImage.at<Vec3b>(Rpt[0].y, Rpt[0].x);
					if ((s.val[0]>95 && s.val[0]<130) && s.val[1]>120 && s.val[2]>70) {
						RhsvImage.at<Vec3b>(Rpt[0].y, Rpt[0].x) = s;
						End1 = true;
					}
					if (End1) break;
				}
				if(End1) break;
			}
			
			//右上
			for (Rpt[1].y=0; Rpt[1].y<HEIGHT/2; Rpt[1].y++) {
				for (Rpt[1].x=WIDTH/2; Rpt[1].x<WIDTH; Rpt[1].x++) {
					s = RhsvImage.at<Vec3b>(Rpt[1].y, Rpt[1].x);
					if ((s.val[0]>95 && s.val[0]<130) && s.val[1]>120 && s.val[2]>70) {
						RhsvImage.at<Vec3b>(Rpt[1].y, Rpt[1].x) = s;
						End1 = true;
					}
					if (End1) break;
				}
				if(End1) break;
			}

			//右下
			for (Rpt[2].y=HEIGHT/2; Rpt[2].y<HEIGHT; Rpt[2].y++) {
				for (Rpt[2].x=WIDTH/2; Rpt[2].x<WIDTH; Rpt[2].x++) {
					s = RhsvImage.at<Vec3b>(Rpt[2].y, Rpt[2].x);
					if ((s.val[0]>95 && s.val[0]<130) && s.val[1]>120 && s.val[2]>70) {
						RhsvImage.at<Vec3b>(Rpt[2].y, Rpt[2].x) = s;
						End2 = true;
					}
					if (End2) break;
				}
				if(End2) break;
			}

			//左下
			for (Rpt[3].y=HEIGHT/2; Rpt[3].y<HEIGHT; Rpt[3].y++) {
				for (Rpt[3].x=0; Rpt[3].x<WIDTH/2; Rpt[3].x++) {
					s = RhsvImage.at<Vec3b>(Rpt[3].y, Rpt[3].x);
					if ((s.val[0]>95 && s.val[0]<130) && s.val[1]>120 && s.val[2]>70) {
						RhsvImage.at<Vec3b>(Rpt[3].y, Rpt[3].x) = s;
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
			circle(RframeImage, Rpt[i], RADIUS, CV_RGB(255, 147, 0), 2, CV_AA, 0);
		}

		//枠の描画
		line(RframeImage, Rpt[0], Rpt[1], Scalar(0,0,150), 1, CV_AA);
		line(RframeImage, Rpt[1], Rpt[2], Scalar(0,0,150), 1, CV_AA);
		line(RframeImage, Rpt[2], Rpt[3], Scalar(0,0,150), 1, CV_AA);
		line(RframeImage, Rpt[3], Rpt[0], Scalar(0,0,150), 1, CV_AA);

		//最終の座標を印字
        if(Rframe<max_frame){ 
			Rframe++;
		}else{ 
			printf("Rpt[0]:(%d,%d)\n",Rpt[0].x ,Rpt[0].y);
			printf("Rpt[1]:(%d,%d)\n",Rpt[1].x ,Rpt[1].y);
			printf("Rpt[2]:(%d,%d)\n",Rpt[2].x ,Rpt[2].y);
			printf("Rpt[3]:(%d,%d)\n",Rpt[3].x ,Rpt[3].y);
		}
		printf("frame数:%d\n",Rframe);

		//RGBに変換
		cv::cvtColor(RhsvImage, RrecImage, CV_HSV2RGB);

		cv::imshow("Right", RframeImage);

		if(Rkey == 'c') Rframe = 0;

        if (Rkey == 'q') break;

		Rkey = cvWaitKey(10);

    }
	cv::waitKey(0);
	
	return 0;
}

//近傍点取得関数
int RNearPoint(CvPoint mouse_pt)
{
    int nx, ny;
    float radius, min_radius = RADIUS;
    int ret = -1;
    
    for(int i=0; i<POINT; i++){
        nx = mouse_pt.x - Rpt[i].x;
        ny = mouse_pt.y - Rpt[i].y;
        radius = sqrt((float)(nx*nx + ny*ny));
        if(radius < min_radius){
            min_radius = radius;
            ret = i;
        }
    }
    return ret;
}

//マウスイベント取得関数
void Ron_mouse(int event, int x, int y, int flags, void *param)

{
    CvPoint push_pt = cvPoint(x,y);

    //左クリック時に一番近い点を取得
	if(event == CV_EVENT_LBUTTONDOWN){
        Rpoint_flag = RNearPoint(push_pt);
	}

	//左クリック時に移動で頂点移動
    if((event == CV_EVENT_MOUSEMOVE)&&(flags == CV_EVENT_FLAG_LBUTTON)){
		Rpt[Rpoint_flag] = cvPoint(x, y);
    }
}
