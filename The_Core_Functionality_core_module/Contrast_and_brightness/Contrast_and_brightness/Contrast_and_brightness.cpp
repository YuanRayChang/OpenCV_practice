// Contrast_and_brightness.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include "pch.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("overexposed.jpg", IMREAD_COLOR);
	Mat dst0 = Mat::zeros(src.size(), src.type());
	Mat dst1;
	Mat dst_gamma;
	double alpha = 0.7;
	int beta = 5;
	
	// implementation
	for (int y = 0; y < src.rows; y++) {
		for (int x = 0; x < src.cols; x++) {
			for (int c = 0; c < src.channels(); c++) {
				dst0.at<Vec3b>(y, x)[c] =
					saturate_cast<uchar>(alpha*src.at<Vec3b>(y, x)[c] + beta);
			}
		}
	}

	// function provided by opencv
	src.convertTo(dst1, -1, alpha, beta);


	// implementation for the gamma correction
	double gamma = 1.4;
	Mat lookUpTable(1, 256, CV_8U);
	uchar* p = lookUpTable.ptr();
	for (int i = 0; i < 256; ++i)
		p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma) * 255.0);
	LUT(src, lookUpTable, dst_gamma);

	imshow("src", src);
	imshow("dst0", dst0);
	imshow("dst1", dst1);
	imshow("dst_gamma", dst_gamma);

	waitKey();
}

