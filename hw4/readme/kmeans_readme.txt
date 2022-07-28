# name of Project
- with BGR image and Grayscale image, cluster intensity of the images into K groups considering,
1. Only intensity
2. Intensity and Position

# Purpose of this code
- when image is given in BGR as "input", convert it to grayscale first, and cluster it with 내장함수, k-means()
- output:
	1. Grayscale image : clustered into K groups of intensity considering only intensity
	2. BGR image : clustered into K groups of intensity considering only intensity
	3. Grayscale image : clustered into K groups of intensity considering intensity & position
	4. BGR image : clustered into K groups of intensity considering intensity & position


# How to run this code
- code is written in C++ and uses visual studio 2019 as IDE
- requires opencv installed(OpenCV version : 2.4.13.6)
    to use opencv you should include the below code on the top of the codes
	#include <opencv2/opencv.hpp>


# How to adjust parameters (if any)
1.	Mat Kmeans_Gray_int(const Mat input, int clusterCount, int attempts);
	    - input : must be a grayscale image
	    - clusterCount : positive integer. It is the number of clustering groups
	    - attempts : specify the number of times the k-means algorithm is executed using different initial labellings (positive integer)

2.	Mat Kmeans_Gray_int_pos(Mat input, int clusterCount, int attemps, int sigma);
	    - input : must be a grayscale image
	    - clusterCount : positive integer. It is the number of clustering groups
	    - attempts : specify the number of times the k-means algorithm is executed using different initial labellings
	    - sigma : constant factor adjusting the ratio between intensity and position (실험적으로 여러번 사용하여 가장 분류가 잘된 sigma를 사용한다.)

3. 	Mat Kmeans_RGB_int(const Mat input, int clusterCount, int attemps);
	    - input : must be a BGR image
	    - clusterCount : positive integer. It is the number of clustering groups
	    - attempts : specify the number of times the k-means algorithm is executed using different initial labellings (positive integer)

4.	Mat Kmeans_RGB_int_pos(Mat input, int clusterCount, int attemps, int sigma);
	    - input : must be a BGR image
	    - clusterCount : positive integer. It is the number of clustering groups
	    - attempts : specify the number of times the k-means algorithm is executed using different initial labellings
	    - sigma : constant factor adjusting the ratio between intensity and position (실험적으로 여러번 사용하여 가장 분류가 잘된 sigma를 사용한다.)
 S
