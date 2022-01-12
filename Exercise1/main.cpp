#define _CRT_SECURE_NO_WARNINGS
/**************************************
 The original copy of the code can be found at http://web.eecs.utk.edu/~mkarakay/courses_files/testfiles.zip
 and it is modified for ELM463/667
 **************************************/
#include "Image.h"

using namespace std;

int main(int argc, char** argv)
{

    /*Problem 1 Burada basliyor*/
    Image input1, output1;
    output1 = input1.CreateGrayScaleImage();
    char outName[] = "out.pgm";
    output1.writeImage(outName);
    /*Problem 1 Burada Bitiyor*/
    

    /*Problem 2 Görüntüyü Yariya indirme burada basliyor*/
    Image input2, output2;
    char inputName[] = "Test_image.pgm";
    char outputName1[] = "Out2.pgm";
    input2.readImage(inputName);
    output2 = input2.RescaleSize(input2, 0.5);
    output2.writeImage(outputName1);
    /*Problem 2 Görüntüyü Yariya indirme Burada bitiyor*/


    /*Problem 2 Görüntüyü 2 kati büyütme burada basliyor*/
    Image input3, output3;
    char outputName2[] = "Out3.pgm";
    input3.readImage(inputName);
    output3 = input3.RescaleSize(input3, 2);
    output3.writeImage(outputName2);
    /*Problem 2 Görüntüyü 2 kati büyütme Burada bitiyor*/
}
