#include "hist_func.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main() {
	Mat input = imread("input.jpg", CV_LOAD_IMAGE_COLOR); // always convert image to the color one
	Mat input_gray;

	cvtColor(input, input_gray, CV_BGR2GRAY);	// change BGR image to grayscale

	// PDF, CDF txt files
	FILE* f_PDF, * f_CDF;


	// fopen_s "w+": 파일을 읽고 쓰기위해 오픈한다. 
	// 지정된 파일이 없는 경우 새로운 파일 생성
	// 지정한 파일 있는경우 내용 모두 지우고 새 파일 만듦.

	fopen_s(&f_PDF, "PDF.txt", "w+");
	fopen_s(&f_CDF, "CDF.txt", "w+");

	// each histogram
	float* PDF = cal_PDF(input_gray);		// PDF of Input image(Grayscale) : [L]
	float* CDF = cal_CDF(input_gray);		// CDF of Input image(Grayscale) : [L]

	for (int i = 0; i < L; i++) {
		// write PDF, CDF
		fprintf(f_PDF, "%d\t%f\n", i, PDF[i]);
		fprintf(f_CDF, "%d\t%f\n", i, CDF[i]);
	}

	// memory release
	free(PDF);	// hist_func.hdml cal_PDF()에서 동적 할당 해주었던 PDF 메모리 해제
	free(CDF);  // hist_func.hdml cal_CDF()에서 동적 할당 해주었던 CDF 메모리 해제
	fclose(f_PDF);
	fclose(f_CDF);

	////////////////////// Show each image ///////////////////////

	namedWindow("RGB", WINDOW_AUTOSIZE);
	imshow("RGB", input);

	namedWindow("Grayscale", WINDOW_AUTOSIZE);
	imshow("Grayscale", input_gray);

	//////////////////////////////////////////////////////////////

	waitKey(0);

	return 0;
}