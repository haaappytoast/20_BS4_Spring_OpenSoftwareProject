# name of Project
- Uniform Mean Filter on BGR image

# Purpose of this code
- when image is given in BGR as "input", filter it with the 'Uniform Mean Filter'. 
- You can choose one of 3 ways of processing pixels which are on image boundaries :
1. Mirroring
2. Zero-padding
3. Adjusting kernel filtering



# How to run this code
- code is written in C++ and uses visual studio 2019 as IDE
- requires opencv installed(OpenCV version : 2.4.13.6)
    to use opencv you should include the below code on the top of the codes
	#include <opencv2/opencv.hpp>
- to use mathametical equations you should include the below code on the top of the ocdes
	#include <math.h>
-to count time, you should include the below code on the top of the ocdes
	 #include <chrono>

# How to adjust parameters (if any)
	Mat meanfilter(const Mat input, int n, const char* opt);
	    - input : must be a BGR image
	    - n : integer. The parameter which determines the kernel size. The size of kernel will be (2*n-1) x (2*n-1)
	    - opt : the way of processing pixels which are on image boundaries.
		there are 3 options to write down
		1. "mirroring"
		2. "zero-paddle"
		3. "adjustkernel"

# How to define default parameters
	line 43: 	output = gaussianfilter(input, 5,1,1, "adjustkernel");
	    - in 2nd parameter, I chose '5'. if you want to scale up or down the kernel size, you can change it to any other integer greater than 0.
- in 3rd,4th parameter, I chose '1' for both. if you want to blur the image more, you can increase these values
	    - in 5th parameter, I chose the 'adjustkernel' option. you can choose other options if you want.

