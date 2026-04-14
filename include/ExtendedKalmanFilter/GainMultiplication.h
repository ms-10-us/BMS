#ifndef GAINMULTIPLICATION_H
#define GAINMULTIPLICATION_H

class GainMultiplication
{
private:
    int ResultMatrixRow;

    int ResultMatrixCol;

    double **ResultMatrix;

    double Gain;

public:
    GainMultiplication(double gain);

    void muliplyByGain(double **matrix);

    void displayResultMatrix();

    double **getResultMatrix();

    void resetObject();

    ~GainMultiplication();
};

#endif