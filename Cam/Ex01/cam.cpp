
#include <opencv2/core/core.hpp>        // coreモジュールのヘッダーをインクルード
#include <opencv2/highgui/highgui.hpp>  // highguiモジュールのヘッダーをインクルード
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>




int main(int argc, const char* argv[])
{
	/*
	int key;
	CvCapture *src;
	
	IplImage *frame;
	cvNamedWindow("camera");

	src = cvCaptureFromCAM(0);

	if(src == NULL){
		printf("映像を取得できません\n");
		cvWaitKey(0);
		return -1;
	}

	while (1){

		frame = cvQueryFrame(src);

		cvShowImage("camera", frame);

		key = cvWaitKey(1000);
		if(key == 27) break;

	}

	cvDestroyWindow("camera");
	cvReleaseCapture(&src);
	*/
  return 0;
}
