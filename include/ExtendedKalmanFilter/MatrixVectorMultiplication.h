#ifndef MATRIXVECTORMULTIPLICATION_H
#define MATRIXVECTORMULTIPLICATION_H

class MatrixVectorMultiplication
{
private:
    int ResultMatrixRow;

    int ResultMatrixCol;

    double **ResultMatrix;

public:
    MatrixVectorMultiplication();

    void multiplyByVector(double **matrixA, double *vector);

    void displayResultMatrix();

    double **getResultMatrix();
};

#endif