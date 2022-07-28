# name of Project
- histogram matching on grayscale image with reference grayscale image

# Purpose of this code
- when BGR image("input") and reference color image("ref") are given,  convert them to grayscale first, and match the "input" with "ref" using trasfer function. 
The output is 
1. txt file of PDF of grayscale image
2. txt file of PDF of reference grayscaled image
3. txt file of PDF of matched output image 
4. txt file of PDF transfer function for matching

# How to run this code
- code is written in C++ and uses visual studio 2019 as IDE
- requires opencv installed(OpenCV version : 2.4.13.6)
    to use opencv you should include the below code on the top of the codes
	#include <opencv2/opencv.hpp>
- requires including "hist_func.h"
    you shoud include the below code on the top of the codes
	#include "hist_func.h"

# How to adjust parameters (if any)
	- void hist_matching(Mat& input, Mat& matched, G* trans_func_T, G* trans_func_G, G* trans_func_matching, float* CDF_T, float* CDF_G);
	    - input : must be a grayscaled image,  Size of matrix must be (Lx1)
	    - matched : Size of matrix must be (Lx1)
	    - trans_func_T,  trans_func_G, trans_func_matching : must be a (Lx1) array
	    - CDF_T : must be a CDF of a grayscaled input
	    - CDF_G : must be a CDF of a reference grayscaled input
	
# How to define default parameters
--
