// opencv_test.cpp : Defines the entry point for the console application.
//

// #include "stdafx.h"
#include <opencv2/opencv.hpp>
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;


Mat get_Gaussian_Kernel(int n, double sigma_t, double sigma_s, bool normalize);
Mat get_Laplacian_Kernel();
Mat Gaussianfilter(const Mat input, int n, double sigma_t, double sigma_s);
Mat Laplacianfilter(const Mat input);
Mat Mirroring(const Mat input, int n);


int main() {

	Mat input = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input_gray, output, output_BGR;

	// check for validation
	if (!input.data) {
		printf("Could not open\n");
		return -1;
	}

	cvtColor(input, input_gray, CV_RGB2GRAY);	// convert RGB to Grayscale
//	input_gray.convertTo(input_gray, CV_64F, 1.0 / 255);	// 8-bit unsigned char -> 64-bit floating point
	
	int thres1 = 100;
	int thres2 = 127;
	Canny(input_gray, output, thres1, thres2);
	Canny(input, output_BGR, thres1, thres2);
	
	namedWindow("Grayscale", WINDOW_AUTOSIZE);
	imshow("Grayscale", input_gray);

	namedWindow("BGR", WINDOW_AUTOSIZE);
	imshow("BGR", input);

	namedWindow("Canny_Gray", WINDOW_AUTOSIZE);
	imshow("Canny_Gray", output);

	namedWindow("Canny_BGR", WINDOW_AUTOSIZE);
	imshow("Canny_BGR", output_BGR);

	waitKey(0);

	return 0;
}



