#include "../../include/ExtendedKalmanFilter/MatrixAddition.h"

#include <iostream>

MatrixAddition::MatrixAddition() = default;

void MatrixAddition::addMatrix(double **matrixA, double **matrixB)
{
    int rowMatrixA = sizeof(matrixA) / sizeof(matrixA[0]);
    int colMatrixA = sizeof(matrixA[0]) / sizeof(matrixA[0][0]);

    int rowMatrixB = sizeof(matrixB) / sizeof(matrixB[0]);
    int colMatrixB = sizeof(matrixB[0]) / sizeof(matrixB[0][0]);

    if (rowMatrixA != rowMatrixB || colMatrixA != colMatrixB)
    {
        std::cerr << "Matrix Addition is not possible!";
    }
    else
    {
        ResultMatrixRow = rowMatrixA;
        ResultMatrixCol = colMatrixA;

        for (int i = 0; i < ResultMatrixRow; i++)
        {
            for (int j = 0; j < ResultMatrixCol; j++)
            {
                ResultMatrix[i][j] = matrixA[i][j] + matrixB[i][j];
            }
        }
    }
}

void MatrixAddition::displayResultMatrix()
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

double **MatrixAddition::getResultMatrix()
{
    return ResultMatrix;
}