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
    BatteryPack &BatteryPackReference;
    DTCManager &DTCManagerReference;
    CANBus &CanReference;
    BatteryStateMachine &StateMachineReference;
    PIDController &CurrentPIDReference;
    ExtendedKalmanFilter &SOCEKFReference;

    void monitorTask();
    void safetyTask();
    void canTask();

public:
    BMSECU(BatteryPack &batteryPackReference,
           DTCManager &dtcManagerReference,
           CANBus &canBusReference,
           BatteryStateMachine &batteryStateMachineReference,
           PIDController &currentPIDReference,
           ExtendedKalmanFilter &socEKFReference);

    ~BMSECU();

    void StopAllTasks();

    void currentControl(BMSEvent bmsEvent);
};

#endif