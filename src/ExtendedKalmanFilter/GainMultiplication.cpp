#include "../../include/ExtendedKalmanFilter/GainMultiplication.h"

#include <iostream>

GainMultiplication::GainMultiplication(double gain)
{
    Gain = gain;
}

void GainMultiplication::muliplyByGain(double **matrix)
{
    ResultMatrixRow = sizeof(matrix) / sizeof(matrix[0]);
    ResultMatrixRow = sizeof(matrix[0]) / sizeof(matrix[0][0]);

    for (int i = 0; i < ResultMatrixRow; i++)
    {
        for (int j = 0; j < ResultMatrixRow; j++)
        {
            ResultMatrix[i][j] = ResultMatrix[i][j] * Gain;
        }
    }
}

void GainMultiplication::displayResultMatrix()
{
    for (int i = 0; i < ResultMatrixRow; i++)
    {
        for (int j = 0; j < ResultMatrixRow; j++)
        {
            std::cout << ResultMatrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

double **GainMultiplication::getResultMatrix()
{
    return ResultMatrix;
}