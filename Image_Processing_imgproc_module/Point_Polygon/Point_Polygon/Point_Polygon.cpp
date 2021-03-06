// Point_Polygon.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include "pch.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat src = Mat::zeros(Size(400, 400), CV_8U);
	vector<Point2i> vert(4);
	vert[0] = Point(100, 100);
	vert[1] = Point(225, 100);
	vert[2] = Point(225, 200);
	vert[3] = Point(100, 200);

	for (int i = 0; i < vert.size(); i++) {
		line(src, vert[i], vert[(i + 1) % 4], Scalar(255), 3);
	}

	vector<vector<Point>> contours;
	findContours(src, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

	Mat raw_dist(src.size(), CV_32F);
	for (int i = 0; i < raw_dist.rows; i++) {
		for (int j = 0; j < raw_dist.cols; j++) {
			raw_dist.at<float>(i, j) = (float)pointPolygonTest(contours[0],
				Point2f((float)j, (float)i), true);
		}
	}
	
	double minVal, maxVal;
	Point maxDistPt; // circle center
	minMaxLoc(raw_dist, &minVal, &maxVal, NULL, &maxDistPt);

	minVal = abs(minVal);
	maxVal = abs(maxVal);

	Mat drawing = Mat::zeros(src.size(), CV_8UC3);
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			if (raw_dist.at<float>(i, j) < 0) {
				drawing.at<Vec3b>(i, j)[0] = (uchar)(255 - abs(raw_dist.at<float>(i, j)) * 255 / minVal);
			}
			else if (raw_dist.at<float>(i, j) > 0) {
				drawing.at<Vec3b>(i, j)[2] = (uchar)(255 - raw_dist.at<float>(i, j) * 255 / maxVal);
			}
			else {
				drawing.at<Vec3b>(i, j)[0] = 255;
				drawing.at<Vec3b>(i, j)[1] = 255;
				drawing.at<Vec3b>(i, j)[2] = 255;

			}
		}
	}

	circle(drawing, maxDistPt, (int)maxVal, Scalar(255), 2);
	imshow("src", src);
	imshow("drawing", drawing);
	waitKey();
}

