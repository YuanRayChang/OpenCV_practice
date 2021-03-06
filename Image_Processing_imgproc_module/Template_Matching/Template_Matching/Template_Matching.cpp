// Template_Matching.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include "pch.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;

Mat src, temp, dst;
const char* win_img = "src";
const char* win_dst = "dst";

int method = 0;
int max_trackbar = 5;

void matching_method(int, void*);

int main()
{
	
	src = imread("dj.jpg", IMREAD_GRAYSCALE);
	temp = imread("dj_temp.jpg", IMREAD_GRAYSCALE);
	imshow("template", temp);
	namedWindow(win_img, WINDOW_AUTOSIZE);
	namedWindow(win_dst, WINDOW_AUTOSIZE);
	createTrackbar("0 - 5", win_img, &method, max_trackbar, matching_method);
	matching_method(0, 0);
	waitKey();
}

void matching_method(int, void*) {
	Mat img_display;
	img_display = src.clone();
	int dst_rows = src.rows - temp.rows + 1;
	int dst_cols = src.cols - temp.cols + 1;
	dst.create(dst_rows, dst_cols, CV_32FC1);
	matchTemplate(src, temp, dst, method);
	normalize(dst, dst, 0, 1, NORM_MINMAX, -1, Mat());

	double minVal, maxVal;
	Point minLoc, maxLoc, matchLoc;
	minMaxLoc(dst, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

	if (method == TM_SQDIFF || method == TM_SQDIFF_NORMED) {
		matchLoc = minLoc;
	}
	else {
		matchLoc = maxLoc;
	}

	rectangle(img_display, matchLoc, Point(matchLoc.x + temp.cols, matchLoc.y + temp.rows),
		Scalar::all(0), 2, 8, 0);
	rectangle(dst, matchLoc, Point(matchLoc.x + temp.cols, matchLoc.y + temp.rows),
		Scalar::all(0), 2, 8, 0);
	imshow(win_img, img_display);
	imshow(win_dst, dst);

}