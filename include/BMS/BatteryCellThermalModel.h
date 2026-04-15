#ifndef BATTERYCELLTHERMALMODEL_H
#define BATTERYCELLTHERMALMODEL_H

class BatteryCellThermalModel
{
private:
    double &CellMass;
    double &CellCp;
    double &CellResistance;
    double &CellTemperature;
    double &DeltaCellTemperature;

public:
    BatteryCellThermalModel(double &cellMass,
                            double &cellCp,
                            double &cellResistance,
                            double &cellInitialTemperature,
                            double &deltaCellTemperature);

    void CalculateCellTemperature(double &current, double &timeStep);

    double &getTemperature() const;
};

#endif