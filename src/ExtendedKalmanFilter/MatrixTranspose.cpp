#include "../../include/ExtendedKalmanFilter/MatrixTranspose.h"

#include <iostream>

MatrixTranspose::MatrixTranspose() = default;

void MatrixTranspose::Transpose(double **matrix, int matrixRow, int matrixCol)
{
    TransposedMatrixRow = matrixCol;
    TransposedMatrixCol = matrixRow;

    TransposedMatrix = new double *[TransposedMatrixRow];

    for (int i = 0; i < TransposedMatrixRow; i++)
    {
        TransposedMatrix[i] = new double[TransposedMatrixCol];
        for (int j = 0; j < TransposedMatrixCol; j++)
        {
            TransposedMatrix[i][j] = matrix[j][i];
        }
    }
}

void MatrixTranspose::displayTranspose()
{
    for (int i = 0; i < TransposedMatrixRow; i++)
    {
        for (int j = 0; j < TransposedMatrixCol; j++)
        {
            std::cout << TransposedMatrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

double **MatrixTranspose::getTranspose()
{
    return TransposedMatrix;
}

void MatrixTranspose::resetObject()
{
    TransposedMatrix = nullptr;
    TransposedMatrixRow = 0;
    TransposedMatrixCol = 0;
}

MatrixTranspose::~MatrixTranspose()
{

    for (int i = 0; i < TransposedMatrixRow; i++)
    {
        delete[] TransposedMatrix[i];
    }
    delete[] TransposedMatrix;
}