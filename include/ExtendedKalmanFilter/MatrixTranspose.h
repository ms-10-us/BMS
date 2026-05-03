#ifndef MATRIXTRANSPOSE_H
#define MATRIXTRANSPOSE_H

class MatrixTranspose
{
private:
    int TransposedMatrixRow;
    int TransposedMatrixCol;
    double **TransposedMatrix;

public:
    MatrixTranspose();

    void Transpose(double **matrix, int matrixRow, int matrixCol);

    void displayTranspose();

    double **getTranspose();

    void resetObject();

    ~MatrixTranspose();
};

#endif