# name of Project
- use adaptive threshold on Grayscale image

# Purpose of this code
- when image is given in BGR as "input", convert it to grayscale first, and use adaptive threshold (by using moving average) to make the image binary(0 or 255) 
- You use zero-padding border process on pixels which are on image boundaries


# How to run this code
- code is written in C++ and uses visual studio 2019 as IDE
- requires opencv installed(OpenCV version : 2.4.13.6)
    to use opencv you should include the below code on the top of the codes
	#include <opencv2/opencv.hpp>


# How to adjust parameters (if any)
	Mat adaptive_thres(const Mat input, int n, float b);
	    - input : must be a grayscale image
	    - n : integer. The parameter which determines the kernel size. The size of kernel will be (2*n-1) x (2*n-1)
	    - bnumber : you can put any float between 0 ~ 1 (However, the thresholding works well when it is given between 0.9 ~ 0.98 with document)

# How to define default parameters
	line 33:   output = adaptive_thres(input_gray, 2, 0.8);
	    - in 2nd parameter, I chose '2'. if you want to scale up or down the kernel size, you can change it to any other integer greater than 0.
	    - in 3rd parameter : the default is 0.9 you can change it to any number, practice and choose the best one
