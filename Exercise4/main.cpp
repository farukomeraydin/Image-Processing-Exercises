#define _CRT_SECURE_NO_WARNINGS
#include "Image.h"
#include <Windows.h>
#include <cmath>

using namespace std;

int main()
{
	/*Lab-3 Problem0 Kodu*/
	Image input1, output1, output1_ft, output1_ift;
	int k = 1;
	input1.createImage(3, 3); //3x3 matriks olusturuldu.
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) { //Bu 2 for döngüsünde matriksi 1 2 3 4 5 6 7 8 9 olarak set ediyoruz.
			input1(i, j) = k;
			++k; //Atama yapildiktan sonra count arttiriliyor.
		}

	output1 = input1.FT(input1);//Fourier transformu aliniyor.

	output1_ft.createImage(input1.getRow(), input1.getCol());
	output1_ft = output1_ft.Abs(output1); //Fourier transformasyonunun genligi alindi.



	printf("Problem0'daki matriksin Fourier sonucu:\n\n");
	for (int i = 0; i < output1.getRow(); i++)
		for (int j = 0; j < output1.getCol() / 2; j++)
			printf("%.3f+(%.3fi)%c", output1(i, j), output1(i, j + input1.getCol()), j % 3 == 2 ? '\n' : ' '); //Fourier sonucu real ve imag degerleri burada print ediyoruz.

	printf("\nProblem0'daki matriksin Fourier sonucu genlikleri:\n\n");
	for (int i = 0; i < output1_ft.getRow(); i++)
		for (int j = 0; j < output1_ft.getCol(); j++)
			printf("%.4f%c", output1_ft(i, j), j % 3 == 2 ? '\n' : ' '); //Buradaki for döngülerinde fourier sonucu genlikleri print ediyoruz.

	output1_ift.createImage(3, 3); //Inverse fourier için 3x3 matriks olusturuyoruz.
	output1_ift = output1.IFT(output1); //Inverse fourier burada aliniyor.

	printf("\n\nTers Fourier ile elde edilen degerler:\n\n");

	for (int i = 0; i < output1_ift.getRow(); i++)
		for (int j = 0; j < output1_ift.getCol(); j++)
			printf("%.2f%c", output1_ift(i, j), j % 3 == 2 ? '\n' : ' '); //Burada inverse fourier sonuçlarini print ediyoruz.

	/*Lab-3 Problem1 kodu*/
	Image input2, output2, output2_ft, input3, output3, output3_ft, input4, output4, output4_ft; //Kullanacagimiz tüm çikti ve girdilerin beyani burada yapiliyor.
	char inputName1[] = "Fig0425(a)(translated_rectangle).pgm";
	char outputName1[] = "Fig0425(b)(translated_rectangle).pgm";
	char inputName2[] = "Fig0425(c)(translated_rectangle).pgm";
	char outputName2[] = "Fig0425(d)(translated_rectangle).pgm";
	char inputName3[] = "Fig0429(a)(blown_ic).pgm";
	char outputName3[] = "Fig0429(b)(blown_ic).pgm";

	input2.readImage(inputName1);
	int input2_rows = input2.getRow();
	int input2_cols = input2.getCol();

	for (int i = 0; i < input2_rows; ++i)
		for (int j = 0; j < input2_cols; ++j) //Buradaki for döngülerinde -1 üzeri x+y ile pikselleri çarparak fftshift yapiyoruz. 
			input2(i, j) *= pow(-1, i + j);

	output2 = input2.FT(input2); //Görüntünün fourieri aliniyor.
	output2_ft.createImage(input2_rows, input2_cols);
	output2_ft = output2_ft.Abs(output2);//Fourier sonucunun spektrumunu görmek için genlikler hesaplaniyor.
	output2_ft = output2_ft.GammaCorrection(output2_ft, 0.2f);//Kitaptaki sekle yakin görmek için gamma correction yapiliyor.
	output2_ft.writeImage(outputName1);

	input3.readImage(inputName2);
	int input3_rows = input3.getRow();
	int input3_cols = input3.getCol();

	for (int i = 0; i < input3_rows; ++i)
		for (int j = 0; j < input3_cols; ++j)//Buradaki for döngülerinde -1 üzeri x+y ile pikselleri çarparak fftshift yapiyoruz.
			input3(i, j) *= pow(-1, i + j);

	output3 = input3.FT(input3);//Görüntünün fourieri aliniyor
	output3_ft.createImage(input3_rows, input3_cols);
	output3_ft = output3_ft.Abs(output3);//Fourier sonucunun spektrumunu görmek için genlikler hesaplaniyor.
	output3_ft = output3_ft.GammaCorrection(output3_ft, 0.5f);//Kitaptaki sekle yakin görmek için gamma correction yapiliyor.
	output3_ft.writeImage(outputName2);

	input4.readImage(inputName3);
	int input4_rows = input4.getRow();
	int input4_cols = input4.getCol();

	for (int i = 0; i < input4_rows; ++i)
		for (int j = 0; j < input4_cols; ++j)//Buradaki for döngülerinde -1 üzeri x+y ile pikselleri çarparak fftshift yapiyoruz.
			input4(i, j) *= pow(-1, i + j);

	output4 = input4.FT(input4);//Görüntünün fourieri aliniyor
	output4_ft.createImage(input4_rows, input4_cols);
	output4_ft = output4_ft.Abs(output4);//Fourier sonucunun spektrumunu görmek için genlikler hesaplaniyor.
	output4_ft = output4_ft.LogTransform(output4_ft);//Kitaptaki sekle yakin görmek için log transform yapiliyor.
	output4_ft.writeImage(outputName3);

	/*Lab-3 Problem2 Kodu*/
	Image output2_ift, output3_ift, output4_ift; // Inverse transform sonucu olusturulacak görüntülerin beyani.
	char outputName1_ift[] = "Fig0425(a_reverted)(translated_rectangle).pgm";
	char outputName2_ift[] = "Fig0425(c_reverted)(translated_rectangle).pgm";
	char outputName3_ift[] = "Fig0429(a_reverted)(blown_ic).pgm";

	output2_ift.createImage(input2_rows, input2_cols);
	output2_ift = output2.IFT(output2); //Inverse transform aliniyor.

	for (int i = 0; i < input2_rows; ++i)
		for (int j = 0; j < input2_cols; ++j)//Inverse transformdan sonra orijinal görüntüyle ayni olmasi için -1 üzeri x+y ile her piksel çarpiliyor.
			output2_ift(i, j) *= pow(-1, i + j);

	output2_ift.writeImage(outputName1_ift);

	output3_ift.createImage(input3_rows, input3_cols);
	output3_ift = output3.IFT(output3);//Inverse transform aliniyor.

	for (int i = 0; i < input3_rows; ++i)
		for (int j = 0; j < input3_cols; ++j)//Inverse transformdan sonra orijinal görüntüyle ayni olmasi için -1 üzeri x+y ile her piksel çarpiliyor.
			output3_ift(i, j) *= pow(-1, i + j);

	output3_ift.writeImage(outputName2_ift);

	output4_ift.createImage(input4_rows, input4_cols);
	output4_ift = output4.IFT(output4);//Inverse transform aliniyor.

	for (int i = 0; i < input4_rows; ++i)
		for (int j = 0; j < input4_cols; ++j)//Inverse transformdan sonra orijinal görüntüyle ayni olmasi için -1 üzeri x+y ile her piksel çarpiliyor.
			output4_ift(i, j) *= pow(-1, i + j);

	output4_ift.writeImage(outputName3_ift);

}



