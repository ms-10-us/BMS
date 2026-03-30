#ifndef DTCMANAGER_H
#define DTCMANAGER_H

#include <vector>
#include <string>

enum class DTCCode
{
    OverVoltage,
    UnderVoltage,
    OverTemperature,
};

class DTCManager
{
private:
    std::vector<DTCCode> activeCodes;

public:
    void addDTCCode(DTCCode dtcCode);

    void clearDTCs();

    void printDTCs() const;

    bool hasFault() const;
};

#endif