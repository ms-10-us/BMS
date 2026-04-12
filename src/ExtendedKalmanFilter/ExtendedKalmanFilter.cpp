#include "../../include/ExtendedKalmanFilter/ExtendedKalmanFilter.h"
#include "../../include/Utilities/GlobalVariables.h"
#include "../../include/ExtendedKalmanFilter/MatrixMultiplication.h"
#include "../../include/ExtendedKalmanFilter/MaxtrixTranspose.h"
#include "../../include/ExtendedKalmanFilter/MatrixAddition.h"
#include "../../include/ExtendedKalmanFilter/MatrixVectorMultiplication.h"
#include "../../include/ExtendedKalmanFilter/GainMultiplication.h"
#include "../../include/ExtendedKalmanFilter/MatrixPieceWiseMultiplication.h"

#include <iostream>
#include <cmath>

ExtendedKalmanFilter::ExtendedKalmanFilter(double initialSOC)
{
    StatesVector[0][0] = initialSOC;
    StatesVector[1][0] = 0.0;

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
    StatesVector[0][0] = StatesVector[0][0] - (current * timeStep) / (globalData.GlobalCapacityAh * 3600.0);
    StatesVector[1][0] = StatesVector[1][0] * std::exp(-1 * timeStep / (globalData.GlobalR1 * globalData.GlobalC1)) +
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

    MatrixMultiplication firstMultiplication = MatrixMultiplication();
    firstMultiplication.multiply(jacobianAPtr, Covariance);
    double **tempResultMatrix = firstMultiplication.getResultMatrix();

    MatrixTranspose jacobianAPtrTranspose = MatrixTranspose();
    jacobianAPtrTranspose.Transpose(jacobianAPtr);
    double **transposedJacobianA = jacobianAPtrTranspose.getTranspose();

    MatrixMultiplication secondMultiplication = MatrixMultiplication();
    secondMultiplication.multiply(tempResultMatrix, transposedJacobianA);
    double **tempResultMatrixTwo = secondMultiplication.getResultMatrix();

    MatrixAddition matrixAddition = MatrixAddition();
    matrixAddition.addMatrix(tempResultMatrixTwo, Noise);
    Covariance = matrixAddition.getResultMatrix();

    batteryCellElectricalModel.CalculateOCV(StatesVector[0][0]);
    batteryCellElectricalModel.Calculate_dOCV_dSOC(StatesVector[0][0]);

    double jacobianH[2] = {batteryCellElectricalModel.get_dOCV_dSOC(), -1.0};
    double *jacobianHPtr = new double[2];
    for (int i = 0; i < 2; i++)
    {
        jacobianHPtr[i] = jacobianH[i];
    }
    double S = jacobianH[0] * Covariance[0][0] * jacobianH[0] + jacobianH[1] * Covariance[1][1] * jacobianH[1] + Noise_measured;
    MatrixVectorMultiplication thirdMultiplication = MatrixVectorMultiplication();
    thirdMultiplication.multiplyByVector(Covariance, jacobianH);
    double **tempResultMatrixThree = thirdMultiplication.getResultMatrix();

    double **kalmanGain = new double *[2];
    GainMultiplication gainMuliplication = GainMultiplication(S);
    gainMuliplication.muliplyByGain(tempResultMatrixThree);
    kalmanGain = gainMuliplication.getResultMatrix();

    double outputState = voltageMeasured - voltagePredicted;
    GainMultiplication gainMultiplicationTwo = GainMultiplication(outputState);
    gainMultiplicationTwo.muliplyByGain(kalmanGain);
    double **tempGainMultiplication = gainMuliplication.getResultMatrix();

    MatrixAddition matrixAdditionTwo = MatrixAddition();
    matrixAdditionTwo.addMatrix(StatesVector, tempGainMultiplication);
    StatesVector = matrixAdditionTwo.getResultMatrix();

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (i == j)
            {
                Covariance[i][j] = Covariance[i][j] * (1 - kalmanGain[i][0] * jacobianHPtr[i]);
            }
        }
    }
}

double ExtendedKalmanFilter::getSOC() const
{
    return StatesVector[0][0];
}
