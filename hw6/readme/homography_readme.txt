# name of Project
- Homography

# Purpose of this code
- run SURF descriptor to the input1 and input2 and match keypoints of two images by FLANNED based algorithm and show the same object in two different images
즉, 어떠한 물체에 대해, 다른 이미지에서는 다른 각도로 보여지는 같은 물체를 SURF를 통해 구한 특징점을 사용하여 그 물체를 인식해주는 코드이다.

# How to run this code
- code is written in C++ and uses visual studio 2019 as IDE
- requires opencv installed(OpenCV version : 4.0.1)
    to use opencv you should include the below code on the top of the codes
	#include <opencv2/opencv.hpp>
- requires the xfeatures2d.hpp file to use SURF
    to use opencv you should include the below code on the top of the codes
	#include "opencv2/xfeatures2d.hpp"
** 주의점: (openCV는 이 xfeatures2d.hpp 파일을 기본적으로 포함하고 있지 않으므로 아래 사이트를 참조하여 이에 해당하는 hpp파일을 추가시켜주어야 한다.... 참고 사이트 : https://webnautes.tistory.com/1036)


# How to adjust parameters (if any)
1. line42:		const float ratio_thresh = 0.8f;
- matching시킨 점들에 대해 좋은 matching 결과들만 남기기 위해 thresholding을 진행해주어야한다. 이때 사용하는 변수가 ratio_thres이다. 이 변수를 0~1로 여러번 조정하여 실험적으로 가장 좋은 값을 채택한다.

# 주의점 : 물체에 대한 corner을 사용하여 최종적으로 결과이미지에서 물체의 테두리를 그려준다. 이 때, corner을 사용하기 때문에 좋은 이미지결과를 얻고 싶다면 인식하고 싶은 물체가 각이 있는 물체를 사용하는 것이 좋다.
