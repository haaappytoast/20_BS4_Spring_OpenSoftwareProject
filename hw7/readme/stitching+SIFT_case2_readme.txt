# name of Project
- image Stitching using Affine Transform with SIFT keypoints And to delete outliers of keypoints, use RANSAC
# Purpose of this code
- get matched keypoints of two images by running SIFT. Then, run RANSAC to delete outliers of keypoints and stitch two images using Affine Transform with these keypoints

There are 2 cases:
	1. when performing NN of SIFT, match features by I1->I2
	2. when performing NN of SIFT, match features by I2->I1

# How to run this code
- code is written in C++ and uses visual studio 2019 as IDE
- requires opencv installed(OpenCV version : 2.4.13.6)
    to use opencv you should include the below code on the top of the codes
	#include <opencv2/opencv.hpp>
- requires the hpp file to use "SIFT.cpp" and "stitching.cpp" (필자가 구현한 cpp 파일임)
    you should include the below code on the top of the codes
	#include "SIFT.cpp"
	#include "stitching.cpp"
- 여러 연산들을 하기 위해 추가해야할 라이브러리
	#include <ctime>
	#include <cmath>
	#include <vector>

# How to adjust parameters (if any)
1. line 40:			bool standard =false;

- standard = true: when performing NN of SIFT, match features by I1->I2
- standard = false: when performing NN of SIFT, match features by I2->I1

2. line 142:		if (mag < 10) { 쪽의 10

- 여기서 10은 threshold를 뜻한다. threshold가 작을 수록 더 엄격하게 inlier을 정하는 것이기 때문에 이 조건을 만족하는 keypoints들이 줄어들며, affine Transform을 구하는데 사용되는 개수가 더 적어진다.
- 실험적으로 여러 값을 대입하여 사용한다.

line 69:		int trialS = 35;	
line 70:		int k = 4;			

- trialS는 RANSAC을 수행할 횟수를 말하며, k는 RANSAC을 한번 수행할 때마다 SIFT로부터 얻은 keypoints들 중 몇개를 sample할 것인지를 정하는 정수이다. k>=2이어야 한다.
- 두 개 모두 실험적으로 정하며, SIFT로부터 얻은 keypoints들 중 만약 outlier들이 많다고 판단되어지면 trialS를 높이는 것이 실험적으로 좋다.

# 주의점
	// 이미지 불러들이기
1. line 27:		Mat input1 = imread("input1.jpg", CV_LOAD_IMAGE_COLOR);
2. line 28:		Mat input2 = imread("input2.jpg", CV_LOAD_IMAGE_COLOR);

- 'input1.jpg'와 'input2.jpg'를 stitching할 때, input1은 왼쪽에 오는 그림이고 input2는 오른쪽에 오는 그림이어야한다.

# 알아둘 점
SIFT 실행시, (SIFT.cpp의 SIFT_mine()함수를 사용할 때), ratio-based thresholding과 cross-checking을 모두 하였으며 ratio-based threshold의 값은 0.15로 정하였다.