#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

template <typename T>
Mat myrotate(const Mat input, float angle, const char* opt);

int main()
{
	Mat input, rotated;

	// Read each image
	input = imread("lena.jpg");

	
	// Check for invalid input
	if (!input.data) {
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	// original image
	namedWindow("image");

	imshow("image", input);
	rotated = myrotate<Vec3b>(input, 45, "nearest");

	// rotated image
	namedWindow("rotated");
	imshow("rotated", rotated);
	waitKey(0);


	return 0;

}

template <typename T>
Mat myrotate(const Mat input, float angle, const char* opt) {
	int row = input.rows;
	int col = input.cols;

	float radian = angle * CV_PI / 180;

	float sq_row = ceil(row * cos(radian) + col * sin(radian));
	float sq_col = ceil(col * cos(radian) + row * sin(radian));
	// float sq_row = ceil(row * sin(radian) + col * cos(radian));
	// float sq_col = ceil(col * sin(radian) + row * cos(radian));


	Mat output = Mat::zeros(sq_row, sq_col, input.type());


	for (int i = 0; i < sq_row; i++) {
		for (int j = 0; j < sq_col; j++) {
			float x = (j - sq_col / 2) * cos(radian) - (i - sq_row / 2) * sin(radian) + col / 2;
			float y = (j - sq_col / 2) * sin(radian) + (i - sq_row / 2) * cos(radian) + row / 2;

			if ((y >= 0) && (y <= (row - 1)) && (x >= 0) && (x <= (col - 1))) {
				if (!strcmp(opt, "nearest")) {
					int int_x = round(x);
					int int_y = round(y);
					output.at<Vec3b>(i, j) = input.at<Vec3b>(int_y, int_x);
				}
				else if (!strcmp(opt, "bilinear")) {
					float mu = x - floor(x);
					float lambda = y - floor(y);
					Vec3b P1 = input.at<Vec3b>(floor(y), floor(x));
					Vec3b P2 = input.at<Vec3b>(floor(y), ceil(x));
					Vec3b P3 = input.at<Vec3b>(ceil(y), floor(x));
					Vec3b P4 = input.at<Vec3b>(ceil(y), ceil(x));
					
					Vec3b R1 = mu * P2 + (1 - mu) * P1;
					Vec3b R2 = mu * P4 + (1 - mu) * P3;

					Vec3b result = lambda * R2 + (1 - lambda) * R1;
					output.at<Vec3b>(i, j) = result;

				}
			}
		}
	}

	return output;
}