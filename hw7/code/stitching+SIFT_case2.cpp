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
	// �̹��� �ҷ����̱�
	Mat input1 = imread("input1.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input2 = imread("input2.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input1_gray, input2_gray;

	if (!input1.data || !input2.data)
	{
		std::cout << "Could not open" << std::endl;
		return -1;
	}

	//SIFT�� keypoint�� ã�� p.srcPoints�� p.dstPoints�� ����ȴ�.
		// �̶�, standard = true�� ���� SIFT�� NN�� �� ��, I1 -> I2�� �� ��
		// standard = false: SIFT�� NN�� �� ��, I2 -> I1�� �Ѱ�
	bool standard = true;
	matched_points p = SIFT_mine(input1, input2, standard);

	vector<double> ptl_x;
	vector<double> ptl_y;
	vector<double> ptr_x;
	vector<double> ptr_y;

	//stitching�ϱ� ���� �����̹����� �������̹����� ������ x,y��ǥ�� ���� ���� ��� �и����� vector�� ����
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


	/* Affine Transformation estimation ���� */
	// ���� ����
	int trialS = 35;	// �ݺ��� Ƚ��
	int k = 3;			// sample�� data ����
	int size = p.srcPoints.size();

	Mat final_T(2, 3, CV_32F, Scalar(0));	// ���������� ����� affine Matrix (2, 3)�̴�.
	samples max_inliers;			// max ������ inlier�� ������ T�� ���� inlier��
	int max = -1;					// inlier�� ������ ���� ����

	// RANSAC 
	for (int i = 0; i < trialS; i++) {
		// STEP 1: randomly sample k data (k >= 3)
		samples data = random(i, k, size, ptl_x, ptl_y, ptr_x, ptr_y);

		// STEP 2: Estimate the affine transformation T by solving Mx = b
		Mat T = cal_affine<float>(data.Lx, data.Ly, data.Rx, data.Ry, k);

		// STEP 3: Score by computing number of inliers from all matches using diff_threshold()
		samples inliers = diff_threshold(T, ptl_x, ptl_y, ptr_x, ptr_y, size);
		int count = inliers.Lx.size();		// inliers�� ���� ������ ����

		// STEP 4: Select the best affine transformation T
		if (count > max) {
			max = count;
			final_T = T;
			max_inliers = inliers;
		}

	}

	std::cout << " ��Ī�ϱ� ���� ����� �� ����: " << max_inliers.Lx.size() << endl;
	std::cout << "trial ��: " << trialS << " sample�� ���� ����: " << k << endl;

	// STEP 5: best�� final_T�� max���� inliers�鸸���� �ٽ� T ���
	implement_stitching(input1, input2, max_inliers.Lx, max_inliers.Ly, max_inliers.Rx, max_inliers.Ry);


	return 0;
}


samples random(int i, int k, int size, vector<double>& ptl1, vector<double>& ptl2, vector<double>& ptl3, vector<double>& ptl4) {
	samples data;
	srand((unsigned)time(NULL) + i);		// Random�ϰ� sample�ϱ� ����, ���� ����
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

		// I2�� ��Ī�Ǵ� ��
		Mat p_prime = *(Mat_<float>(2, 1) << ptr_x[i], ptr_y[i]);

		// compute Tp ( random�ϰ� ���� K���� sample�� ����� affine Transfomation Matrix T�� ��� )
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