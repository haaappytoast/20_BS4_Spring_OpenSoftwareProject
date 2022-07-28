# name of Project
- Denoising the Gaussian Noise whiched is added on Grayscale&BGR images using Bilateral Filter

# Purpose of this code
- when image is given in BGR as "input", make a grayscale image with the input and add Gaussian Noise to both of images.  And, filter them with Bilateral Filter to Denoise them.
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
1.	Mat Add_Gaussian_noise(const Mat input, double mean, double sigma);
	    - input : BGR or Grayscale image (the image should include gaussian noise)
	    - mean : mean of gaussian noise distribution
	    - sigma : sigma of gaussian noise distribution

2. 	Mat Bilateralfilter_Gray(const Mat input, int n, double sigma_t, double sigma_s, double sigma_r, const char* opt);
	    - input : must be a grayscaled image (the image should include gaussian noise)
	    - n : positive integer. The parameter which determines the kernel size. The size of kernel will be (2*n-1) x (2*n-1)
	    - sigma_t, sigma_s : positive double. each is for standard deviation for x-axis, and y-axis
	    - sigma_r : positive double, r is standard deviation for the Gaussian Distribution with intensity Distance
	    - opt : the way of processing pixels which are on image boundaries.
		there are 3 options to write down
		1. "mirroring"
		2. "zero-paddle"
		3. "adjustkernel"

3.	Mat Bilateralfilter_RGB(const Mat input, int n, double sigma_t, double sigma_s, double sigma_r, const char* opt);
	    - input : must be a RGB image (the image should include gaussian noise)
	    - other parameters are all same with 1.

# How to define default parameters
1. 	line 31 : Mat noise_Gray = Add_Gaussian_noise(input_gray, 0, 0.1);
	line 32 : Mat noise_RGB = Add_Gaussian_noise(input, 0, 0.1);
	        - '0' is commly selected as the mean of gaussian distribution
	        - 0.1 : if you scale it up, the noise gets more noisy

2. 	Mat Denoised_Gray = Bilateralfilter_Gray(noise_Gray, 2, 10, 10, 10, "zero-padding");
	Mat Denoised_RGB = Bilateralfilter_RGB(noise_RGB, 2, 10, 10, 10, "zero-padding");

	     -in 2nd parameter, I chose '2'. if you want to scale up or down the kernel size, you can change it to any other integer greater than 0.
- in 3rd,4th parameter, I chose '10' for both. if you want to blur the image more to denoise it, you can increase these values
	    - in 6th parameter, I chose the 'zero-padding' option. you can choose other options if you want.