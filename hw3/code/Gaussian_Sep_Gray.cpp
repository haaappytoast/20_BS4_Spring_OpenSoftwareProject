#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>       /* exp */
#include <chrono>		//for time count
#define IM_TYPE	CV_8UC3

using namespace cv;

// Image Type
// "G" for GrayScale Image, "C" for Color Image
#if (IM_TYPE == CV_8UC3)
typedef uchar G;
typedef cv::Vec3b C;
#elif (IM_TYPE == CV_16SC3)
typedef short G;
typedef Vec3s C;
#elif (IM_TYPE == CV_32SC3)
typedef int G;
typedef Vec3i C;
#elif (IM_TYPE == CV_32FC3)
typedef float G;
typedef Vec3f C;
#elif (IM_TYPE == CV_64FC3)
typedef double G;
typedef Vec3d C;
#endif

Mat gaussianfilter_sep(const Mat input, int n, float sigmaT, float sigmaS, const char* opt);

int main() {
	
	Mat input = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input_gray;
	Mat output;


	cvtColor(input, input_gray, CV_BGR2GRAY); 

	

	if (!input.data)
	{
		std::cout << "Could not open" << std::endl;
		return -1;
	}

	namedWindow("Grayscale", WINDOW_AUTOSIZE);
	imshow("Grayscale", input_gray);

	std::chrono::system_clock::time_point StartTime = std::chrono::system_clock::now();	// 함수 시작 전, 현재 시각 가져오기

	output = gaussianfilter_sep(input_gray, 5, 1, 1, "zero-paddle"); //Boundary process: zero-paddle, mirroring, adjustkernel

	std::chrono::system_clock::time_point EndTime = std::chrono::system_clock::now();	// 함수 끝난 후, 현재 시각 가져오기
	
	std::chrono::duration<double> DefaultSec = EndTime - StartTime;						// 함수 실행하는데 걸린 시간
	std::cout << "gaussianfilter_sep() 함수를 수행하는 걸린 시간 : " << DefaultSec.count() << " sec" << std::endl;

	namedWindow("Gaussian Filter", WINDOW_AUTOSIZE);
	imshow("Gaussian Filter", output);


	waitKey(0);

	return 0;
}


Mat gaussianfilter_sep(const Mat input, int n, float sigmaT, float sigmaS, const char* opt) {

	Mat kernel_s;
	Mat kernel_t;
	
	int row = input.rows;
	int col = input.cols;
	int kernel_size = (2 * n + 1);
	int tempa;
	int tempb;
	float denom_s, denom_t;

 // Initialiazing Kernel Matrix 
	kernel_s = Mat::zeros(kernel_size, 1, CV_32F);
	kernel_t = Mat::zeros(1, kernel_size, CV_32F);

	denom_s = 0.0;
	denom_t = 0.0;


	for (int a = -n; a <= n; a++) {  // numerator in w(s)
		float value_s = exp(-(pow(a, 2) / (2 * pow(sigmaS, 2))));
		kernel_s.at<float>(a + n, 0) = value_s;
		denom_s += value_s;
	}

	for (int b = -n; b <= n; b++) {	 // numerator in w(t)
		float value_t = exp(-pow(b, 2) / (2 * pow(sigmaT, 2)));
		kernel_t.at<float>(0, b + n) = value_t;
		denom_t += value_t;
	}

	for (int a = -n; a <= n; a++) {  // Denominator in w(s)
		kernel_s.at<float>(a + n, 0) /= denom_s;
	}

	for (int b = -n; b <= n; b++) {	 // Denominator in w(t)
		kernel_t.at<float>(0, b + n) /= denom_t;
	}



	Mat output = Mat::zeros(row, col, input.type());
	
	
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {

			if (!strcmp(opt, "zero-paddle")) {
				float sum2 = 0.0;
				for (int a = -n; a <= n; a++) {
					float sum1 = 0.0;
					for (int b = -n; b <= n; b++) {
						if ((i + a <= row - 1) && (i + a >= 0) && (j + b <= col - 1) && (j + b >= 0)) { //if the pixel is not a border pixel
							sum1 += kernel_t.at<float>(0, b + n) * (float)(input.at<G>(i + a, j + b));
						}
					}
					if ((i + a <= row - 1) && (i + a >= 0)) { //if the pixel is not a border pixel
						sum2 += kernel_s.at<float>(a + n, 0) * sum1;
					}
				}
				output.at<G>(i, j) = (G)sum2;
			}
			
			else if (!strcmp(opt, "mirroring")) {
				float sum2 = 0.0;
				for (int a = -n; a <= n; a++) {
					float sum1 = 0.0;
					for (int b = -n; b <= n; b++) {
						if (i + a > row - 1) {  //mirroring for the border pixels
							tempa = i - a;
						}
						else if (i + a < 0) {
							tempa = -(i + a);
						}
						else {
							tempa = i + a;
						}
						if (j + b > col - 1) {
							tempb = j - b;
						}
						else if (j + b < 0) {
							tempb = -(j + b);
						}
						else {
							tempb = j + b;
						}

						sum1 += kernel_t.at<float>(0, b + n) * (float)(input.at<G>(tempa, tempb));
					}
					sum2 += kernel_s.at<float>(a + n, 0) * sum1;
				}
				output.at<G>(i, j) = (G)sum2;
			}


			else if (!strcmp(opt, "adjustkernel")) {
				float sum2 = 0.0;
				float denom = 0.0;
				int count = 0;
				for (int a = -n; a <= n; a++) {
					float sum1 = 0.0;
					for (int b = -n; b <= n; b++) {
						if ((i + a <= row - 1) && (i + a >= 0) && (j + b <= col - 1) && (j + b >= 0)) {
							sum1 += kernel_t.at<float>(0, b + n) * (float)(input.at<G>(i + a, j + b));
							denom += kernel_t.at<float>(0, b + n) * kernel_s.at<float>(a + n, 0);
						}
					}
					if ((i + a <= row - 1) && (i + a >= 0)) { //if the pixel is not a border pixel
						sum2 += kernel_s.at<float>(a + n, 0) * sum1;
						}
				}
				output.at<G>(i, j) = (G)(sum2/denom);
			}
		}
	}
	return output;
}