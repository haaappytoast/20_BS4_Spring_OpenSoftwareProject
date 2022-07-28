# name of Project
- Harris corner detector

# Purpose of this code
- 내장함수 cornerHarris()를 사용하여 harris response R을 구하고 그 R을 사용하여, input에 corner을 표시해준다. 이때, non-maximum suppression과 cornerSubpixel()함수를 사용한 결과도 볼 수 있다.

# How to run this code
- code is written in C++ and uses visual studio 2019 as IDE
- requires opencv installed(OpenCV version : 2.4.13.6)
    to use opencv you should include the below code on the top of the codes
	#include <opencv2/opencv.hpp>

# How to adjust parameters (if any)
	cornerHarris(input, output, blockSize, apertureSize, k, BORDER_DEFAULT);
	input : 무조건  1) single-channel 8-bit or 2) floating-point image. 중 하나이어야한다.
	output : harris response R을 담고 있다.
	k와 BORDER_DEFAULT는 이미 defualt가 정해져 있으므로 굳이 값을 넣어주지 않아도 상관없다.



# How to define default parameters
line 43:		bool NonMaxSupp = true;
		    true/false 둘 중 하나의 값을 택하여non-maximum suppression을 할지 말지를 정할 수 있다.

line 47:		bool Subpixel = true;
		    true/false 둘 중 하나의 값을 택하여 cornersubPixel()을 적용할지 말지를 정할 수 있다. cornersubPixel()을 거치면 더 정교한 corner을 얻는다.
