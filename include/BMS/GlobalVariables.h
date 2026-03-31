#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

struct GlobalVariables
{
    double GlobalCapacityAh;         // Amp-hour
    double GlobalR0;                 // ohms
    double GlobalR1;                 // ohms
    double GlobalC1;                 // mF
    double GlobalInitialSOC;         // no units
    double GlobalSimTime;            // sec
    double GlobalTimeStep;           // sec
    double GlobalCellMass;           // kg
    double GlobalCellCp;             // J/(kg·K)
    double GlobalInitialTemperature; // degC
    double TestCurrent;              // A
};

#endif