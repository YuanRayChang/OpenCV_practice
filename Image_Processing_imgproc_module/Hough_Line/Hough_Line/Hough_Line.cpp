// Hough_Line.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include "pch.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;
Mat src, src_gray, edges;
Mat std_hough, prob_hough;
int min_threshold = 50;
int max_trackbar = 150;
int s_trackbar = max_trackbar;
int p_trackbar = max_trackbar;
const char* win_std = "standard hough";
const char* win_prob = "probabilistic hough";

void standard_hough(int, void*);
void probabilistic_hough(int, void*);


int main()
{
	src = imread("window.png", IMREAD_COLOR);
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	Canny(src_gray, edges, 50, 200, 3);

	char thresh_label[50];
	sprintf(thresh_label, "Thres: %d + input", min_threshold);

	namedWindow(win_std, WINDOW_AUTOSIZE);
	createTrackbar(thresh_label, win_std, &s_trackbar, max_trackbar, standard_hough);

	namedWindow(win_prob, WINDOW_AUTOSIZE);
	createTrackbar(thresh_label, win_prob, &p_trackbar, max_trackbar, probabilistic_hough);

	standard_hough(0, 0);
	probabilistic_hough(0, 0);
	waitKey();

}

void standard_hough(int, void*) {
	vector<Vec2f> s_lines;
	//cvtColor(edges, std_hough, COLOR_GRAY2BGR);
	std_hough = src.clone();
	HoughLines(edges, s_lines, 1, CV_PI / 180, min_threshold + s_trackbar, 0, 0);

	for (int i = 0; i < s_lines.size(); i++) {
		float r = s_lines[i][0];
		float t = s_lines[i][1];
		double cos_t = cos(t);
		double sin_t = sin(t);
		double x0 = r * cos_t;
		double y0 = r * sin_t;
		double alpha = 1000;

		Point pt1(cvRound(x0 + alpha * (-sin_t)), cvRound(y0 + alpha * cos_t));
		Point pt2(cvRound(x0 - alpha * (-sin_t)), cvRound(y0 - alpha * cos_t));
		line(std_hough, pt1, pt2, Scalar(0, 0, 255), 2, LINE_AA);
	}

	imshow(win_std, std_hough);
}

void probabilistic_hough(int, void*) {
	vector<Vec4i> p_lines;
	//cvtColor(edges, prob_hough, COLOR_GRAY2BGR);
	prob_hough = src.clone();

	HoughLinesP(edges, p_lines, 1, CV_PI / 180, min_threshold + p_trackbar, 30, 10);

	for (int i = 0; i < p_lines.size(); i++) {
		Vec4i l = p_lines[i];
		line(prob_hough, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 2, LINE_AA);

	}
	imshow(win_prob, prob_hough);
}