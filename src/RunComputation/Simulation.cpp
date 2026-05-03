#include "../../include/RunComputation/Simulation.h"
#include "../../include/Utilities/GlobalVariables.h"
#include <vector>
#include <math.h>
#include <future>

using std::make_unique;

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

    BMSECUPtr = new BMSECU(BatteryPackPtr, DTCManagerPtr, CANBusPtr, BatteryStateMachinePtr, CurrentPIDController);

    ResultVectorNames.push_back("Cells Current [A]");
    ResultVectorNames.push_back("Cells Voltage [V]");
    ResultVectorNames.push_back("Cells Temperature [degC]");
    ResultVectorNames.push_back("Cells SOC");

    CellModelPerCell.resize(globalData.CellInParallel * globalData.CellInSeries);
    EKFPerCell.resize(globalData.CellInParallel * globalData.CellInSeries);

    for (int j = 0; j < globalData.CellInParallel; j++)
    {
        for (int k = 0; k < globalData.CellInSeries; j++)
        {
            int dataIndex = j * globalData.CellInParallel + k;
            CellModelPerCell[dataIndex] = std::make_unique<BatteryCellElectricalModel>(BatteryPackPtr->getBatteryCellElectricalModel(j, k));
            EKFPerCell[dataIndex] = std::make_unique<ExtendedKalmanFilter>(globalData.GlobalInitialSOC);
        }
    }
}

void Simulation::RunSimulation(std::function<void(int)> progressCallBack)
{
    int cellSeries = BatteryPackPtr->getCellInSeries();
    int cellParallel = BatteryPackPtr->getCellInParallel();
    int totalCells = cellSeries * cellParallel;

    CurrentResultData.resize(totalCells);
    VoltageResultData.resize(totalCells);
    TemperatureResultData.resize(totalCells);
    SOCResultData.resize(totalCells);

    std::vector<double> currentSetPointData = SimulationData->getColumn("pack_current_A");
    std::vector<double> timeStampData = SimulationData->getColumn("timestamp_ms");
    std::vector<double> cellVoltageData;

    int stepCount = SimulationData->getRowNumber();

    for (int i = 0; i < stepCount; i++)
    {
        std::vector<std::future<void>> futuresVector;

        CurrentPIDController->RunPIDController(currentSetPointData[i], CurrentPIDController->getCommand(), globalData.GlobalTimeStep);
        double cellCurrent = abs(BatteryPackPtr->getCellCurrent(CurrentPIDController->getCommand()));

        for (int j = 0; j < cellParallel; j++)
        {
            for (int k = 0; k < cellSeries; k++)
            {

                futuresVector.push_back(std::async(std::launch::async, [&, j, k]()
                                                   {
                                                    
                                                        int dataIndex = j * cellParallel + k;

                                                        cellVoltageData = SimulationData->getColumn(std::format("Cell{}_V", dataIndex));

                                                        BatteryPackPtr->calculateCellVoltage(cellCurrent);
                                                        BatteryPackPtr->claculateAverageTemperature(cellCurrent);

                                                        double cellVoltage = BatteryPackPtr->getCellVolatge(j, k);
                                                        double cellTemp = BatteryPackPtr->getCellTemperature(j, k);

                                                        EKFPerCell[dataIndex]->runExtendedKalmanFilter(cellCurrent,
                                                                                        cellVoltage,
                                                                                        cellVoltageData[i],
                                                                                        globalData.GlobalTimeStep,
                                                                                        CellModelPerCell[dataIndex].get());
                                                        double cellSOC = EKFPerCell[dataIndex]->getSOC();

                                                        CurrentResultData[dataIndex].push_back(cellCurrent);
                                                        VoltageResultData[dataIndex].push_back(cellVoltage);
                                                        TemperatureResultData[dataIndex].push_back(cellTemp);
                                                        SOCResultData[j * k].push_back(cellSOC); }));
            }
        }

        for (auto &future : futuresVector)
        {
            future.get();
        }

        progressCallBack(i);
    }
    BMSECUPtr->currentControl(BMSEvent::STOP);
}

bool &Simulation::getIsSimulationReady()
{
    return isSimulationReady;
}

const std::vector<std::string> &Simulation::getResultVectorNames()
{
    return ResultVectorNames;
}

const std::vector<std::vector<double>> &Simulation::getCurrentResultData()
{
    return CurrentResultData;
}

const std::vector<std::vector<double>> &Simulation::getVoltageResultData()
{
    return VoltageResultData;
}

const std::vector<std::vector<double>> &Simulation::getTemperatureResultData()
{
    return TemperatureResultData;
}

const std::vector<std::vector<double>> &Simulation::getSOCResultData()
{
    return SOCResultData;
}