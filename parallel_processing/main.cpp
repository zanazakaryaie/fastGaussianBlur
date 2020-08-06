#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>

#include "../Matrix.h"
#include "../memory_management/Gaussian_refinement3.hpp"
#include "../simd/Gaussian_refinement4.hpp"
#include "Gaussian_refinement5.hpp"

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


    Mat OpenCV_Output;

    /// **************** ///
    /// **** OpenCV **** ///
    /// **************** ///
    auto t1 = std::chrono::high_resolution_clock::now();

    for (unsigned int i=0; i<ITERATIONS; i++)
        GaussianBlur(img_converted, OpenCV_Output, Size(5,5), 1.0, 1.0, BORDER_REPLICATE);

    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration_cv = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    cout << "OpenCV took " << duration_cv/float(ITERATIONS) << " ms" << endl << endl;


    cout << "Ours:" << endl;

    /// ******************************* ///
    /// ****** Memory Management ****** ///
    /// ******************************* ///
    t1 = std::chrono::high_resolution_clock::now();

    for (unsigned int i=0;i<ITERATIONS;i++)
        Gaussian_blur_ref3(IMG, Imrid_Output);

    t2 = std::chrono::high_resolution_clock::now();
    auto duration_memory = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    cout << "Memory Management took " << duration_memory/float(ITERATIONS) << " ms" << endl;


    /// ********************************** ///
    /// **** Memory Management + SIMD **** ///
    /// ********************************** ///
    t1 = std::chrono::high_resolution_clock::now();

    for (unsigned int i=0;i<ITERATIONS;i++)
        Gaussian_blur_ref4(IMG, Imrid_Output);

    t2 = std::chrono::high_resolution_clock::now();
    auto duration_memory_simd = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    cout << "Memory Management + SIMD took " << duration_memory_simd/float(ITERATIONS) << " ms" << endl;


    /// ******************************************************** ///
    /// **** Memory Management + SIMD + Parallel Processing **** ///
    /// ******************************************************** ///
    t1 = std::chrono::high_resolution_clock::now();

    for (unsigned int i=0;i<ITERATIONS;i++)
        Gaussian_blur_ref5(IMG, Imrid_Output);

    t2 = std::chrono::high_resolution_clock::now();
    auto duration_memory_simd_parallel = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    cout << "Memory Management + SIMD + Parallel Processing took " << duration_memory_simd_parallel/float(ITERATIONS) << " ms" << endl;

    //Display
    Mat blurred(Imrid_Output.rows, Imrid_Output.cols, CV_32F, Imrid_Output.val[0]);
    imshow("image", img);
    imshow("smoothed", blurred);
    waitKey(0);

    return 0;
}
