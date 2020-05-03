void padd_image_H(const Matrixf &input, Matrixf &output)
{
    //borderType REPLICATE: aaaaaa|abcdefgh|hhhhhhh

    const unsigned int rows = input.rows;
    const unsigned int cols = input.cols;

    output.resize(rows, cols+4);

    for (unsigned int i=0; i<rows; i++)
    {
        //Filling left and right columns
        output.val[i][0] = input.val[i][0];
        output.val[i][cols+2] = input.val[i][cols-1];
        output.val[i][1] = input.val[i][0];
        output.val[i][cols+3] = input.val[i][cols-1];

        //Filling middle columns
        memcpy(output.val[i]+2, input.val[i], cols*sizeof(float));
    }
}

void padd_image_V(const Matrixf &input, Matrixf &output)
{
    //borderType REPLICATE: aaaaaa|abcdefgh|hhhhhhh

    const unsigned int rows = input.rows;
    const unsigned int cols = input.cols;

    output.resize(rows+4, cols);

    //Filling top and bottom rows
    memcpy(output.val[0], input.val[0], cols*sizeof(float));
    memcpy(output.val[rows+2], input.val[rows-1], cols*sizeof(float));
    memcpy(output.val[1], input.val[0], cols*sizeof(float));
    memcpy(output.val[rows+3], input.val[rows-1], cols*sizeof(float));

    //Filling middle rows
    for (unsigned int i=0; i<rows; i++)
        memcpy(output.val[i+2], input.val[i], cols*sizeof(float));
}

void convolve_gaussian_H_base(const Matrixf &padded, Matrixf &output)
{
    const unsigned int rows = padded.rows;
    const unsigned int cols = padded.cols;

    output.resize(rows, cols-4);

    for (unsigned int j=2; j<cols-2; j++)
        for (unsigned int i=0; i<rows; i++)
            output.val[i][j-2] = (padded.val[i][j-2]+padded.val[i][j+2])*0.054488685f +  (padded.val[i][j-1]+padded.val[i][j+1])*0.24420135f + padded.val[i][j]*0.40261996f;
}

void convolve_gaussian_V_base(const Matrixf &padded, Matrixf &output)
{

    const unsigned int rows = padded.rows;
    const unsigned int cols = padded.cols;

    output.resize(rows-4, cols);

    for (unsigned int j=0; j<cols; j++)
        for (unsigned int i=2; i<rows-2; i++)
            output.val[i-2][j] = (padded.val[i-2][j]+padded.val[i+2][j])*0.054488685f +  (padded.val[i-1][j]+padded.val[i+1][j])*0.24420135f + padded.val[i][j]*0.40261996f;
}

void Gaussian_blur_base(const Matrixf &input, Matrixf &output)
{
    //sigma is 1.0f
    //kernel previously calculated
    //border type is replicate

    Matrixf temp, paddedH, paddedV;

    padd_image_H(input, paddedH);
    convolve_gaussian_H_base(paddedH, temp);

    padd_image_V(temp, paddedV);
    convolve_gaussian_V_base(paddedV, output);
}
