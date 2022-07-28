# name of Project
- histogram equalization on BGR image (equalize on Y channel only)

# Purpose of this code
- when image is given in BGR as "input", convert it to YUV channel, and equalize the image of only Y channel. the code generates PDF of BGR image, equalized BGR image(on Y channel) and linear transfer function as txt files seperately


# How to run this code
- code is written in C++ and uses visual studio 2019 as IDE
- requires opencv installed(OpenCV version : 2.4.13.6)
    to use opencv you should include the below code on the top of the codes
	#include <opencv2/opencv.hpp>
- requires including "hist_func.h"
    you shoud include the below code on the top of the codes
	#include "hist_func.h"

# How to adjust parameters (if any)
	- void hist_eq(Mat& input, Mat& equalized, G* trans_func, float* CDF);
	    - input : must be a Y channel of BGR image. Size of matrix must be (Lx1)
	    - equalized : output of after doing HE on Y channel. In my code I put Y, same Matrix as input but if you want to save in another Matrix, you have to assign another matrix such as "Mat after_eq"
	    - trans_func : must be a (Lx1) array
	    - CDF : must be a CDF of a Y channel of BGR image, must be a (Lx1) array
	