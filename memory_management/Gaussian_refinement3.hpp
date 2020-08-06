inline void GaussianBlur_row(const float *in, float *out, const unsigned int cols)
{
    //Left columns
    out[0] = (in[0]+in[2])*0.054488685f + (in[0]+in[1])*0.24420135f + in[0]*0.40261996f;
    out[1] = (in[0]+in[3])*0.054488685f + (in[0]+in[2])*0.24420135f + in[1]*0.40261996f;

    //Middle columns
    for (unsigned int j=2; j<cols-2; j++)
        out[j] = (in[j-2]+in[j+2])*0.054488685f + (in[j-1]+in[j+1])*0.24420135f + in[j]*0.40261996f ;

    //Right columns
    out[cols-2] = (in[cols-4]+in[cols-1])*0.054488685f + (in[cols-3]+in[cols-1])*0.24420135f + in[cols-2]*0.40261996f;
    out[cols-1] = (in[cols-3]+in[cols-1])*0.054488685f + (in[cols-2]+in[cols-1])*0.24420135f + in[cols-1]*0.40261996f;
}


void Gaussian_blur_ref3(const Matrixf &input, Matrixf &output)
{
    //sigma is 1.0f
    //kernel previously calculated
    //border type is replicate

    const unsigned int rows = input.rows;
    const unsigned int cols = input.cols;

    output.resize(rows, cols);

    float buffer[cols];

    //Top rows
    for (unsigned int i=0; i<2; i++)
    {
        for (unsigned int j=0; j<cols; j++)
            buffer[j] = (input.val[0][j]+input.val[i+2][j])*0.054488685f + (input.val[0][j]+input.val[i+1][j])*0.24420135f + input.val[i][j]*0.40261996f;

        GaussianBlur_row(buffer, output.val[i], cols);
    }

    //Middle rows
    for (unsigned int i=2; i<rows-2; i++)
    {
        for (unsigned int j=0; j<cols; j++)
            buffer[j] = (input.val[i-2][j]+input.val[i+2][j])*0.054488685f + (input.val[i-1][j]+input.val[i+1][j])*0.24420135f + input.val[i][j]*0.40261996f;

        GaussianBlur_row(buffer, output.val[i], cols);
    }

    //Bottom rows
    for (unsigned int i=rows-2; i<rows; i++)
    {
        for (unsigned int j=0; j<cols; j++)
            buffer[j] = (input.val[i-2][j]+input.val[rows-1][j])*0.054488685f + (input.val[i-1][j]+input.val[rows-1][j])*0.24420135f + input.val[i][j]*0.40261996f;

        GaussianBlur_row(buffer, output.val[i], cols);
    }
}
