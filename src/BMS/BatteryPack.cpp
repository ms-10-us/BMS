#include "../../include/BMS/BatteryPack.h"
#include <iostream>

BatteryPack::BatteryPack(int cellInSeries, int cellInParallel)
{
    CellInSeries = cellInSeries;
    CellInParallel = cellInParallel;

    batteryPackElectricModel.resize(CellInParallel);
    batteryPackThermalModel.resize(CellInParallel);

    for (int i = 0; i < CellInParallel; i++)
    {
        batteryPackElectricModel[i].resize(CellInSeries);
        batteryPackThermalModel[i].resize(CellInSeries);

        for (int j = 0; j < CellInSeries; j++)
        {

            batteryPackElectricModel[i][j] = BatteryCellElectricalModel();

            batteryPackThermalModel[i][j] = BatteryCellThermalModel();
        }
    }
}

void BatteryPack::setGlobalVariables(GlobalVariables *globalData)
{
    GlobalVariablesPointer = globalData;
}

void BatteryPack::createBatteryPack()
{
    for (int i = 0; i < CellInParallel; i++)
    {
        for (int j = 0; j < CellInSeries; j++)
        {
            if (GlobalVariablesPointer)
            {
                batteryPackElectricModel[i][j] = BatteryCellElectricalModel(
                    GlobalVariablesPointer->GlobalCapacityAh,
                    GlobalVariablesPointer->GlobalR0,
                    GlobalVariablesPointer->GlobalR1,
                    GlobalVariablesPointer->GlobalC1,
                    GlobalVariablesPointer->GlobalInitialSOC);

                batteryPackThermalModel[i][j] = BatteryCellThermalModel(
                    GlobalVariablesPointer->GlobalCellMass,
                    GlobalVariablesPointer->GlobalCellCp,
                    GlobalVariablesPointer->GlobalR1,
                    GlobalVariablesPointer->GlobalInitialTemperature);
            }
        }
    }
}

void BatteryPack::calculateCellVoltage(double soc)
{
    for (int i = 0; i < CellInParallel; i++)
    {
        for (int j = 0; j < CellInSeries; j++)
        {
            batteryPackElectricModel[i][j].RunRCModel((GlobalVariablesPointer->TestCurrent) / CellInParallel, GlobalVariablesPointer->GlobalTimeStep);
        }
    }
}

float BatteryPack::getTotalVoltage() const
{
    std::vector voltageVector(CellInParallel, 0);

    for (int i = 0; i < CellInParallel; i++)
    {
        float voltageSum = 0.0;

        for (int j = 0; j < CellInSeries; j++)
        {
            voltageSum += batteryPackElectricModel[i][j].getVoltage();
        }

        voltageVector[i] = voltageSum;
    }

    float voltageTotal = 0.0;

    for (int i = 0; i < CellInParallel; i++)
    {
        voltageTotal += voltageVector[i];
    }

    return (voltageTotal / (float)CellInParallel);
}

float BatteryPack::getAverageTemperature()
{
    for (int i = 0; i < CellInParallel; i++)
    {
        for (int j = 0; j < CellInSeries; j++)
        {
            batteryPackThermalModel[i][j].CalculateCellTemperature(GlobalVariablesPointer->TestCurrent, GlobalVariablesPointer->GlobalTimeStep);
        }
    }

    float sumTemperature = 0.0;

    for (int i = 0; i < CellInParallel; i++)
    {
        for (int j = 0; j < CellInSeries; j++)
        {
            sumTemperature += (float)batteryPackThermalModel[i][j].getTemperature();
        }
    }

    return sumTemperature / (float)(CellInParallel * CellInSeries);
}

void BatteryPack::printStatus()
{
    std::cout << "Battery Voltage: " << getTotalVoltage() << "[V]\n";
    std::cout << "Battery Temperature: " << getAverageTemperature() << "[degC]\v";
}