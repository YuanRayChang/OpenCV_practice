// Eroding_and_Dilating.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include "pch.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;


Mat src, dst_erode, dst_dilate;
int erosion_elem = 1;
int erosion_size = 1;
int dilation_elem = 1;
int dilation_size = 1;
int const max_elem = 2;
int const max_kernel_size = 21;

void Erosion(int, void*);
void Dilation(int, void*);

int main()
{
	src = imread("manu.jpg", IMREAD_COLOR);
	namedWindow("erode", WINDOW_AUTOSIZE);
	namedWindow("dilate", WINDOW_AUTOSIZE);

	createTrackbar("Element", "erode", 
		&erosion_elem, max_elem, Erosion);
	createTrackbar("Kernel size", "erode",
		&erosion_size, max_kernel_size,
		Erosion);

	createTrackbar("Element", "dilate",
		&dilation_elem, max_elem, Dilation);
	createTrackbar("Kernel size", "dilate",
		&dilation_size, max_kernel_size,
		Dilation);
	Erosion(0, 0);
	Dilation(0, 0);
	waitKey();
}

void Erosion(int, void*) {
	int erosion_type = 0;
	if (erosion_elem == 0) { erosion_type = MORPH_RECT; }
	else if (erosion_elem == 1) { erosion_type = MORPH_CROSS; }
	else if (erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }
	Mat element = getStructuringElement(erosion_type,
		Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		Point(erosion_size, erosion_size));
	erode(src, dst_erode, element);
	imshow("erode", dst_erode);
}


void Dilation(int, void*)
{
	int dilation_type = 0;
	if (dilation_elem == 0) { dilation_type = MORPH_RECT; }
	else if (dilation_elem == 1) { dilation_type = MORPH_CROSS; }
	else if (dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }
	Mat element = getStructuringElement(dilation_type,
		Size(2 * dilation_size + 1, 2 * dilation_size + 1),
		Point(dilation_size, dilation_size));
	dilate(src, dst_dilate, element);
	imshow("dilate", dst_dilate);
}