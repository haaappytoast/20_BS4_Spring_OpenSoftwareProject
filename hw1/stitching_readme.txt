# Project name
stitching two colored images

#purpose of the project
with this code, you can stitch two colored images

#How to run this code (requirements)
code is written in C++ and uses visual studio 2019 as IDE
requires opencv installed

to use opencv you should include the below code on the top of the codes
	#include <opencv2/opencv.hpp>


#how to adjust parameters
line 147,
    Mat cal_affine(int ptl_x[], int ptl_y[], int ptr_x[], int ptr_y[], int number_of_points)
        - ptl_x[] : arrays of pixels' x axis location corresponding to the points of left image
        - plt_y[] : arrays of pixels' y axis location corresponding to the points of left image
        - ptr_x[] : arrays of pixels' x axis location corresponding to the points of right image
        - ptr_y[] : arrays of pixels' y axis location corresponding to the points of right image
	if you put other two images to stitch, you should change these parameters since corresponding points of being overlapped are changed