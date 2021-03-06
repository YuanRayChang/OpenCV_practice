// Bounding_boxes_and_circles.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
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

void thresh_callback(int, void*);

int main()
{
	Mat src = imread("src.png", IMREAD_COLOR);
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	blur(src_gray, src_gray, Size(3, 3));
	const char* win = "src";
	namedWindow(win, WINDOW_AUTOSIZE);
	imshow(win, src);
	const int max_thresh = 255;
	createTrackbar("Threshold", win, &thresh, max_thresh, thresh_callback);
	thresh_callback(0, 0);
	waitKey();
}

void thresh_callback(int, void*) {
	Mat canny_output;
	Canny(src_gray, canny_output, thresh, thresh * 2);
	vector<vector<Point>> contours;
	findContours(canny_output, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

	vector<vector<Point>> contours_poly(contours.size());
	vector<Rect> boundRect(contours.size());
	vector<Point2f> centers(contours.size());
	vector<float> radius(contours.size());
	for (int i = 0; i < contours.size(); i++) {
		approxPolyDP(contours[i], contours_poly[i], 3, true);
		boundRect[i] = boundingRect(contours_poly[i]);
		minEnclosingCircle(contours_poly[i], centers[i], radius[i]);
	}

	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	for (int i = 0; i < contours.size(); i++) {
		
		drawContours(drawing, contours_poly, int(i), Scalar(255, 255, 255));
		rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), Scalar(100, 100, 100), 2);
		circle(drawing, centers[i], (int)radius[i], Scalar(220, 150, 180), 2);
	}
	imshow("contours", drawing);
}