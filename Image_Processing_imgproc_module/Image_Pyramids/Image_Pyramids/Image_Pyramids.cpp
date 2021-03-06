// Image_Pyramids.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
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

	for (;;) {
		imshow("src", src);
		char c = (char)waitKey(0);
		
		if (c == 27) { // 27 means ESC
			break;
		}
		else if(c == 'i') { // press i to zoom in
			pyrUp(src, src, Size(src.cols * 2, src.rows * 2));
			cout << "zoom in: Image*2 \n";
		}
		else if (c == 'o') { // press o to zoom out
			pyrDown(src, src, Size(src.cols / 2, src.rows / 2));
			cout << "zoom out: Image/2 \n";
		}
	}
	
}


