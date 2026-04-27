#include "../../include/BMS/BatteryPack.h"
#include <iostream>

BatteryPack::BatteryPack(int &cellInSeries, int &cellInParallel)
    : CellInSeries(cellInSeries),
      CellInParallel(cellInParallel)
{

    batteryPackElectricModel.resize(CellInParallel);
    batteryPackThermalModel.resize(CellInParallel);

    for (int i = 0; i < CellInParallel; i++)
    {
        batteryPackElectricModel[i].resize(CellInSeries);
        batteryPackThermalModel[i].resize(CellInSeries);

        for (int j = 0; j < CellInSeries; j++)
        {
            batteryPackElectricModel[i][j] = new BatteryCellElectricalModel(globalData.GlobalCapacityAh,
                                                                            globalData.GlobalR0,
                                                                            globalData.GlobalR1,
                                                                            globalData.GlobalC1,
                                                                            globalData.GlobalInitialSOC,
                                                                            globalData.GlobalV1,
                                                                            globalData.GlobalVoltage,
                                                                            globalData.GlobalCurrent,
                                                                            globalData.dOCV_dSOC);

            batteryPackThermalModel[i][j] = new BatteryCellThermalModel(
                globalData.GlobalCellMass,
                globalData.GlobalCellCp,
                globalData.GlobalR1,
                globalData.GlobalInitialTemperature,
                globalData.GlobalTemperatureIncrease);
        }
    }
}

double BatteryPack::getCellCurrent(double &totalCurrent)
{
    return (totalCurrent / (double)CellInParallel);
}

void BatteryPack::calculateCellVoltage(double &batteryTotalCurrent)
{

    if (batteryTotalCurrent)
    {
        double currentInSeries = batteryTotalCurrent / (double)CellInParallel;

        for (int i = 0; i < CellInParallel; i++)
        {
            for (int j = 0; j < CellInSeries; j++)
            {
                batteryPackElectricModel[i][j]->RunRCModel(currentInSeries, globalData.GlobalTimeStep);
            }
        }
    }
}

double &BatteryPack::getCellVolatge(int cellRow, int cellCol)
{
    return batteryPackElectricModel[cellCol][cellCol]->getVoltage();
}

double BatteryPack::getTotalVoltage() const
{
    std::vector<double> voltageVector(CellInParallel, 0.0);

    for (int i = 0; i < CellInParallel; i++)
    {
        double voltageSum = 0.0;

        for (int j = 0; j < CellInSeries; j++)
        {
            voltageSum += batteryPackElectricModel[i][j]->getVoltage();
        }

        voltageVector[i] = voltageSum;
    }

    double voltageTotal = 0.0;

    for (int i = 0; i < CellInParallel; i++)
    {
        voltageTotal += voltageVector[i];
    }
    voltageTotal = voltageTotal / (double)CellInParallel;

    return voltageTotal;
}

void BatteryPack::claculateAverageTemperature(double &batteryTotalCurrent)
{
    double currentInSeries = batteryTotalCurrent / (double)CellInParallel;

    for (int i = 0; i < CellInParallel; i++)
    {
        for (int j = 0; j < CellInSeries; j++)
        {
            batteryPackThermalModel[i][j]->CalculateCellTemperature(currentInSeries, globalData.GlobalTimeStep);
        }
    }
}

double BatteryPack::getAverageTemperature()
{
    double sumTemperature = 0.0;

    for (int i = 0; i < CellInParallel; i++)
    {
        for (int j = 0; j < CellInSeries; j++)
        {
            sumTemperature += (double)batteryPackThermalModel[i][j]->getTemperature();
        }
    }

    return (sumTemperature + globalData.GlobalInitialTemperature);
}

double &BatteryPack::getCellTemperature(int cellRow, int cellCol)
{
    return batteryPackThermalModel[cellRow][cellCol]->getTemperature();
}

double BatteryPack::getAverageSOC()
{
    double sumSOC = 0.0;

    for (int i = 0; i < CellInParallel; i++)
    {
        for (int j = 0; j < CellInSeries; j++)
        {
            sumSOC += (double)batteryPackElectricModel[i][j]->getSOC();
        }
    }

    return ((sumSOC / (CellInParallel * CellInSeries)) * 100);
}

BatteryCellElectricalModel *BatteryPack::getBatteryCellElectricalModel(int cellRow, int cellCol)
{
    return batteryPackElectricModel[cellRow][cellCol];
}

void BatteryPack::printStatus()
{
    std::cout << "SOC: " << getAverageSOC() << " [%]\n"
              << "Battery Voltage: " << getTotalVoltage() << "[V]\n"
              << "Battery Temperature: " << getAverageTemperature() << "[degC]\n"
              << "\n";
}

int &BatteryPack::getCellInSeries()
{
    return CellInSeries;
}

int &BatteryPack::getCellInParallel()
{
    return CellInParallel;
}