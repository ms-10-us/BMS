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
    DeltaCellTemperature = 0.0;
}

void BatteryCellThermalModel::CalculateCellTemperature(double *current, double timeStep)
{
    double dTdt = (1 / (CellMass * CellCp)) * pow(*current, 2) * CellResistance;
    DeltaCellTemperature += dTdt * timeStep;
}

double BatteryCellThermalModel::getTemperature() const
{
    return DeltaCellTemperature;
}