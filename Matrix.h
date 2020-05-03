#include <stdio.h>
#include <stdlib.h>
#include <cstring>

template <typename T>
class matrix
{

public:

    matrix () // init empty 0x0 matrix
    {
        rows = 0;
        cols = 0;
        val = 0;
    }

    matrix (const unsigned m,const unsigned n) // init uninitialized mxn matrix
    {
        allocateMemory(m,n);
    }

    matrix (const unsigned m,const unsigned n, const T* data) // init mxn matrix with values from array 'data'
    {
        allocateMemory(m,n);
        unsigned k=0;
        for (unsigned i=0; i<m; i++)
            for (unsigned j=0; j<n; j++)
                val[i][j] = data[k++];
    }

    ~matrix () // destructor
    {
        releaseMemory();
    }

    void resize(const unsigned m,const unsigned n) // changes size of array
    {
        releaseMemory();
        allocateMemory(m,n);
    }

    matrix& operator= (const matrix<T> &a) // assignment operator, copies contents of a
    {
        releaseMemory();
        allocateMemory(a.rows,a.cols);
        for (unsigned i=0; i<a.rows; i++)
            memcpy(val[i],a.val[i],a.cols*sizeof(T));

        return *this;
    }

    matrix  operator+ (const matrix<T> &a) // simple add operation
    {
        const matrix &A = *this;
        const matrix &B = a;

        matrix C(A.rows,A.cols);
        for (unsigned i=0; i<rows; i++)
            for (unsigned j=0; j<cols; j++)
                C.val[i][j] = A.val[i][j]+B.val[i][j];

        return C;
    }

    // direct data access
    T   **val;
    unsigned   rows,cols;

private:

    void allocateMemory (const unsigned m,const unsigned n)
    {
        rows = m;
        cols = n;

        if (m==0 || n==0)
        {
            val = 0;
            return;
        }

        val    = (T**)malloc(m*sizeof(T*));
        val[0] = (T*)calloc(m*n,sizeof(T));

        for(unsigned i=1; i<m; i++)
            val[i] = val[i-1]+n;
    }


    void releaseMemory ()
    {
        if (val!=0)
        {
            free(val[0]);
            free(val);
        }
    }

};


typedef matrix<unsigned char> Matrix;
typedef matrix<float> Matrixf;
