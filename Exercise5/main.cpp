#define _CRT_SECURE_NO_WARNINGS
#include "Image.h"
#include <cmath>
using namespace std;

int main()
{
	/*Lab-4 Problem1 kodlari*/
	Image input, Laplacian, sharpened, sobel_horizontal, sobel_vertical, sobel_result, smoothed_sobel, mask_form, sharpened2, final;
	/*Burada dosya isimleri tanimlandi*/
	char inputName[] = "Fig0343(a)(skeleton_orig).pgm";
	char outputName1[] = "Fig0343(b)(skeleton_orig).pgm";
	char outputName2[] = "Fig0343(c)(skeleton_orig).pgm";
	char outputName3[] = "Fig0343(d)(skeleton_orig).pgm";
	char outputName4[] = "Fig0343(e)(skeleton_orig).pgm";
	char outputName5[] = "Fig0343(f)(skeleton_orig).pgm";
	char outputName6[] = "Fig0343(g)(skeleton_orig).pgm";
	char outputName7[] = "Fig0343(h)(skeleton_orig).pgm";

	input.readImage(inputName);
	Laplacian.createImage(input.getRow(), input.getCol());
	Laplacian = input.Mask3x3(input, -1, -1, -1, -1, 8, -1, -1, -1, -1);  //Laplacian g�r�nt�s� i�in sekil 3.37(d) maskesi uygulandi
	Laplacian = Laplacian.Scale(Laplacian); //Display etmek i�in 0-255 dinamik araligina getirildi
	Laplacian.writeImage(outputName1);

	/*Keskinlestirme isi i�in Laplacian g�r�nt�s� maskeleme ile tekrar elde edildi ��nk� scale'siz hali lazim*/
	input.readImage(inputName);
	sharpened.createImage(input.getRow(), input.getCol());
	Laplacian = input.Mask3x3(input, -1, -1, -1, -1, 8, -1, -1, -1, -1);

	sharpened = input + Laplacian;//Keskin g�r�nt� elde edildi.
	sharpened.writeImage(outputName2);

	input.readImage(inputName);
	sobel_vertical.createImage(input.getRow(), input.getCol());
	sobel_vertical = input.Mask3x3(input, -1, -2, -1, 0, 0, 0, 1, 2, 1); //Dikey sobel girdi g�r�nt�s�ne uygulandi
	input.readImage(inputName);
	sobel_horizontal.createImage(input.getRow(), input.getCol());
	sobel_horizontal = input.Mask3x3(input, -1, 0, 1, -2, 0, 2, -1, 0, 1);//Yatay sobel girdi g�r�nt�s�ne uygulandi
	sobel_result.createImage(input.getRow(), input.getCol());
	sobel_result = sobel_vertical.Absolute(sobel_vertical) + sobel_horizontal.Absolute(sobel_horizontal); //Dikey ve yatay sobellerin ayri ayri mutlak degerleri toplandi
	sobel_result.writeImage(outputName3);

	smoothed_sobel.createImage(input.getRow(), input.getCol());
	smoothed_sobel = sobel_result.AveragingFilter(sobel_result, 5); //Blur islemi i�in sobel g�r�nt�s� averaj filtresi ile maskelendi
	smoothed_sobel.writeImage(outputName4);

	mask_form.createImage(input.getRow(), input.getCol());
	sharpened.readImage(outputName2);
	smoothed_sobel.readImage(outputName4);
	mask_form = sharpened * smoothed_sobel; //Kitapta s�ylendigi �zere keskinlestirilmis g�r�nt� ile blurl� g�r�nt� �arpildi
	mask_form = mask_form.Scale(mask_form); //Display i�in 0-255 dinamik araligina getirildi.
	mask_form.writeImage(outputName5);

	input.readImage(inputName);
	sharpened2.createImage(input.getRow(), input.getCol());
	mask_form.readImage(outputName5);
	sharpened2 = input + mask_form;//Kitapta s�ylendigi �zere girdi g�r�nt�s� ile maske formundaki g�r�nt� toplandi
	sharpened2.writeImage(outputName6);

	final.createImage(input.getRow(), input.getCol());
	final = sharpened2.GammaCorrection(sharpened2, 0.5); //Kitapta s�ylendigi �zere gamma sabiti 0.5 se�ildi.
	final.writeImage(outputName7);

	/*Lab-4 Problem2 kodlari*/
	Image input_, ft_of_input, H_u_v, laplacian, ift_laplacian, sharpened_, sobel_vertical_, sobel_horizontal_, sobel_result_, smoothed_sobel_, mask_form_, sharpened2_, final_;
	char inputName_[] = "Fig0343(a)(skeleton_orig).pgm";
	char outputName1_[] = "Fig0343(b_ft)(skeleton_orig).pgm";
	char outputName2_[] = "Fig0343(c_ft)(skeleton_orig).pgm";
	char outputName3_[] = "Fig0343(d_ft)(skeleton_orig).pgm";
	char outputName4_[] = "Fig0343(e_ft)(skeleton_orig).pgm";
	char outputName5_[] = "Fig0343(f_ft)(skeleton_orig).pgm";
	char outputName6_[] = "Fig0343(g_ft)(skeleton_orig).pgm";
	char outputName7_[] = "Fig0343(h_ft)(skeleton_orig).pgm";
	input_.readImage(inputName_);
	int nrows = input_.getRow();
	int ncols = input_.getCol();
	for (int i = 0; i < input_.getRow(); i++) //Buradaki for d�ng�leri fftshift yapar
		for (int j = 0; j < input_.getCol(); j++)
			input_(i, j) = input_(i, j) * pow(-1, i + j);

	ft_of_input.createImage(nrows, 2 * ncols);//Fourier sonucu g�r�nt�de reel ve imajinerler tutulmasi i�in Mx2N'lik g�r�nt� olusturuldu
	ft_of_input = input_.FT(input_); //Fourier d�n�s�m� yapildi
	H_u_v.createImage(nrows, ncols);
	for (int u = 0; u < nrows; u++)//Buradaki for d�ng�lerinde H(u,v) fonksiyonu verilen form�le g�re dolduruldu.
		for (int v = 0; v < ncols; v++)
			H_u_v(u, v) = -4 * PI * PI * (pow((u - nrows / 2), 2) + pow((v - ncols / 2), 2));

	laplacian.createImage(nrows, 2 * ncols);
	for (int i = 0; i < nrows; i++)//Buradaki for d�ng�lerinde frekans domaininde H(u,v)*F(u,v) yapildi.F(u,v)'nin real kismiyla �arpildi.
		for (int j = 0; j < ncols; j++)
			laplacian(i, j) = H_u_v(i, j) * ft_of_input(i, j);

	int k;
	for (int i = 0; i < nrows; i++)//Buradaki for d�ng�lerinde frekans domaininde H(u,v)*F(u,v) yapildi.F(u,v)'nin imajiner kismiyla �arpildi.
		for (int j = ncols, k=0; j < 2*ncols; j++,k++)
			laplacian(i, j) = H_u_v(i, k) * ft_of_input(i, j);



	ift_laplacian.createImage(nrows, ncols);
	ift_laplacian = laplacian.IFT(laplacian);// Ters Fourier d�n�s�m� alindi

	for (int i = 0; i < nrows; i++)//Buradaki for d�ng�lerinde ifftshift yapildi
		for (int j = 0; j < ncols; j++)
			ift_laplacian(i, j) = ift_laplacian(i, j) * pow(-1, i + j);
	

	ift_laplacian.writeImage(outputName1_, true);

	input_.readImage(inputName_);
	sharpened_.createImage(nrows, ncols);
	ift_laplacian = input_.Mask3x3(input_, -1, -1, -1, -1, 8, -1, -1, -1, -1);//Laplacian g�r�nt�s� i�in sekil 3.37(d) maskesi uygulandi

	sharpened_ = input_ + ift_laplacian;//Keskin g�r�nt� elde edildi.
	sharpened_.writeImage(outputName2_);

	input_.readImage(inputName_);
	sobel_vertical_.createImage(nrows, ncols);
	sobel_vertical_ = input_.Mask3x3(input_, -1, -2, -1, 0, 0, 0, 1, 2, 1);//Dikey sobel girdi g�r�nt�s�ne uygulandi
	input_.readImage(inputName_);
	sobel_horizontal_.createImage(nrows, ncols);
	sobel_horizontal_ = input_.Mask3x3(input_, -1, 0, 1, -2, 0, 2, -1, 0, 1);//Yatay sobel girdi g�r�nt�s�ne uygulandi
	sobel_result_.createImage(nrows, ncols);
	sobel_result_ = sobel_vertical_.Absolute(sobel_vertical_) + sobel_horizontal_.Absolute(sobel_horizontal_);//Dikey ve yatay sobellerin ayri ayri mutlak degerleri toplandi
	sobel_result_.writeImage(outputName3_);

	smoothed_sobel_.createImage(nrows, ncols);
	smoothed_sobel_ = sobel_result_.AveragingFilter(sobel_result_, 5);//Blur islemi i�in sobel g�r�nt�s� averaj filtresi ile maskelendi
	smoothed_sobel_.writeImage(outputName4_);

	mask_form_.createImage(nrows, ncols);
	sharpened_.readImage(outputName2_);
	smoothed_sobel_.readImage(outputName4_);
	mask_form_ = sharpened_ * smoothed_sobel_;//Kitapta s�ylendigi �zere keskinlestirilmis g�r�nt� ile blurl� g�r�nt� �arpildi
	mask_form_ = mask_form_.Scale(mask_form_);//Display i�in dinamik aralik 0-255 yapildi
	mask_form_.writeImage(outputName5_);

	input_.readImage(inputName_);
	sharpened2_.createImage(nrows, ncols);
	mask_form_.readImage(outputName5_);
	sharpened2_ = input_ + mask_form_;//Kitapta s�ylendigi �zere girdi g�r�nt�s� ile maske formundaki g�r�nt� toplandi
	sharpened2_.writeImage(outputName6_);

	final_.createImage(nrows, ncols);
	final_ = sharpened2_.GammaCorrection(sharpened2_, 0.5);//Kitapta s�ylendigi �zere gamma sabiti 0.5 se�ildi.
	final_.writeImage(outputName7_); 
}



