#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>       /* exp */
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

Mat sobelfilter(const Mat input);

int main() {

	Mat input = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
	Mat output;

	if (!input.data)
	{
		std::cout << "Could not open" << std::endl;
		return -1;
	}

	namedWindow("Original_BGR", WINDOW_AUTOSIZE);
	imshow("Original_BGR", input);
	output = sobelfilter(input); //Boundary process: fixed with 'mirroring'

	namedWindow("Sobel Filter", WINDOW_AUTOSIZE);
	imshow("Sobel Filter", output);


	waitKey(0);

	return 0;
}


Mat sobelfilter(const Mat input) {

	Mat kernel;

	int row = input.rows;
	int col = input.cols;
	int n = 1; // Sobel Filter Kernel N
	int tempa;
	int tempb;

	// Initialiazing 2 Kernel Matrix with 3x3 size for Sx and Sy
	Mat Sx = (Mat_<float>(3, 3)<<-1, 0, 1, -2, 0, 2, -1, 0, 1);
	Mat Sy = (Mat_<float>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);

	Mat output = Mat::zeros(row, col, input.type());


	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			float sum1_b = 0.0;
			float sum1_g = 0.0;
			float sum1_r = 0.0;
			float sum2_b = 0.0;
			float sum2_g = 0.0;
			float sum2_r = 0.0;

			for (int a = -n; a <= n; a++) {
				for (int b = -n; b <= n; b++) {
					// Use mirroring boundary process
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

					// computing Ix for each channel BGR
					sum1_b += Sx.at<float>(a + n, b + n) * (float)(input.at<C>(tempa, tempb)[0]);	
					sum1_g += Sx.at<float>(a + n, b + n) * (float)(input.at<C>(tempa, tempb)[1]);
					sum2_r += Sx.at<float>(a + n, b + n) * (float)(input.at<C>(tempa, tempb)[2]);

					sum2_b += Sy.at<float>(a + n, b + n) * (float)(input.at<C>(tempa, tempb)[0]);
					sum2_g += Sy.at<float>(a + n, b + n) * (float)(input.at<C>(tempa, tempb)[1]);
					sum2_r += Sy.at<float>(a + n, b + n) * (float)(input.at<C>(tempa, tempb)[2]);
				}  
			}
			// Find output M(x,y) = sqrt( input.at<G>(x, y)*Sx + input.at<G>(x, y)*Sy )
			double temp = (sqrt(pow(sum1_b, 2.0) + pow(sum2_b, 2.0)) + (G)sqrt(pow(sum1_g, 2.0) + pow(sum2_g, 2.0)) + (G)sqrt(pow(sum1_r, 2.0) + pow(sum2_r, 2.0))) / 3.0;
			output.at<C>(i, j)[0] = (G)temp;
			output.at<C>(i, j)[1] = (G)temp;
			output.at<C>(i, j)[2] = (G)temp;
		}
	}
	return output;
}