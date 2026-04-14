#include "../../include/ExtendedKalmanFilter/MaxtrixTranspose.h"

#include <iostream>

MatrixTranspose::MatrixTranspose() = default;

void MatrixTranspose::Transpose(const double **matrix)
{
    int matrixRow = sizeof(matrix) / sizeof(matrix[0]);
    int matrixCol = sizeof(matrix[0]) / sizeof(matrix[0][0]);

    TransposedMatrixRow = matrixCol;
    TransposedMatrixCol = matrixRow;

    for (int i = 0; i < TransposedMatrixRow; i++)
    {
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
    if (TransposedMatrix != nullptr)
    {
        for (int i = 0; i < TransposedMatrixRow; i++)
        {
            if (TransposedMatrix[i] != nullptr)
            {
                TransposedMatrix[i] = nullptr;
            }
        }
        TransposedMatrix = nullptr;
    }

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