void convolve_gaussian_H_ref1(const Matrixf &padded, Matrixf &output)
{
    const unsigned int rows = padded.rows;
    const unsigned int cols = padded.cols;

    output.resize(rows, cols-4);

    for (unsigned int i=0; i<rows; i++)
        for (unsigned int j=2; j<cols-2; j++)
            output.val[i][j-2] = (padded.val[i][j-2]+padded.val[i][j+2])*0.054488685f +  (padded.val[i][j-1]+padded.val[i][j+1])*0.24420135f + padded.val[i][j]*0.40261996f;
}

void convolve_gaussian_V_ref1(const Matrixf &padded, Matrixf &output)
{

    const unsigned int rows = padded.rows;
    const unsigned int cols = padded.cols;

    output.resize(rows-4, cols);

    for (unsigned int i=2; i<rows-2; i++)
        for (unsigned int j=0; j<cols; j++)
            output.val[i-2][j] = (padded.val[i-2][j]+padded.val[i+2][j])*0.054488685f +  (padded.val[i-1][j]+padded.val[i+1][j])*0.24420135f + padded.val[i][j]*0.40261996f;
}

void Gaussian_blur_ref1(const Matrixf &input, Matrixf &output)
{
    //sigma is 1.0f
    //kernel previously calculated
    //border type is replicate

    Matrixf temp, paddedH, paddedV;

    padd_image_H(input, paddedH);
    convolve_gaussian_H_ref1(paddedH, temp);

    padd_image_V(temp, paddedV);
    convolve_gaussian_V_ref1(paddedV, output);
}
