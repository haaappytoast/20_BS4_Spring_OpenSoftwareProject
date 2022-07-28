# name of Project
- PDF_CDF

# Purpose of this code
- when image is given in BGR as "input", convert it to grayscale first, and generate PDF and CDF as a txt file


# How to run this code
- code is written in C++ and uses visual studio 2019 as IDE
- requires opencv installed(OpenCV version : 2.4.13.6)
    to use opencv you should include the below code on the top of the codes
	#include <opencv2/opencv.hpp>
- requires including "hist_func.h"
    you shoud include the below code on the top of the codes
	#include "hist_func.h"

# How to adjust parameters (if any)

# How to define default parameters
line 8,
	Mat input = imread("input.jpg", CV_LOAD_IMAGE_COLOR);
	    - if name of your image file is different to "input" image, change the parameter to the same as your image file's name