#define _CRT_SECURE_NO_WARNINGS
#include "Image.h"
#include <Windows.h>
using namespace std;

int main()
{
	/*Lab-2 Adim 1 kodlari*/
	Image input1, output1, input2, output2, input3, output3, input4, output4;
	char inputName1[] = "Fig0316(1)(top_left).pgm";
	char outputName1[] = "Fig0316(output)(top_left).pgm";

	char inputName2[] = "Fig0316(2)(2nd_from_top).pgm";
	char outputName2[] = "Fig0316(output)(2nd_from_top).pgm";

	char inputName3[] = "Fig0316(3)(third_from_top).pgm";
	char outputName3[] = "Fig0316(output)(third_from_top).pgm";

	char inputName4[] = "Fig0316(4)(bottom_left).pgm";
	char outputName4[] = "Fig0316(output)(bottom_left).pgm";

	input1.readImage(inputName1);
	output1 = input1.HistogramEqualization(input1);
	output1.writeImage(outputName1);

	input2.readImage(inputName2);
	output2 = input2.HistogramEqualization(input2);
	output2.writeImage(outputName2);

	input3.readImage(inputName3);
	output3 = input3.HistogramEqualization(input3);
	output3.writeImage(outputName3);

	input4.readImage(inputName4);
	output4 = input4.HistogramEqualization(input4);
	output4.writeImage(outputName4);

	/*Lab-2 Adim 2 kodlari*/
	Image chosenInputDark, chosenInputBright, chosenInputContrast, result1, result2, result3;
	char chosenInputNameDark[] = "ChosenInputDark.pgm";
	char chosenInputNameBright[] = "ChosenInputBright.pgm";
	char chosenInputNameContrast[] = "ChosenInputContrast.pgm";
	char resultName1[] = "Result1.pgm";
	char resultName2[] = "Result2.pgm";
	char resultName3[] = "Result3.pgm";

	chosenInputDark.readImage(chosenInputNameDark);
	result1 = chosenInputDark.HistogramEqualization(chosenInputDark);
	result1.writeImage(resultName1);

	chosenInputBright.readImage(chosenInputNameBright);
	result2 = chosenInputBright.HistogramEqualization(chosenInputBright);
	result2.writeImage(resultName2);

	chosenInputContrast.readImage(chosenInputNameContrast);
	result3 = chosenInputContrast.HistogramEqualization(chosenInputContrast);
	result3.writeImage(resultName3);

	/*Lab-2 Adim 3 kodlari*/
	Image input5, output5, input6, output6, input7, output7, input8, output8;
	char inputName[] = "Fig0338(a)(blurry_moon).pgm";
	char outputName5[] = "Fig0338(b)(blurry_moon).pgm";
	char outputName6[] = "Fig0338(c)(blurry_moon).pgm";
	char outputName7[] = "Fig0338(d)(blurry_moon).pgm";
	char outputName8[] = "Fig0338(e)(blurry_moon).pgm";

	input5.readImage(inputName);
	output5 = input5.Sharpen(input5, .0, 1.0, .0, 1.0, -4.0, 1.0, .0, 1.0, .0); //Kitapta kullanilmasi istenen maske:fig.3.37a
	output5.writeImage(outputName5);

	input6.readImage(inputName);
	int rows = input6.getRow();
	int cols = input6.getCol();
	float min = input6.getMinimum();
	float max = input6.getMaximum();
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			input6(i, j) = input6(i, j) - min; //Kitapta verilen 2-6.10 denklemi

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			input6(i, j) = 255 * (input6(i, j) / max); //Kitapta verilen 2-6.11 denklemi

	output6 = input6;
	output6.writeImage(outputName6);

	input7.readImage(inputName);
	output7 = input7.Sharpen(input7, .0, -1.0, .0, -1.0, 5.0, -1.0, .0, -1.0, .0); //Keskinlestirme için uygun maske
	output7.writeImage(outputName7);

	input8.readImage(inputName);
	output8 = input8.Sharpen(input8, -1.0, -1.0, -1.0, -1.0, 9.0, -1.0, -1.0, -1.0, -1.0); //Daha iyi keskinlestirme için uygun maske
	output8.writeImage(outputName8);

	Image input9, output9, output10, output11, output12;
	char inputName9[] = "Fig0340(a)(dipxe_text).pgm";
	char outputName9[] = "Fig0340(b)(dipxe_text).pgm";
	char outputName10[] = "Fig0340(c)(dipxe_text).pgm";
	char outputName11[] = "Fig0340(d)(dipxe_text).pgm";

	input9.readImage(inputName9);
	output9 = input9.GaussianFilter5x5(input9, 1.0f);  //k=1 seçildi.
	output9.writeImage(outputName9);


	input9.readImage(inputName9);
	output10 = input9 - output9; //Kitaptaki 3.6-8 denklemi
	output10.writeImage(outputName10);

	input9.readImage(inputName9);
	output11 = output10 + input9;//Kitaptaki 3.6-9 denklemi
	output11.writeImage(outputName11);

}



