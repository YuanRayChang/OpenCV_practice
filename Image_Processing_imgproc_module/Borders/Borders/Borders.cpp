// Borders.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
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
	Mat src, dst;
	int top, bottom, left, right;
	int borderType = BORDER_CONSTANT;
	RNG rng(12345);

	src = imread("dj.jpg", IMREAD_COLOR);

	top = (int)src.rows*0.05;
	bottom = top;
	left = (int)src.cols*0.05;
	right = left;

	for (;;) {
		Scalar value(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		copyMakeBorder(src, dst, top, bottom, left, right, borderType, value);
		imshow("src", dst);
		char c = (char)waitKey(0);
		if (c == 27) {
			break;
		}
		else if (c == 'c') {
			borderType = BORDER_CONSTANT;
		}
		else if (c == 'r') {
			borderType = BORDER_REPLICATE;
		}
	}



}

