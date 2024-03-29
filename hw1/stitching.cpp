#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

template <typename T>
Mat cal_affine(int ptl_x[], int ptl_y[], int ptr_x[], int ptr_y[], int number_of_points);

void blend_stitching(const Mat I1, const Mat I2, Mat& I_f, int diff_x, int diff_y, float alpha);

int main() {
	Mat I1, I2;

	// Read each image
	I1 = imread("stitchingL.jpg");
	I2 = imread("stitchingR.jpg");

	I1.convertTo(I1, CV_32FC3, 1.0 / 255);
	I2.convertTo(I2, CV_32FC3, 1.0 / 255);

	// corresponding pixels
	/*int ptl_x[6] = { 528, 505, 500, 482, 530, 645 };
	int ptl_y[6] = { 509, 686, 768, 846, 917, 968 };
	int ptr_x[6] = { 488, 469, 467, 452, 500, 609 };
	int ptr_y[6] = { 45, 234, 314, 392, 456, 493 };*/

	int ptl_x[28] = { 528,597,581,520,526,581,587,496,506,500,342,558,499,642,474,456,451,475,530,381,472,475,426,539,329,341,492,511 };
	int ptl_y[28] = { 509,558,605,649,680,689,705,730,734,768,795,802,818,837,877,889,894,902,917,924,930,948,964,969,980,988,994,998 };
	int ptr_x[28] = { 488,561,544,482,490,546,552,462,471,467,313,526,468,607,445,429,424,447,500,358,446,449,403,510,312,324,466,484 };
	int ptr_y[28] = { 45,89,142,194,226,230,246,279,281,314,352,345,365,372,421,434,439,446,456,472,471,488,506,503,527,532,528,531 };


	// Check for invalid input
	if (!I1.data || !I2.data) {
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	// height(row), width(col) of each image
	const float I1_row = I1.rows;
	const float I1_col = I1.cols;
	const float I2_row = I2.rows;
	const float I2_col = I2.cols;

	// calculate affine Matrix A12, A21
	Mat A12 = cal_affine<float>(ptl_x, ptl_y, ptr_x, ptr_y, 28);
	Mat A21 = cal_affine<float>(ptr_x, ptr_y, ptl_x, ptl_y, 28);

	//Point2f p1 = (p1.x,p1.y)
	Point2f p1(A21.at<float>(0) * 0 + A21.at<float>(1) * 0 + A21.at<float>(2),
		A21.at<float>(3) * 0 + A21.at<float>(4) * 0 + A21.at<float>(5));

	Point2f p2(A21.at<float>(0) * 0 + A21.at<float>(1) * I2_col + A21.at<float>(2),
		A21.at<float>(3) * 0 + A21.at<float>(4) * I2_col + A21.at<float>(5));

	Point2f p3(A21.at<float>(0) * I2_row + A21.at<float>(1) * 0 + A21.at<float>(2),
		A21.at<float>(3) * I2_row + A21.at<float>(4) * 0 + A21.at<float>(5));

	Point2f p4(A21.at<float>(0) * I2_row + A21.at<float>(1) * I2_col + A21.at<float>(2),
		A21.at<float>(3) * I2_row + A21.at<float>(4) * I2_col + A21.at<float>(5));

	// for inverse warping
	Point2f p1_(A12.at<float>(0) * 0 + A12.at<float>(1) * 0 + A12.at<float>(2),
		A12.at<float>(3) * 0 + A12.at<float>(4) * 0 + A12.at<float>(5));

	Point2f p2_(A12.at<float>(0) * 0 + A12.at<float>(1) * I1_col + A12.at<float>(2),
		A12.at<float>(3) * 0 + A12.at<float>(4) * I1_col + A12.at<float>(5));

	Point2f p3_(A12.at<float>(0) * I1_row + A12.at<float>(1) * 0 + A12.at<float>(2),
		A12.at<float>(3) * I1_row + A12.at<float>(4) * 0 + A12.at<float>(5));

	Point2f p4_(A12.at<float>(0) * I1_row + A12.at<float>(1) * I1_col + A12.at<float>(2),
		A12.at<float>(3) * I1_row + A12.at<float>(4) * I1_col + A12.at<float>(5));

	// compute boundary for merged image(I_f)
	int bound_u = (int)round(min(0.0f, min(p1.x, p2.x)));
	int bound_b = (int)round(std::max(I1_row, std::max(p3.x, p4.x)));
	int bound_l = (int)round(min(0.0f, min(p1.y, p3.y)));
	int bound_r = (int)round(std::max(I1_col, std::max(p2.y, p4.y)));

	// compute boundary for inverse warping
	int bound_u_ = (int)round(min(0.0f, min(p1_.x, p2_.x)));
	int bound_b_ = (int)round(std::max(I2_row, std::max(p3_.x, p4_.x)));
	int bound_l_ = (int)round(min(0.0f, min(p1_.y, p3_.y)));
	int bound_r_ = (int)round(std::max(I2_col, std::max(p2_.y, p4_.y)));

	int diff_x = abs(bound_u);
	int diff_y = abs(bound_l);

	int diff_x_ = abs(bound_u_);
	int diff_y_ = abs(bound_l_);

	// initialize merged image
	Mat I_f(bound_b - bound_u + 1, bound_r - bound_l + 1, CV_32FC3, Scalar(0));


	// inverse warping with bilinear interpolation
	for (int i = -diff_x_; i < I_f.rows - diff_x_; i++) {

		for (int j = -diff_y_; j < I_f.cols - diff_y_; j++) {

			float x = A12.at<float>(0) * i + A12.at<float>(1) * j + A12.at<float>(2) + diff_x_;
			float y = A12.at<float>(3) * i + A12.at<float>(4) * j + A12.at<float>(5) + diff_y_;

			float y1 = floor(y);
			float y2 = ceil(y);
			float x1 = floor(x);
			float x2 = ceil(x);

			float mu = y - y1;
			float lambda = x - x1;
			if (x1 >= 0 && x2 < I2_row && y1 >= 0 && y2 < I2_col) {
				Vec3f P1 = I2.at<Vec3f>(x1, y1);
				Vec3f P2 = I2.at<Vec3f>(x2, y2);
				Vec3f P3 = I2.at<Vec3f>(x1, y2);
				Vec3f P4 = I2.at<Vec3f>(x2, y2);

				Vec3f R1 = lambda * P2 + (1 - lambda) * P1;
				Vec3f R2 = lambda * P4 + (1 - lambda) * P3;

				Vec3f result = mu * R2 + (1 - mu) * R1;

				I_f.at<Vec3f>(i + diff_x_, j + diff_y_) = result;

			}
		}
	}

	// image stitching with blend
	blend_stitching(I1, I2, I_f, diff_x, diff_y, 0.5);

	namedWindow("Left Image");
	imshow("Left Image", I1);

	namedWindow("Right Image");
	imshow("Right Image", I2);

	namedWindow("result");
	imshow("result", I_f);

	waitKey(0);

	return 0;
}

template <typename T>
Mat cal_affine(int ptl_x[], int ptl_y[], int ptr_x[], int ptr_y[], int number_of_points) {

	Mat M(2 * number_of_points, 6, CV_32F, Scalar(0));
	Mat b(2 * number_of_points, 1, CV_32F);

	Mat M_trans, temp, affineM;

	// initialize matrix
	for (int i = 0; i < number_of_points; i++) {
		//initialize M
		Mat row1 = *(Mat_<int>(1, 6) << ptl_x[i], ptl_y[i], 1, 0, 0, 0);
		Mat row2 = *(Mat_<int>(1, 6) << 0, 0, 0, ptl_x[i], ptl_y[i], 1);
		row1.copyTo(M.row(2 * i));
		row2.copyTo(M.row(2 * i + 1));

		//initialize b
		b.at<float>(2 * i, 0) = float(ptr_x[i]);
		b.at<float>(2 * i + 1, 0) = float(ptr_y[i]);
	}

	// values of M_trans
	M_trans = M.t();

	//compute to get the values of affineM
	temp = (M_trans * M).inv() * M_trans * b;
	affineM = temp.reshape(1, 2);

	return affineM;
}

void blend_stitching(const Mat I1, const Mat I2, Mat& I_f, int diff_x, int diff_y, float alpha) {

	int bound_x = I1.rows + diff_x;
	int bound_y = I1.cols + diff_y;

	int col = I_f.cols;
	int row = I_f.rows;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			// for check validation of I1 & I2
			bool cond1 = (i < bound_x && i > diff_x) && (j < bound_y && j > diff_y) ? true : false;
			bool cond2 = I_f.at<Vec3f>(i, j) != Vec3f(0, 0, 0) ? true : false;

			// I2 is already in I_f by inverse warping
			// So, It is not necessary to check that only I2 is valid
			// if both are valid
			if (cond1 && cond2) {
				I_f.at<Vec3f>(i, j) = alpha * I1.at<Vec3f>(i - diff_x, j - diff_y) + (1 - alpha) * I_f.at<Vec3f>(i, j);
			}
			// only I1 is valid
			else if (cond1) {
				I_f.at<Vec3f>(i, j) = I1.at<Vec3f>(i - diff_x, j - diff_y);
			}
		}
	}
}