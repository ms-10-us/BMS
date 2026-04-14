#ifndef MATRIXMULTIPLICATION_H
#define MATRIXMULTIPLICATION_H

class MatrixMultiplication
{
private:
    int ResultMatrixRow;

    int ResultMatrixCol;

    double **ResultMatrix;

public:
    MatrixMultiplication();

    void multiply(double **matrixA, double **matrixB);

    void displayResultMatrix();

    double **getResultMatrix();

    void resetObject();

    ~MatrixMultiplication();
};

#endif