# name of Project
- image Stitching using Affine Transform with SIFT keypoints
# Purpose of this code
- get matched keypoints of two images by running SIFT. Then, stitch two images using Affine Transform with these keypoints

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


# How to adjust parameters (if any)
1. line 40:			bool standard =false;

- standard = true: when performing NN of SIFT, match features by I1->I2
- standard = false: when performing NN of SIFT, match features by I2->I1


# 주의점
	// 이미지 불러들이기
1. line 27:		Mat input1 = imread("input1.jpg", CV_LOAD_IMAGE_COLOR);
2. line 28:		Mat input2 = imread("input2.jpg", CV_LOAD_IMAGE_COLOR);

- 'input1.jpg'와 'input2.jpg'를 stitching할 때, input1은 왼쪽에 오는 그림이고 input2는 오른쪽에 오는 그림이어야한다.

# 알아둘 점
SIFT 실행시, (SIFT.cpp의 SIFT_mine()함수를 사용할 때), ratio-based thresholding과 cross-checking을 모두 하였으며 ratio-based threshold의 값은 0.15로 정하였다.