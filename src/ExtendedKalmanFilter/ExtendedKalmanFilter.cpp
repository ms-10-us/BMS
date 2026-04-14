#include "../../include/ExtendedKalmanFilter/ExtendedKalmanFilter.h"
#include "../../include/Utilities/GlobalVariables.h"
#include "../../include/ExtendedKalmanFilter/MatrixMultiplication.h"
#include "../../include/ExtendedKalmanFilter/MatrixTranspose.h"
#include "../../include/ExtendedKalmanFilter/MatrixAddition.h"
#include "../../include/ExtendedKalmanFilter/MatrixVectorMultiplication.h"
#include "../../include/ExtendedKalmanFilter/GainMultiplication.h"
#include "../../include/ExtendedKalmanFilter/MatrixPieceWiseMultiplication.h"

#include <iostream>
#include <cmath>

ExtendedKalmanFilter::ExtendedKalmanFilter(double initialSOC)
{
    StatesVector[0] = initialSOC;
    StatesVector[1] = 0.0;

    for (int i = 0; i < 2; i++)
    {
        Covariance[2] = new double[2];
        Noise[2] = new double[2];
    }

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (i == j)
            {
                Covariance[i][j] = 1.0;
                Noise[i][j] = pow(10, -5);
            }
            else
            {
                Covariance[i][j] = 0.0;
                Noise[i][j] = 0.0;
            }
        }
    }

    Noise_measured = 0.01;
}

void ExtendedKalmanFilter::runExtendedKalmanFilter(
    double &current,
    double &voltagePredicted,
    double &voltageMeasured,
    double &timeStep,
    BatteryCellElectricalModel &batteryCellElectricalModel)
{
    StatesVector[0] = StatesVector[0] - (current * timeStep) / (globalData.GlobalCapacityAh * 3600.0);
    StatesVector[1] = StatesVector[1] * std::exp(-1 * timeStep / (globalData.GlobalR1 * globalData.GlobalC1)) +
                      globalData.GlobalR1 * (1 - std::exp(-1 * timeStep / (globalData.GlobalR1 * globalData.GlobalC1))) * current;

    double jacobianA[2][2] = {{1.0, 0.0},
                              {0, std::exp(-1 * timeStep / (globalData.GlobalR1 * globalData.GlobalC1))}};

    double **jacobianAPtr = new double *[2];
    for (int i = 0; i < 2; i++)
    {
        jacobianAPtr[i] = new double[2];
    }
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            jacobianAPtr[i][j] = jacobianA[i][j];
        }
    }

    MatrixMultiplication matrixMultiplication = MatrixMultiplication();
    matrixMultiplication.multiply(jacobianAPtr, Covariance);
    double **tempResultMatrix = matrixMultiplication.getResultMatrix();
    matrixMultiplication.resetObject();

    MatrixTranspose matrixTranspose = MatrixTranspose();
    matrixTranspose.Transpose(jacobianAPtr);
    double **transposedJacobianA = matrixTranspose.getTranspose();
    matrixTranspose.resetObject();

    matrixMultiplication.multiply(tempResultMatrix, transposedJacobianA);
    double **tempResultMatrixTwo = matrixMultiplication.getResultMatrix();
    matrixMultiplication.resetObject();

    MatrixAddition matrixAddition = MatrixAddition();
    matrixAddition.addMatrix(tempResultMatrixTwo, Noise);
    Covariance = matrixAddition.getResultMatrix();
    matrixAddition.resetObject();

    batteryCellElectricalModel.CalculateOCV(StatesVector[0]);
    batteryCellElectricalModel.Calculate_dOCV_dSOC(StatesVector[0]);

    double jacobianH[2] = {batteryCellElectricalModel.get_dOCV_dSOC(), -1.0};
    double *jacobianHPtr = new double[2];
    for (int i = 0; i < 2; i++)
    {
        jacobianHPtr[i] = jacobianH[i];
    }

    double S = Noise_measured;
    for (int i = 0; i < 2; i++)
    {
        S += jacobianHPtr[i] * Covariance[i][i] * jacobianHPtr[i];
    }

    double *kalmanGain = new double[2];
    for (int i = 0; i < 2; i++)
    {
        kalmanGain[i] = Covariance[i][i] * jacobianHPtr[i] * (1 / S);
    }

    double outputState = voltageMeasured - voltagePredicted;

    for (int i = 0; i < 2; i++)
    {
        StatesVector[i] += kalmanGain[i] * outputState;
    }

    for (int i = 0; i < 2; i++)
    {
        Covariance[i][i] = Covariance[i][i] * (1 - kalmanGain[i] * jacobianHPtr[i]);
    }

    matrixMultiplication.~MatrixMultiplication();
    matrixTranspose.~MatrixTranspose();
    matrixAddition.~MatrixAddition();
}

double ExtendedKalmanFilter::getSOC() const
{
    return StatesVector[0];
}
