// Affine_Transformations.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
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
	Mat src = imread("dj.jpg", IMREAD_COLOR);

	Point2f srcTri[3];
	srcTri[0] = Point2f(0, 0);
	srcTri[1] = Point2f(src.cols - 1, 0);
	srcTri[2] = Point2f(0, src.rows - 1);

	Point2f dstTri[3];
	dstTri[0] = Point2f(0.f, src.rows*0.33f);
	dstTri[1] = Point2f(src.cols*0.85f, src.rows*0.25f);
	dstTri[2] = Point2f(src.cols*0.15f, src.rows*0.7f);

	Mat warp_mat = getAffineTransform(srcTri, dstTri);
	Mat warp_dst = Mat::zeros(src.rows, src.cols, src.type());
	warpAffine(src, warp_dst, warp_mat, warp_dst.size());

	Point center = Point(warp_dst.cols / 2, warp_dst.rows / 2);
	double angle = -50;
	double scale = 0.6;

	Mat rot_mat = getRotationMatrix2D(center, angle, scale);
	Mat warp_rotate_dst;
	warpAffine(warp_dst, warp_rotate_dst, rot_mat, warp_dst.size());

	imshow("src", src);
	imshow("warp", warp_dst);
	imshow("warp + rotate", warp_rotate_dst);
	waitKey();
}
