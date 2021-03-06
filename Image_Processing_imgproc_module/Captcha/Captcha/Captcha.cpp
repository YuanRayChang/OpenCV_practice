// Captcha.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include "pch.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;

#define MAXROW 210
#define MAXCOL 120

Scalar randomColor(RNG& rng);
string randomText(RNG rng);
void generateText(Mat& img, RNG rng);
void Draw_random_line(Mat img, RNG rng);
void Draw_random_circle(Mat img, RNG rng);


int main()
{
	time_t t = time(NULL);
	RNG rng(static_cast<int64_t>(t));
	Scalar background(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
	Mat captcha(MAXCOL, MAXROW, CV_8UC3, background);
	generateText(captcha, rng);
	Draw_random_line(captcha, rng);
	Draw_random_circle(captcha, rng);
	imshow("Captcha", captcha);



	waitKey();

}

Scalar randomColor(RNG& rng)
{
	int icolor = (unsigned)rng;
	return Scalar(icolor & 255, (icolor >> 8) & 255, (icolor >> 16) & 255);
}

string randomText(RNG rng) {
	string text[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
		"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k",
		"l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v",
		"w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G",
		"H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R",
		"S", "T", "U", "V", "W", "X", "Y", "Z" };
	
	return text[rng.uniform(0, 62)];
}

void generateText(Mat& img, RNG rng) {
	for (int i = 0; i < 4; i++) {
		Point org;
		org.x = 50 * i + 5;
		org.y = 80 + rng.uniform(-8, 8);
		
		putText(img, randomText(rng), org, rng.uniform(0, 8), rng.uniform(3, 4),
			randomColor(rng), rng.uniform(2, 3), 8);
	}
}

void Draw_random_line(Mat img, RNG rng) {
	int lineType = LINE_8;
	Point pt1, pt2;
	for (int i = 0; i < 5; i++) {
		pt1.x = rng.uniform(0, MAXROW);
		pt1.y = rng.uniform(0, MAXCOL);
		pt2.x = rng.uniform(0, MAXROW);
		pt2.y = rng.uniform(0, MAXCOL);

		line(img, pt1, pt2, randomColor(rng), rng.uniform(1, 4), 8);
		randomColor(rng);

	}
}

void Draw_random_circle(Mat img, RNG rng) {
	Point center;
	for (int i = 0; i < rng.uniform(15, 45); i++) {
		center.x = rng.uniform(0, MAXROW);
		center.y = rng.uniform(0, MAXCOL);
		circle(img, center, rng.uniform(0, 3), randomColor(rng), -1, 8);
	}
}
