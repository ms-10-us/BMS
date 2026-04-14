#include "../../include/ExtendedKalmanFilter/MatrixMultiplication.h"

#include <iostream>

MatrixMultiplication::MatrixMultiplication() = default;

void MatrixMultiplication::multiply(double **matrixA, double **matrixB)
{
    int rowMatrixA = sizeof(matrixA) / sizeof(matrixA[0]);
    int colMatrixA = sizeof(matrixA[0]) / sizeof(matrixA[0][0]);

    int rowMatrixB = sizeof(matrixB) / sizeof(matrixB[0]);
    int colMatrixB = sizeof(matrixB[0]) / sizeof(matrixB[0][0]);

    if (colMatrixA != rowMatrixB)
    {
        std::cerr << "Matrix Multiplication is not possible!";
    }
    else
    {
        ResultMatrixRow = rowMatrixA;
        ResultMatrixCol = colMatrixB;

        for (int i = 0; i < ResultMatrixRow; i++)
        {
            for (int j = 0; j < ResultMatrixCol; j++)
            {
                ResultMatrix[i][j] = 0.0;
                for (int k = 0; k < colMatrixA; k++)
                {
                    ResultMatrix[i][j] += matrixA[i][k] * matrixB[k][j];
                }
            }
        }
    }
}

void MatrixMultiplication::displayResultMatrix()
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

double **MatrixMultiplication::getResultMatrix()
{
    return ResultMatrix;
}

void MatrixMultiplication::resetObject()
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

MatrixMultiplication::~MatrixMultiplication()
{
    for (int i = 0; i < ResultMatrixRow; i++)
    {
        delete[] ResultMatrix[i];
    }
    delete[] ResultMatrix;
}
