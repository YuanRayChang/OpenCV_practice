// Laplace_operator.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
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
	Mat src, dst, abs_dst;
	int ksize = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	src = imread("manu.jpg", IMREAD_GRAYSCALE);
	Laplacian(src, dst, ddepth, ksize, scale, delta, BORDER_DEFAULT);
	
	// converting back to CV_8U
	convertScaleAbs(dst, abs_dst);
	
	imshow("abs_dst", abs_dst);
	waitKey();
}


