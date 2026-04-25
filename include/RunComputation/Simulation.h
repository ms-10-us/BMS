#ifndef SIMULATION_H
#define SIMULATION_H

#include "../../dataParser/DataParse.h"
#include "../../include/Utilities/PIDController.h"
#include "../../include/BMS/BatteryPack.h"
#include "../../include/BMS/DTCManager.h"
#include "../../include/Utilities/CANBus.h"
#include "../../include/BMS/BatteryStateMachine.h"
#include "../../include/ECUs/BMSECU.h"
#include "../../include/ExtendedKalmanFilter/ExtendedKalmanFilter.h"
#include <QString>

class Simulation
{
private:
    DataParse *SimulationData = nullptr;

    PIDController *CurrentPIDController = nullptr;

    BatteryPack *BatteryPackPtr = nullptr;

    DTCManager *DTCManagerPtr = nullptr;

    CANBus *CANBusPtr = nullptr;

    BatteryStateMachine *BatteryStateMachinePtr = nullptr;

    ExtendedKalmanFilter *EKFPtr = nullptr;

    BMSECU *BMSECUPtr = nullptr;

    std::vector<std::vector<double>> ResultData;

public:
    Simulation(DataParse *parsedData);

    void RunSimulation();

    ~Simulation();

signals:
    void logMessage(const QString &message);
};

#endif