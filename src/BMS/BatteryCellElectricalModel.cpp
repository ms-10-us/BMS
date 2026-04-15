#include "../../include/BMS/BatteryCellElectricalModel.h"
#include <cmath>
#include <algorithm>

BatteryCellElectricalModel::BatteryCellElectricalModel(double &capacityAh,
                                                       double &r0,
                                                       double &r1,
                                                       double &c1,
                                                       double &initialSOC,
                                                       double &v1,
                                                       double &voltage,
                                                       double &current,
                                                       double &dOCV_dSOC)
    : CellCapacity(capacityAh),
      CellR0(r0),
      CellR1(r1),
      CellC1(c1),
      CellSOC(initialSOC),
      CellV1(v1),
      CellVoltage(voltage),
      CellCurrent(current),
      Cell_dOCV_dSOC(dOCV_dSOC)

{
}

double BatteryCellElectricalModel::CalculateOCV(double &soc) const
{
    return 3.0 + 1.2 * soc - 0.3 * pow(soc, 2) + 0.1 * pow(soc, 3);
}

double BatteryCellElectricalModel::Calculate_dOCV_dSOC(double &soc) const
{
    return 1.2 - 0.3 * 2 * soc + 0.1 * 3 * pow(soc, 2);
}

void BatteryCellElectricalModel::RunRCModel(double &current, double &dt)
{
    // Update SOC
    double dSOCdt = -current / CellCapacity;
    CellSOC += dSOCdt * dt;
    CellSOC = std::clamp(CellSOC, 0.0, 1.0);

    // Update RC Branch
    double dV1dt = (-CellV1 / (CellR1 * CellC1)) + current / CellC1;
    CellV1 += dV1dt * dt;

    // Voltage
    double ocv = CalculateOCV(CellSOC);
    CellVoltage = ocv - current * CellR0 - CellV1;
}

double &BatteryCellElectricalModel::getVoltage() const
{
    return CellVoltage;
}

double &BatteryCellElectricalModel::getSOC() const
{
    return CellSOC;
}

double &BatteryCellElectricalModel::get_dOCV_dSOC() const
{
    return Cell_dOCV_dSOC;
}