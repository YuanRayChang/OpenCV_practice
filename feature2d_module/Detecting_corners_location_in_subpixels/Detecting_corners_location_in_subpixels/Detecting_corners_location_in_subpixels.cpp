// Detecting_corners_location_in_subpixels.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include "pch.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;

Mat src, src_gray;
int max_corners = 8;
int max_trackbar = 50;
const char* win = "window";

void goodFeaturesToTrack_demo(int, void*);

int main()
{
	src = imread("src.png", IMREAD_COLOR);
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	namedWindow(win, WINDOW_AUTOSIZE);
	createTrackbar("corner num", win, &max_corners, max_trackbar, goodFeaturesToTrack_demo);
	goodFeaturesToTrack_demo(0, 0);
	//imshow(win, src);
	waitKey();
}

void goodFeaturesToTrack_demo(int, void*) {
	vector<Point2f> corners;
	double qualityLevel = 0.01;
	double minDistance = 10;
	int blockSize = 3;
	int gradientSize = 3;
	bool useHarrisDetector = false;
	double k = 0.04;

	Mat copy = src.clone();
	goodFeaturesToTrack(src_gray, corners, max_corners, qualityLevel, minDistance, Mat(),
		blockSize, gradientSize, useHarrisDetector, k);

	cout << "number of corners detected: " << corners.size() << endl;
	for (int i = 0; i < corners.size(); i++) {
		cout << "corner[" << i << "] = (" << corners[i].x << ", " << corners[i].y << ")" << endl;
	}

	for (int i = 0; i < corners.size(); i++) {
		circle(copy, corners[i], 4, Scalar(255), FILLED);
	}
	imshow(win, copy);


	Size winSize = Size(3, 3);
	Size zeroZone = Size(-1, -1);
	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 40, 0.001);
	cornerSubPix(src_gray, corners, winSize, zeroZone, criteria);
	for (int i = 0; i < corners.size(); i++) {
		cout << "refined corner[" << i << "] = (" << corners[i].x << ", " << corners[i].y << ")" << endl;
	}

}
