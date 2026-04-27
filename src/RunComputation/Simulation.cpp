#include "../../include/RunComputation/Simulation.h"
#include "../../include/Utilities/GlobalVariables.h"
#include <vector>

Simulation::Simulation(DataParse *parsedData, QObject *parent)
    : QObject(parent),
      SimulationData(parsedData)
{
    if (SimulationData == nullptr)
    {
        isSimulationReady = false;
        return;
    }

    isSimulationReady = true;

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

    int vectorSize = SimulationData->getRowNumber();

    for (int i = 0; i < SimulationData->getRowNumber(); i++)
    {
        CurrentPIDController->RunPIDController(currentSetPoint[i], CurrentPIDController->getCommand(), globalData.GlobalTimeStep);
        double cellCurrent = BatteryPackPtr->getCellCurrent(CurrentPIDController->getCommand());

        CurrentResultData.resize(BatteryPackPtr->getCellInSeries() * BatteryPackPtr->getCellInParallel());
        VoltageResultData.resize(BatteryPackPtr->getCellInSeries() * BatteryPackPtr->getCellInParallel());
        TemperatureResultData.resize(BatteryPackPtr->getCellInSeries() * BatteryPackPtr->getCellInParallel());
        SOCResultData.resize(BatteryPackPtr->getCellInSeries() * BatteryPackPtr->getCellInParallel());

        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                CurrentResultData[j * k].push_back(cellCurrent);

                BatteryPackPtr->calculateCellVoltage(cellCurrent);
                VoltageResultData[j * k].push_back(BatteryPackPtr->getCellVolatge(j, k));

                BatteryPackPtr->claculateAverageTemperature(CurrentPIDController->getCommand());
                TemperatureResultData[j * k].push_back(BatteryPackPtr->getCellTemperature(j, k));

                EKFPtr->runExtendedKalmanFilter(cellCurrent,
                                                BatteryPackPtr->getCellVolatge(j, k),
                                                cellVoltage[i],
                                                globalData.GlobalTimeStep,
                                                BatteryPackPtr->getBatteryCellElectricalModel(j, k));
                double cellSOC = EKFPtr->getSOC();
                SOCResultData[j * k].push_back(cellSOC);
            }
        }
    }
    BMSECUPtr->currentControl(BMSEvent::STOP);

    emit logMessage("Simulation Completed");
}

bool &Simulation::getIsSimulationReady()
{
    return isSimulationReady;
}