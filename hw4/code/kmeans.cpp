#include <iostream>
#include <opencv2/opencv.hpp>

#define IM_TYPE	CV_8UC3

using namespace cv;

Mat Kmeans_Gray_int(const Mat input, int clusterCount, int attempts);
Mat Kmeans_Gray_int_pos(Mat input, int clusterCount, int attemps, int sigma);
Mat Kmeans_RGB_int(const Mat input, int clusterCount, int attemps);
Mat Kmeans_RGB_int_pos(Mat input, int clusterCount, int attemps, int sigma);

// Note that this code is for the case when an input data is a color value.
int main() {

	Mat input = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input_gray;

	// check for validation
	if (!input.data)
	{
		std::cout << "Could not open" << std::endl;
		return -1;
	}

	cvtColor(input, input_gray, CV_BGR2GRAY);	// convert BGR to Grayscale

	// Clustered images using Kmeans clustering (considering intensity only )
	Mat clustered_Gray_int = Kmeans_Gray_int(input_gray, 15, 5);
	Mat clustered_BGR_int = Kmeans_RGB_int(input, 15, 5);

	// Clustered images using Kmeans clustering (considering intensity and position)
	Mat clustered_Gray_int_pos = Kmeans_Gray_int_pos(input_gray, 15, 5, 100);
	Mat clustered_BGR_int_pos = Kmeans_RGB_int_pos(input, 15, 5, 100);

	namedWindow("Original_Gray", WINDOW_AUTOSIZE);
	imshow("Original_Gray", input_gray);

	namedWindow("RGB", WINDOW_AUTOSIZE);
	imshow("RGB", input);

	namedWindow("clustered with I (Grayscale)", WINDOW_AUTOSIZE);
	imshow("clustered with I (Grayscale)", clustered_Gray_int);

	namedWindow("clustered with I (RGB)", WINDOW_AUTOSIZE);
	imshow("clustered with I (RGB)", clustered_BGR_int);

	namedWindow("clustered with I and pos (Grayscale)", WINDOW_AUTOSIZE);
	imshow("clustered with I and pos (Grayscale)", clustered_Gray_int_pos);

	namedWindow("clustered with I and pos (RGB)", WINDOW_AUTOSIZE);
	imshow("clustered with I and pos (RGB)", clustered_BGR_int_pos);

	waitKey(0);

	return 0;
}
Mat Kmeans_Gray_int(const Mat input, int clusterCount, int attempts){

	int rows = input.rows;
	int cols = input.cols;

	Mat samples(rows * cols, 1, CV_32F);	// Grayscale : samples.size() : [1 x ( rows * cols ) ]
											//								(intensity)

	for (int y = 0; y < rows; y++)
		for (int x = 0; x < cols; x++)
				samples.at<float>(y + x* rows, 0) = input.at<uchar>(y, x);

	
	// Clustering is performed for intensity (Grayscale)
	// Note that the intensity value is not normalized here (0~1). You should normalize both intensity and position when using them simultaneously.
	Mat labels;
	Mat centers;

	std::cout << "Starting K-means Algorithm for GrayScale image with intensity info" << "\n";

	kmeans(samples, clusterCount, labels, TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 10000, 0.0001), attempts, KMEANS_PP_CENTERS, centers);
	// labels : stores the cluster indices for ever sample,	labels.size() : [1 x ( input.rows() * input.cols() )]
	// centers : stores the the intensity of centers, centers.size() : [ 1 x clusterCount ]

	std::cout << "finished" << "\n";

	Mat new_image(input.size(), input.type());

	for (int y = 0; y < input.rows; y++)
		for (int x = 0; x < input.cols; x++)
		{
			int cluster_idx = labels.at<int>(y + x*input.rows, 0);		// cluster_idx find;
				new_image.at<uchar>(y, x) = (int) centers.at<float>(cluster_idx, 0);

		}

	return new_image;
}

Mat Kmeans_Gray_int_pos(Mat input, int clusterCount, int attempts, int sigma) {

	//normalization of input pixel's intensity [0~255] -> [0 ~1]
	input.convertTo(input, CV_64F, 1.0 / 255);

	int rows = input.rows;
	int cols = input.cols;

	Mat samples(rows * cols, 3, CV_32F);	// Grayscale : samples.size() : [3 x ( rows * cols ) ]  
											//								(I,x/sigma, y/sigma)

	//making samples for k-means clustering
	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			samples.at<float>(y + x * rows, 0) = (float)input.at<double>(y, x);

			// divide x,y with sigma to adjust the ratio between intensity and position
			samples.at<float>(y + x * rows, 1) = (float)x / (float) (cols * sigma);		//normalize position x by dividing with cols
			samples.at<float>(y + x * rows, 2) = (float)y / (float) (rows * sigma);		// normalize position y by dividing with rows;
		}
	}


	// Clustering is performed for intensity (Grayscale)
	Mat labels;
	Mat centers;

	std::cout << "Starting K-means Algorithm for GrayScale image with intensity & position info" << "\n";

	kmeans(samples, clusterCount, labels, TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 10000, 0.0001), attempts, KMEANS_PP_CENTERS, centers);
	// labels : stores the cluster indices for ever sample,	labels.size() : [1 x ( input.rows() * input.cols() )]
	// centers : stores the the intensity of center, centers.size() : [ 3 x clusterCount ]
	
	std::cout << "finished" << "\n";


	Mat new_image(input.size(), input.type());

	for (int y = 0; y < rows; y++){
		for (int x = 0; x < cols; x++){
			int cluster_idx = labels.at<int>(y + x * rows, 0);		// cluster_idx find;
			new_image.at<double>(y, x) = centers.at<float>(cluster_idx, 0);
		}	
	}

	return new_image;
}

Mat Kmeans_RGB_int(const Mat input, int clusterCount, int attempts) {

	int rows = input.rows;
	int cols = input.cols;

	Mat samples(rows * cols, 3, CV_32F);	// BGR : samples.size() : [3 x ( rows * cols ) ] 
												//					  (B_I, G_I, R_I)

	//making samples for k-means clustering (2D image with 3 channels-> 1D samples with 3 channels)
	for (int y = 0; y < input.rows; y++)
		for (int x = 0; x < input.cols; x++)
			for (int z = 0; z < 3; z++)
				samples.at<float>(y + x * input.rows, z) = input.at<Vec3b>(y, x)[z];


	// Clustering is performed for intensity (Grayscale)
	Mat labels;
	Mat centers;

	std::cout << "Starting K-means Algorithm for BGR image with intensity info" << "\n";

	kmeans(samples, clusterCount, labels, TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 10000, 0.0001), attempts, KMEANS_PP_CENTERS, centers);
	// labels : stores the cluster indices for ever sample,	labels.size() : [1 x ( input.rows() * input.cols() )]
	// centers : stores the the intensity of center, centers.size() : [ 3 x clusterCount ]

	std::cout << "finished" << "\n";

	Mat new_image(input.size(), input.type());

	for (int y = 0; y < input.rows; y++)
		for (int x = 0; x < input.cols; x++)
		{
			int cluster_idx = labels.at<int>(y + x * input.rows, 0);		// cluster_idx find;
			for (int z = 0; z < 3; z++) {
				new_image.at<Vec3b>(y, x)[z] = (int)centers.at<float>(cluster_idx, z);
			}
		}

	return new_image;
}


Mat Kmeans_RGB_int_pos(Mat input, int clusterCount, int attempts, int sigma) {

	//normalization of input pixel's intensity [0~255] -> [0 ~1]
	input.convertTo(input, CV_64FC3, 1.0 / 255);

	int rows = input.rows;
	int cols = input.cols;

	Mat samples(rows * cols, 5, CV_32F);	// BGR : samples.size() : [5 x ( rows * cols ) ]

	//making samples for k-means clustering
	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			for (int z = 0; z < 3; z++){
				samples.at<float>(y + x * input.rows, z) = input.at<Vec3d>(y, x)[z];
			}
			// divide x,y with sigma to adjust the ratio between intensity and position
			samples.at<float>(y + x * rows, 3) = (float)x / (float)(cols * sigma);		//normalize position x by dividing with cols
			samples.at<float>(y + x * rows, 4) = (float)y / (float)(rows * sigma);		// normalize position y by dividing with rows;
		}
	}

	// Clustering is performed for intensity (Grayscale)
	Mat labels;
	Mat centers;
	std::cout << "Starting K-means Algorithm for BGR image with intensity & position info" << "\n";

	kmeans(samples, clusterCount, labels, TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 10000, 0.0001), attempts, KMEANS_PP_CENTERS, centers);
	// labels : stores the cluster indices for ever sample,	labels.size() : [1 x ( input.rows() * input.cols() )]
	// centers : stores the the intensity of center, centers.size() : [ 3 x clusterCount ]

	std::cout << "finished" << "\n";

	Mat new_image(input.size(), input.type());

	for (int y = 0; y < input.rows; y++)
		for (int x = 0; x < input.cols; x++)
		{
			int cluster_idx = labels.at<int>(y + x * input.rows, 0);		// cluster_idx find;
			for (int z = 0; z < 3; z++) {
				new_image.at<Vec3d>(y, x)[z] = centers.at<float>(cluster_idx, z);
			}

		}

	return new_image;
}