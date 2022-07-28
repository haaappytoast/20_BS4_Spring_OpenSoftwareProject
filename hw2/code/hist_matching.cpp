#include "hist_func.h"
void hist_matching(Mat& input, Mat& matched, G* trans_func_T, G* trans_func_G, G* trans_func_matching, float* CDF_T, float* CDF_G);

int main() {
	Mat input = imread("input.jpg", CV_LOAD_IMAGE_COLOR);
	Mat ref = imread("ref_img.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input_gray;
	Mat ref_gray;

	cvtColor(input, input_gray, CV_BGR2GRAY);	// convert BRG to Grayscale
	cvtColor(ref, ref_gray, CV_BGR2GRAY);		// convert BRG to Grayscale

	Mat matched = input_gray.clone();			// matrix for matched image


	//PDF or transfer function txt files

	FILE* f_PDF;
	FILE* f_PDF_ref_gray;
	FILE* f_matched_PDF_gray;

	FILE* f_trans_func_matching;	// G_inv(T(r))

	fopen_s(&f_PDF, "PDF.txt", "w+");
	fopen_s(&f_PDF_ref_gray, "PDF_ref_gray.txt", "w+");
	fopen_s(&f_matched_PDF_gray, "matched_PDF_gray.txt", "w+");

	fopen_s(&f_trans_func_matching, "trans_func_matching.txt", "w+");

	float* PDF = cal_PDF(input_gray);	// PDF of Input image(Grayscale) : [L]
	float* PDF_ref_gray = cal_PDF(ref_gray);	// PDF of Input image(Grayscale) : [L]

	float* CDF = cal_CDF(input_gray);	// CDF of Input image(Grayscale) : [L]
	float* CDF_ref_gray = cal_CDF(ref_gray);	// CDF of Input image(Grayscale) : [L]

	// transfer function
	G trans_func_T[L] = { 0 };	// s = T(r)
	G trans_func_G[L] = { 0 };	// s = G(z)
	G trans_func_matching[L] = { 0 };	// z = inv_G(T(r))

	hist_matching(input_gray, matched, trans_func_T, trans_func_G, trans_func_matching, CDF, CDF_ref_gray);

	// matched PDF (Gray)
	float* matched_PDF_gray = cal_PDF(matched);


	for (int i = 0; i < L; i++) {
		// write PDF;		
		fprintf(f_PDF, "%d\t%f\n", i, PDF[i]);
		fprintf(f_PDF_ref_gray, "%d\t%f\n", i, PDF_ref_gray[i]);
		fprintf(f_matched_PDF_gray, "%d\t%f\n", i, matched_PDF_gray[i]);

		// write transfer functions
		fprintf(f_trans_func_matching, "%d\t%d\n", i, trans_func_matching[i]);

	}


	free(PDF);
	free(CDF);
	free(PDF_ref_gray);
	free(CDF_ref_gray);

	fclose(f_PDF);
	fclose(f_PDF_ref_gray);
	fclose(f_matched_PDF_gray);
	fclose(f_trans_func_matching);


	////////////////////// Show each image ///////////////////////

	namedWindow("Grayscale", WINDOW_AUTOSIZE);
	imshow("Grayscale", input_gray);

	namedWindow("ref_gray", WINDOW_AUTOSIZE);
	imshow("ref_gray", ref_gray);

	namedWindow("matched", WINDOW_AUTOSIZE);
	imshow("matched", matched);

	//////////////////////////////////////////////////////////////
	waitKey(0);



	return 0;

}

void hist_matching(Mat& input, Mat& matched, G* trans_func_T, G* trans_func_G, G* trans_func_matching, float* CDF_T, float* CDF_G) {
	// compute transfer function T(r), G(r)
	for (int i = 0; i < L; i++) {
		trans_func_T[i] = (G)((L - 1) * CDF_T[i]);
		trans_func_G[i] = (G)((L - 1) * CDF_G[i]);
	}

	G temp[L] = { 0 };
	// compute G^(-1)(s)
	for (int i = 0; i < L; i++) {
		for (int j = 0; j < L; j++) {
			if (trans_func_G[j] == i) {
				temp[i] = j;
				break;
			}
		}
	}
	temp[L - 1] = temp[L - 2];

	for (int i = 1; i < L; i++) {
		if (temp[i] != 0)	continue;

		else {
			temp[i] = temp[i - 1];
		}
	}

	// compute G^(-1)(T(r))
	for (int i = 1; i < L; i++) {
		trans_func_matching[i] = temp[trans_func_T[i]];
	}

	// perform the transfer function
	for (int i = 0; i < input.rows; i++)
		for (int j = 0; j < input.cols; j++)
			matched.at<G>(i, j) = trans_func_matching[input.at<G>(i, j)];
}
