#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <omp.h>

#include "../Matrix.h"
#include "Gaussian_base.hpp"
#include "Gaussian_refinement1.hpp"
#include "Gaussian_refinement2.hpp"
#include "Gaussian_refinement3.hpp"

using namespace std;
using namespace cv;

#define ITERATIONS 100

int main()
{
    Mat img = imread("../../image.jpg", 0);

    //resize(img, img, Size(), 2, 2); //Use to see the effect of image size

    Mat img_converted;
    img.convertTo(img_converted, CV_32F, 1.0 / 255.0, 0);

    Mat OpenCV_Output;

    /// **************** ///
    /// **** OpenCV **** ///
    /// **************** ///
    auto t1 = std::chrono::high_resolution_clock::now();

    for (unsigned int i=0; i<ITERATIONS; i++)
        GaussianBlur(img_converted, OpenCV_Output, Size(5,5), 1.0, 1.0, BORDER_REPLICATE);

    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration_cv = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    cout << "OpenCV took " << duration_cv/float(ITERATIONS) << " ms" << endl;


    //Construct Matrixf
    Matrixf IMG(img.rows, img.cols, (float*)img_converted.data);
    Matrixf Imrid_Output;


    /// ************** ///
    /// **** Base **** ///
    /// ************** ///
    t1 = std::chrono::high_resolution_clock::now();

    for (unsigned int i=0; i<ITERATIONS; i++)
        Gaussian_blur_base(IMG, Imrid_Output);

    t2 = std::chrono::high_resolution_clock::now();
    auto duration_base = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    cout << "Base version took " << duration_base/float(ITERATIONS) << " ms" << endl;


    /// ********************* ///
    /// **** Refinment 1 **** ///
    /// ********************* ///
    t1 = std::chrono::high_resolution_clock::now();

    for (unsigned int i=0; i<ITERATIONS; i++)
        Gaussian_blur_ref1(IMG, Imrid_Output);

    t2 = std::chrono::high_resolution_clock::now();
    auto duration_ref1 = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    cout << "Refinement1 took " << duration_ref1/float(ITERATIONS) << " ms" << endl;



    /// ********************* ///
    /// **** Refinment 2 **** ///
    /// ********************* ///
    t1 = std::chrono::high_resolution_clock::now();

    for (unsigned int i=0; i<ITERATIONS; i++)
        Gaussian_blur_ref2(IMG, Imrid_Output);

    t2 = std::chrono::high_resolution_clock::now();
    auto duration_ref2 = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    cout << "Refinement2 took " << duration_ref2/float(ITERATIONS) << " ms" << endl;



    /// ********************* ///
    /// **** Refinment 3 **** ///
    /// ********************* ///
    t1 = std::chrono::high_resolution_clock::now();

    for (unsigned int i=0; i<ITERATIONS; i++)
        Gaussian_blur_ref3(IMG, Imrid_Output);

    t2 = std::chrono::high_resolution_clock::now();
    auto duration_ref3 = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    cout << "Refinement3 took " << duration_ref3/float(ITERATIONS) << " ms" << endl;


    //Display
    Mat blurred(Imrid_Output.rows, Imrid_Output.cols, CV_32F, Imrid_Output.val[0]);
    imshow("image", img);
    imshow("opencv", OpenCV_Output);
    imshow("smoothed", blurred);
    waitKey(0);

    return 0;
}
