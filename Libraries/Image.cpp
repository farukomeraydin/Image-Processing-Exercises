#define _CRT_SECURE_NO_WARNINGS
/**********************************************************
 The original copy of the code can be found at http://web.eecs.utk.edu/~mkarakay/courses_files/testfiles.zip
 and it is modified for ELM463/667

 * Image.cpp - the image library which implements
 *             the member functions defined in Image.h
 *
 * Author: Hairong Qi, ECE, University of Tennessee
 *
 * Created: 02/05/02
 *
 * Copyright (C) hqi@utk.edu
 **********************************************************/

#include "Image.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <complex>

using namespace std;

/**
 * Default constructor.
 */
Image::Image() {
    image = NULL;
    nrows = 0;
    ncols = 0;
    maximum = 255;
    //createImage(0, 0);
}

/**
 * Constructor for grayscale images.
 * @param nrows Numbers of rows (height).
 * @param ncols Number of columns (width).
 * @return The created image.
 */
Image::Image(int nRows, int nCols) {
    if (nRows <= 0 || nCols <= 0) {
        cout << "Image: Index out of range.\n";
        exit(3);
    }
    image = NULL;
    createImage(nRows, nCols);
}

/**
 * Copy constructor.
 * @param img Copy image.
 * @return The created image.
 */
Image::Image(const Image& img) {
    int rows, cols;

    image = NULL;
    nrows = img.getRow();
    ncols = img.getCol();
    createImage(nrows, ncols);             // allocate memory

    for (rows = 0; rows < nrows; rows++)
        for (cols = 0; cols < ncols; cols++)
            image[rows * ncols + cols] = img(rows, cols);
}

/**
 * Destructor.  Frees memory.
 */
Image::~Image() {
    if (image)
        delete[] image;       // free the image buffer
}






/**
 * Allocate memory for the image and initialize the content to be 0.
 */
void Image::createImage() {

    if (image != NULL)
        delete[] image;

    maximum = 255;

    image = (float*) new float[nrows * ncols];
    if (!image) {
        cout << "CREATEIMAGE: Out of memory.\n";
        exit(1);
    }

    initImage();
}


/**
 * Allocate memory for the image and initialize the content to be zero.
 * @param r Numbers of rows (height).
 * @param c Number of columns (width).
 */
void Image::createImage(int numberOfRows, int numberOfColumns) {

    if (image != NULL)
        delete[] image;

    nrows = numberOfRows;
    ncols = numberOfColumns;
    maximum = 255;

    image = (float*) new float[nrows * ncols];
    if (!image) {
        cout << "CREATEIMAGE: Out of memory.\n";
        exit(1);
    }

    initImage();
}

/**
 * Initialize the image.
 * @para init The value the image is initialized to. Default is 0.0.
 */
void Image::initImage(float initialValue) {
    int i;

    for (i = 0; i < nrows * ncols; i++)
        image[i] = initialValue;
}

/**
 * Returns the total number of rows in the image.
 * @return Total number of rows.
 * \ingroup getset
 */
int Image::getRow() const {
    return nrows;
}

/**
 * Returns the total number of columns in the image.
 * @return Total number of columns.
 * \ingroup getset
 */
int Image::getCol() const {
    return ncols;
}

/**
 * Returns the maximum pixel value of a gray-level image.
 * @return The intensity of that pixel.
 * \ingroup getset
 */
float Image::getMaximum() const {
    int i, j;
    float maxi = -10000;


    for (i = 0; i < nrows; i++)
        for (j = 0; j < ncols; j++)
            if (maxi < image[i * ncols + j])
                maxi = image[i * ncols + j];

    return maxi;
}


/**
 * Returns the minimum pixel value of the image.
 * @return The minimum pixel value.
 * \ingroup getset
 */
float Image::getMinimum() const {
    int i, j;
    float mini = 10000;

    for (i = 0; i < nrows; i++)
        for (j = 0; j < ncols; j++)
            if (mini > image[i * ncols + j])
                mini = image[i * ncols + j];

    return mini;
}



/**
 * Returns the pixel value at rows, cols
 * @return The pixel value
 * \ingroup getset
 */
float Image::getPix(int rows, int cols) {
    return image[rows * ncols + cols];
}


/**
 * Returns the image.
 * @return a gray-scale image
 * \ingroup getset
 */
Image Image::getImage() const {
    Image temp;
    int rows, cols;

    temp.createImage(nrows, ncols);   // temp is a gray-scale image
    for (rows = 0; rows < nrows; rows++)
        for (cols = 0; cols < ncols; cols++)
            temp(rows, cols) = image[rows * ncols + cols];

    return temp;
}

/**
 * Sets the total number of rows in an image.
 * @param r Total number of rows.
 * \ingroup getset
 */
void Image::setRow(int numberOfRows) {
    nrows = numberOfRows;
}

/**
 * Sets the total number of columns in an image.
 * @param c Total number of columns.
 * \ingroup getset
 */
void Image::setCol(int numberOfColumns) {
    ncols = numberOfColumns;
}


/**
 * Sets the pixel value at rows,cols.
 * @param row and col index.
 * \ingroup getset
 */
void Image::setPix(int rows, int cols, float value) {
    image[rows * ncols + cols] = value;
}


/**
 * Sets the image given a grayscale image.
 * \ingroup getset
 */
void Image::setImage(Image& img) {
    int rows, cols;

    for (rows = 0; rows < nrows; rows++)
        for (cols = 0; cols < ncols; cols++)
            image[rows * ncols + cols] = img(rows, cols);
}

/**
 * Overloading () operator
 * \ingroup overload
 * @param i Row
 * @param j Column
 */
float& Image::operator()(int rows, int cols) const {
    return image[rows * ncols + cols];
}

/**
 * Overloading = operator.
 * \ingroup overload
 * @param img Image to copy.
 * @return Newly copied image.
 */
const Image Image::operator=(const Image& img) {
    int rows, cols;

    if (this == &img)
        return *this;

    nrows = img.getRow();
    ncols = img.getCol();
    createImage(nrows, ncols);

    for (rows = 0; rows < nrows; rows++)
        for (cols = 0; cols < ncols; cols++)
            (*this)(rows, cols) = img(rows, cols);

    return *this;
}

/**
 * Overloading + operator.
 * \ingroup overload
 * @param img Image to add to specified image.
 * @return Addition of the two images.
 */
Image Image::operator+(const Image& img) const {
    int i, j, nr, nc;
    Image temp;

    nr = img.getRow();
    nc = img.getCol();

    if (nr != nrows || nc != ncols) {
        cout << "operator+: "
            << "Images are not of the same size or type, can't do addition\n";
        exit(3);
    }
    temp.createImage(nrows, ncols);

    for (i = 0; i < nrows; i++)
        for (j = 0; j < ncols; j++)
            temp(i, j) = image[i * ncols + j] + img(i, j);

    return temp;
}

/**
 * Overloading - operator.
 * \ingroup overload
 * @param img Image to subtract from specified image.
 * @return Subtraction of the two images.
 */
Image Image::operator-(const Image& img) const {
    int i, j, nr, nc;
    Image temp;

    nr = img.getRow();
    nc = img.getCol();

    if (nr != nrows || nc != ncols) {
        cout << "operator-: "
            << "Images are not of the same size or type, can't do subtraction\n";
        exit(3);
    }
    temp.createImage(nrows, ncols);

    for (i = 0; i < nrows; i++)
        for (j = 0; j < ncols; j++)
            temp(i, j) = image[i * ncols + j] - img(i, j);

    return temp;
}

/**
 * Overloading * operator.  This function does pixel by pixel multiplication.
 * \ingroup overload
 * @param img Image to multiply with specified image.
 * @return Multiplication of the two images.
 */
Image Image::operator*(const Image& img) const {
    int i, j, nr, nc;
    Image temp;

    nr = img.getRow();
    nc = img.getCol();

    if (nr != nrows || nc != ncols) {
        cout << "operator*: "
            << "Images are not of the same size or type, can't do multiplication\n";
        exit(3);
    }
    temp.createImage(nrows, ncols);

    for (i = 0; i < nrows; i++)
        for (j = 0; j < ncols; j++)
            temp(i, j) = image[i * ncols + j] * img(i, j);

    return temp;
}

/**
 * Overloading / operator.  This function does pixel by pixel division.
 * Specified image is the dividend.
 * \ingroup overload
 * @param img Image to be divided (divisor).
 * @return Quotient of the two images.
 */
Image Image::operator/(const Image& img) const {
    int i, j, nr, nc;
    Image temp;

    nr = img.getRow();
    nc = img.getCol();

    if (nr != nrows || nc != ncols) {
        cout << "operator/: "
            << "Images are not of the same size or type, can't do division\n";
        exit(3);
    }
    temp.createImage(nrows, ncols);

    for (i = 0; i < nrows; i++)
        for (j = 0; j < ncols; j++)
            temp(i, j) = image[i * ncols + j] / (img(i, j) + 0.001);

    return temp;
}


/**
 * Overloading << operator.  Output the image to the specified destination.
 * \ingroup overload
 * @param out The specified output stream (or output destination).
 * @param img Image to be output.
 * @result Output image to the specified file destination.
 */
ostream& operator<<(ostream& out, Image& img) {
    int rows, cols;


    for (rows = 0; rows < img.getRow(); rows++) {
        for (cols = 0; cols < img.getCol(); cols++)
            out << setw(4) << img(rows, cols) << ' ';
        out << endl;
    }

    return out;
}

/**
 * Overloading / operator.  The left operand is the image and the right
 * is the dividend (a double point number). Each pixel in the image is
 * divided by the double point number.
 * \ingroup overload
 * @param img Image as the left operand.
 * @param val A double point number as the right operand.
 * @result Image divided by a double point number.
 */
Image operator/(Image& img, double val) {
    int i, j, nr, nc;
    Image temp;

    nr = img.getRow();
    nc = img.getCol();
    temp.createImage(nr, nc);

    for (i = 0; i < nr; i++)
        for (j = 0; j < nc; j++)
            temp(i, j) = img(i, j) / val;

    return temp;
}

/**
 * Overloading * operator.  The left operand is the image and the right
 * is a double point number. Each pixel in the image is multiplied by the
 * double point number.
 * \ingroup overload
 * @param img Image as the left operand.
 * @param s A double point number as the right operand.
 * @result Image multiplied by a double point scalar.
 */
Image operator*(Image& img, double s) {
    int i, j, nr, nc;
    Image temp;

    nr = img.getRow();
    nc = img.getCol();
    temp.createImage(nr, nc);

    for (i = 0; i < nr; i++)
        for (j = 0; j < nc; j++)
            temp(i, j) = img(i, j) * s;

    return temp;
}


/**
 * Overloading + operator.  The left operand is the image and the right
 * is a double point number. Each pixel in the image is added by the
 * double point number.
 * \ingroup overload
 * @param img Image as the left operand.
 * @param s A double point number as the right operand.
 * @result Image add a double point scalar.
 */
Image operator+(Image& img, double s) {
    int i, j, nr, nc;
    Image temp;

    nr = img.getRow();
    nc = img.getCol();
    temp.createImage(nr, nc);

    for (i = 0; i < nr; i++)
        for (j = 0; j < nc; j++)
            temp(i, j) = img(i, j) + s;

    return temp;
}

/**
 * Overloading - operator.  The left operand is the image and the right
 * is a double point number. Each pixel in the image is subtracted by the
 * double point number.
 * \ingroup overload
 * @param img Image as the left operand.
 * @param s A double point number as the right operand.
 * @result Image subtract a double point scalar.
 */
Image operator-(Image& img, double s) {
    int i, j, nr, nc;
    Image temp;

    nr = img.getRow();
    nc = img.getCol();
    temp.createImage(nr, nc);

    for (i = 0; i < nr; i++)
        for (j = 0; j < nc; j++)
            temp(i, j) = img(i, j) - s;

    return temp;
}

/**
 * Read image from a file
 * @param fname The name of the file
 * @return An Image object
 */
void Image::readImage(char* fname) {
    ifstream ifp;
    char dummy[80];
    unsigned char* img;
    int rows, cols;
    int nRows, nCols, nt, maxi;

    ifp.open(fname, ios::in | ios::binary);

    if (!ifp) {
        cout << "readImage: Can't read image: " << fname << endl;
        exit(1);
    }

    // identify image format
    ifp.getline(dummy, 80, '\n');

    if (dummy[0] == 'P' && dummy[1] == '5')
        ;
    else {
        cout << "readImage: Can't identify image format." << endl;
        exit(1);
    }

    // skip the comments
    ifp.getline(dummy, 80, '\n');

    while (dummy[0] == '#') {
        ifp.getline(dummy, 80, '\n');
    }

    // read the row number and column number
    sscanf(dummy, "%d %d", &nCols, &nRows);

    // read the maximum pixel value
    ifp.getline(dummy, 80, '\n');
    sscanf(dummy, "%d", &maxi);
    if (maxi > 255) {
        cout << "Don't know what to do: maximum value is over 255.\n";
        exit(1);
    }

    if (image != NULL)
        delete[] image;

    nrows = nRows;
    ncols = nCols;
    maximum = 255;

    // read the image data
    img = (unsigned char*) new unsigned char[nRows * nCols];
    if (!img) {
        cout << "READIMAGE: Out of memory.\n";
        exit(1);
    }
    image = (float*) new float[nRows * nCols];
    if (!image) {
        cout << "READIMAGE: Out of memory.\n";
        exit(1);
    }

    ifp.read((char*)img, (nRows * nCols * sizeof(unsigned char)));

    for (rows = 0; rows < nRows; rows++)
        for (cols = 0; cols < nCols; cols++)
            image[rows * nCols + cols] = (float)img[rows * nCols + cols];

    ifp.close();

    delete[] img;
}


/**
 * Write image buffer to a file.
 * @param fname The output file name.
 */
void Image::writeImage(char* fname, bool flag) {
    ofstream ofp;
    int i, j;
    int nRows, nCols, nt;
    unsigned char* img;

    ofp.open(fname, ios::out | ios::binary);

    if (!ofp) {
        cout << "writeImage: Can't write image: " << fname << endl;
        exit(1);
    }


    ofp << "P5" << endl;
    ofp << ncols << " " << nrows << endl;


    ofp << 255 << endl;



    // convert the image data type back to unsigned char
    img = (unsigned char*) new unsigned char[nrows * ncols];
    if (!img) {
        cout << "WRITEIMAGE: Out of memory.\n";
        exit(1);
    }

    float maxi = getMaximum();
    float mini = getMinimum();


    for (i = 0; i < nrows; i++)
        for (j = 0; j < ncols; j++) {
            // rescale if the flag is set
            if ((maxi != mini) && flag == true)
                img[i * ncols + j] = (unsigned char)((image[i * ncols + j] - mini) / (float)(maxi - mini) * 255.0);
            // any intensity that is larger than the maximum would be set as maximum
            else if (image[i * ncols + j] > 255)
                img[i * ncols + j] = 255;
            else if (image[i * ncols + j] < 0)
                img[i * ncols + j] = 0;
            else
                img[i * ncols + j] = (unsigned char)image[i * ncols + j];
        }

    ofp.write((char*)img, (nrows * ncols * sizeof(unsigned char)));


    ofp.close();
    delete[] img;
}




// YOUR FUNCTIONS

/**
 * Returns the image.
 * @return a gray-scale image
 * \ingroup getset
 */
Image Image::thresholdImage(float thresholdValue, float lowValue, float highValue) {
    Image temp;
    int rows, cols;

    temp.createImage(nrows, ncols);   // temp is a gray-scale image
    for (rows = 0; rows < nrows; rows++)
        for (cols = 0; cols < ncols; cols++)
            if (image[rows * ncols + cols] <= thresholdValue)
                temp(rows, cols) = lowValue;
            else
                temp(rows, cols) = highValue;


    return temp;
}

Image Image::ThresholdFunc(int th) {
    Image temp;
    temp.createImage(nrows, ncols);
    int rows, cols;
    for (rows = 0; rows < nrows; rows++)
        for (cols = 0; cols < ncols; cols++)
            if (image[rows * ncols + cols] < th)
                temp(rows, cols) = 0;
            else
                temp(rows, cols) = 255;
    return temp;
}

/*Lab-0 Problem1 için yazilan Fonksiyon*/
Image Image::CreateGrayScaleImage(void) {
    Image temp;
    int nrows = 10;
    int ncols = 15;
    int initial_pixel = 50; //Sol üst pikselin degeri
    temp.createImage(nrows, ncols);
    int rows, cols;
    for (rows = 0; rows < nrows; rows++)
        for (cols = 0; cols < ncols; cols++) {
            temp(rows, cols) = initial_pixel; //Baslangiç degeri burada atanir.
            ++initial_pixel; //Her turda 1 arttirilir
            if (cols % (ncols - 1) == 0 && cols != 0) // Eger satir sonuna gelinmisse
                initial_pixel = temp(rows, 0) + 1; //Satir basindaki piksel degerine 1 eklenir ve alt satirdan 1 artttirilarak deger verilmeye devam edilir

        }
    return temp;
}


/*Lab-0 Problem2 için yazilan Fonksiyon*/
Image Image::RescaleSize(Image input, float scale) {
    Image temp;
    int nrows = input.getRow(); //Okunan görüntünün satir sayisi
    int ncols = input.getCol();//Okunan görüntünün sütun sayisi
    temp.createImage(scale * nrows, scale * ncols); //Ölçege göre okunan görüntünün satir ve sütun sayisi çarpilarak yeni görüntü olusturulur.
    for (int x = 0; x < scale * nrows; ++x)
        for (int y = 0; y < scale * ncols; ++y)
            temp.setPix(x, y, 0.0f); //Bu yeni üretilen görüntünün tüm piksellerine önce sifir atanir.

    int rows, cols;
    for (rows = 0; rows < scale * nrows; rows++)
        for (cols = 0; cols < scale * ncols; cols++)
            temp(rows, cols) = input.getPix(rows / scale, cols / scale); //Scale 1den küçükse downsample büyükse upsample yapilir.

    return temp;
}

/*Lab1-Adim1 için Negatif Transform Fonksiyonu*/
Image Image::NegativeTransform(Image input) {
    Image temp;
    int rows = input.getRow();
    int cols = input.getCol();

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            input(i, j) = 255 - input.getPix(i, j); //Piksel degerini 255'e tamamlayan degerini elde etmek için 255'den çikariyoruz

    temp = input;
    return temp;
}

/*Lab1-Adim1 için Log Transform Fonksiyonu*/
Image Image::LogTransform(Image input) {
    Image temp;
    int rows = input.getRow();
    int cols = input.getCol();
    float c = (float)255 / log10(1 + input.getMaximum()); //Log transformasyonunda c sabitini yalniz biraktik

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            input(i, j) = c * log10(1 + input.getPix(i, j)); //Log transformasyon formülünün uygulanmasi

    temp = input;
    return temp;
}

/*Lab-1 Adim 1 için Gamma Correction Fonksiyonu*/
Image Image::GammaCorrection(Image input, float gamma) {
    Image temp;
    int rows = input.getRow();
    int cols = input.getCol();
    float c = (float)255 / pow(input.getMaximum(), gamma); //Gamma correction formülünde c'yi yalniz biraktik

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            input(i, j) = c * pow(input.getPix(i, j), gamma); //Gamma correction formülünü uyguladik

    temp = input;
    return temp;
}

/*Lab-1 Adim 1 için Average Filtering*/
Image Image::AveragingFilter(Image input, int squareMaskSize) {
    Image temp = input;
    int rows = input.getRow();
    int cols = input.getCol();
    float maskValue = (float)1 / ((squareMaskSize) * (squareMaskSize)); //Örnegin kare filtre 5x5 ise her deger 1/25 olacak
    float maskSum = .0f; //Kare filtreyi skaler çarptiktan sonra toplam sonuç bu degiskende tutulacak

    for (int i = 1; i < rows; i++) //i ve j degerleri indeks hatasi almamak için 1 degerinden baslar
        for (int j = 1; j < cols; j++) {
            for (int k = (squareMaskSize - 1) / 2; k >= -(squareMaskSize - 1) / 2; k--) // Filtre 3x3 ise 1 yukari ve 1 asagi satirlara bakariz. Genel formüldür.
                for (int m = (squareMaskSize - 1) / 2; m >= -(squareMaskSize - 1) / 2; m--)
                    maskSum += input(i - k, j - m) * maskValue;
            input(i, j) = maskSum;
            maskSum = 0; //Islem bitince toplami sifirlayip tekrardan hesaplariz.
        }

    temp = input;
    return temp;
}

/*Bubble sortingde kullanilacak hazir swap fonksiyonu*/
void swap(float* p1, float* p2) {
    float temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}


/*Bubble sorting fonksiyonu*/
void bsort(float* p, size_t size) {
    for (size_t i = 0; i < size - 1; ++i)
        for (size_t k = 0; k < size - 1; ++k)
            if (p[k] > p[k + 1])
                swap(p + k, p + k + 1);
}

/*Lab-1 Adim 1 için Median Filtering*/
Image Image::MedianFilter(Image input) {
    Image temp = input;
    int rows = input.getRow();
    int cols = input.getCol();

    float temp2[9]; //Siraladigimiz matrixdeki degerleri bu arrayde depolayacagiz. 9 elemanli çünkü filtremiz 3x3
    int p = 0;

    for (int i = 1; i < rows; i++)
        for (int j = 1; j < cols; j++) {
            for (int k = 1; k >= -1; k--)
                for (int m = 1; m >= -1; m--)
                    temp2[p++] = input(i - k, j - m); //3x3 matrix degerlerini vektörde topladik

            bsort(temp2, 9); //bubble sorting yaptik
            p = 0; //Indexi sifirladik
            temp(i, j) = temp2[4]; //Orta degeri atadik
        }

    return temp;
}

/*Lab-2 için Histogram Equalization fonksiyonu*/
Image Image::HistogramEqualization(Image input) {
    Image temp;
    temp = input;
    int nrows = input.getRow();
    int ncols = input.getCol();
    int hr[256] = { 0 };
    float Pr[256] = { 0.0f };
    float Tr[256] = { 0.0f };

    for (int i = 0; i < nrows; ++i)
        for (int j = 0; j < ncols; j++)
            for (int k = 0; k < 256; k++)
                if (input(i, j) == k)// Her piksel degerinden kaç tane varsa hr arrayinde o elemani 1 arttiriyoruz.
                    ++hr[k];

    for (int i = 0; i < 256; i++)
        Pr[i] = (float)hr[i] / (nrows * ncols); //Elde ettigimiz degerleri toplam piksel sayisina bölüyoruz

    float sum = 0.0f;

    for (int i = 0; i < 256; i++) {
        for (int j = 0; j <= i; j++)
            sum += Pr[j]; //Daha sonra cdf degerlerini kümülatif sekilde toplayarak gidiyoruz. Her toplama bitince toplam degiskeni sifirlanmali.
        Tr[i] = sum;
        sum = 0.0f;
    }

    for (int i = 0; i < 256; i++)
        Tr[i] *= 255;//Ayni dinamik aralikta olabilmesi için 0-1 araligini 0-255 yapiyoruz.


    for (int i = 0; i < nrows; ++i)
        for (int j = 0; j < ncols; j++)
            for (int k = 0; k < 256; k++)
                if (input(i, j) == k)
                    temp(i, j) = (int)((Tr[k] > 0 ? .5 : -.5) + Tr[k]); //Float degerleri yuvarliyoruz.Piksel degerlerimizin hiçbiri negatif degil ama yine de negatifi de yuvarlasin diye ternary operatörü kullandim.

    return temp;

}

/*Lab-2 Adim 3 için keskinlestirme fonksiyonu*/
Image Image::Mask3x3(Image input, float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22) {
    Image temp; //Bu fonksiyona girdigimiz 9 eleman mask'imizin her satirda soldan saga elemanlaridir.
    temp = input;
    int nrows = input.getRow();
    int ncols = input.getCol();
    float mask[3][3] = { m00, m01, m02, m10, m11, m12, m20, m21, m22 };

    for (int i = 1; i < nrows; ++i)
        for (int j = 1; j < ncols; ++j) //Buradaki for döngüsü içinde mask görüntü boyunca skaler çarpimlari toplanarak kaydirilmistir.
            temp(i, j) = input(i - 1, j - 1) * mask[0][0] + input(i - 1, j) * mask[0][1] +
            input(i - 1, j + 1) * mask[0][2] + input(i, j - 1) * mask[1][0] + input(i, j) * mask[1][1] +
            input(i, j + 1) * mask[1][2] + input(i + 1, j - 1) * mask[2][0] + input(i + 1, j) * mask[2][1] +
            input(i + 1, j + 1) * mask[2][2];

    return temp;
}

Image Image::GaussianFilter5x5(Image input, float k) {
    Image temp;
    temp = input;
    int nrows = input.getRow();
    int ncols = input.getCol();
    float mask[5][5] = { {0.0318f, 0.0375f, 0.0397f, 0.0375f, 0.0318f}, //Burada olusturulan kitapta söylendigi üzere 5x5 sigma=3 olan Gaussian filtresidir.
                         {0.0375f, 0.0443f, 0.0469f, 0.0443f, 0.0375f}, //Bu matriks matlabda fspecial('gaussian', [5 5], 3) çagrisi ile olusturulup cpp'ye kopyalanmistir.
                         {0.0397f, 0.0469f, 0.0495f, 0.0469f, 0.0397f},
                         {0.0375f, 0.0443f, 0.0469f, 0.0443f, 0.0375f},
                         {0.0318f, 0.0375f, 0.0397f, 0.0375f, 0.0318f} };

    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j) //Buradaki for döngüsü g(x,y) = f(x,y) + k*mask formülünde k katsayisini kullanmak için olusturulmustur.
            mask[i][j] *= k;

    for (int i = 2; i < nrows; ++i)
        for (int j = 2; j < ncols; ++j) //Buradaki for döngüsü içinde mask görüntü boyunca skaler çarpimlari toplanarak kaydirilmistir.
            temp(i, j) = input(i - 2, j - 2) * mask[0][0] + input(i - 2, j - 1) * mask[0][1] +
            input(i - 2, j) * mask[0][2] + input(i - 2, j + 1) * mask[0][3] + input(i - 2, j + 2) * mask[0][4] +
            input(i - 1, j - 2) * mask[1][0] + input(i - 1, j - 1) * mask[1][1] + input(i - 1, j) * mask[1][2] +
            input(i - 1, j + 1) * mask[1][3] + input(i - 1, j + 2) * mask[1][4] + input(i, j - 2) * mask[2][0] +
            input(i, j - 1) * mask[2][1] + input(i, j) * mask[2][2] + input(i, j + 1) * mask[2][3] + input(i, j + 2) * mask[2][4] +
            input(i + 1, j - 2) * mask[3][0] + input(i + 1, j - 1) * mask[3][1] + input(i + 1, j) * mask[3][2] +
            input(i + 1, j + 1) * mask[3][3] + input(i + 1, j + 2) * mask[3][4] + input(i + 2, j - 2) * mask[4][0] +
            input(i + 2, j - 1) * mask[4][1] + input(i + 2, j) * mask[4][2] + input(i + 2, j + 1) * mask[4][3] + input(i + 2, j + 2) * mask[4][4];

    return temp;
}

/*Kompleks degerlerin real ve imag terimlerini saklamak için structure olusturuldu.*/
typedef struct Complex {
    double real;
    double imag;
}Complex;

/*Lab-3 fonksiyonlari*/
Image Image::FT(Image input) {
    int nrows = input.getRow();
    int ncols = input.getCol();
    /*Hafizayi gereksiz yere mesgul etmemek adina asagida pd ve pd2 isimli Complex türünde matriksler dinamik hafizada olusturulmustur. Elde
    edilecek degerler bu matrikslerde saklanacak.*/

    Complex** pd = (Complex**)malloc(nrows * sizeof(Complex*)); //Olusturulacak matriksin satir sayisinin dinamik hafiza tahsisi
    if (!pd) {
        printf("Hafizada yer yok\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < nrows; ++i) { //Olusturulacak matriksin her satirinda sütun sayisinin dinamik hafiza tahsisi
        pd[i] = (Complex*)malloc(ncols * sizeof(Complex));
        if (!pd[i]) {
            printf("Hafizada yer yok\n");
            exit(EXIT_FAILURE);
        }
    }

    Complex** pd2 = (Complex**)malloc(nrows * sizeof(Complex*));//Olusturulacak matriksin satir sayisinin dinamik hafiza tahsisi
    if (!pd2) {
        printf("Hafizada yer yok\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < nrows; ++i) { //Olusturulacak matriksin her satirinda sütun sayisinin dinamik hafiza tahsisi
        pd2[i] = (Complex*)malloc(ncols * sizeof(Complex));
        if (!pd2[i]) {
            printf("Hafizada yer yok\n");
            exit(EXIT_FAILURE);
        }
    }

    /*Asagidaki iç içe 3 for döngüsü, kitaptaki 4.11-2 denklemini gerçeklestirir. Önce tüm satirlarin 1 boyutlu DFT'si alinir.
    önce tum sutunlar dolasildigi icin en icteki dongu y, ncols'a kadar döner.En distaki for dongusu ise exponansiyeldeki v degiskeni olmalidir.
    elde edilen degerler, satir guncellenmeden dinamik pd matriksinde saklanir. Bu 3 for döngünün cikisinda F(x,v) elde edilir.*/
    for (int v = 0; v < ncols; ++v) {
        for (int x = 0; x < nrows; ++x) {
            double real = 0;
            double imag = 0;
            for (int y = 0; y < ncols; ++y) {
                double theta = 2 * PI * y * v / ncols;
                real += input(x, y) * cos(theta);  //4.11 - 2 denklemini gerçeklestirir.Real bir görüntüyü ele aliriz.
                imag += -input(x, y) * sin(theta);
            }
            pd[x][v].real = real;
            pd[x][v].imag = imag;
        }
    }

    /*Asagidaki iç içe 3 for döngüsü, kitaptaki 4.11-1 denklemini gerçeklestirir. Önce tüm sutunlarin 1 boyutlu DFT'si alinir.
önce tum satirlar dolasildigi icin en icteki dongu x, nrows'a kadar döner.En distaki for dongusu ise exponansiyeldeki u degiskeni olmalidir.
elde edilen degerler, sutun guncellenmeden dinamik pd2 matriksinde saklanir. Bu 3 for döngünün cikisinda F(u,v) elde edilir.*/

    for (int u = 0; u < nrows; ++u) {
        for (int v = 0; v < ncols; ++v) {
            double real = 0;
            double imag = 0;
            for (int x = 0; x < nrows; ++x) {
                double theta = 2 * PI * x * u / nrows;
                real += pd[x][v].real * cos(theta) + pd[x][v].imag * sin(theta); //4.11 - 2 denklemini gerçeklestirir. Ancak artik real ve imag
                imag += -pd[x][v].real * sin(theta) + pd[x][v].imag * cos(theta); //terimleri olan bir goruntuyu ele aldigimiz icin 4 terimli bir islem yapilir.
            }
            pd2[u][v].real = real;
            pd2[u][v].imag = imag;
        }
    }

    /*Artik dinamik hafizadaki pd matriksiyle isimiz bittigi için burada tüm satirlari free edilir.*/
    for (size_t i = 0; i < nrows; ++i)
        free(pd[i]);

    free(pd);

    Image output;
    //Fourier sonucu elde edilecek görüntü Mx2N olacak. Ilk N sütunda real degerler, N-2N sutunlari arasinda imag degerleri bulunacak.
    output.createImage(nrows, 2 * ncols);
    for (int i = 0; i < nrows; i++)
        for (int j = 0; j < ncols; j++)//0-N sutunlarina real degerler ataniyor.
            output(i, j) = pd2[i][j].real;

    int k;
    for (int i = 0; i < nrows; i++)
        for (int j = ncols, k = 0; j < 2 * ncols; j++, k++)//N-2N sutunlarina imag degerler ataniyor.
            output(i, j) = pd2[i][k].imag;


    for (size_t i = 0; i < nrows; ++i)/*Artik dinamik hafizadaki pd2 matriksiyle isimiz bittigi için burada tüm satirlari free edilir.*/
        free(pd2[i]);

    free(pd2);

    return output;
}
Image Image::Abs(Image input) {
    Image output_ft;
    int nrows = input.getRow();
    int ncols = input.getCol();
    output_ft.createImage(nrows, ncols / 2); //Genlik degerlerini barindiran görüntü tekrardan MxN olmalidir. Girdi ise Mx2N görüntüsüdür.
    int p;
    /*Buradaki for dongulerinde genlik hesaplanmistir. Real kisma karsilik gelen imag degeri ncols/2 kadar uzaktadir. Dolayisiyla sutun indexine
    ncols/2 eklenmistir. 3. degisken olarak p indeksi N sayisina kadar donerek ciktidaki görüntünün sutun indeksini ifade eder.
    Diger taraftan j indeksi ise imag degerlerine ulasabilmek icin 2N degerine kadar doner.*/
    for (int i = 0; i < nrows; i++)
        for (int j = 0, p = 0; p < ncols / 2, j < ncols; j++, p++)
            output_ft(i, p) = sqrt(input(i, j) * input(i, j) + input(i, j + ncols / 2) * input(i, j + ncols / 2));

    return output_ft;
}

Image Image::IFT(Image input) {
    int nrows = input.getRow();
    int ncols = input.getCol();
    /*Hafizayi gereksiz yere mesgul etmemek adina asagida pd, pd2 ve pd3 isimli Complex türünde matriksler dinamik hafizada olusturulmustur. Elde
edilecek degerler bu matrikslerde saklanacak.*/
    Complex** pd = (Complex**)malloc(nrows * sizeof(Complex*));//Olusturulacak matriksin satir sayisinin dinamik hafiza tahsisi
    if (!pd) {
        printf("Hafizada yer yok\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < nrows; ++i) {
        pd[i] = (Complex*)malloc((ncols / 2) * sizeof(Complex));//Olusturulacak matriksin her satirinda sütun sayisinin dinamik hafiza tahsisi
        if (!pd[i]) {
            printf("Hafizada yer yok\n");
            exit(EXIT_FAILURE);
        }
    }

    Complex** pd2 = (Complex**)malloc(nrows * sizeof(Complex*));//Olusturulacak matriksin satir sayisinin dinamik hafiza tahsisi
    if (!pd2) {
        printf("Hafizada yer yok\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < nrows; ++i) {//Olusturulacak matriksin her satirinda sütun sayisinin dinamik hafiza tahsisi
        pd2[i] = (Complex*)malloc((ncols / 2) * sizeof(Complex));
        if (!pd2[i]) {
            printf("Hafizada yer yok\n");
            exit(EXIT_FAILURE);
        }
    }

    Complex** pd3 = (Complex**)malloc(nrows * sizeof(Complex*));//Olusturulacak matriksin satir sayisinin dinamik hafiza tahsisi
    if (!pd3) {
        printf("Hafizada yer yok\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < nrows; ++i) {//Olusturulacak matriksin her satirinda sütun sayisinin dinamik hafiza tahsisi
        pd3[i] = (Complex*)malloc((ncols / 2) * sizeof(Complex));
        if (!pd3[i]) {
            printf("Hafizada yer yok\n");
            exit(EXIT_FAILURE);
        }
    }

    /*Buradaki 2 for dongusunde girdi goruntusundeki real degerler dinamik hafizadaki pd matriksinin real kisminda saklanir.*/
    for (int i = 0; i < nrows; ++i)
        for (int j = 0; j < ncols / 2; ++j) {
            pd[i][j].real = input(i, j);
        }
    /*Buradaki 2 for dongusunde girdi goruntusundeki imag degerler dinamik hafizadaki pd matriksinin imag kisminda saklanir.*/
    for (int i = 0; i < nrows; ++i)
        for (int j = 0; j < ncols / 2; ++j) {
            pd[i][j].imag = input(i, j + ncols / 2); //j + ncols/2 yapilmasinin sebebi daha once belirtildigi üzere real kisma karsilik gelen imag degerinin ncols/2 uzaklikta olmasi. Girdi görüntüsünün Mx2N oldugu unutulmamalidir.
        }

    /*Asagidaki iç içe 3 for döngüsü, kitaptaki 4.11-2 denklemini tersten gerçeklestirir. F(x,v) burada elde edilir. Dikkat edilmesi gereken
    girdinin Mx2N olmasidir ve real-imag terimlerini bulundurmasidir. Bu yüzden en bastan beri real-imag görüntüyü ele almamiz gerektiginden
    for donguleri icinde 4 terimli toplam vardir.Ayrica e üzeri +j ile artik carpildigi icin isaretler eksi olur. for dongulerinde sutun indeksinin
    ncols/2'ye kadar donmesinin sebebi Mx2N girdi goruntusunun MxN goruntuye donusmesi gerektigi icindir. Ayrica elde ettigimiz degerleri satir bilgisi
    guncellenmeden pd2 isimli matrikste saklariz.*/

    for (int v = 0; v < ncols / 2; ++v) {
        for (int x = 0; x < nrows; ++x) {
            double real = 0;
            double imag = 0;
            for (int y = 0; y < ncols / 2; ++y) {
                double theta = 2 * PI * y * v / (ncols / 2);
                real += pd[x][y].real * cos(theta) + pd[x][y].imag * (-sin(theta));
                imag += pd[x][y].real * sin(theta) + pd[x][y].imag * cos(theta);
            }
            pd2[x][v].real = real;
            pd2[x][v].imag = imag;
        }
    }

    /*Artik dinamik hafizadaki pd matriksiyle isimiz bittigi için burada tüm satirlari free edilir.*/
    for (size_t i = 0; i < nrows; ++i)
        free(pd[i]);

    free(pd);

    /*Asagidaki iç içe 3 for döngüsü, elde ettigimiz F(x,v)'yi kullanarak f(x,y) elde eder. Dikkat edilmesi gereken
girdinin Mx2N olmasidir ve real-imag terimlerini bulundurmasidir. Bu yüzden real-imag görüntüyü ele almamiz gerektiginden
for donguleri icinde 4 terimli toplam vardir.Ayrica e üzeri +j ile artik carpildigi icin isaretler eksi olur. for dongulerinde sutun indeksinin
ncols/2'ye kadar donmesinin sebebi Mx2N girdi goruntusunun MxN goruntuye donusmesi gerektigi icindir. Ayrica elde ettigimiz degerleri satir bilgisi
guncellenmeden pd3 isimli matrikste saklariz.*/

    for (int u = 0; u < nrows; ++u) {
        for (int v = 0; v < ncols / 2; ++v) {
            double real = 0;
            double imag = 0;
            for (int x = 0; x < nrows; ++x) {
                double theta = 2 * PI * x * u / nrows;
                real += pd2[x][v].real * cos(theta) + pd2[x][v].imag * (-sin(theta));
                imag += pd2[x][v].real * sin(theta) + pd2[x][v].imag * cos(theta);
            }
            pd3[u][v].real = real;
            pd3[u][v].imag = imag;
        }
    }

    /*Artik dinamik hafizadaki pd2 matriksiyle isimiz bittigi için burada tüm satirlari free edilir.*/
    for (size_t i = 0; i < nrows; ++i)
        free(pd2[i]);

    free(pd2);

    Image output;
    output.createImage(nrows, ncols / 2); //Girdi goruntumuz Mx2n idi.Cikti goruntusu ise MxN olmali.
    for (int i = 0; i < nrows; i++)
        for (int j = 0; j < ncols / 2; j++)
            output(i, j) = pd3[i][j].real / (nrows * ncols / 2);// Burada ise pd3 matrisinde saklanan real degerler artik cikti goruntusune ataniyor. imag degerlerin toplami sifir yaptigi icin kullanmaya gerek yoktur. Ayrica tum degerler 4.11-3 denklem geregi MN degerine bolunmustur.

    /*Artik dinamik hafizadaki pd3 matriksiyle isimiz bittigi için burada tüm satirlari free edilir.*/
    for (size_t i = 0; i < nrows; ++i)
        free(pd3[i]);

    free(pd3);

    return output;

}

/*Lab-4 fonksiyonlari*/
Image Image::Scale(Image input) {
    int nrows = input.getRow();
    int ncols = input.getCol();
    float min = input.getMinimum();
    float max = input.getMaximum();
    for (int i = 0; i < nrows; i++)
        for (int j = 0; j < ncols; ++j)
            input(i, j) = 255 * ((input(i, j) - min) / (max-min));

    return input;
}
Image Image::Absolute(Image input) {
    int nrows = input.getRow();
    int ncols = input.getCol();
    for (int i = 0; i < nrows; i++)
        for (int j = 0; j < ncols; j++)
            input(i, j) = input(i, j) < 0 ? -input(i, j) : input(i, j);
    return input;
}

//END OF YOUR FUNCTIONS //


