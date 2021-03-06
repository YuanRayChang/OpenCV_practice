// Harris_corner_detector.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include "pch.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;

Mat src, src_gray;
int thresh = 100;
const int max_thresh = 255;

const char* win = "src";

void cornerHarrisDemo(int, void*);

int main()
{
	src = imread("window.png", IMREAD_COLOR);
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	namedWindow(win, WINDOW_AUTOSIZE);
	createTrackbar("threshold", win, &thresh, max_thresh, cornerHarrisDemo);
	imshow(win, src);
	cornerHarrisDemo(0, 0);
	waitKey();
}

void cornerHarrisDemo(int, void*) {
	int blockSize = 3;
	int apertureSize = 3; // for sobel
	double k = 0.02;
	Mat dst = Mat::zeros(src.size(), CV_32FC1);
	cornerHarris(src_gray, dst, blockSize, apertureSize, k);
	Mat dst_norm, dst_norm_scaled;
	normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(dst_norm, dst_norm_scaled); // converts the result to 8-bit

	for (int i = 0; i < dst_norm.rows; i++) {
		for (int j = 0; j < dst_norm.cols; j++) {
			if ((int)dst_norm.at<float>(i, j) > thresh) {
				circle(dst_norm_scaled, Point(j, i), 5, Scalar(255), 1, LINE_8);
			}
		}
	}
	imshow("dst", dst_norm_scaled);
}