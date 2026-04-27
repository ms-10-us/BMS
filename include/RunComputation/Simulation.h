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
#include <QObject>

class Simulation : public QObject
{
    Q_OBJECT

private:
    DataParse *SimulationData = nullptr;

    PIDController *CurrentPIDController = nullptr;

    BatteryPack *BatteryPackPtr = nullptr;

    DTCManager *DTCManagerPtr = nullptr;

    CANBus *CANBusPtr = nullptr;

    BatteryStateMachine *BatteryStateMachinePtr = nullptr;

    ExtendedKalmanFilter *EKFPtr = nullptr;

    BMSECU *BMSECUPtr = nullptr;

    std::vector<std::vector<double>> CurrentResultData;

    std::vector<std::vector<double>> VoltageResultData;

    std::vector<std::vector<double>> TemperatureResultData;

    std::vector<std::vector<double>> SOCResultData;

    bool isSimulationReady = false;

public:
    Simulation(DataParse *parsedData, QObject *parent = nullptr);

    void RunSimulation();

    bool &getIsSimulationReady();

    // ~Simulation();

signals:
    void logMessage(const QString &message);
};

#endif