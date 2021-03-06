// Hit_and_Miss.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
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
	Mat src = (Mat_<uchar>(8, 8)<<
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 255, 255, 255, 0, 0, 0, 255,
		0, 255, 255, 255, 0, 0, 0, 0,
		0, 255, 255, 255, 0, 255, 0, 0,
		0, 0, 255, 0, 0, 0, 0, 0,
		0, 0, 255, 0, 0, 255, 255, 0,
		0, 255, 0, 255, 0, 0, 255, 0,
		0, 255, 255, 255, 0, 0, 0, 0);

	Mat kernel = (Mat_<int>(3, 3)<<
		0, 1, 0,
		1, -1, 1,
		0, 1, 0);

	Mat dst;
	morphologyEx(src, dst, MORPH_HITMISS, kernel);
	const int rate = 50;
	kernel = (kernel + 1) * 127;
	kernel.convertTo(kernel, CV_8U); // must have this line in order to use imshow
	resize(kernel, kernel, Size(), rate, rate, INTER_NEAREST);
	resize(src, src, Size(), rate, rate, INTER_NEAREST);
	resize(dst, dst, Size(), rate, rate, INTER_NEAREST);

	imshow("src", src);
	imshow("dst", dst);
	imshow("kernel", kernel);

	waitKey();
}
