// Basic_Thresholding_Operations.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include "pch.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;

int threshold_value = 0;
int threshold_type = 3;
const int max_value = 255;
const int max_type = 4;
const int max_binary_value = 255;

Mat src, dst;
const char* win_name = "Thresholding";

void Threshold_demo(int, void*);

int main()
{
	src = imread("dj.jpg", IMREAD_GRAYSCALE);
	namedWindow(win_name, WINDOW_AUTOSIZE);
	
	createTrackbar("type", win_name, &threshold_type, max_type, Threshold_demo);
	createTrackbar("value", win_name, &threshold_value, max_value, Threshold_demo);
	Threshold_demo(0, 0);
	waitKey();
}

void Threshold_demo(int, void*) {
	/* 
	 0: Binary
	 1: Binary Inverted
	 2: Threshold Truncated
	 3: Threshold to Zero
	 4: Threshold to Zero Inverted
	*/

	threshold(src, dst, threshold_value, max_binary_value, threshold_type);
	imshow(win_name, dst);
	
}