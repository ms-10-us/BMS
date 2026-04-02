#include "../../include/Utilities/PIDController.h"

PIDController::PIDController(double kp, double ki, double kd)
{
    Kp = kp;
    Ki = ki;
    Kd = Kd;
    PreviousError = 0.0;
    IntegralError = 0.0;
    DerivativeError = 0.0;
}

double PIDController::RunPIDController(double setPoint, double measured, double dt)
{
    double error = setPoint - measured;
    IntegralError += error * dt;
    DerivativeError = (error - PreviousError) / dt;
    PreviousError = error;
    return (Kp * error) + (Ki * IntegralError) + (Kd * DerivativeError);
}

void PIDController::reset()
{
    PreviousError = 0.0;
    IntegralError = 0.0;
    DerivativeError = 0.0;
}