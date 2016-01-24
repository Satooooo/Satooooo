
//頂点取得と透視変換のウィンドウを表示
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cv.h>
#include <cxcore.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "windows.h"


using namespace cv;
using namespace std;


void my_mouse_callback(int event, int x, int y, int flags, void* param);
void draw_box(Mat* img, Rect rect);
BOOL SetCursorPos(CvPoint X, CvPoint Y);

Rect box;
RECT rect;
bool drawing_box = false;
char str[32];
int t=0;
int mouseflag = 0;//マウス切り替え
int flag = -1;
int key = NULL;
POINT WP;
POINT CP;

int maxk = 0;
int cx = 0;
int cy = 0;
CvPoint C;


#define RADIUS 4
#define WIDTH 640
#define HEIGHT 480



int main(int argc, const char* argv[])
{
	VideoCapture cap(0);

	cap.set(CV_CAP_PROP_FRAME_WIDTH, WIDTH);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, HEIGHT);

	if (!cap.isOpened()) return -1;

	
	namedWindow("Processed", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
	namedWindow("Video", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
	moveWindow("Video", 320, 150);

	Mat src_img, out_img, mask_img;
	Mat dst_img = Mat::zeros(WIDTH, HEIGHT, CV_8UC3);
	Mat dst2_img = Mat::zeros(HEIGHT, WIDTH, CV_8UC3);

	Scalar paint(0,0,255);
	
	double tmparea;
	double maxarea;

	///////////////////

	box = Rect(-1, -1, 0, 0);
	//Mat temp = src_img.clone();

	setMouseCallback("Video", my_mouse_callback, (void *)&src_img);

	///////////////////

	while (1) {
		cap >> src_img;

		//矩形描画
		if (drawing_box) {
			draw_box(&src_img, box);
        }

		///////////////

		Mat lab_img,img,img_Result,copy_Result, r_img, g_img,b_img;

		cvtColor(src_img, lab_img, CV_BGR2Lab);

		vector<Mat> planes;

		split(src_img, planes);

		threshold(planes[2], r_img, 100, 255, THRESH_BINARY);

		img=10*planes[2]/planes[1];

		threshold(img, g_img,15, 255, THRESH_BINARY);

		img=10*planes[2]/planes[0];

		threshold(img, b_img, 15, 255, THRESH_BINARY);

		img=g_img&b_img; 

		img_Result = img & r_img;

		copy_Result=img_Result.clone();

		vector <vector<Point>> contours;

  		vector <Vec4i> hierarchy;

		//赤色のエリアを探す
		if(!contours.empty()){
			maxarea = contourArea(Mat(contours[0]));

			findContours(copy_Result, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

			for ( size_t k = 1; k < contours.size(); k++) {
				if ((tmparea = contourArea(Mat(contours[k]))) > maxarea) {
					maxk = k; 
					maxarea = tmparea;
				}
			}
		}

		//drawContours(dst_img, contours, maxk, paint, CV_FILLED, 8, hierarchy);
		//drawContours(dst2_img, contours, maxk, Scalar(0,0,0), CV_FILLED, 8, hierarchy);

		Moments m = moments(img_Result,true);

		//赤色の重心を計算
		cx=(int)(m.m10/m.m00);
		cy=(int)(m.m01/m.m00);

		if(cx <= 0) cx = NULL;
		if(cy <= 0) cy = NULL;

		C.x = cx;
		C.y = cy;

		CP.x = cx;
		CP.y = cy;

		if(mouseflag==1){//aを押したとき
			setMouseCallback("Video", my_mouse_callback, (void *)&src_img);

			HWND hwnd = (HWND)cvGetWindowHandle("Video");

			GetCursorPos(&WP);//マウスの座標取得

			//

			//GetWindowRect(hwnd, &rect);

			//printf("%d, %d\n",rect.left, rect.top);

			//ScreenToClient(hwnd, &CP);

			WP.x = C.x;
			WP.y = C.y;

			SetCursorPos(WP.x, WP.y);//マウスの座標に赤の重心の座標を代入
			
		}
		
		printf("赤色重心: x:%d y:%d\n",C.x, C.y);
		printf("マウス　: x:%d y:%d\n",WP.x, WP.y);
		
		circle(src_img, C, RADIUS, CV_RGB(255, 170, 0), 2, CV_AA, 0);

		imshow("Video", src_img);
		imshow("Processed", img_Result);

		key = cvWaitKey(10);

		if(flag == 1){//左ボタンを離したとき
			sprintf_s(str,sizeof(str),"img%d.jpg",t);
			Mat cap_img(src_img, box);
			imwrite(str, cap_img);
			printf("スクリーンショットを保存しました.\n");
			printf("名前: img%d.jpg\n",t);
			t++;
			flag = -1;
		}
		if (key == 'a') mouseflag = 1;//マウス切り替え
		if (key == 'b') mouseflag = 0;

		if (key == 'q') break;
	}

	return 0;
}

// コールバック関数
void my_mouse_callback(int event, int x, int y, int flags, void* param){
    Mat* image = static_cast<Mat*>(param);

    switch (event){
    case CV_EVENT_MOUSEMOVE:
        if (drawing_box){
            box.width = x - box.x;
            box.height = y - box.y;
        }
        break;

    case CV_EVENT_LBUTTONDOWN:
        drawing_box = true;
        box = Rect(x, y, 0, 0);
        break;

    case CV_EVENT_LBUTTONUP:
        drawing_box = false;
        if (box.width < 0){
            box.x += box.width;
            box.width *= -1;
        }
        if (box.height < 0){
            box.y += box.height;
            box.height *= -1;
        }
		flag = 1;
        draw_box(image, box);
        break;
	
	}
}

void draw_box(Mat* img, Rect rect){
    rectangle(*img, Point2d(box.x, box.y), Point2d(box.x + box.width, box.y + box.height),
        Scalar(0xff, 0x00, 0x00));
}