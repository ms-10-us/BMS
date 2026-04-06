#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include <atomic>

struct GlobalVariables
{
    double GlobalCapacityAh = 2.5; // Amp-hour
    double GlobalR0 = 0.01;        // ohms
    double GlobalR1 = 0.02;        // ohms
    double GlobalC1 = 2000.0;      // mF
    double GlobalInitialSOC = 1.0; // no units
    double GlobalSimTime = 10.0;   // sec
    double GlobalCurrentSimTime = 0.0;
    double GlobalTimeStep = 1;              // sec
    double GlobalCellMass = 0.05;           // kg
    double GlobalCellCp = 900;              // J/(kg·K)
    double GlobalInitialTemperature = 25.0; // degC
    double TestCurrent = 15.0;              // A
    int ThreadSleepTime = 1000.0;           // ms
    double CurrentInitialCondition = 0.0;   // A
    int VoltageMinValue = 30;               // V
    int VoltageMaxValue = 100;              // V
    int GlobalCurrentCycle = 0;
    std::atomic<bool> RunningBMS = false;
};

extern GlobalVariables globalData;
// class GlobalVariables
// {
// private:
//     GlobalVariables() = default;
//     GlobalVariables(const GlobalVariables &) = delete;
//     GlobalVariables &operator=(const GlobalVariables &) = delete;

// public:

//     static GlobalVariables &getSingeltonInstance()
//     {
//         static GlobalVariables GlobalVariableSingelton;
//         return GlobalVariableSingelton;
//     }
// };

#endif