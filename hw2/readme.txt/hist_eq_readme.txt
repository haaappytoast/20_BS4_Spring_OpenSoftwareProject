# name of Project
- histogram equalization on grayscale image

# Purpose of this code
- when image is given in BGR as "input", convert it to grayscale first, and equalize the image. Also it generates PDF of grayscale image, equalized grayscale image and linear transfer function as a txt file sperately


# How to run this code
- code is written in C++ and uses visual studio 2019 as IDE
- requires opencv installed(OpenCV version : 2.4.13.6)
    to use opencv you should include the below code on the top of the codes
	#include <opencv2/opencv.hpp>
- requires including "hist_func.h"
    you shoud include the below code on the top of the codes
	#include "hist_func.h"

# How to adjust parameters (if any)
	void hist_eq(Mat& input, Mat& equalized, G* trans_func, float* CDF);
	    - input : must be a grayscaled image,  Size of matrix must be (Lx1)
	    - trans_func : must be a (Lx1) array
	    - CDF : must be a CDF of a grayscaled input
	
# How to define default parameters
--
