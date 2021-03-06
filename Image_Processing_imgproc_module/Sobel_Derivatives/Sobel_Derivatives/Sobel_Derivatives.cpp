// Sobel_Derivatives.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include "pch.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat src = imread("manu.jpg", IMREAD_GRAYSCALE);
	int ddepth = CV_16S;
	int ksize = 1;
	int scale = 1;
	int delta = 0;

	for (;;) {
		Mat grad_x, grad_y, abs_grad_x, abs_grad_y, grad;
		Sobel(src, grad_x, ddepth, 1, 0, ksize, scale, delta, BORDER_DEFAULT);
		Sobel(src, grad_y, ddepth, 1, 0, ksize, scale, delta, BORDER_DEFAULT);

		// converting back to CV_8U
		convertScaleAbs(grad_x, abs_grad_x);
		convertScaleAbs(grad_y, abs_grad_y);

		addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
		imshow("grad", grad);
		char key = (char)waitKey();
		if (key == 27) {
			break;
		}
		else if (key == 'k') {
			ksize = ksize + 2;
		}
		else if (key == 's') {
			scale++;
		}
		else if (key == 'd') {
			delta++;
		}
		else if (key == 'r') {
			scale = 1;
			ksize = 1;
			delta = 0;
		}
	}
	
}
