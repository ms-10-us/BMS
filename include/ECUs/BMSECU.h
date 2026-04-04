#ifndef BMSECU_H
#define BMSECU_H

#include "../BMS/BatteryPack.h"
#include "../BMS/DTCManager.h"
#include "../Utilities/CANBus.h"
#include "../BMS/BatteryStateMachine.h"
#include "../Utilities/PIDController.h"

#include <thread>
#include <atomic>

class BMSECU
{
private:
    BatteryPack *BatteryPackPtr;
    DTCManager *DTCManagerPtr;
    CANBus *CanPtr;
    BatteryStateMachine *StateMachinePtr;
    PIDController *CurrentPIDPtr;

    std::thread monitorTaskThread;
    std::thread safetyTaskThread;
    std::thread canTaskThread;
    std::thread currentPIDThread;
    std::thread batteryPackThread;

    std::atomic<bool> Running;

    void monitorTask();
    void safetyTask();
    void canTask();

public:
    BMSECU(BatteryPack *batteryPackPtr, DTCManager *dtcManagerPtr, CANBus *canBusPtr, BatteryStateMachine *batteryStateMachinePtr, PIDController *currentPIDPtr);

    ~BMSECU();

    void StartAllTasks();

    void StopAllTasks();

    void currentControl(double *currentCommand, BMSEvent bmsEvent);
};

#endif