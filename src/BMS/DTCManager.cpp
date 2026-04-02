#include "../../include/BMS/DTCManager.h"
#include <iostream>

using namespace std;

void DTCManager::addDTCCode(DTCCode dtcCode)
{
    activeCodes.push_back(dtcCode);
}

void DTCManager::clearDTCs()
{
    activeCodes.clear();
}

bool DTCManager::hasFault() const
{
    return !activeCodes.empty();
}

void DTCManager::printDTCs() const
{
    for (DTCCode code : activeCodes)
    {
        switch (code)
        {
        case DTCCode::OverVoltage:
            cout << "DTC: Over Volage\n";
            break;

        case DTCCode::UnderVoltage:
            cout << "DTC: Under Voltage\n";
            break;

        case DTCCode::OverTemperature:
            cout << "DTC: Over Temperature\n";
        }
    }
}
