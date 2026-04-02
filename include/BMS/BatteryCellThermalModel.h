#ifndef BATTERYCELLTHERMALMODEL_H
#define BATTERYCELLTHERMALMODEL_H

class BatteryCellThermalModel
{
private:
    double CellMass;
    double CellCp;
    double CellResistance;
    double CellTemperature;

public:
    BatteryCellThermalModel();

    BatteryCellThermalModel(double cellMass, double cellCp, double cellResistance, double cellInitialTemperature);

    void CalculateCellTemperature(double current, double timeStep);

    double getTemperature() const;
};

#endif