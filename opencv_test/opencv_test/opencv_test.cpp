#include "pch.h"
#include <iostream>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;
int main()
{
	Mat img_color = imread("wade.jpg", -1);
	Mat img_gray = imread("wade.jpg", 0);
	Mat img_mod = img_color.clone();
	for (int r = 0; r < img_color.rows; r++) {
		for (int c = 0; c < img_color.cols; c++) {
			img_mod.at<Vec3b>(r, c)[0] = 0;
		}
	}

	//namedWindow("color", WINDOW_FREERATIO);
	//namedWindow("gray", WINDOW_AUTOSIZE);

	imshow("color", img_color);
	imshow("gray", img_gray);
	imshow("mod", img_mod);

	moveWindow("color", 100, 90);
	moveWindow("gray", 100 + img_color.cols + 5, 90);
	moveWindow("mod", 100, 90 + img_color.rows + 20);

	//imwrite("wade_gray.jpg", img_gray);

	// blend two image (must have same image size)
	double alpha = 0.78;
	double beta = (1.0 - alpha);
	Mat blend;
	addWeighted(img_color, alpha, img_mod, beta, 0.0, blend);
	imshow("Linear Blend", blend);

	waitKey();

}

