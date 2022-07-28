# name of Project
- run SIFT descriptor to the input1 and input2 and match keypoints from Input2 to Input1

# Purpose of this code
- run SIFT descriptor to the input1 and input2 and draw the line between the matched keypoints of two images
There are 3 cases:
	1. feature matching using only NN (input2 -> input1)
	2. feature matching using NN + cross-checking
	3. feature matching using NN + cross-checking + ratio-threshold

# How to run this code
- code is written in C++ and uses visual studio 2019 as IDE
- requires opencv installed(OpenCV version : 2.4.13.6)
    to use opencv you should include the below code on the top of the codes
	#include <opencv2/opencv.hpp>
- requires the hpp file to use SIFT
    to use opencv you should include the below code on the top of the codes
	#include <opencv2/nonfree/nonfree.hpp>


# How to adjust parameters (if any)
1. line93:		bool crossCheck = true;
2. line94:		bool ratio_threshold = true;

- As I mentioned in <the purpose of this code>, you can either choose to run cross-checking or ratio-threshold or not.
If you don't want to run them, you have to change true -> false. 
If you want to run, set them in true.



# 주의점
line26:	Mat input1 = imread("input1.jpg", CV_LOAD_IMAGE_COLOR);
line27:	Mat input2 = imread("input2.jpg", CV_LOAD_IMAGE_COLOR);
line95: 	findPairs(keypoints2, descriptors2, keypoints1, descriptors1, srcPoints, dstPoints, crossCheck, ratio_threshold);
	기준이미지가 input2이고 이에 대한 정보가 keypoints2과 descriptors2이다.
	타겟 이미지는 input1이고 이에 대한 정보가 keypoints1와 descriptors1이다.

이들의 matching된 이미지는 input2(왼) - input1(오)로 그려진다. 
line99~104를 보면, 왼쪽에 위치하게 되는 input2의 사이즈를 사용하여, 기준이미지 input2의 keypoint(코드 상에서는 변수 from)로부터 타겟 이미지 input1의 matching된 keypoint점들의 좌표(코드 상에서는 변수 to)를 찍어주었으므로 만약 기준 이미지를 input1, 타겟 이미지를 input2으로 바꾸기 위해 line95의 파라미터만을 바꾼다면 matching되는 점들의 좌표가 이상하게 찍히게 된다. 
따라서 기준 이미지를 input1, 타겟 이미지를 input2로 바꾸고 싶다면, 이 코드가 아닌, SIFT-(I1_to_I2)을 사용하여라.

