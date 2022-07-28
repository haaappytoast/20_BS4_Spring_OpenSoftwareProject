# Project name
rotating images

#purpose of the project
with this code, you can rotate colored images with data type of CV_8UC3, counterclockwise

#How to run this code (requirements)
code is written in C++ and uses visual studio 2019 as IDE
requires opencv installed

to use opencv you should include the below code on the top of the codes
	#include <opencv2/opencv.hpp>


#how to adjust parameters
line 40,
    Mat myrotate(const Mat input, float angle, const char* opt)
        - input : input you want to rotate
        - angle : how many degrees you want to rotate in counterclockwise (unit : arc degree)
        - opt : you can choose either "bilinear" or "nearest" as an interpolation method

#how to define default parameter
line 27,	
    rotated = myrotate<Vec3b>(input, 45, "bilinear");
        - you can change parameters here to change degrees you want to rotate, or the interpolation method