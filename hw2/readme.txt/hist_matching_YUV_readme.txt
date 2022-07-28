# name of Project
- histogram matching on BGR image with reference color image

# Purpose of this code
- when BGR image("input") and reference color image("ref") are given, convert them to Y, U, V channel, and match the "input" with "ref" using trasfer function on ONLY Y channel 
The output is 
1. txt file of PDF of BGR image
2. txt file of PDF of reference color image
3. txt file of PDF of matched output BGR image 
4. txt file of PDF transfer function for matching (only for Y channel)

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
	    - input : must be a array consisting of U channel of BGR input image, Size of matrix must be (Lx1)
	    - matched : Size of matrix must be (Lx1), In my code I put Y, same Matrix as input but if you want to save the outpuf ot matched Y channel in another Matrix, you have to assign another matrix such as "Mat after_matching"
	    - trans_func_T,  trans_func_G, trans_func_matching : must be a (Lx1) array
	    - CDF_T : must be a CDF of a Y channel of input BGR image, must be a (Lx1) array
	    - CDF_G : must be a CDF of a Y channel of reference color image, must be a (Lx1) array
	
# How to define default parameters
--
