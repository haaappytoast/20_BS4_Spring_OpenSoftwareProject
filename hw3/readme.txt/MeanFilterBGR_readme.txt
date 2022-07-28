# name of Project
- Gaussian Filter on color image

# Purpose of this code
- when image is given in BGR as "input", filter it with the 2D 'Gaussian Filter'. 
- You can choose one of 3 ways of processing pixels which are on image boundaries :
1. Mirroring
2. Zero-padding
3. Adjusting kernel filtering

# How to run this code
- code is written in C++ and uses visual studio 2019 as IDE
- requires opencv installed(OpenCV version : 2.4.13.6)
    to use opencv you should include the below code on the top of the codes
	#include <opencv2/opencv.hpp>

# How to adjust parameters (if any)
	Mat gaussianfilter(const Mat input, int n, float sigmaT, float sigmaS, const char* opt);
	    - input : must be a color image
	    - n : positive integer. The parameter which determines the kernel size. The size of kernel will be (2*n-1) x (2*n-1)
	    - sigmaT, sigmaS : positive float. each is for standard deviation for x-axis, and y-axis
	    - opt : the way of processing pixels which are on image boundaries.
		there are 3 options to write down
		1. "mirroring"
		2. "zero-paddle"
		3. "adjustkernel"

# How to define default parameters
	line 42: 	output = gaussianfilter(input, 1,3,3, "mirroring");
	    - in 2nd parameter, I chose '1'. if you want to scale up the kernel size, you can change it to any other integer greater than 0.
	    - in 3rd, 4th parameter, I chose 3 for both. if you want to blur the image more, you can increase these values
	    - in 4rd parameter, I chose the 'mirroring' option. you can choose other options if you want.

