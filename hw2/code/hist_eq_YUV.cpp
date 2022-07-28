#include "hist_func.h"

void hist_eq(Mat& input, Mat& equalized, G* trans_func, float* CDF);

int main() {

	Mat input = imread("input.jpg", CV_LOAD_IMAGE_COLOR);
	Mat equalized_YUV;

	cvtColor(input, equalized_YUV, CV_BGR2YUV);	// BGR -> YUV

	// split each channel(Y, U, V)
	Mat channels[3];
	split(equalized_YUV, channels);
	Mat Y = channels[0];						// U = channels[1], V = channels[2]

	// PDF or transfer function txt files
	FILE* f_equalized_PDF_YUV, * f_PDF_BGR;
	FILE* f_trans_func_eq_YUV;

	float** PDF_BGR = cal_PDF_BGR(input);		// PDF of Input image(RGB) : [L][3]
	float* CDF_YUV = cal_CDF(Y);				// CDF of Y channel image

	fopen_s(&f_PDF_BGR, "PDF_BGR.txt", "w+");
	fopen_s(&f_equalized_PDF_YUV, "equalized_PDF_YUV.txt", "w+");
	fopen_s(&f_trans_func_eq_YUV, "trans_func_eq_YUV.txt", "w+");

	G trans_func_eq_YUV[L] = { 0 };			// transfer function

	// histogram equalization on Y channel
	hist_eq(Y, Y, trans_func_eq_YUV, CDF_YUV);

	// merge Y, U, V channels
	merge(channels, 3, equalized_YUV);	// 담긴 배열, 배열의크기(3채널), 결과를 담을 곳

	// YUV -> RGB (use "CV_YUV2BGR" flag)
	cvtColor(equalized_YUV,equalized_YUV ,CV_YUV2BGR);

	// equalized PDF (YUV)
	float** equalized_PDF_YUV = cal_PDF_BGR(equalized_YUV);

	for (int i = 0; i < L; i++) {
		//write PDF
		fprintf(f_PDF_BGR, "%d\t%f\t%f\t%f\n", i, PDF_BGR[i][0], PDF_BGR[i][1], PDF_BGR[i][2]);
		fprintf(f_equalized_PDF_YUV, "%d\t%f\t%f\t%f\n", i, equalized_PDF_YUV[i][0], equalized_PDF_YUV[i][1], equalized_PDF_YUV[i][2]);

		// write transfer functions
		fprintf(f_trans_func_eq_YUV, "%d\t%d\n", i, trans_func_eq_YUV[i]);

	}

	// memory release
	free(PDF_BGR);
	free(CDF_YUV);
	fclose(f_PDF_BGR);
	fclose(f_equalized_PDF_YUV);
	fclose(f_trans_func_eq_YUV);

	////////////////////// Show each image ///////////////////////

	namedWindow("BGR", WINDOW_AUTOSIZE);
	imshow("BGR", input);

	namedWindow("Equalized_YUV", WINDOW_AUTOSIZE);
	imshow("Equalized_YUV", equalized_YUV);

	//////////////////////////////////////////////////////////////

	waitKey(0);

	return 0;
}

// histogram equalization
void hist_eq(Mat& input, Mat& equalized, G* trans_func, float* CDF) {

	// compute transfer function
	for (int i = 0; i < L; i++)
		trans_func[i] = (G)((L - 1) * CDF[i]);

	// perform the transfer function
	for (int i = 0; i < input.rows; i++)
		for (int j = 0; j < input.cols; j++)
			equalized.at<G>(i, j) = trans_func[input.at<G>(i, j)];
}