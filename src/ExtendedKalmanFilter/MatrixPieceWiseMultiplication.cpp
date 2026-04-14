#include "../../include/ExtendedKalmanFilter/MatrixPieceWiseMultiplication.h"

#include <iostream>

MatrixPieceWiseMutiplication::MatrixPieceWiseMutiplication() = default;

void MatrixPieceWiseMutiplication::PieceWiseMultilply(double **matrixA, double **matrixB)
{
    int rowMatrixA = sizeof(matrixA) / sizeof(matrixA[0]);
    int colMatrixA = sizeof(matrixA[0]) / sizeof(matrixA[0][0]);

    int rowMatrixB = sizeof(matrixB) / sizeof(matrixB[0]);
    int colMatrixB = sizeof(matrixB[0]) / sizeof(matrixB[0][0]);

    if (rowMatrixA != rowMatrixB && colMatrixA != colMatrixB)
    {
        std::cerr << "Piece Wise Mutiplication is Not Possible!";
    }
    else
    {
        ResultMatrixRow = rowMatrixA;
        ResultMatrixCol = colMatrixA;

        for (int i = 0; i < ResultMatrixRow; i++)
        {
            for (int j = 0; j < ResultMatrixCol; j++)
            {
                ResultMatrix[i][j] = matrixA[i][j] * matrixB[i][j];
            }
        }
    }
}

void MatrixPieceWiseMutiplication::diplayResultMatrix()
{
    for (int i = 0; i < ResultMatrixRow; i++)
    {
        for (int j = 0; j < ResultMatrixCol; j++)
        {
            std::cout << ResultMatrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

double **MatrixPieceWiseMutiplication::getResultMatrix()
{
    return ResultMatrix;
}

void MatrixPieceWiseMutiplication::resetObject()
{
    if (ResultMatrix != nullptr)
    {
        for (int i = 0; i < ResultMatrixRow; i++)
        {
            if (ResultMatrix[i] != nullptr)
            {
                ResultMatrix[i] = nullptr;
            }
        }
        ResultMatrix = nullptr;
    }

    ResultMatrixRow = 0;
    ResultMatrixCol = 0;
}

MatrixPieceWiseMutiplication::~MatrixPieceWiseMutiplication()
{
    for (int i = 0; i < ResultMatrixRow; i++)
    {
        delete[] ResultMatrix[i];
    }
    delete[] ResultMatrix;
}