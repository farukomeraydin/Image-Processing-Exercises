#define _CRT_SECURE_NO_WARNINGS
#include "Image.h"

using namespace std;

int main()
{
	/*Adim-1'de Figure304 için Negatif Transformun yapildigi kod*/
	/*Image input, output;
	
	char inputName[] = "Fig0304(a)(breast_digital_Xray).pgm";
	char outputName[] = "Fig0304(b)(breast_digital_Xray).pgm";
	input.readImage(inputName);

	output = input.NegativeTransform(input);
	output.writeImage(outputName);*/

	/*Adim-1'de Figure305 için Log Transformun yapildigi kod*/
	/*Image input, output;

	char inputName[] = "Fig0305(a)(DFT_no_log).pgm";
	char outputName[] = "Fig0305(b)(DFT_no_log).pgm";
	input.readImage(inputName);

	output = input.LogTransform(input);
	output.writeImage(outputName);*/

	/*Adim-1'de Figure308 için Gamma Correction yapildigi kod*/
	/*Image input, output;

	char inputName[] = "Fig0308(a)(fractured_spine).pgm";
	char outputName1[] = "Fig0308(b)(fractured_spine).pgm";
	char outputName2[] = "Fig0308(c)(fractured_spine).pgm";
	char outputName3[] = "Fig0308(d)(fractured_spine).pgm";

	input.readImage(inputName);
	output = input.GammaCorrection(input, 0.6f);
	output.writeImage(outputName1);

	input.readImage(inputName);
	output = input.GammaCorrection(input, 0.4f);
	output.writeImage(outputName2);

	input.readImage(inputName);
	output = input.GammaCorrection(input, 0.3f);
	output.writeImage(outputName3);*/

	/*Adim-1'de Figure309 için Gamma Correction yapildigi kod*/
	/*Image input, output;

	char inputName[] = "Fig0309(a)(washed_out_aerial_image).pgm";
	char outputName1[] = "Fig0309(b)(washed_out_aerial_image).pgm";
	char outputName2[] = "Fig0309(c)(washed_out_aerial_image).pgm";
	char outputName3[] = "Fig0309(d)(washed_out_aerial_image).pgm";

	input.readImage(inputName);
	output = input.GammaCorrection(input, 3.0f);
	output.writeImage(outputName1);

	input.readImage(inputName);
	output = input.GammaCorrection(input, 4.0f);
	output.writeImage(outputName2);

	input.readImage(inputName);
	output = input.GammaCorrection(input, 5.0f);
	output.writeImage(outputName3);*/

	/*Adim-1'de Figure0333 için Averaging Filter yapildigi kod*/
	/*Image input, output;
	char inputName[] = "Fig0333(a)(test_pattern_blurring_orig).pgm";
	char outputName1[] = "Fig0333(b)(test_pattern_blurring_orig).pgm";
	char outputName2[] = "Fig0333(c)(test_pattern_blurring_orig).pgm";
	char outputName3[] = "Fig0333(d)(test_pattern_blurring_orig).pgm";
	char outputName4[] = "Fig0333(e)(test_pattern_blurring_orig).pgm";
	char outputName5[] = "Fig0333(f)(test_pattern_blurring_orig).pgm";

	input.readImage(inputName);
	output = input.AveragingFilter(input,3);
	output.writeImage(outputName1);

	input.readImage(inputName);
	output = input.AveragingFilter(input, 5);
	output.writeImage(outputName2);

	input.readImage(inputName);
	output = input.AveragingFilter(input, 9);
	output.writeImage(outputName3);

	input.readImage(inputName);
	output = input.AveragingFilter(input, 15);
	output.writeImage(outputName4);

	input.readImage(inputName);
	output = input.AveragingFilter(input, 35);
	output.writeImage(outputName5);*/

	/*Adim-1'de Figure0335 için Averaging Filter yapildigi kod*/
	/*Image input, output;
	char inputName[] = "Fig0335(a)(ckt_board_saltpep_prob_pt05).pgm";
	char outputName[] = "Fig0335(b)(ckt_board_saltpep_prob_pt05).pgm";

	input.readImage(inputName);
	output = input.MedianFilter(input);
	output.writeImage(outputName);*/

	/*Adim-2'de Kontrast sorunu olan 3 resmin düzenlenmesi*/
	/*Image input1, output1, input2, output2, input3, output3;

	char inputName1[] = "ContrastIssue1.pgm";
	char outputName1[] = "ContrastIssue1_Output.pgm";

	char inputName2[] = "ContrastIssue2.pgm";
	char outputName2[] = "ContrastIssue2_Output.pgm";

	char inputName3[] = "ContrastIssue3.pgm";
	char outputName3[] = "ContrastIssue3_Output.pgm";

	input1.readImage(inputName1);
	output1 = input1.NegativeTransform(input1);
	output1.writeImage(outputName1);

	input2.readImage(inputName2);
	output2 = input1.GammaCorrection(input2, 1.5f);
	output2.writeImage(outputName2);

	input3.readImage(inputName3);
	output3 = input3.MedianFilter(input3);
	output3.writeImage(outputName3);*/
}



