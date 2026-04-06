#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

#include "GlobalVariables.h"

class PIDController
{
private:
    double Kp, Ki, Kd;
    double PreviousError;
    double IntegralError;
    double DerivativeError;
    double *SetPointPtr;
    double Command;
    double *CommandPtr;

public:
    PIDController(double kp, double ki, double kd);

    void setSetPointPtr(double *setPoint);

    double *getSetPointPtr();

    double *getCommandPtr();

    void RunPIDController(double *setPoint, double *measured, double dt);

    void printCommand();

    void reset();
};

#endif