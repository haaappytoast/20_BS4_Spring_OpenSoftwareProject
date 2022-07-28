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
	Mat output;

	

	if (!input.data)
	{
		std::cout << "Could not open" << std::endl;
		return -1;
	}

	namedWindow("Original", WINDOW_AUTOSIZE);
	imshow("Original", input);

	std::chrono::system_clock::time_point StartTime = std::chrono::system_clock::now();	// 함수 시작 전, 현재 시각 가져오기

	output = gaussianfilter_sep(input, 5, 5, 5, "adjustkernel"); //Boundary process: zero-paddle, mirroring, adjustkernel

	std::chrono::system_clock::time_point EndTime = std::chrono::system_clock::now();	// 함수 끝난 후, 현재 시각 가져오기
	
	std::chrono::duration<double> DefaultSec = EndTime - StartTime;						// 함수 실행하는데 걸린 시간
	std::cout << "gaussianfilter_sep() 함수를 수행하는 걸린 시간 : " << DefaultSec.count() << " sec" << std::endl;

	namedWindow("Gaussian Filter_sep", WINDOW_AUTOSIZE);
	imshow("Gaussian Filter_sep", output);


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
				float sum2_b = 0.0;
				float sum2_g = 0.0;
				float sum2_r = 0.0;
				for (int a = -n; a <= n; a++) {
					float sum1_b = 0.0;
					float sum1_g = 0.0;
					float sum1_r = 0.0;
					for (int b = -n; b <= n; b++) {
						if ((i + a <= row - 1) && (i + a >= 0) && (j + b <= col - 1) && (j + b >= 0)) { //if the pixel is not a border pixel
							sum1_b += kernel_t.at<float>(0, b + n) * (float)(input.at<C>(i + a, j + b)[0]);
							sum1_g += kernel_t.at<float>(0, b + n) * (float)(input.at<C>(i + a, j + b)[1]);
							sum1_r += kernel_t.at<float>(0, b + n) * (float)(input.at<C>(i + a, j + b)[2]);
						}
					}
					if ((i + a <= row - 1) && (i + a >= 0)) { //if the pixel is not a border pixel
						sum2_b += kernel_s.at<float>(a + n, 0) * sum1_b;
						sum2_g += kernel_s.at<float>(a + n, 0) * sum1_g;
						sum2_r += kernel_s.at<float>(a + n, 0) * sum1_r;
					}
				}

				output.at<C>(i, j)[0] = (G)sum2_b;
				output.at<C>(i, j)[1] = (G)sum2_g;
				output.at<C>(i, j)[2] = (G)sum2_r;
			}
			
			else if (!strcmp(opt, "mirroring")) {
				float sum2_b = 0.0;
				float sum2_g = 0.0;
				float sum2_r = 0.0;
				for (int a = -n; a <= n; a++) {
					float sum1_b = 0.0;
					float sum1_g = 0.0;
					float sum1_r = 0.0;
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
						sum1_b += kernel_t.at<float>(0, b + n) * (float)(input.at<C>(tempa, tempb)[0]);
						sum1_g += kernel_t.at<float>(0, b + n) * (float)(input.at<C>(tempa, tempb)[1]);
						sum1_r += kernel_t.at<float>(0, b + n) * (float)(input.at<C>(tempa, tempb)[2]);
					}
					sum2_b += kernel_s.at<float>(a + n, 0) * sum1_b;
					sum2_g += kernel_s.at<float>(a + n, 0) * sum1_g;
					sum2_r += kernel_s.at<float>(a + n, 0) * sum1_r;
				}
				output.at<C>(i, j)[0] = (G)sum2_b;
				output.at<C>(i, j)[1] = (G)sum2_g;
				output.at<C>(i, j)[2] = (G)sum2_r;
			}


			else if (!strcmp(opt, "adjustkernel")) {
				float sum2_b = 0.0;
				float sum2_g = 0.0;
				float sum2_r = 0.0;
				float denom = 0.0;

				for (int a = -n; a <= n; a++) {
					float sum1_b = 0.0;
					float sum1_g = 0.0;
					float sum1_r = 0.0;
					for (int b = -n; b <= n; b++) {
						if ((i + a <= row - 1) && (i + a >= 0) && (j + b <= col - 1) && (j + b >= 0)) {
							sum1_b += kernel_t.at<float>(0, b + n) * (float)(input.at<C>(i + a, j + b)[0]);
							sum1_g += kernel_t.at<float>(0, b + n) * (float)(input.at<C>(i + a, j + b)[1]);
							sum1_r += kernel_t.at<float>(0, b + n) * (float)(input.at<C>(i + a, j + b)[2]);
							denom += kernel_t.at<float>(0, b + n) * kernel_s.at<float>(a + n, 0);
						}
					}
					if ((i + a <= row - 1) && (i + a >= 0)) { //if the pixel is not a border pixel
						sum2_b += kernel_s.at<float>(a + n, 0) * sum1_b;
						sum2_g += kernel_s.at<float>(a + n, 0) * sum1_g;
						sum2_r += kernel_s.at<float>(a + n, 0) * sum1_r;
					}
				}
				output.at<C>(i, j)[0] = (G)(sum2_b / denom);
				output.at<C>(i, j)[1] = (G)(sum2_g / denom);
				output.at<C>(i, j)[2] = (G)(sum2_r / denom);
			}
		}
	}
	return output;
}