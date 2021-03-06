// Mask_operations_on_matrices.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include "pch.h"
#include <iostream>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

void Sharpen(const Mat& Input, Mat& Output);

int main()
{
	Mat src, dst0, dst1;
	src = imread("wade.jpg", IMREAD_COLOR);
	imshow("Input", src);

	double t = (double)getTickCount();
	Sharpen(src, dst0);
	t = ((double)getTickCount() - t) / getTickFrequency();
	cout << "Hand written function time passed in seconds: " << t << endl;
	imshow("Output0", dst0);

	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0,
									-1, 5, -1,
									0, -1, 0);

	t = (double)getTickCount();
	filter2D(src, dst1, src.depth(), kernel);
	t = ((double)getTickCount() - t) / getTickFrequency();
	cout << "Built-in filter2D time passed in seconds:     " << t << endl;
	imshow("Output1", dst1);


	waitKey();
}

void Sharpen(const Mat& Input, Mat& Output)
{
	CV_Assert(Input.depth() == CV_8U); // accept only uchar image
	const int nChannels = Input.channels();
	Output.create(Input.size(), Input.type());

	for (int i = 1; i < Input.rows - 1; i++) {
		const uchar* previous = Input.ptr<uchar>(i - 1);
		const uchar* current = Input.ptr<uchar>(i);
		const uchar* next = Input.ptr<uchar>(i + 1);

		uchar* output = Output.ptr<uchar>(i);

		for (int j = nChannels; j < nChannels*(Input.cols - 1); j++) {
			*output++ = saturate_cast<uchar>(5 * current[j] - previous[j] - next[j] -
				current[j - nChannels] - current[j + nChannels]);
		}

	}

	Output.row(0).setTo(Scalar(0));
	Output.row(Output.rows - 1).setTo(Scalar(0));
	Output.col(0).setTo(Scalar(0));
	Output.col(Output.cols - 1).setTo(Scalar(0));

}