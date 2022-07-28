# name of Project
- Sobel Filter on grayscale image

# Purpose of this code
- when image is given in BGR as "input", convert it to grayscale first, and filter it with the  'Sobel Filter'. 
- the boundary processing is fixed with : "Mirroring"

# How to run this code
- code is written in C++ and uses visual studio 2019 as IDE
- requires opencv installed(OpenCV version : 2.4.13.6)
    to use opencv you should include the below code on the top of the codes
	#include <opencv2/opencv.hpp>
- to use mathametical equations you should include the below code on the top of the ocdes
	#include <math.h>

# How to adjust parameters (if any)
	- output = sobelfilter(input_gray);
	    -input_gray : the input must be a grayscale image

# How to define default parameters
	--

