#include "../../include/BMS/BatteryCellThermalModel.h"
#include <cmath>

BatteryCellThermalModel::BatteryCellThermalModel()
{
}

BatteryCellThermalModel::BatteryCellThermalModel(double cellMass, double cellCp, double cellResistance, double cellInitialTemperature)
{
    CellMass = cellMass;
    CellCp = cellCp;
    CellResistance = cellResistance;
    CellTemperature = cellInitialTemperature;
}

void BatteryCellThermalModel::CalculateCellTemperature(double current, double timeStep)
{
    double dTdt = (1 / (CellMass * CellCp)) * pow(current, 2) * CellResistance;
    double DeltaCellTemperature = dTdt * timeStep;
    CellTemperature += DeltaCellTemperature;
}

double BatteryCellThermalModel::getTemperature() const
{
    return CellTemperature;
}