// Histogram_Equalization.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
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
	Mat src = imread("dj.jpg", IMREAD_GRAYSCALE);
	Mat dst;
	equalizeHist(src, dst);
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	
}
