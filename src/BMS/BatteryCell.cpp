#include "../../include/BMS/BatteryCell.h"

BatteryCell::BatteryCell(float voltage, float current, float temperature, float soc)
{
    Voltage = voltage;
    Current = current;
    Temperature = temperature;
    SOC = soc;
}

void BatteryCell::updateCellParameters(float voltage, float current, float temperature, float soc)
{
    Voltage = voltage;
    Current = current;
    Temperature = temperature,
    SOC = soc;
}

float BatteryCell::getCellVoltage() const
{
    return Voltage;
}

float BatteryCell::getCellCurrent() const
{
    return Current;
}

float BatteryCell::getCellTemperature() const
{
    return Temperature;
}

float BatteryCell::getCellSOC() const
{
    return SOC;
}