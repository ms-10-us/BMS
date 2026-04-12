#ifndef EXTENDEDKALMANFILTER_H
#define EXTENDEDKALMANFILTER_H

#include "../../include/BMS/BatteryCellElectricalModel.h"

class ExtendedKalmanFilter
{
private:
    double SOC_estimate;
    double Voltage_measured;
    double **StatesVector = new double *[2];

    double **Covariance = new double *[2];

    double **Noise = new double *[2];

    double Noise_measured;

public:
    ExtendedKalmanFilter(double initialSOC);

    void runExtendedKalmanFilter(
        double &current,
        double &voltagePredicted,
        double &voltageMeasured,
        double &timeStep,
        BatteryCellElectricalModel &batteryCellElectricalModel);

    double getSOC() const;
};

#endif