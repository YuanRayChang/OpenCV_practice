// Morphology_Transformations.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include "pch.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;

Mat src, dst;

int morph_elem = 0;
int morph_size = 0;
int morph_operator = 0;
int const max_operator = 4;
int const max_elem = 2;
int const max_kernel_size = 21;

const char* win_name = "Morphology Transformations Demo";
void Morphology_Operations(int, void*);

int main()
{
	src = imread("spurs.jpg", IMREAD_COLOR);
	//imshow("src", src);
	namedWindow(win_name, WINDOW_AUTOSIZE);

	createTrackbar("Operator", win_name, &morph_operator, max_operator,
		Morphology_Operations);
	createTrackbar("Element", win_name, &morph_elem, max_elem,
		Morphology_Operations);
	createTrackbar("Size", win_name, &morph_size, max_kernel_size,
		Morphology_Operations);
	Morphology_Operations(0, 0);
	waitKey();
}

void Morphology_Operations(int, void*) {
	int operation = morph_operator + 2;
	Mat element = getStructuringElement(morph_elem, Size(2 * morph_size + 1, 2 * morph_size + 1),
		Point(morph_size, morph_size));

	morphologyEx(src, dst, operation, element);
	imshow(win_name, dst);
}

/*
	Opening: MORPH_OPEN: 2
	Closing : MORPH_CLOSE : 3
	Gradient : MORPH_GRADIENT : 4
	Top Hat : MORPH_TOPHAT: 5
	Black Hat : MORPH_BLACKHAT: 6

*/

	