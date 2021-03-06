// Moments.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
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
	createTrackbar("threshold", win, &thresh, max_thresh, thresh_callback);
	thresh_callback(0, 0);
	waitKey();
}

void thresh_callback(int, void*) {
	Mat canny_output;
	Canny(src_gray, canny_output, thresh, thresh * 2, 3);
	vector<vector<Point>> contours;
	findContours(canny_output, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

	vector<Moments> mu(contours.size());
	for (int i = 0; i < contours.size(); i++) {
		mu[i] = moments(contours[i]);
	}

	vector<Point2f> m_center(contours.size());
	for (int i = 0; i < contours.size(); i++) {
		m_center[i] = Point2f(static_cast<float>(mu[i].m10 / (mu[i].m00 + 0.0005)),
			static_cast<float>(mu[i].m01 / (mu[i].m00 + 0.0005)));
		cout << "mass center [" << i << "] = " << m_center[i] << endl;
	}

	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	for (int i = 0; i < contours.size(); i++) {
		drawContours(drawing, contours, (int)i, Scalar(200, 240, 180));
		circle(drawing, m_center[i], 2, Scalar(0, 0, 0), -1); // -1 means filled
	}
	imshow("contours", drawing);
	for (int i = 0; i < contours.size(); i++) {
		cout << "contour area(m00) = " << mu[i].m00 << ", contour area(contourArea) = "
			<< contourArea(contours[i]) << ", length = " << arcLength(contours[i], true) << endl;
	}

}
