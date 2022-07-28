#include "SIFT.cpp"
#include "stitching.cpp"
#include <iostream>

int main() {
	// 이미지 불러들이기
	Mat input1 = imread("input1.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input2 = imread("input2.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input1_gray, input2_gray;

	if (!input1.data || !input2.data)
	{
		std::cout << "Could not open" << std::endl;
		return -1;
	}

	//SIFT로 keypoint들 찾기 p.srcPoints와 p.dstPoints에 저장된다.
		// 이때, standard = true일 경우는 SIFT의 NN을 할 때, I1 -> I2를 한 것
		// standard = false: SIFT의 NN을 할 때, I2 -> I1을 한것
	bool standard =false;
	matched_points p = SIFT_mine(input1, input2, standard);

	vector<double> ptl_x;
	vector<double> ptl_y;
	vector<double> ptr_x;
	vector<double> ptr_y;

	//stitching하기 위해 왼쪽이미지와 오른쪽이미지의 각각의 x,y좌표에 대한 값을 모두 분리시켜 vector에 저장
	if(standard == true){
		for (int i = 0; i < p.srcPoints.size(); i++) {
			ptl_x.push_back(p.srcPoints[i].x);
			ptl_y.push_back(p.srcPoints[i].y);
			ptr_x.push_back(p.dstPoints[i].x);
			ptr_y.push_back(p.dstPoints[i].y);
		}
	}
	else if (standard == false) {
		for (int i = 0; i < p.srcPoints.size(); i++) {
			ptl_x.push_back(p.dstPoints[i].x);
			ptl_y.push_back(p.dstPoints[i].y);
			ptr_x.push_back(p.srcPoints[i].x);
			ptr_y.push_back(p.srcPoints[i].y);
		}
	}


	implement_stitching(input1, input2, ptl_x, ptl_y, ptr_x, ptr_y);
	

	return 0;

}