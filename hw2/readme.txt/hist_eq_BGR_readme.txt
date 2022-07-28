# name of Project
- histogram equalization of BGR image (equalize on B,G,R channels)

# Purpose of this code
- when image is given in BGR as "input", convert it to YUV channel, equalize it on B, G, R channels seperately. the code generates PDF of BGR image, equalized BGR image(for B, G, R channels) and linear transfer function(for B, G, R channels) as txt files seperately


# How to run this code
- code is written in C++ and uses visual studio 2019 as IDE
- requires opencv installed(OpenCV version : 2.4.13.6)
    to use opencv you should include the below code on the top of the codes
	#include <opencv2/opencv.hpp>
- requires including "hist_func.h"
    you shoud include the below code on the top of the codes
	#include "hist_func.h"

# How to adjust parameters (if any)
	- void hist_eq_Color(Mat& input, Mat& equalized, G(*trans_func)[3], float** CDF);
	    - input : must be a BGR channels of BGR image. Size of matrix must be (Lx3)
	    - trans_func : must be a (Lx3) array (each columns for B, G, R)
	    - CDF : must be a CDF of a B, G, R channels of BGR image, must be a (Lx3) array
	
# How to define default parameters
--
