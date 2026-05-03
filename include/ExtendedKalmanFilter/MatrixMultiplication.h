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

    void multiply(double **matrixA, int rowMatrixA, int colMatrixA, double **matrixB, int rowMatrixB, int colMatrixB);

    void displayResultMatrix();

    double **getResultMatrix();

    void resetObject();

    ~MatrixMultiplication();
};

#endif