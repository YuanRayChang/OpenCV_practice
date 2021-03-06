// Shi_Tomasi_corner_detector.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include "pch.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
using namespace std;
using namespace cv;


Mat src, src_gray;
int corner_num = 5;
int max_corner = 100;
const char* win = "corner";
void goodFeaturesToTrack_demo(int, void*);

int main()
{
	src = imread("corner.png", IMREAD_COLOR);
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	namedWindow(win, WINDOW_AUTOSIZE);
	createTrackbar("corner number", win, &corner_num, max_corner, goodFeaturesToTrack_demo);
	//imshow("src", src);
	goodFeaturesToTrack_demo(0, 0);
	waitKey();
}

void goodFeaturesToTrack_demo(int, void*) {
	vector<Point2f> corners;
	double qualityLevel = 0.05;
	double minDistance = 20;
	int blockSize = 9;
	int gradientSize = 9;
	bool useHarrisDetector = false;
	double k = 0.04;

	Mat copy = src.clone();
	goodFeaturesToTrack(src_gray, corners, corner_num, qualityLevel, minDistance,
		Mat(), blockSize, gradientSize, useHarrisDetector, k);

	for (int i = 0; i < corners.size(); i++) {
		circle(copy, corners[i], 3, Scalar(255), -1);
	}
	imshow(win, copy);

}

