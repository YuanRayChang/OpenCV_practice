// Mat.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include "pch.h"
#include <iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat A, C;
	A = imread("ginobili.png", IMREAD_COLOR);
	Mat B(A); // use the copy constructor
	C = A; // assignment operator
	Mat D(A, Rect(0, 0, 200, 200)); // using a rectangle to create ROI
	Mat E = A(Range::all(), Range(100, 200)); // using row and column boundaries

	// B, C, D, E will only copy the headers

	/*imshow("A", A);
	imshow("B", B);
	imshow("C", C);
	imshow("D", D);
	imshow("E", E);*/

	Mat F = A.clone();
	Mat G;
	A.copyTo(G);

	// for F and G, matrix of an image were copied

	Mat M(2, 3, CV_8UC3, Scalar(0, 0, 255));
	cout << "M = " << endl << M << endl;


	Mat Eye = Mat::eye(4, 4, CV_8U);
	cout << "Eye = " << endl << Eye << endl;
	Mat O = Mat::ones(3, 3, CV_8U);
	cout << "Ones = " << endl << O << endl;
	Mat Z = Mat::zeros(2, 2, CV_8U);
	cout << "Zeros = " << endl << Z << endl;

	Mat H = (Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	cout << "H = " << endl << " " << H << endl << endl;
	Mat RowClone = H.row(1).clone();
	cout << "RowClone = " << endl << " " << RowClone << endl << endl;

	Mat R = Mat(4, 3, CV_8UC3);
	randu(R, Scalar::all(0), Scalar::all(255));
	cout << "R = " << endl << R << endl;

	Point2f P2(3, 3);
	cout << "Point(2D) = " << P2 << endl;
	Point3f P3(1, 2, 3);
	cout << "Point(3D) = " << P3 << endl;

	vector<float> v;
	v.push_back(1); v.push_back(2); v.push_back(CV_PI);
	cout << "Vector of float via Mat = " << endl << Mat(v) << endl;

	vector<Point2f> vPoints(20);
	for (int i = 0; i < vPoints.size(); i++)
		vPoints[i] = Point2f((float)(i * 5), (float)(i % 5));
	cout << "A vector of 2D Points = " << endl << vPoints << endl << endl;
	waitKey();
}

