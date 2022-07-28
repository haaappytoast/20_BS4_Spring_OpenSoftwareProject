# name of Project
- Denoising the salt and pepper Noise whiched is added on Grayscale&BGR images using median Filter

# Purpose of this code
- when image is given in BGR as "input", make a grayscale image with the input and add salt and pepper Noise to both of images. And, filter them with median Filter to Denoise them.
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
1.	Mat Salt_pepper_noise_removal_Gray(const Mat input, int n, const char *opt);
	    - input : must be a grayscaled image (it must include salt and pepper noise)
	    - n : positive integer. The parameter which determines the kernel size. The size of kernel will be (2*n-1) x (2*n-1)
	    - opt : the way of processing pixels which are on image boundaries.
		there are 3 options to write down
		1. "mirroring"
		2. "zero-paddle"
		3. "adjustkernel"


2. 	Mat Gaussianfilter_BGR(const Mat input, int n, double sigma_t, double sigma_s, const char *opt);
	    - input : must be a BGR image (it must include salt and pepper noise)
	    - other parameters are all same with 1.


3.	Mat Add_salt_pepper_Noise(const Mat input, float ps, float pp);
	    - input : BGR or Grayscale image (the image should include gaussian noise)
	    - ps : salt noise(intensity 255)의 비율 [0~1]
	    - pp : pepper noise(intensity 0)의 비율 [0~1]


# How to define default parameters
 	line 30 : Mat noise_Gray = Add_salt_pepper_Noise(input_gray, 0.3f, 0.3f);
	line 31 : Mat noise_RGB = Add_salt_pepper_Noise(input, 0.3f, 0.3f);
	       
	    - 2nd, 3rd parameter : 값이 증가할수록 noisy해지기 때문에 median filter를 적용해도 효과가 떨어질 수 있다. 적당한 값을 넣는 것이 중요하다. 0.1f이면 충분하다고 생각함.

