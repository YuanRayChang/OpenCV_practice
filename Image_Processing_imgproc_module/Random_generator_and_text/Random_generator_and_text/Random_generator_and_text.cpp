// Random_generator_and_text.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include "pch.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;

#define NUM 30
#define x1 0
#define x2 800
#define y1 0
#define y2 600

void Draw_random_line(Mat img, RNG rng);
static Scalar randomColor(RNG& rng);
void Display_random_text(Mat img, RNG rng);

int main()
{	
	//RNG implements a random number generator. 
	//In this example, rng is a RNG element initialized with the value 0xFFFFFFFF
	RNG rng(0xFFFFFFFF); 

	Mat image = Mat::zeros(600, 800, CV_8UC3);
	
	Draw_random_line(image, rng);
	Display_random_text(image, rng);

	imshow("image", image);

	waitKey();
}

void Draw_random_line(Mat img, RNG rng) {
	int lineType = LINE_8;
	Point pt1, pt2;
	for (int i = 0; i < NUM; i++) {
		pt1.x = rng.uniform(x1, x2);
		pt1.y = rng.uniform(y1, y2);
		pt2.x = rng.uniform(x1, x2);
		pt2.y = rng.uniform(y1, y2);

		line(img, pt1, pt2, randomColor(rng), rng.uniform(1, 10), 8);
		randomColor(rng);
				
	}
}

static Scalar randomColor(RNG& rng)
{
	int icolor = (unsigned)rng;
	return Scalar(icolor & 255, (icolor >> 8) & 255, (icolor >> 16) & 255);
}

void Display_random_text(Mat img, RNG rng) {
	for (int i = 0; i < NUM; i++) {
		Point org; // left bottom of the font
		org.x = rng.uniform(x1, x2);
		org.y = rng.uniform(y1, y2);
		putText(img, "ABC", org, rng.uniform(0, 8), rng.uniform(0, 200)*0.05 + 0.1,
			randomColor(rng), rng.uniform(1, 10), LINE_8);
	}
	
}