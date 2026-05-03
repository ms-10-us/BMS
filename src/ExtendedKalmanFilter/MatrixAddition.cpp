#include "../../include/ExtendedKalmanFilter/MatrixAddition.h"

#include <iostream>

MatrixAddition::MatrixAddition() = default;

void MatrixAddition::addMatrix(double **matrixA, int rowMatrixA, int colMatrixA, double **matrixB, int rowMatrixB, int colMatrixB)
{
    if (rowMatrixA != rowMatrixB || colMatrixA != colMatrixB)
    {
        std::cerr << "Matrix Addition is not possible!";
    }
    else
    {
        ResultMatrixRow = rowMatrixA;
        ResultMatrixCol = colMatrixA;

        ResultMatrix = new double *[ResultMatrixRow];

        for (int i = 0; i < ResultMatrixRow; i++)
        {
            ResultMatrix[i] = new double[ResultMatrixCol];
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

void MatrixAddition::resetObject()
{
    ResultMatrix = nullptr;
    ResultMatrixRow = 0;
    ResultMatrixCol = 0;
}

MatrixAddition::~MatrixAddition()
{
    for (int i = 0; i < ResultMatrixRow; i++)
    {
        delete[] ResultMatrix[i];
    }
    delete[] ResultMatrix;
}