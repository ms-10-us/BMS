#include "../../include/Utilities/PIDController.h"

PIDController::PIDController(double kp, double ki, double kd)
{
    Kp = kp;
    Ki = ki;
    Kd = kd;
    PreviousError = 0.0;
    IntegralError = 0.0;
    DerivativeError = 0.0;
    SetPointPtr = nullptr;
    Command = 0.0;
    CommandPtr = nullptr;
}

void PIDController::RunPIDController(double *setPoint, double *measured, double dt)
{
    double error = *setPoint - *measured;
    IntegralError += error * dt;
    DerivativeError = (error - PreviousError) / dt;
    PreviousError = error;
    Command = (Kp * error) + (Ki * IntegralError) + (Kd * DerivativeError);
    CommandPtr = &Command;
}

void PIDController::setSetPointPtr(double *setPoint)
{
    SetPointPtr = setPoint;
}

double *PIDController::getSetPointPtr()
{
    return SetPointPtr;
}

double *PIDController::getCommandPtr()
{
    return CommandPtr;
}

void PIDController::reset()
{
    PreviousError = 0.0;
    IntegralError = 0.0;
    DerivativeError = 0.0;
}