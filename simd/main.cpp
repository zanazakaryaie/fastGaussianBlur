#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>

#include "../Matrix.h"
#include "../memory_management/Gaussian_refinement3.hpp"
#include "Gaussian_refinement4.hpp"

using namespace std;
using namespace cv;

#define ITERATIONS 100

int main()
{
    Mat img = imread("../../image.jpg", 0);
    //resize(img, img, Size(), 2, 2); //Use to see the effect of image size

    Mat img_converted;
    img.convertTo(img_converted, CV_32F, 1.0 / 255.0, 0);

    //Construct Matrixf
    Matrixf IMG(img.rows, img.cols, (float*)img_converted.data);
    Matrixf Imrid_Output;


    /// ******************************* ///
    /// **** Best Non-SIMD Version **** ///
    /// ******************************* ///
    auto t1 = std::chrono::high_resolution_clock::now();

    for (unsigned int i=0;i<ITERATIONS;i++)
        Gaussian_blur_ref3(IMG, Imrid_Output);

    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration_base = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    cout << "Non-SIMD version took " << duration_base/float(ITERATIONS) << " ms" << endl;


    /// ********************* ///
    /// **** SIMD Version **** ///
    /// ********************* ///
    t1 = std::chrono::high_resolution_clock::now();

    for (unsigned int i=0;i<ITERATIONS;i++)
        Gaussian_blur_ref4(IMG, Imrid_Output);

    t2 = std::chrono::high_resolution_clock::now();
    auto duration_ref1 = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    cout << "SIMD version took " << duration_ref1/float(ITERATIONS) << " ms" << endl;


    //Display
    Mat blurred(Imrid_Output.rows, Imrid_Output.cols, CV_32F, Imrid_Output.val[0]);
    imshow("image", img);
    imshow("smoothed", blurred);
    waitKey(0);

    return 0;
}
