#ifndef BATTERYCADMODEL_H
#define BATTERYCADMODEL_H

#include <string>

class BatteryCADModel
{
public:
    BatteryCADModel();

    void generateBatteryCADModel(const std::string &path);
};

#endif