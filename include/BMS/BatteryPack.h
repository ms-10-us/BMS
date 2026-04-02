#ifndef BATTERYPACK_H
#define BATTERYPACK_H

#include <vector>
#include "BatteryCellElectricalModel.h"
#include "BatteryCellThermalModel.h"
#include "GlobalVariables.h"

class BatteryPack
{
private:
    std::vector<std::vector<BatteryCellElectricalModel>> batteryPackElectricModel;
    std::vector<std::vector<BatteryCellThermalModel>> batteryPackThermalModel;
    int CellInSeries;
    int CellInParallel;
    GlobalVariables *GlobalVariablesPointer = nullptr;

public:
    BatteryPack(int cellInSeries, int cellInParallel);

    void setGlobalVariables(GlobalVariables *globalData);

    void createBatteryPack();

    void calculateCellVoltage(double soc);

    float getTotalVoltage() const;

    float getAverageTemperature();

    void printStatus();
};

#endif