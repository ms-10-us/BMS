#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

class PIDController
{
private:
    double Kp, Ki, Kd;
    double PreviousError;
    double IntegralError;
    double DerivativeError;

public:
    PIDController(double kp, double ki, double kd);

    double RunPIDController(double setPoint, double measured, double dt);

    void reset();
};

#endif