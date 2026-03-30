#ifndef BATTERYCELL_H
#define BATTERYCELL_H

class BatteryCell
{
private:
    float Voltage;
    float Current;
    float Temperature;
    float SOC;

public:
    BatteryCell(float voltage, float current, float temperature, float soc);

    void updateCellParameters(float voltage, float current, float temperature, float soc);

    float getCellVoltage() const;

    float getCellCurrent() const;

    float getCellTemperature() const;

    float getCellSOC() const;
};

#endif