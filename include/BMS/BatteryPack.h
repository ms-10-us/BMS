#ifndef BATTERYPACK_H
#define BATTERYPACK_H

#include <vector>
#include "BatteryCellElectricalModel.h"
#include "BatteryCellThermalModel.h"
#include "../Utilities/GlobalVariables.h"
#include <algorithm>

class BatteryPack
{
private:
    std::vector<std::vector<BatteryCellElectricalModel>> batteryPackElectricModel;
    std::vector<std::vector<BatteryCellThermalModel>> batteryPackThermalModel;
    int CellInSeries;
    int CellInParallel;

public:
    BatteryPack(int cellInSeries, int cellInParallel);

    void calculateCellVoltage(double *batteryTotalCurrent);

    float getTotalVoltage() const;

    void claculateAverageTemperature(double *batteryTotalCurrent);

    float getAverageTemperature();

    void printStatus();
};

#endif