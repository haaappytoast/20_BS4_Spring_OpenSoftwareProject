#include "SIFT.cpp"
#include "stitching.cpp"
#include <iostream>

int main() {
	// �̹��� �ҷ����̱�
	Mat input1 = imread("input1.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input2 = imread("input2.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input1_gray, input2_gray;

	if (!input1.data || !input2.data)
	{
		std::cout << "Could not open" << std::endl;
		return -1;
	}

	//SIFT�� keypoint�� ã�� p.srcPoints�� p.dstPoints�� ����ȴ�.
		// �̶�, standard = true�� ���� SIFT�� NN�� �� ��, I1 -> I2�� �� ��
		// standard = false: SIFT�� NN�� �� ��, I2 -> I1�� �Ѱ�
	bool standard =false;
	matched_points p = SIFT_mine(input1, input2, standard);

	vector<double> ptl_x;
	vector<double> ptl_y;
	vector<double> ptr_x;
	vector<double> ptr_y;

	//stitching�ϱ� ���� �����̹����� �������̹����� ������ x,y��ǥ�� ���� ���� ��� �и����� vector�� ����
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