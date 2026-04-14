#ifndef BMSECU_H
#define BMSECU_H

#include "../BMS/BatteryPack.h"
#include "../BMS/DTCManager.h"
#include "../Utilities/CANBus.h"
#include "../BMS/BatteryStateMachine.h"
#include "../Utilities/PIDController.h"
#include "../ExtendedKalmanFilter/ExtendedKalmanFilter.h"

class BMSECU
{
private:
    BatteryPack *BatteryPackPtr;
    DTCManager *DTCManagerPtr;
    CANBus *CanPtr;
    BatteryStateMachine *StateMachinePtr;
    PIDController *CurrentPIDPtr;
    ExtendedKalmanFilter &SOCEKF;

    void monitorTask();
    void safetyTask();
    void canTask();

public:
    BMSECU(BatteryPack *batteryPackPtr,
           DTCManager *dtcManagerPtr,
           CANBus *canBusPtr,
           BatteryStateMachine *batteryStateMachinePtr,
           PIDController *currentPIDPtr,
           ExtendedKalmanFilter &socEKF);

    ~BMSECU();

    void StopAllTasks();

    void currentControl(BMSEvent bmsEvent);
};

#endif