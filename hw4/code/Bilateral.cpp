#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <math.h>

#define IM_TYPE	CV_64FC3

using namespace cv;

Mat Add_Gaussian_noise(const Mat input, double mean, double sigma);
Mat Bilateralfilter_Gray(const Mat input, int n, double sigma_t, double sigma_s, double sigma_r, const char* opt);
Mat Bilateralfilter_RGB(const Mat input, int n, double sigma_t, double sigma_s, double sigma_r, const char* opt);

int main() {

	Mat input = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input_gray;

	// check for validation
	if (!input.data) {
		printf("Could not open\n");
		return -1;
	}

	cvtColor(input, input_gray, CV_RGB2GRAY);	// convert RGB to Grayscale

	// 8-bit unsigned char -> 64-bit floating point
	input.convertTo(input, CV_64FC3, 1.0 / 255);
	input_gray.convertTo(input_gray, CV_64F, 1.0 / 255);

	// Add noise to original image
	Mat noise_Gray = Add_Gaussian_noise(input_gray, 0, 0.1);
	Mat noise_RGB = Add_Gaussian_noise(input, 0, 0.1);

	// Denoise, using bilateral filter
	Mat Denoised_Gray = Bilateralfilter_Gray(noise_Gray, 2, 10, 10, 10, "zero-padding");
	Mat Denoised_RGB = Bilateralfilter_RGB(noise_RGB, 2, 10, 10, 10, "zero-padding");

	namedWindow("Grayscale", WINDOW_AUTOSIZE);
	imshow("Grayscale", input_gray);

	namedWindow("RGB", WINDOW_AUTOSIZE);
	imshow("RGB", input);

	namedWindow("Gaussian Noise (Grayscale)", WINDOW_AUTOSIZE);
	imshow("Gaussian Noise (Grayscale)", noise_Gray);

	namedWindow("Gaussian Noise (RGB)", WINDOW_AUTOSIZE);
	imshow("Gaussian Noise (RGB)", noise_RGB);

	namedWindow("Denoised - Bilateral (Grayscale)", WINDOW_AUTOSIZE);
	imshow("Denoised - Bilateral (Grayscale)", Denoised_Gray);

	namedWindow("Denoised - Bilateral (RGB)", WINDOW_AUTOSIZE);
	imshow("Denoised - Bilateral (RGB)", Denoised_RGB);

	waitKey(0);

	return 0;
}

Mat Add_Gaussian_noise(const Mat input, double mean, double sigma) {

	Mat NoiseArr = Mat::zeros(input.rows, input.cols, input.type());
	RNG rng;
	rng.fill(NoiseArr, RNG::NORMAL, mean, sigma);

	add(input, NoiseArr, NoiseArr);

	return NoiseArr;
}

Mat Bilateralfilter_Gray(const Mat input, int n, double sigma_t, double sigma_s, double sigma_r, const char* opt) {

	Mat kernel;

	int row = input.rows;
	int col = input.cols;
	int kernel_size = (2 * n + 1);

	int tempa;
	int tempb;

	// Initialiazing Bilateralfilter Kernel Matrix
	kernel = Mat::zeros(kernel_size, kernel_size, CV_64F);

	Mat output = Mat::zeros(row, col, input.type());

	// convolution
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {

			if (!strcmp(opt, "zero-padding")) {
				double sum1 = 0.0;
				double denom = 0.0;
				double value1 = 0.0;
				double value2 = 0.0;
				for (int x = -n; x <= n; x++) { // for each kernel window
					for (int y = -n; y <= n; y++) {

						value1 = exp(-(pow(x, 2) / (2 * pow(sigma_s, 2))) - (pow(y, 2) / (2 * pow(sigma_t, 2))));

						if ((i + x <= row - 1) && (i + x >= 0) && (j + y <= col - 1) && (j + y >= 0)) { //if the pixel is not a border pixel
							value2 = exp(-(pow(input.at<double>(i, j) - input.at<double>(i + x, j + y), 2) / (2 * pow(sigma_r, 2))));
							kernel.at<double>(x + n, y + n) = value1 * value2;

							sum1 += kernel.at<double>(x + n, y + n) * input.at<double>(i + x, j + y);
						}

						else {
							value2 = exp(-pow(input.at<double>(i, j) - 0, 2) / (2 * pow(sigma_r, 2)));
							kernel.at<double>(x + n, y + n) = value1 * value2;
						}

						denom += value1 * value2;
					}
				}
				sum1 = sum1 / denom;
				output.at<double>(i, j) = sum1;
			}

			else if (!strcmp(opt, "mirroring")) {
				double sum1 = 0.0;
				double denom = 0.0;
				double value1 = 0.0;
				double value2 = 0.0;
				for (int x = -n; x <= n; x++) { // for each kernel window
					for (int y = -n; y <= n; y++) {
						if (i + x > row - 1) {  //mirroring for the border pixels
							tempa = i - x;
						}
						else if (i + x < 0) {
							tempa = -(i + x);
						}
						else {
							tempa = i + x;
						}
						if (j + y > col - 1) {
							tempb = j - y;
						}
						else if (j + y < 0) {
							tempb = -(j + y);
						}
						else {
							tempb = j + y;
						}
						value1 = exp(-(pow(x, 2) / (2 * pow(sigma_s, 2))) - (pow(y, 2) / (2 * pow(sigma_t, 2))));
						value2 = exp(-(pow(input.at<double>(i, j) - input.at<double>(tempa, tempb), 2) / (2 * pow(sigma_r, 2))));
						kernel.at<double>(x + n, y + n) = value1 * value2;

						sum1 += kernel.at<double>(x + n, y + n) * input.at<double>(tempa, tempb);

						denom += value1 * value2;
					}
				}
				sum1 = sum1 / denom;
				output.at<double>(i, j) = sum1;
			}

			else if (!strcmp(opt, "adjustkernel")) {
				double sum1 = 0.0;
				double sum2 = 0.0;
				double denom = 0.0;
				double value1 = 0.0;
				double value2 = 0.0;
				for (int x = -n; x <= n; x++) { // for each kernel window
					for (int y = -n; y <= n; y++) {
						if ((i + x <= row - 1) && (i + x >= 0) && (j + y <= col - 1) && (j + y >= 0)) {
							value1 = exp(-(pow(x, 2) / (2 * pow(sigma_s, 2))) - (pow(y, 2) / (2 * pow(sigma_t, 2))));
							value2 = exp(-(pow(input.at<double>(i, j) - input.at<double>(i + x, j + y), 2) / (2 * pow(sigma_r, 2))));
							kernel.at<double>(x + n, y + n) = value1 * value2;

							sum1 += kernel.at<double>(x + n, y + n) * input.at<double>(i + x, j + y);
							sum2 += kernel.at<double>(x + n, y + n);
							denom += value1 * value2;
						}
					}
				}
				sum1 = (double) (sum1 / denom);
				sum2 = (double)(sum2 / denom);
				output.at<double>(i, j) = (double)(sum1 / sum2);
			}

		}
	}
	return output;
}

Mat Bilateralfilter_RGB(const Mat input, int n, double sigma_t, double sigma_s, double sigma_r, const char* opt) {

	Mat kernel;

	int row = input.rows;
	int col = input.cols;
	int kernel_size = (2 * n + 1);

	int tempa;
	int tempb;

	// Initialiazing Kernel Matrix 
	kernel = Mat::zeros(kernel_size, kernel_size, CV_64F);

	Mat output = Mat::zeros(row, col, input.type());

	// convolution
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {

			if (!strcmp(opt, "zero-padding")) {
				double sum1_b = 0.0;
				double sum1_g = 0.0;
				double sum1_r = 0.0;

				double denom = 0.0;
				double value1 = 0.0;
				double value2_b, value2_g, value2_r, value2 = 0.0;
				for (int x = -n; x <= n; x++) { // for each kernel window
					for (int y = -n; y <= n; y++) {
						value1 = exp(-(pow(x, 2) / (2 * pow(sigma_s, 2))) - (pow(y, 2) / (2 * pow(sigma_t, 2))));

						if ((i + x <= row - 1) && (i + x >= 0) && (j + y <= col - 1) && (j + y >= 0)) { //if the pixel is not a border pixel
							value2_b = exp(-pow(input.at<Vec3d>(i, j)[0] - input.at<Vec3d>(i + x, j + y)[0], 2) / (2 * pow(sigma_r, 2)));
							value2_g = exp(-pow(input.at<Vec3d>(i, j)[1] - input.at<Vec3d>(i + x, j + y)[1], 2) / (2 * pow(sigma_r, 2)));
							value2_r = exp(-pow(input.at<Vec3d>(i, j)[2] - input.at<Vec3d>(i + x, j + y)[2], 2) / (2 * pow(sigma_r, 2)));
							value2 = value2_b + value2_g + value2_r;

							kernel.at<double>(x + n, y + n) = value1 * value2;

							sum1_b += kernel.at<double>(x + n, y + n) * input.at<Vec3d>(i + x, j + y)[0];
							sum1_g += kernel.at<double>(x + n, y + n) * input.at<Vec3d>(i + x, j + y)[1];
							sum1_r += kernel.at<double>(x + n, y + n) * input.at<Vec3d>(i + x, j + y)[2];

						}
						else {
							value2_b = exp(-(pow(input.at<Vec3d>(i, j)[0], 2) / (2 * pow(sigma_r, 2))));
							value2_g = exp(-(pow(input.at<Vec3d>(i, j)[1], 2) / (2 * pow(sigma_r, 2))));
							value2_r = exp(-(pow(input.at<Vec3d>(i, j)[2], 2) / (2 * pow(sigma_r, 2))));
							value2 = value2_b + value2_g + value2_r;

							kernel.at<double>(x + n, y + n) = value1 * value2;
						}

						denom += value1 * value2;
					}
				}
				sum1_b = sum1_b / denom;
				sum1_g = sum1_g / denom;
				sum1_r = sum1_r / denom;

				output.at<Vec3d>(i, j)[0] = sum1_b;
				output.at<Vec3d>(i, j)[1] = sum1_g;
				output.at<Vec3d>(i, j)[2] = sum1_r;
			}

			else if (!strcmp(opt, "mirroring")) {
				double sum1_b = 0.0;
				double sum1_g = 0.0;
				double sum1_r = 0.0;

				double denom = 0.0;
				double value1 = 0.0;
				double value2_b, value2_g, value2_r, value2 = 0.0;
				for (int x = -n; x <= n; x++) { // for each kernel window
					for (int y = -n; y <= n; y++) {
						if (i + x > row - 1) {  //mirroring for the border pixels
							tempa = i - x;
						}
						else if (i + x < 0) {
							tempa = -(i + x);
						}
						else {
							tempa = i + x;
						}
						if (j + y > col - 1) {
							tempb = j - y;
						}
						else if (j + y < 0) {
							tempb = -(j + y);
						}
						else {
							tempb = j + y;
						}
						value1 = exp(-(pow(x, 2) / (2 * pow(sigma_s, 2))) - (pow(y, 2) / (2 * pow(sigma_t, 2))));
						value2_b = exp(-pow(input.at<Vec3d>(i, j)[0] - input.at<Vec3d>(tempa, tempb)[0], 2) / (2 * pow(sigma_r, 2)));
						value2_g = exp(-pow(input.at<Vec3d>(i, j)[1] - input.at<Vec3d>(tempa, tempb)[1], 2) / (2 * pow(sigma_r, 2)));
						value2_r = exp(-pow(input.at<Vec3d>(i, j)[2] - input.at<Vec3d>(tempa, tempb)[2], 2) / (2 * pow(sigma_r, 2)));
						value2 = value2_b + value2_g + value2_r;

						kernel.at<double>(x + n, y + n) = value1 * value2;

						sum1_b += kernel.at<double>(x + n, y + n) * input.at<Vec3d>(tempa, tempb)[0];
						sum1_g += kernel.at<double>(x + n, y + n) * input.at<Vec3d>(tempa, tempb)[1];
						sum1_r += kernel.at<double>(x + n, y + n) * input.at<Vec3d>(tempa, tempb)[2];

						denom += value1 * value2;
					}
				}
				sum1_b = sum1_b / denom;
				sum1_g = sum1_g / denom;
				sum1_r = sum1_r / denom;

				output.at<Vec3d>(i, j)[0] = sum1_b;
				output.at<Vec3d>(i, j)[1] = sum1_g;
				output.at<Vec3d>(i, j)[2] = sum1_r;
			}

			else if (!strcmp(opt, "adjustkernel")) {
				double sum1_b = 0.0;
				double sum1_g = 0.0;
				double sum1_r = 0.0;

				double sum2= 0.0;
				double denom = 0.0;
				double value1 = 0.0;
				double value2_b, value2_g, value2_r, value2 = 0.0;
				for (int x = -n; x <= n; x++) { // for each kernel window
					for (int y = -n; y <= n; y++) {
						if ((i + x <= row - 1) && (i + x >= 0) && (j + y <= col - 1) && (j + y >= 0)) {
							value1 = exp(-(pow(x, 2) / (2 * pow(sigma_s, 2))) - (pow(y, 2) / (2 * pow(sigma_t, 2))));
							value2_b = exp(-pow(input.at<Vec3d>(i, j)[0] - input.at<Vec3d>(i + x, j + y)[0], 2) / (2 * pow(sigma_r, 2)));
							value2_g = exp(-pow(input.at<Vec3d>(i, j)[1] - input.at<Vec3d>(i + x, j + y)[1], 2) / (2 * pow(sigma_r, 2)));
							value2_r = exp(-pow(input.at<Vec3d>(i, j)[2] - input.at<Vec3d>(i + x, j + y)[2], 2) / (2 * pow(sigma_r, 2)));
							value2 = value2_b + value2_g + value2_r;

							kernel.at<double>(x + n, y + n) = value1 * value2;

							sum1_b += kernel.at<double>(x + n, y + n) * input.at<Vec3d>(i + x, j + y)[0];
							sum1_g += kernel.at<double>(x + n, y + n) * input.at<Vec3d>(i + x, j + y)[1];
							sum1_r += kernel.at<double>(x + n, y + n) * input.at<Vec3d>(i + x, j + y)[2];

							sum2 += kernel.at<double>(x + n, y + n);

							denom += value1 * value2;

						}
					}
				}
				sum1_b = sum1_b / denom;
				sum1_g = sum1_g / denom;
				sum1_r = sum1_r / denom;

				sum2 = sum2/ denom;


				output.at<Vec3d>(i, j)[0] = (double)(sum1_b / sum2);
				output.at<Vec3d>(i, j)[1] = (double)(sum1_g / sum2);
				output.at<Vec3d>(i, j)[2] = (double)(sum1_r / sum2);
			}
		}
	}

	return output;
}