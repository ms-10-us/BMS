#ifndef MATRIXPIECEWISEMULTIPLICATION_H
#define MATRIXPIECEWISEMULTIPLICATION_H

class MatrixPieceWiseMutiplication
{
private:
    int ResultMatrixRow;

    int ResultMatrixCol;

    double **ResultMatrix;

public:
    MatrixPieceWiseMutiplication();

    void PieceWiseMultilply(double **matrixA, double **matrixB);

    void diplayResultMatrix();

    double **getResultMatrix();

    void resetObject();

    ~MatrixPieceWiseMutiplication();
};

#endif