#include "../../include/ECUs/BMSECU.h"

#include <iostream>
#include <chrono>

BMSECU::BMSECU(BatteryPack *batteryPackPtr, DTCManager *dtcManagerPtr, CANBus *canBusPtr, BatteryStateMachine *batteryStateMachinePtr, PIDController *currentPIDPtr)
{
    BatteryPackPtr = batteryPackPtr;
    DTCManagerPtr = dtcManagerPtr;
    CanPtr = canBusPtr;
    StateMachinePtr = batteryStateMachinePtr;
    CurrentPIDPtr = currentPIDPtr;
    globalData.RunningBMS = false;
}

BMSECU::~BMSECU()
{
    StopAllTasks();
}

void BMSECU::monitorTask()
{

    if (BatteryPackPtr)
    {
        BatteryPackPtr->printStatus();
    }
}

void BMSECU::safetyTask()
{
    if (BatteryPackPtr)
    {
        float batteryVoltage = BatteryPackPtr->getTotalVoltage();
        float batteryTemperature = BatteryPackPtr->getAverageTemperature();

        DTCManagerPtr->clearDTCs();

        if (batteryTemperature >= 60.0)
        {
            DTCManagerPtr->addDTCCode(DTCCode::OverTemperature);
        }

        if (batteryVoltage < 30.0)
        {
            DTCManagerPtr->addDTCCode(DTCCode::UnderVoltage);
        }

        if (batteryVoltage > 100)
        {
            DTCManagerPtr->addDTCCode(DTCCode::OverVoltage);
        }

        if (DTCManagerPtr->hasFault())
        {
            StateMachinePtr->handleEvent(BMSEvent::FAULT_DETECTED);
        }
        else
        {
            StateMachinePtr->handleEvent(BMSEvent::FAULT_CLEARED);
        }
    }
}

void BMSECU::canTask()
{

    if (BatteryPackPtr)
    {
        float batteryVoltage = BatteryPackPtr->getTotalVoltage();
        CanPtr->sendMessage(0x100, &batteryVoltage);
    }
}

void BMSECU::StopAllTasks()
{
    globalData.RunningBMS = false;
}

void BMSECU::currentControl(BMSEvent bmsEvent)
{
    if (bmsEvent != BMSEvent::STOP)
    {
        globalData.RunningBMS = true;

        StateMachinePtr->handleEvent(bmsEvent);

        CurrentPIDPtr->RunPIDController(CurrentPIDPtr->getSetPointPtr(), CurrentPIDPtr->getCommandPtr(), globalData.GlobalTimeStep);
        CurrentPIDPtr->printCommand();
        BatteryPackPtr->calculateCellVoltage(CurrentPIDPtr->getCommandPtr());
        monitorTask();
        safetyTask();
        canTask();
    }
    else
    {
        globalData.RunningBMS = false;
        StateMachinePtr->handleEvent(bmsEvent);
        BMSECU::~BMSECU();
    }
}
