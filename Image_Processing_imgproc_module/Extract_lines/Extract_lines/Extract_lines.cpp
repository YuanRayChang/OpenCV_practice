// Extract_lines.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
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
	Mat src = imread("src.png", IMREAD_GRAYSCALE);
	imshow("src", src);
	Mat bin;
	adaptiveThreshold(~src, bin, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);
	imshow("binary", bin);

	Mat horizontal, vertical;
	int horizontal_size = bin.cols / 30;
	Mat horizontalStructure = getStructuringElement(MORPH_RECT, Size(horizontal_size, 1),
		Point(-1, -1));
	erode(bin, horizontal, horizontalStructure);
	dilate(horizontal, horizontal, horizontalStructure);
	imshow("horizontal", horizontal);
	
	int vertical_size = bin.rows / 30;
	Mat verticalStructure = getStructuringElement(MORPH_RECT, Size(1, vertical_size));
	erode(bin, vertical, verticalStructure);
	dilate(vertical, vertical, verticalStructure);
	imshow("vertical", vertical);
	
	bitwise_not(vertical, vertical);
	imshow("vertical_bit", vertical);

	// Extract edges and smooth image according to the logic
	// 1. extract edges
	// 2. dilate(edges)
	// 3. src.copyTo(smooth)
	// 4. blur smooth img
	// 5. smooth.copyTo(src, edges)


	// 1. extract edges
	Mat edges;
	adaptiveThreshold(vertical, edges, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, -2);
	imshow("edges", edges);

	// 2. dilate(edges)
	Mat kernel = Mat::ones(2, 2, CV_8UC1);
	dilate(edges, edges, kernel);
	imshow("edges(dilate", edges);

	// 3. src.copyTo(smooth)
	Mat smooth;
	vertical.copyTo(smooth);

	// 4. blur smooth img
	blur(smooth, smooth, Size(2, 2));
	imshow("smooth", smooth);

	// 5. smooth.copyTo(src, edges)
	smooth.copyTo(vertical, edges);
	imshow("final", vertical);

	waitKey();
}

