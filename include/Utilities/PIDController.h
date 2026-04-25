#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

#include "GlobalVariables.h"

class PIDController
{
private:
    double &Kp, &Ki, &Kd;
    double &SetPoint;
    double &PreviousError;
    double &IntegralError;
    double &DerivativeError;
    double &Command;

public:
    PIDController(double &kp,
                  double &ki,
                  double &kd,
                  double &setPoint,
                  double &previousError,
                  double &integralError,
                  double &derivativeError,
                  double &command);

    void setSetPoint(double &setPoint);

    void RunPIDController(double &setPoint, double &measured, double &dt);

    double &getCommand();

    double &getSetPoint();

    void printCommand();

    void ClampPIDCommand(double &commandMin, double &commandMax);

    void reset();
};

#endif