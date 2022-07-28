# name of Project
- filtering the Grayscale image with Laplacian of Gaussian Filter

# Purpose of this code
- when image is given in BGR as "input", make a grayscale image first. And then filter the input with Gaussian Filter. Finally filter the input with the Laplacian Filter. Then, you can get the edge of the image.
- the image boundary processing is mirroring for both Gaussian filter and laplacian filter

# How to run this code
- code is written in C++ and uses visual studio 2019 as IDE
- requires opencv installed(OpenCV version : 2.4.13.6)
    to use opencv you should include the below code on the top of the codes
	#include <opencv2/opencv.hpp>


# How to adjust parameters (if any)
1.	Mat get_Gaussian_Kernel(int n, double sigma_t, double sigma_s, bool normalize);
	    - input : must be a grayscaled image
	    - sigma_t, sigma_s : positive double. each is for standard deviation for x-axis, and y-axis
	    - normalize : bool type. whether you want to normalize or not


2. 	Mat Gaussianfilter(const Mat input, int n, double sigma_t, double sigma_s);
	    - input : must be a grayscaled image
	    - n : positive integer. the kernel size will be (2n+1)  x (2n+1)
	    - sigma_t, sigma_s : positive double. each is for standard deviation for x-axis, and y-axis


# How to define default parameters
...

