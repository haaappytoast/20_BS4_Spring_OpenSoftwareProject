# name of Project
- histogram stretching

# Purpose of this code
- when image is given in BGR as "input", convert it to grayscale first, and stretch the image. Also it generates PDF of grayscale image, stretched grayscale image and linear transfer function as a txt file seperately


# How to run this code
- code is written in C++ and uses visual studio 2019 as IDE
- requires opencv installed(OpenCV version : 2.4.13.6)
    to use opencv you should include the below code on the top of the codes
	#include <opencv2/opencv.hpp>
- requires including "hist_func.h"
    you shoud include the below code on the top of the codes
	#include "hist_func.h"

# How to adjust parameters (if any)
	void linear_stretching(Mat& input, Mat& stretched, G* trans_func, G x1, G x2, G y1, G y2);
	    - x1, x2 : input pixel ( x1 < x2 )
	    - y1, y2 : output pixel ( y1 < y2 )
	
# How to define default parameters
line 8,
	void linear_stretching(Mat& input, Mat& stretched, G* trans_func, G x1, G x2, G y1, G y2);
	    : (x1, x2) input pixels stretch to (y1, y2) output pixels. So, put appropriate values of start pixel point you want to stretch from and the end pixel point you want to stretch to. (x1, x2, y1, y2) must be all bigger than or same to 0 and less than 256.
