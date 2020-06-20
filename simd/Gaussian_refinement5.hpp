#include <opencv2/core/hal/intrin.hpp>

void Gaussian_blur_ref5(const Matrixf &input, Matrixf &output)
{
    //sigma is 1.0f
    //kernel previously calculated
    //border type is replicate

    const unsigned int rows = input.rows;
    const unsigned int cols = input.cols;

    output.resize(rows, cols);

    float buffer[cols] __attribute__((aligned(16)));

    cv::v_float32x4 coef1 = cv::v_setall_f32(0.054488685f);
    cv::v_float32x4 coef2 = cv::v_setall_f32(0.24420135f);
    cv::v_float32x4 coef3 = cv::v_setall_f32(0.40261996f);

    //Top rows
    for (unsigned int i=0; i<2; i++)
    {
        unsigned int j=0;
        for (; j<cols; j+=4)
        {
            cv::v_float32x4 c = cv::v_load_aligned(&input.val[i  ][j]);
            cv::v_float32x4 d = cv::v_load_aligned(&input.val[i+1][j]);
            cv::v_float32x4 e = cv::v_load_aligned(&input.val[i+2][j]);

            cv::v_float32x4 result = ((c+e)*coef1) + ((c+d)*coef2) + (c*coef3);

            cv::v_store_aligned(&buffer[j], result);
        }

        //leftovers
        for (unsigned int j=0; j<cols; j++)
            buffer[j] = (input.val[0][j]+input.val[i+2][j])*0.054488685f + (input.val[0][j]+input.val[i+1][j])*0.24420135f + input.val[i][j]*0.40261996f;

        GaussianBlur_row_tiled(buffer, output.val[i], cols);
    }

    //Middle rows
    for (unsigned int i=2; i<rows-2; i++)
    {
        unsigned int j=0;
        for (; j<cols; j+=4)
        {
            cv::v_float32x4 a = cv::v_load_aligned(&input.val[i-2][j]);
            cv::v_float32x4 b = cv::v_load_aligned(&input.val[i-1][j]);
            cv::v_float32x4 c = cv::v_load_aligned(&input.val[i  ][j]);
            cv::v_float32x4 d = cv::v_load_aligned(&input.val[i+1][j]);
            cv::v_float32x4 e = cv::v_load_aligned(&input.val[i+2][j]);

            cv::v_float32x4 result = ((a+e)*coef1) + ((b+d)*coef2) + (c*coef3);

            cv::v_store_aligned(&buffer[j], result);
        }

        //leftovers
        for (; j<cols; j++)
            buffer[j] = (input.val[i-2][j]+input.val[i+2][j])*0.054488685f + (input.val[i-1][j]+input.val[i+1][j])*0.24420135f + input.val[i][j]*0.40261996f;

        GaussianBlur_row_tiled(buffer, output.val[i], cols);
    }

    //Bottom rows
    for (unsigned int i=rows-2; i<rows; i++)
    {
        unsigned int j=0;
        for (; j<cols; j+=4)
        {
            cv::v_float32x4 a = cv::v_load_aligned(&input.val[i-2][j]);
            cv::v_float32x4 b = cv::v_load_aligned(&input.val[i-1][j]);
            cv::v_float32x4 c = cv::v_load_aligned(&input.val[i  ][j]);
            cv::v_float32x4 d = cv::v_load_aligned(&input.val[rows-1][j]);

            cv::v_float32x4 result = ((a+d)*coef1) + ((b+d)*coef2) + (c*coef3);

            cv::v_store_aligned(&buffer[j], result);
        }

        //leftovers
        for (; j<cols; j++)
            buffer[j] = (input.val[i-2][j]+input.val[rows-1][j])*0.054488685f + (input.val[i-1][j]+input.val[rows-1][j])*0.24420135f + input.val[i][j]*0.40261996f;

        GaussianBlur_row_tiled(buffer, output.val[i], cols);
    }
}
