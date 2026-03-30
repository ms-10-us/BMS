#include "../include/BMS/BatteryCell.h"
#include "../include/BMS/BatteryCellElectricalModel.h"
#include "../include/BMS/BatteryCellThermalModel.h"
#include <iostream>
using namespace std;

double GlobalCapacityAh = 2.5;        // Amp-hour
double GlobalR0 = 0.01;               // ohms
double GlobalR1 = 0.02;               // ohms
double GlobalC1 = 2000.0;             // mF
double GlobalInitialSOC = 1.0;        // no units
double GlobalSimTime = 10;            // sec
double GlobalTimeStep = 0.1;          // sec
double GlobalCellMass = 0.05;         // kg
double GlobalCellCp = 900;            // J/(kg·K)
double GlobalInitialTemperature = 25; // degC

int main()
{

    BatteryCellElectricalModel BMSElectricalModel = BatteryCellElectricalModel(GlobalCapacityAh, GlobalR0, GlobalR1, GlobalC1, GlobalInitialSOC);
    BatteryCellThermalModel BMSThermalModel = BatteryCellThermalModel(GlobalCellMass, GlobalCellCp, GlobalR0, GlobalInitialTemperature);
    double current = 0.0;

    for (int i = 0; i <= (GlobalSimTime / GlobalTimeStep); i++)
    {
        current += 0.25;

        BMSElectricalModel.RunRCModel(current, GlobalTimeStep);

        cout << "@time = " << GlobalTimeStep * i << endl;
        cout << "Voltage = " << BMSElectricalModel.getVoltage() << " V \n";
        cout << "SOC = " << BMSElectricalModel.getSOC() << endl;
        cout << "Current = " << current << " A \n";

        BMSThermalModel.CalculateCellTemperature(current, GlobalTimeStep);
        cout << "Cell Temperature = " << BMSThermalModel.getTemperature() << " degC \n";
        cout << "\n";
    }

    return 0;
}