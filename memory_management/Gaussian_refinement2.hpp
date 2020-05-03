void convolve_gaussian_H_ref2(const Matrixf &input, Matrixf &output)
{
    const unsigned int rows = input.rows;
    const unsigned int cols = input.cols;

    output.resize(rows, cols);

    for (unsigned int i=0; i<rows; i++)
    {
        //Left columns
        output.val[i][0] = (input.val[i][0]+input.val[i][2])*0.054488685f + (input.val[i][0]+input.val[i][1])*0.24420135f + input.val[i][0]*0.40261996f;
        output.val[i][1] = (input.val[i][0]+input.val[i][3])*0.054488685f + (input.val[i][0]+input.val[i][2])*0.24420135f + input.val[i][1]*0.40261996f;

        //Middle columns
        for (unsigned int j=2; j<cols-2; j++)
            output.val[i][j] = (input.val[i][j-2]+input.val[i][j+2])*0.054488685f + (input.val[i][j-1]+input.val[i][j+1])*0.24420135f + input.val[i][j]*0.40261996f ;

        //Right columns
        output.val[i][cols-2] = (input.val[i][cols-4]+input.val[i][cols-1])*0.054488685f + (input.val[i][cols-3]+input.val[i][cols-1])*0.24420135f + input.val[i][cols-2]*0.40261996f;
        output.val[i][cols-1] = (input.val[i][cols-3]+input.val[i][cols-1])*0.054488685f + (input.val[i][cols-2]+input.val[i][cols-1])*0.24420135f + input.val[i][cols-1]*0.40261996f;
    }

}

void convolve_gaussian_V_ref2(const Matrixf &input, Matrixf &output)
{

    const unsigned int rows = input.rows;
    const unsigned int cols = input.cols;

    output.resize(rows, cols);

    //Top rows
    for (unsigned int i=0; i<2; i++)
        for (unsigned int j=0; j<cols; j++)
            output.val[i][j] = (input.val[0][j]+input.val[i+2][j])*0.054488685f + (input.val[0][j]+input.val[i+1][j])*0.24420135f + input.val[i][j]*0.40261996f;

    //Middle rows
    for (unsigned int i=2; i<rows-2; i++)
        for (unsigned int j=0; j<cols; j++)
            output.val[i][j] = (input.val[i-2][j]+input.val[i+2][j])*0.054488685f + (input.val[i-1][j]+input.val[i+1][j])*0.24420135f + input.val[i][j]*0.40261996f;

    //Bottom rows
    for (unsigned int i=rows-2; i<rows; i++)
        for (unsigned int j=0; j<cols; j++)
            output.val[i][j] = (input.val[i-2][j]+input.val[rows-1][j])*0.054488685f + (input.val[i-1][j]+input.val[rows-1][j])*0.24420135f + input.val[i][j]*0.40261996f;
}

void Gaussian_blur_ref2(const Matrixf &input, Matrixf &output)
{
    //sigma is 1.0f
    //kernel previously calculated
    //border type is replicate

    Matrixf temp;
    convolve_gaussian_H_ref2(input, temp);
    convolve_gaussian_V_ref2(temp, output);
}
