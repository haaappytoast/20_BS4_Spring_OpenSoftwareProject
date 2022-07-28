#include <iostream>
#include <ctime>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "SIFT.cpp"
#include "stitching.cpp"



typedef struct samples {

	vector<double> Lx;
	vector<double> Ly;
	vector<double> Rx;
	vector<double> Ry;

}samples;

samples random(int i, int k, int size, vector<double>& ptl1, vector<double>& ptl2, vector<double>& ptl3, vector<double>& ptl4);
samples diff_threshold(Mat& T, vector<double>& ptl_x, vector<double>& ptl_y, vector<double>& ptr_x, vector<double>& ptr_y, int number_of_points);


int main() {
	// 이미지 불러들이기
	Mat input1 = imread("input1.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input2 = imread("input2.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input1_gray, input2_gray;

	if (!input1.data || !input2.data)
	{
		std::cout << "Could not open" << std::endl;
		return -1;
	}

	//SIFT로 keypoint들 찾기 p.srcPoints와 p.dstPoints에 저장된다.
		// 이때, standard = true일 경우는 SIFT의 NN을 할 때, I1 -> I2를 한 것
		// standard = false: SIFT의 NN을 할 때, I2 -> I1을 한것
	bool standard = true;
	matched_points p = SIFT_mine(input1, input2, standard);

	vector<double> ptl_x;
	vector<double> ptl_y;
	vector<double> ptr_x;
	vector<double> ptr_y;

	//stitching하기 위해 왼쪽이미지와 오른쪽이미지의 각각의 x,y좌표에 대한 값을 모두 분리시켜 vector에 저장
	if (standard == true) {
		for (int i = 0; i < p.srcPoints.size(); i++) {
			ptl_x.push_back(p.srcPoints[i].x);
			ptl_y.push_back(p.srcPoints[i].y);
			ptr_x.push_back(p.dstPoints[i].x);
			ptr_y.push_back(p.dstPoints[i].y);
		}
	}
	else if (standard == false) {
		for (int i = 0; i < p.srcPoints.size(); i++) {
			ptl_x.push_back(p.dstPoints[i].x);
			ptl_y.push_back(p.dstPoints[i].y);
			ptr_x.push_back(p.srcPoints[i].x);
			ptr_y.push_back(p.srcPoints[i].y);
		}
	}


	/* Affine Transformation estimation 과정 */
	// 변수 설정
	int trialS = 35;	// 반복할 횟수
	int k = 3;			// sample할 data 개수
	int size = p.srcPoints.size();

	Mat final_T(2, 3, CV_32F, Scalar(0));	// 최종적으로 사용할 affine Matrix (2, 3)이다.
	samples max_inliers;			// max 개수의 inlier을 가지는 T에 대한 inlier들
	int max = -1;					// inlier의 개수를 비교할 정수

	// RANSAC 
	for (int i = 0; i < trialS; i++) {
		// STEP 1: randomly sample k data (k >= 3)
		samples data = random(i, k, size, ptl_x, ptl_y, ptr_x, ptr_y);

		// STEP 2: Estimate the affine transformation T by solving Mx = b
		Mat T = cal_affine<float>(data.Lx, data.Ly, data.Rx, data.Ry, k);

		// STEP 3: Score by computing number of inliers from all matches using diff_threshold()
		samples inliers = diff_threshold(T, ptl_x, ptl_y, ptr_x, ptr_y, size);
		int count = inliers.Lx.size();		// inliers에 들어가는 점들의 개수

		// STEP 4: Select the best affine transformation T
		if (count > max) {
			max = count;
			final_T = T;
			max_inliers = inliers;
		}

	}

	std::cout << " 매칭하기 위해 사용한 점 개수: " << max_inliers.Lx.size() << endl;
	std::cout << "trial 수: " << trialS << " sample한 점의 개수: " << k << endl;

	// STEP 5: best인 final_T의 max개의 inliers들만으로 다시 T 계산
	implement_stitching(input1, input2, max_inliers.Lx, max_inliers.Ly, max_inliers.Rx, max_inliers.Ry);


	return 0;
}


samples random(int i, int k, int size, vector<double>& ptl1, vector<double>& ptl2, vector<double>& ptl3, vector<double>& ptl4) {
	samples data;
	srand((unsigned)time(NULL) + i);		// Random하게 sample하기 위해, 난수 생성
	int index = rand() % size;
	for (int i = 0; i < k; i++) {
		data.Lx.push_back(ptl1[index]);
		data.Ly.push_back(ptl2[index]);
		data.Rx.push_back(ptl3[index]);
		data.Ry.push_back(ptl4[index]);
	}
	return data;
}

samples diff_threshold(Mat& T, vector<double>& ptl_x, vector<double>& ptl_y, vector<double>& ptr_x, vector<double>& ptr_y, int number_of_points) {
	samples inliers;
	Mat Tp(2, 1, CV_32F, Scalar(0));
	Mat diff(2, 1, CV_32F, Scalar(0));
	int count = 0;
	// compute | Tp - p' | for each matching points
	for (int i = 0; i < number_of_points; i++) {
		double mag = 0;

		// I2의 매칭되는 점
		Mat p_prime = *(Mat_<float>(2, 1) << ptr_x[i], ptr_y[i]);

		// compute Tp ( random하게 얻은 K개의 sample로 계산한 affine Transfomation Matrix T를 사용 )
		Mat p = *(Mat_<float>(3, 1) << ptl_x[i], ptl_y[i], 1);
		Tp = T * p;
		// | Tp - p' |
		diff = Tp - p_prime;

		mag = sqrt(pow(diff.at<float>(0), 2) + pow(diff.at<float>(1), 2));

		if (mag < 10) {
			inliers.Lx.push_back(ptl_x[i]);
			inliers.Ly.push_back(ptl_y[i]);
			inliers.Rx.push_back(ptr_x[i]);
			inliers.Ry.push_back(ptr_y[i]);
		}
	}
	return inliers;
}