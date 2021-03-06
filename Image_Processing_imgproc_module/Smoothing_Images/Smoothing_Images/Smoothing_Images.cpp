// Smoothing_Images.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
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
	Mat src = imread("twd.jpg", IMREAD_COLOR);
	imshow("src", src);

	int MAX_KERNEL_LENGTH = 9;
	Mat dst_blur, dst_gaussian, dst_median, dst_bilateral;

	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2) {
		blur(src, dst_blur, Size(i, i), Point(-1, -1));
		imshow("dst_blur", dst_blur);
		waitKey();
	}

	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2) {
		GaussianBlur(src, dst_gaussian, Size(i, i), 0, 0);
		imshow("dst_gaussian", dst_gaussian);
		waitKey();
	}

	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2) {
		medianBlur(src, dst_median, i);
		imshow("dst_median", dst_median);
		waitKey();
	}

	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2) {
		bilateralFilter(src, dst_bilateral, i, 2*i, i/2);
		imshow("dst_bilateral", dst_bilateral);
		waitKey();
	}


	waitKey();

}

