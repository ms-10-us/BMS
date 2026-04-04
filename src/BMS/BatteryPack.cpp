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

            batteryPackElectricModel[i][j] = BatteryCellElectricalModel(
                globalData.GlobalCapacityAh,
                globalData.GlobalR0,
                globalData.GlobalR1,
                globalData.GlobalC1,
                globalData.GlobalInitialSOC);

            batteryPackThermalModel[i][j] = BatteryCellThermalModel(
                globalData.GlobalCellMass,
                globalData.GlobalCellCp,
                globalData.GlobalR1,
                globalData.GlobalInitialTemperature);
        }
    }
}

void BatteryPack::calculateCellVoltage(double *current)
{
    for (int i = 0; i < CellInParallel; i++)
    {
        for (int j = 0; j < CellInSeries; j++)
        {
            batteryPackElectricModel[i][j].RunRCModel(*current, globalData.GlobalTimeStep);
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

    return std::clamp(voltageTotal, static_cast<float>(globalData.VoltageMinValue), static_cast<float>(globalData.VoltageMaxValue));
}

float BatteryPack::getAverageTemperature()
{
    for (int i = 0; i < CellInParallel; i++)
    {
        for (int j = 0; j < CellInSeries; j++)
        {
            batteryPackThermalModel[i][j].CalculateCellTemperature(globalData.TestCurrent, globalData.GlobalTimeStep);
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
    std::cout << "Battery Temperature: " << getAverageTemperature() << "[degC]\n";
    std::cout << "\n";
}