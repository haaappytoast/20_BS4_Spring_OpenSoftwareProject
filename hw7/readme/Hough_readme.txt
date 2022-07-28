# name of Project
- Hough Transformation

# Purpose of this code
- Perform Hough Transformation by using HoughLines() or using HoughLinesP()

# How to run this code
- code is written in C++ and uses visual studio 2019 as IDE
- requires opencv installed(OpenCV version : 2.4.13.6)
    to use opencv you should include the below code on the top of the codes
	#include <opencv2/opencv.hpp>
- 콘솔창에서 수행하기 위해 다음 라이브러리를 추가해야한다.
	#include "stdafx.h"
- 여러 연산들을 하기 위해 추가해야할 라이브러리
	#include <ctime>
	#include <cmath>
	#include <vector>

# How to adjust parameters (if any)
1. line 30:		HoughLines(dst, lines, rho, theta, threshold, srn, stn);

dist: 8-bit 이미지이고, 이는 GrayScale image이어야 한다. 
lines: output vector of lines은 검출된 직선들의 rho와 theta를 포함한다.
rho: Distance resolution of the accumulator in pixels이다. 즉, hough space에서 rho값을 얼만큼씩 증가시키면서 조사하겠냐는 뜻이다.
theta: 단위는 라디안. 직선의 유일성을 위해, 180도를 넘지 않도록 [0:180] 사이의 범위로 입력해야한다
threshold: accumulator threshold parameter로 threshold를 넘는 line들만 return된다.
srn: default = 0; rho의 divisor이다. 만약에 0으로 두지 않는다면 둘다, positive이어야한다.
stn: default = 0; theta의 divisor이다.


2. line 46:	 HoughLinesP(dst, lines, 1, theta, threshold, minLineLength=0, maxLineGap);

- dist, lines, rho, theta, threshold는 모두 1.의 HoughLines()와 같다.

minLineLength:  line segment의 길이의 최소값이다. 만약 line segment가 이보다 작다면 reject 된다.
maxLineGap: 같은 line에서 연결시켜줄 점들의 최소 허용 거리(Gap)이다.

1,2의 파라미터들은 실험적으로 모두 바꿔가면서 가장 잘 나오는 값을 사용한다.