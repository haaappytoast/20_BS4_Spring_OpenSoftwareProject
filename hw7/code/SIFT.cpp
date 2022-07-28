#include <opencv2/opencv.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>

#define RATIO_THR 0.4

using namespace std;
using namespace cv;

typedef struct value {
	int neighbor = -1;
	int neighbor_2nd = -1;
}values;

double euclidDistance(Mat& vec1, Mat& vec2);
values nearestNeighbor(Mat& vec, vector<KeyPoint>& keypoints, Mat& descriptors);
void findPairs(vector<KeyPoint>& keypoints1, Mat& descriptors1,
	vector<KeyPoint>& keypoints2, Mat& descriptors2,
	vector<Point2f>& srcPoints, vector<Point2f>& dstPoints, bool crossCheck, bool ratio_threshold);

typedef struct matched_points{

	vector<Point2f> srcPoints;
	vector<Point2f> dstPoints;

}matched_points;


matched_points SIFT_mine(Mat& I1, Mat& I2, bool standard=true){

	Mat input1 = I1;
	Mat input2 = I2;
	Mat input1_gray, input2_gray;

	if (!input1.data || !input2.data)
	{
		std::cout << "Could not open" << std::endl;
		exit(1);
	}

	//resize(input1, input1, Size(input1.cols / 2, input1.rows / 2));
	//resize(input2, input2, Size(input2.cols / 2, input2.rows / 2));

	cvtColor(input1, input1_gray, CV_BGR2GRAY);
	cvtColor(input2, input2_gray, CV_BGR2GRAY);

	FeatureDetector* detector = new SiftFeatureDetector(
		0,		// nFeatures
		4,		// nOctaveLayers
		0.04,	// contrastThreshold
		10,		// edgeThreshold
		1.6		// sigma
	);

	DescriptorExtractor* extractor = new SiftDescriptorExtractor();

	// Create a image for displaying mathing keypoints
	Size size = input2.size();
	Size sz = Size(size.width + input1_gray.size().width, max(size.height, input1_gray.size().height));

	Mat matchingImage = Mat::zeros(sz, CV_8UC3);

	input1.copyTo(matchingImage(Rect(size.width, 0, input1_gray.size().width, input1_gray.size().height)));
	input2.copyTo(matchingImage(Rect(0, 0, size.width, size.height)));

	// Compute keypoints and descriptor from the source image in advance
	vector<KeyPoint> keypoints1;
	Mat descriptors1;

	detector->detect(input1_gray, keypoints1);
	extractor->compute(input1_gray, keypoints1, descriptors1);
	printf("input1 : %d keypoints are found.\n", (int)keypoints1.size());

	vector<KeyPoint> keypoints2;
	Mat descriptors2;

	// Detect keypoints
	detector->detect(input2_gray, keypoints2);
	extractor->compute(input2_gray, keypoints2, descriptors2);

	printf("input2 : %zd keypoints are found.\n", keypoints2.size());


	// Find nearest neighbor pairs
	matched_points pt;
	bool crossCheck = true;
	bool ratio_threshold = true;
	if (standard == true){
		findPairs(keypoints1, descriptors1, keypoints2, descriptors2, pt.srcPoints, pt.dstPoints, crossCheck, ratio_threshold);
	}
	else {
		findPairs(keypoints2, descriptors2, keypoints1, descriptors1, pt.srcPoints, pt.dstPoints, crossCheck, ratio_threshold);
	}

	printf("%zd keypoints are matched.\n", pt.srcPoints.size());
	
	return pt;
}

/**
* Calculate euclid distance
*/
double euclidDistance(Mat& vec1, Mat& vec2) {
	double sum = 0.0;
	int dim = vec1.cols;
	for (int i = 0; i < dim; i++) {
		sum += (vec1.at<float>(0, i) - vec2.at<float>(0, i)) * (vec1.at<float>(0, i) - vec2.at<float>(0, i));
	}

	return sqrt(sum);
}

/**
* Find the index of nearest neighbor point from keypoints.
*/
values nearestNeighbor(Mat& vec, vector<KeyPoint>& keypoints, Mat& descriptors) {
	values p;
	p.neighbor = -1;
	p.neighbor_2nd = -1;
	double minDist = 1e6;
	double min_dist1;
	double min_dist2;

	for (int i = 0; i < descriptors.rows; i++) {
		Mat v = descriptors.row(i);		// each row of descriptor

		min_dist1 = euclidDistance(vec, v);
		if (min_dist1 <= minDist) {
			min_dist2 = minDist;
			minDist = min_dist1;

			p.neighbor_2nd = p.neighbor;
			p.neighbor = i;
		}
	}
	return p;
}

/**
* Find pairs of points with the smallest distace between them
*/
void findPairs(vector<KeyPoint>& keypoints1, Mat& descriptors1,
	vector<KeyPoint>& keypoints2, Mat& descriptors2,
	vector<Point2f>& srcPoints, vector<Point2f>& dstPoints, bool crossCheck, bool ratio_threshold) {
	for (int i = 0; i < descriptors1.rows; i++) {
		KeyPoint pt1 = keypoints1[i];
		Mat desc1 = descriptors1.row(i);
		values neigh;
		if (i % 100 == 0)std::cout << i << " / " << descriptors1.rows << " finished...\n";
		neigh = nearestNeighbor(desc1, keypoints2, descriptors2);
		int nn = neigh.neighbor;

		// Refine matching points using ratio_based thresholding
		if (ratio_threshold) {
			if ( neigh.neighbor < 0 || neigh.neighbor_2nd < 0) continue;

			float Tr = 0.15;
			int nn_2nd = neigh.neighbor_2nd;

			Mat v1 = descriptors2.row(nn);
			Mat v2 = descriptors2.row(nn_2nd);
			if (euclidDistance(desc1, v1) / euclidDistance(desc1, v2) >= Tr) {	// if the ratio is high (when interval is low)
				continue;
			}
		}

		// Refine matching points using cross-checking
		if (crossCheck) {
			values neigh2;
			Mat desc2 = descriptors2.row(nn);
			int nn2 = nearestNeighbor(desc2, keypoints1, descriptors1).neighbor;
			if (i == nn2) {
				KeyPoint pt2 = keypoints2[nn];
				srcPoints.push_back(pt1.pt);
				dstPoints.push_back(pt2.pt);
			}
			continue;
		}

		KeyPoint pt2 = keypoints2[nn];
		srcPoints.push_back(pt1.pt);
		dstPoints.push_back(pt2.pt);
	}
}