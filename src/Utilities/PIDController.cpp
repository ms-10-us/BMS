#include "../../include/Utilities/PIDController.h"
#include <iostream>

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
    CommandPtr = &Command;
}

void PIDController::RunPIDController(double *setPoint, double *measured, double dt)
{
    if (setPoint && measured)
    {
        double error = *setPoint - *measured;
        IntegralError += error * dt;
        DerivativeError = (error - PreviousError) / dt;
        PreviousError = error;
        Command = (Kp * error) + (Ki * IntegralError) + (Kd * DerivativeError);
        CommandPtr = &Command;
    }
}

void PIDController::printCommand()
{
    std::cout << "PID Command: " << Command << " [A]\n";
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

void PIDController::ClampPIDCommand(double *commandMin, double *commandMax)
{
    if (*CommandPtr < *commandMin)
    {
        *CommandPtr = *commandMin;
    }
    else if (*CommandPtr > *commandMax)
    {
        *CommandPtr = *commandMax;
    }
}

void PIDController::reset()
{
    PreviousError = 0.0;
    IntegralError = 0.0;
    DerivativeError = 0.0;
}