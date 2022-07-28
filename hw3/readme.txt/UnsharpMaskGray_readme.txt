# name of Project
- UnsharpMasking Filter on grayscale image

# Purpose of this code
- when image is given in BGR as "input", convert it to grayscale first, and filter it with the  'UnsharpMasking Filter'. 
- the filter makes an image look sharper by boosting high-frequency components

# How to run this code
- code is written in C++ and uses visual studio 2019 as IDE
- requires opencv installed(OpenCV version : 2.4.13.6)
    to use opencv you should include the below code on the top of the codes
	#include <opencv2/opencv.hpp>
- to use mathametical equations you should include the below code on the top of the ocdes
	#include <math.h>

# How to adjust parameters (if any)
	Mat unsharpmask(const Mat input, int n, float sigmaT, float sigmaS, const char* opt, float k)
	    - input : must be a grayscaled image
	    - n : positive integer. The parameter which determines the kernel size. The size of kernel will be (2*n-1) x (2*n-1)
	    - sigmaT, sigmaS : positive float. each is for standard deviation for x-axis, and y-axis
	    - opt : the way of processing pixels which are on image boundaries.
		there are 3 options to write down
		1. "mirroring"
		2. "zero-paddle"
		3. "adjustkernel"
	    - k : scaling factor of blurred image (0 < k < 1) / the more k is increased, the sharper the output becomes

# How to define default parameters
	line 46: output = unsharpmask(input_gray, 1, 1, 1, "zero-paddle", 0.5);
	    - in 2nd parameter, I chose '1'. if you want to scale up or down the kernel size, you can change it to any other integer greater than 0.
	    - in 3rd,4th parameter, I chose 1 for both. if you want to blur the image more in the middle of the process, you can increase these values
	    - in 4rd parameter, I chose the 'mirroring' option. you can choose other options if you want.

