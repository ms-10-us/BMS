#ifndef BMSECU_H
#define BMSECU_H

#include "../BMS/BatteryPack.h"
#include "../BMS/DTCManager.h"
#include "../Utilities/CANBus.h"
#include "../BMS/BatteryStateMachine.h"
#include "../Utilities/PIDController.h"

class BMSECU
{
private:
    BatteryPack *BatteryPackPtr;
    DTCManager *DTCManagerPtr;
    CANBus *CanPtr;
    BatteryStateMachine *StateMachinePtr;
    PIDController *CurrentPIDPtr;

    void monitorTask();
    void safetyTask();
    void canTask();

public:
    BMSECU(BatteryPack *batteryPackPtr, DTCManager *dtcManagerPtr, CANBus *canBusPtr, BatteryStateMachine *batteryStateMachinePtr, PIDController *currentPIDPtr);

    ~BMSECU();

    void StopAllTasks();

    void currentControl(BMSEvent bmsEvent);
};

#endif