#ifndef BATTERYCELLELECTRICALMODEL_H
#define BATTERYCELLELECTRICALMODEL_H

class BatteryCellElectricalModel
{
private:
    double CellR0;
    double CellR1;
    double CellC1;
    double CellCapacity;
    double CellSOC;
    double CellV1;
    double CellVoltage;
    double CellCurrent;

    double CalculateOCV(double soc) const;

public:
    BatteryCellElectricalModel();

    BatteryCellElectricalModel(double capacityAh, double r0, double r1, double c1, double initialSOC);

    void RunRCModel(double current, double dt);

    double getVoltage() const;

    double getSOC() const;

    double getCurrent() const;
};

#endif