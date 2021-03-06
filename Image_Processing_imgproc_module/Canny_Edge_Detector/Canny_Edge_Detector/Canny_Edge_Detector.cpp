// Canny_Edge_Detector.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include "pch.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;

Mat src, src_gray;
Mat dst, edges;
int lowThreshold = 0;
const int max_lowThreshold = 100;
const int ratio = 3;
const int ksize = 3;
const char* win_name = "edges";
void cannyThreshold(int, void*);

int main()
{
	src = imread("window.jpg", IMREAD_COLOR);
	dst.create(src.size(), src.type());
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	namedWindow(win_name, WINDOW_AUTOSIZE);
	createTrackbar("Min threshold", win_name, &lowThreshold, max_lowThreshold, cannyThreshold);
	cannyThreshold(0, 0);
	waitKey();
}

void cannyThreshold(int, void*) {
	blur(src_gray, edges, Size(3, 3));
	Canny(edges, edges, lowThreshold, lowThreshold * 2.5, ksize);
	dst = Scalar::all(0);
	src.copyTo(dst, edges);
	imshow(win_name, dst);
}