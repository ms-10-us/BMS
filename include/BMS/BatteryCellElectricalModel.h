#ifndef BATTERYCELLELECTRICALMODEL_H
#define BATTERYCELLELECTRICALMODEL_H

class BatteryCellElectricalModel
{
private:
    double &CellCapacity;
    double &CellR0;
    double &CellR1;
    double &CellC1;
    double &CellSOC;
    double &CellV1;
    double &CellVoltage;
    double &CellCurrent;
    double &Cell_dOCV_dSOC;

public:
    BatteryCellElectricalModel(double &capacityAh,
                               double &r0,
                               double &r1,
                               double &c1,
                               double &initialSOC,
                               double &v1,
                               double &voltage,
                               double &current,
                               double &dOCV_dSOC);

    double CalculateOCV(double &soc) const;

    double Calculate_dOCV_dSOC(double &soc) const;

    void RunRCModel(double &current, double &dt);

    double &getVoltage() const;

    double &getSOC() const;

    double &get_dOCV_dSOC() const;
};

#endif