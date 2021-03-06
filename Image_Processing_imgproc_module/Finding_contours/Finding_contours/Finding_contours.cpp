// Finding_contours.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include "pch.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;

Mat src_gray;
int thresh = 100;
RNG rng(123);

void thresh_callback(int, void*);

int main()
{
	Mat src = imread("src.jpg", IMREAD_COLOR);
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	blur(src_gray, src_gray, Size(3, 3));
	const char* win = "src";
	//const char* win_convex = "src";

	namedWindow(win, WINDOW_AUTOSIZE);
	imshow(win, src);
	const int max_thresh = 255;
	createTrackbar("threshold", win, &thresh, max_thresh, thresh_callback);
	thresh_callback(0, 0);
	waitKey();

}

void thresh_callback(int, void*) {
	Mat canny_output;
	Canny(src_gray, canny_output, thresh, thresh * 2);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	for (int i = 0; i < contours.size(); i++) {
		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
	}
	imshow("Contours", drawing);

	vector<vector<Point> > hull(contours.size());
	for (size_t i = 0; i < contours.size(); i++)
	{
		convexHull(contours[i], hull[i]);
	}
	Mat convex = Mat::zeros(canny_output.size(), CV_8UC3);
	for (int i = 0; i < contours.size(); i++) {
		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		drawContours(convex, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
		drawContours(convex, hull, (int)i, color);
	}
	imshow("convex", convex);

}
