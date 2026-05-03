#ifndef MATRIXADDITION_H
#define MATRIXADDITION_H

class MatrixAddition
{
private:
    int ResultMatrixRow;

    int ResultMatrixCol;

    double **ResultMatrix;

public:
    MatrixAddition();

    void addMatrix(double **matrixA, int rowMatrixA, int colMatrixA, double **matrixB, int rowMatrixB, int colMatrixB);

    void displayResultMatrix();

    double **getResultMatrix();

    void resetObject();

    ~MatrixAddition();
};

#endif