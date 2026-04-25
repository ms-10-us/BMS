#include "../../include/RunComputation/Simulation.h"
#include "../../include/Utilities/GlobalVariables.h"
#include <vector>

Simulation::Simulation(DataParse *parsedData)
{
    if (parsedData == nullptr)
    {
        throw std::invalid_argument("Data Must be Parsed Before Simulation Starts");
        emit logMessage("Data Must be Parsed Before Simulation Starts");
        return;
    }

    SimulationData = parsedData;

    CurrentPIDController = new PIDController(globalData.GlobalCurrentKp,
                                             globalData.GlobalCurrentKi,
                                             globalData.GlobalCurrentKd,
                                             globalData.InitialPIDSetpoint,
                                             globalData.InintialPreviousError,
                                             globalData.InitialIntegralError,
                                             globalData.InitialDerivativeError,
                                             globalData.InitalCommand);

    BatteryPackPtr = new BatteryPack(globalData.CellInSeries, globalData.CellInParallel);

    DTCManagerPtr = new DTCManager();

    CANBusPtr = new CANBus();

    BatteryStateMachinePtr = new BatteryStateMachine();

    EKFPtr = new ExtendedKalmanFilter(globalData.GlobalInitialSOC);

    BatteryCellElectricalModel batteryCellElectricalModel = BatteryCellElectricalModel(globalData.GlobalCapacityAh,
                                                                                       globalData.GlobalR0,
                                                                                       globalData.GlobalR1,
                                                                                       globalData.GlobalC1,
                                                                                       globalData.GlobalInitialSOC,
                                                                                       globalData.GlobalV1,
                                                                                       globalData.GlobalVoltage,
                                                                                       globalData.GlobalCurrent,
                                                                                       globalData.dOCV_dSOC);

    BMSECUPtr = new BMSECU(BatteryPackPtr, DTCManagerPtr, CANBusPtr, BatteryStateMachinePtr, CurrentPIDController, EKFPtr);
}

void Simulation::RunSimulation()
{
    emit logMessage("Simulation Running");

    std::vector<double> currentSetPoint = SimulationData->getColumn("pack_current_A");
    std::vector<double> timeStamp = SimulationData->getColumn("timestamp_ms");
    std::vector<double> cellVoltage = SimulationData->getColumn("cell1_V");

    for (int i = 0; i < SimulationData->getRowNumber(); i++)
    {
        CurrentPIDController->RunPIDController(currentSetPoint[i], CurrentPIDController->getCommand(), globalData.GlobalTimeStep);
        double cellCurrent = BatteryPackPtr->getCellCurrent(CurrentPIDController->getCommand());
        ResultData[0].push_back(cellCurrent);

        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                BatteryPackPtr->calculateCellVoltage(cellCurrent);
                ResultData[(j + 1) * (k + 1)].push_back(BatteryPackPtr->getCellVolatge(j, k));

                BatteryPackPtr->claculateAverageTemperature(CurrentPIDController->getCommand());
                ResultData[(j + 1) * (k + 1)].push_back(BatteryPackPtr->getCellTemperature(j, k));

                EKFPtr->runExtendedKalmanFilter(cellCurrent,
                                                BatteryPackPtr->getCellVolatge(j, k),
                                                cellVoltage[i],
                                                globalData.GlobalTimeStep,
                                                BatteryPackPtr->getBatteryCellElectricalModel(j, k));
                double cellSOC = EKFPtr->getSOC();
                ResultData[(j + 1) * (k + 1)].push_back(cellSOC);
            }
        }
    }
    BMSECUPtr->currentControl(BMSEvent::STOP);

    emit logMessage("Simulation Completed");
}