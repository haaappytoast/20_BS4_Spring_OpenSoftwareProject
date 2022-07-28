#include "hist_func.h"

void hist_eq_Color(Mat& input, Mat& equalized, G(*trans_func)[3], float** CDF);

int main() {

	Mat input = imread("input.jpg", CV_LOAD_IMAGE_COLOR);
	Mat equalized_BGR = input.clone();

	// PDF or transfer function txt files
	FILE* f_equalized_PDF_BGR, * f_PDF_BGR;
	FILE* f_trans_func_eq_BGR;

	fopen_s(&f_PDF_BGR, "PDF_BGR.txt", "w+");
	fopen_s(&f_equalized_PDF_BGR, "equalized_PDF_BGR.txt", "w+");
	fopen_s(&f_trans_func_eq_BGR, "trans_func_eq_BGR.txt", "w+");

	float** PDF_BGR = cal_PDF_BGR(input);	// PDF of Input image(RGB) : [L][3]
	float** CDF_BGR = cal_CDF_BGR(input);	// CDF of Input image(RGB) : [L][3]

	G trans_func_eq_BGR[L][3] = { 0 };		// transfer function

	// histogram equalization on RGB image
	hist_eq_Color(input, equalized_BGR, trans_func_eq_BGR, CDF_BGR);

	// equalized PDF (BGR)
	float** equalized_PDF_BGR = cal_PDF_BGR(equalized_BGR);

	for (int i = 0; i < L; i++) {
		// write PDF
		fprintf(f_PDF_BGR, "%d\t%f\t%f\t%f\n", i, PDF_BGR[i][0], PDF_BGR[i][1], PDF_BGR[i][2]);
		fprintf(f_equalized_PDF_BGR, "%d\t%f\t%f\t%f\n", i, equalized_PDF_BGR[i][0], equalized_PDF_BGR[i][1], equalized_PDF_BGR[i][2]);

		// write transfer functions
		fprintf(f_trans_func_eq_BGR, "%d\t%d\t%d\t%d\n", i, trans_func_eq_BGR[i][0], trans_func_eq_BGR[i][1], trans_func_eq_BGR[i][2]);
	}

	// memory release
	free(PDF_BGR);
	free(CDF_BGR);
	fclose(f_PDF_BGR);
	fclose(f_equalized_PDF_BGR);
	fclose(f_trans_func_eq_BGR);

	////////////////////// Show each image ///////////////////////

	namedWindow("RGB", WINDOW_AUTOSIZE);
	imshow("RGB", input);

	namedWindow("Equalized_BGR", WINDOW_AUTOSIZE);
	imshow("Equalized_BGR", equalized_BGR);

	//////////////////////////////////////////////////////////////

	waitKey(0);

	return 0;
}

// histogram equalization on 3 channel image
void hist_eq_Color(Mat& input, Mat& equalized, G(*trans_func)[3], float** CDF) {

	////////////////////////////////////////////////
	//											  //
	// How to access multi channel matrix element //
	//											  //
	// if matrix A is CV_8UC3 type,				  //
	// A(i, j, k) -> A.at<Vec3b>(i, j)[k]		  //
	//											  //
	////////////////////////////////////////////////
	
	// compute transfer function
	for (int k = 0; k < 3; k++) {
		for (int i = 0; i < L; i++)
			trans_func[i][k] = (G)((L - 1) * CDF[i][k]);
	}

	// perform the transfer function
	for (int k = 0; k < 3; k++) {
		for (int i = 0; i < input.rows; i++)
			for (int j = 0; j < input.cols; j++)
			equalized.at<Vec3b>(i,j)[k] = trans_func[input.at<Vec3b>(i,j)[k]][k];
	}




}