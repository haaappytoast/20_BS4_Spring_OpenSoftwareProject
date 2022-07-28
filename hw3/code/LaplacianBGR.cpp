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

Mat laplacianfilter(const Mat input);

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

	output = laplacianfilter(input); //Boundary process: fixed with 'mirroring'

	namedWindow("Laplacian Filter", WINDOW_AUTOSIZE);
	imshow("Laplacian Filter", output);


	waitKey(0);

	return 0;
}


Mat laplacianfilter(const Mat input) {


	int row = input.rows;
	int col = input.cols;
	int n = 1; // Laplacian Filter Kernel N
	int tempa;
	int tempb;

	// Initialiazing 1 Kernel Matrix with 3x3 size
	Mat kernel = (Mat_<double>(3, 3) << 0, 1, 0, 1, -4, 1, 0, 1, 0);

	Mat output = Mat::zeros(row, col, input.type());

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			double sum1_b = 0.0;
			double sum1_g = 0.0;
			double sum1_r = 0.0;
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

					sum1_b += kernel.at<double>(a + n, b + n) * (double)(input.at<C>(tempa, tempb)[0]);	//blue channel
					sum1_g += kernel.at<double>(a + n, b + n) * (double)(input.at<C>(tempa, tempb)[1]);	//green channel
					sum1_r += kernel.at<double>(a + n, b + n) * (double)(input.at<C>(tempa, tempb)[2]);	//red channel
				}  
			}

			double temp = (sum1_b + sum1_g + sum1_r) / 3.0;
			output.at<C>(i, j)[0] = (G)abs(temp);
			output.at<C>(i, j)[1] = (G)abs(temp);
			output.at<C>(i, j)[2] = (G)abs(temp);
		}
	}
	return output;
}