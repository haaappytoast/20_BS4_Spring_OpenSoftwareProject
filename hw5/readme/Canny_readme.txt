# name of Project
- use Canny Detector for both BGR input and Grayscale input

# Purpose of this code
- 내장함수 Canny()를 사용하여 엣지를 검출하는 것

# How to run this code
- code is written in C++ and uses visual studio 2019 as IDE
- requires opencv installed(OpenCV version : 2.4.13.6)
    to use opencv you should include the below code on the top of the codes
	#include <opencv2/opencv.hpp>

# How to adjust parameters (if any)
1.	Canny(input, output, thres1, thres2);
	    input : can be both BGR or grayscale image
	    output : detected edge
	    thres1 : [0 ~ 255]
	    thres2 : [0 ~ 255] must be greater than thres1
	    try many numbers for thres1 and thres2 and find the best numbers by experiment.


# How to define default parameters
...

