
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cv.h>
#include <cxcore.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 640
#define HEIGHT 480
#define RADIUS 4
#define POINT 4
#define max_frame 30

CvPoint pt[POINT];
int frame=0;//フレーム数
int key = NULL;
int point_flag = -1;

//プロトタイプ
int NearPoint(CvPoint mouse_pt);
void on_mouse(int event, int x, int y, int flags, void *param);

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

		//最終の座標を印字
        if(frame<max_frame){ frame++;
		}else{ 
			printf("pt[0]:(%d,%d)\n",pt[0].x ,pt[0].y);
			printf("pt[1]:(%d,%d)\n",pt[1].x ,pt[1].y);
			printf("pt[2]:(%d,%d)\n",pt[2].x ,pt[2].y);
			printf("pt[3]:(%d,%d)\n",pt[3].x ,pt[3].y);
		}
		printf("frame数:%d\n",frame);

		if(key == 'c') frame = 0;

        if (key == 'q') break;

		key = cvWaitKey(10);
    }

	cvWaitKey(0);
	
	cvReleaseCapture(&capture);
	
	cvReleaseImage(&recImage);
	cvReleaseImage(&hsvImage);
	
	cvDestroyAllWindows();

	return 0;
}

//近傍点取得関数
int NearPoint(CvPoint mouse_pt)
{
    int nx, ny;
    float radius, min_radius = RADIUS;
    int ret = -1;
    
    for(int i=0; i<POINT; i++){
        nx = mouse_pt.x - pt[i].x;
        ny = mouse_pt.y - pt[i].y;
        radius = sqrt((float)(nx*nx + ny*ny));
        if(radius < min_radius){
            min_radius = radius;
            ret = i;
        }
    }
    return ret;
}

//マウスイベント取得関数
void on_mouse(int event, int x, int y, int flags, void *param)

{
    CvPoint push_pt = cvPoint(x,y);

    //左クリック時に一番近い点を取得
	if(event == CV_EVENT_LBUTTONDOWN){
        point_flag = NearPoint(push_pt);
	}

	//左クリック時に移動で頂点移動
    if((event == CV_EVENT_MOUSEMOVE)&&(flags == CV_EVENT_FLAG_LBUTTON)){
		pt[point_flag] = cvPoint(x, y);
    }
}