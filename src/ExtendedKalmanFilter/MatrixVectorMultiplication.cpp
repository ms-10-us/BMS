#include "../../include/ExtendedKalmanFilter/MatrixVectorMultiplication.h"

#include <iostream>

MatrixVectorMultiplication::MatrixVectorMultiplication() = default;

void MatrixVectorMultiplication::multiplyByVector(double **matrixA, double *vector)
{
    int rowMatrixA = sizeof(matrixA) / sizeof(matrixA[0]);
    int colMatrixA = sizeof(matrixA[0]) / sizeof(matrixA[0][0]);

    int rowVector = sizeof(vector) / sizeof(vector[0]);

    if (colMatrixA != rowVector)
    {
        std::cerr << "Matrix Multiplication is not possible!";
    }
    else
    {
        ResultMatrixRow = rowMatrixA;
        ResultMatrixCol = 1;

        for (int i = 0; i < ResultMatrixRow; i++)
        {
            ResultMatrix[i][ResultMatrixCol] = 0.0;
            for (int k = 0; k < colMatrixA; k++)
            {
                ResultMatrix[i][ResultMatrixCol] += matrixA[i][k] * vector[k];
            }
        }
    }
}

void MatrixVectorMultiplication::displayResultMatrix()
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

double **MatrixVectorMultiplication::getResultMatrix()
{
    return ResultMatrix;
}

void MatrixVectorMultiplication::resetObject()
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

MatrixVectorMultiplication::~MatrixVectorMultiplication()
{
    for (int i = 0; i < ResultMatrixRow; i++)
    {
        delete[] ResultMatrix[i];
    }
    delete[] ResultMatrix;
}