#include "../../include/ExtendedKalmanFilter/MatrixMultiplication.h"

#include <iostream>

MatrixMultiplication::MatrixMultiplication() = default;

void MatrixMultiplication::multiply(double **matrixA, int rowMatrixA, int colMatrixA, double **matrixB, int rowMatrixB, int colMatrixB)
{
    if (colMatrixA != rowMatrixB)
    {
        std::cerr << "Matrix Multiplication is not possible!";
    }
    else
    {
        ResultMatrixRow = rowMatrixA;
        ResultMatrixCol = colMatrixB;

        ResultMatrix = new double *[ResultMatrixRow];

        for (int i = 0; i < ResultMatrixRow; i++)
        {
            ResultMatrix[i] = new double[ResultMatrixCol];
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
    ResultMatrix = nullptr;
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
