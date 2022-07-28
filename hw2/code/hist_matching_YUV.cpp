#include "hist_func.h"
void hist_matching(Mat& input, Mat& matched, G* trans_func_T, G* trans_func_G, G* trans_func_matching, float* CDF_T, float* CDF_G);

int main() {
	Mat input = imread("input.jpg", CV_LOAD_IMAGE_COLOR);
	Mat ref = imread("ref_img.jpg", CV_LOAD_IMAGE_COLOR);

	Mat matched_YUV;
	Mat ref_YUV;
	cvtColor(input, matched_YUV, CV_BGR2YUV);	// BGR -> YUV
	cvtColor(ref, ref_YUV, CV_BGR2YUV);		// BGR -> YUV

	// split each channel(Y, U, V) -- matched_YUV
	Mat channels[3];
	split(matched_YUV, channels);
	Mat Y = channels[0];						// U = channels[1], V = channels[2]

	// split each channel(Y, U, V) --- ref_YUV
	Mat channels_ref[3];
	split(ref_YUV, channels_ref);
	Mat ref_Y = channels_ref[0];						// U = channels[1], V = channels[2]

	//PDF or transfer function txt files
	FILE* f_PDF_BGR, *f_PDF_ref_BGR, * f_matched_PDF_YUV;
	FILE* f_trans_func_matching_YUV;	//G_inv(T(r))

	float** PDF_BGR = cal_PDF_BGR(input);	// PDF of Input image(BGR) : [L][3]
	float** PDF_ref_BGR = cal_PDF_BGR(ref);	// PDF of ref image(BGR)

	float* CDF_YUV = cal_CDF(Y);				// CDF of Y channel image
	float* CDF_ref_YUV = cal_CDF(ref_Y);				// CDF of ref_Y channel image

	fopen_s(&f_PDF_BGR, "PDF_BGR.txt", "w+");
	fopen_s(&f_PDF_ref_BGR, "PDF_ref_BGR.txt", "w+");
	fopen_s(&f_matched_PDF_YUV, "matched_PDF_YUV.txt", "w+");
	fopen_s(&f_trans_func_matching_YUV, "trans_func_matching_YUV.txt", "w+");

	// transfer function
	G trans_func_T[L] = { 0 };	// s = T(r)
	G trans_func_G[L] = { 0 };	// s = G(z)
	G trans_func_matching_YUV[L] = { 0 };	// z = inv_G(T(r))

	hist_matching(Y, Y, trans_func_T, trans_func_G, trans_func_matching_YUV, CDF_YUV, CDF_ref_YUV);

	// merge Y, U, V channels
	merge(channels, 3, matched_YUV);	// 담긴 배열, 배열의크기(3채널), 결과를 담을 곳

	// YUV -> RGB (use "CV_YUV2BGR" flag)
	cvtColor(matched_YUV, matched_YUV, CV_YUV2BGR);	

	// matched PDF (YUV)
	float** matched_PDF_YUV = cal_PDF_BGR(matched_YUV);

	for (int i = 0; i < L; i++) {
		// write PDF;		
		fprintf(f_PDF_BGR,"%d\t%f\t%f\t%f\n", i, PDF_BGR[i][0], PDF_BGR[i][1], PDF_BGR[i][2]);
		fprintf(f_PDF_ref_BGR, "%d\t%f\t%f\t%f\n", i, PDF_ref_BGR[i][0], PDF_ref_BGR[i][1], PDF_ref_BGR[i][2]);
		fprintf(f_matched_PDF_YUV, "%d\t%f\t%f\t%f\n", i, matched_PDF_YUV[i][0], matched_PDF_YUV[i][1], matched_PDF_YUV[i][2]);
			
		// write transfer functions
		fprintf(f_trans_func_matching_YUV, "%d\t%d\n", i, trans_func_matching_YUV[i]);
	}

	//memory release
	free(PDF_BGR);
	free(CDF_YUV);
	free(CDF_ref_YUV);
	free(matched_PDF_YUV);

	fclose(f_PDF_BGR);
	fclose(f_PDF_ref_BGR);
	fclose(f_matched_PDF_YUV);
	fclose(f_trans_func_matching_YUV);


	////////////////////// Show each image ///////////////////////

	namedWindow("Grayscale", WINDOW_AUTOSIZE);
	imshow("Grayscale", input);

	namedWindow("ref", WINDOW_AUTOSIZE);
	imshow("ref", ref);

	namedWindow("matched", WINDOW_AUTOSIZE);
	imshow("matched", matched_YUV);

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
