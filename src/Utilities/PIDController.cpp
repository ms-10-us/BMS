#include "../../include/Utilities/PIDController.h"
#include <iostream>

PIDController::PIDController(double &kp,
                             double &ki,
                             double &kd,
                             double &setPoint,
                             double &previousError,
                             double &integralError,
                             double &derivativeError,
                             double &command)
    : Kp(kp),
      Ki(ki),
      Kd(kd),
      SetPoint(setPoint),
      PreviousError(previousError),
      IntegralError(integralError),
      DerivativeError(derivativeError),
      Command(command)
{
}

void PIDController::setSetPoint(double &setPoint)
{
    SetPoint = setPoint;
}

void PIDController::RunPIDController(double &setPoint, double &measured, double &dt)
{

    double error = setPoint - measured;
    IntegralError += error * dt;
    DerivativeError = (error - PreviousError) / dt;
    PreviousError = error;
    Command = (Kp * error) + (Ki * IntegralError) + (Kd * DerivativeError);
}

double &PIDController::getCommand()
{
    return Command;
}

double &PIDController::getSetPoint()
{
    return SetPoint;
}

void PIDController::printCommand()
{
    std::cout << "PID Command: " << Command << " \n";
}

void PIDController::ClampPIDCommand(double &commandMin, double &commandMax)
{
    if (Command < commandMin)
    {
        Command = commandMin;
    }
    else if (Command > commandMax)
    {
        Command = commandMax;
    }
}

void PIDController::reset()
{
    Kp = 0.0;
    Ki = 0.0;
    Kd = 0.0;
    SetPoint = 0.0;
    PreviousError = 0.0;
    IntegralError = 0.0;
    DerivativeError = 0.0;
    Command = 0.0;
}