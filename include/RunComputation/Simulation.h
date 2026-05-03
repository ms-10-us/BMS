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

    BMSECU *BMSECUPtr = nullptr;

    std::vector<std::string> ResultVectorNames;

    std::vector<std::vector<double>> CurrentResultData;

    std::vector<std::vector<double>> VoltageResultData;

    std::vector<std::vector<double>> TemperatureResultData;

    std::vector<std::vector<double>> SOCResultData;

    bool isSimulationReady = false;

    std::vector<std::unique_ptr<ExtendedKalmanFilter>> EKFPerCell;

    std::vector<std::unique_ptr<BatteryCellElectricalModel>> CellModelPerCell;

public:
    Simulation(DataParse *parsedData, QObject *parent = nullptr);

    void RunSimulation(std::function<void(int)> progressCallBack);

    bool &getIsSimulationReady();

    const std::vector<std::string> &getResultVectorNames();

    const std::vector<std::vector<double>> &getCurrentResultData();

    const std::vector<std::vector<double>> &getVoltageResultData();

    const std::vector<std::vector<double>> &getTemperatureResultData();

    const std::vector<std::vector<double>> &getSOCResultData();

    // ~Simulation();
};

#endif