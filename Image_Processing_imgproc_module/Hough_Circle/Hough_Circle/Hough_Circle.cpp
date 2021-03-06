// Hough_Circle.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include "pch.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;

Mat src, src_gray, src_circle;
const char* win = "hough circle";
int param2 = 30;
int max_param2 = 75;
void hough_circle(int, void*);

int main()
{
	src = imread("circles.jpg", IMREAD_COLOR);
	namedWindow(win, WINDOW_AUTOSIZE);
	createTrackbar("param2", win, &param2, max_param2, hough_circle);
	hough_circle(0, 0);
	waitKey();
}

void hough_circle(int, void*) {
	src_circle = src.clone();
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	medianBlur(src_gray, src_gray, 5);
	vector<Vec3f> circles;
	HoughCircles(src_gray, circles, HOUGH_GRADIENT, 1, src_gray.cols / 50, 100 , param2,
		1, 30);
	for (int i = 0; i < circles.size(); i++) {
		Vec3i c = circles[i];
		Point center = Point(c[0], c[1]);
		int radius = c[2];
		circle(src_circle, center, 1, Scalar(0, 0, 255), 1, LINE_AA);
		circle(src_circle, center, radius, Scalar(0, 0, 0), 2, LINE_AA);
	}
	imshow(win, src_circle);
}