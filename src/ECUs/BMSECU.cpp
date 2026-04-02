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
    Running = false;
    monitorTaskThread = std::thread(&BMSECU::monitorTask, this);
    safetyTaskThread = std::thread(&BMSECU::safetyTask, this);
    canTaskThread = std::thread(&BMSECU::canTask, this);
    pidControllerThread = std::thread(&PIDController::RunPIDController, CurrentPIDPtr);
}

BMSECU::~BMSECU()
{
    Running = false;
    if (monitorTaskThread.joinable())
    {
        monitorTaskThread.join();
    }

    if (safetyTaskThread.joinable())
    {
        safetyTaskThread.join();
    }

    if (canTaskThread.joinable())
    {
        canTaskThread.join();
    }

    if (pidControllerThread.joinable())
    {
        pidControllerThread.join();
    }
}

void BMSECU::monitorTask()
{
    while (Running)
    {
        BatteryPackPtr->printStatus();
        std::this_thread::sleep_for(std::chrono::milliseconds(GlobalVariablePtr->ThreadSleepTime));
    }
}

void BMSECU::safetyTask()
{
    while (Running)
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

        if (batteryVoltage > 42)
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

        std::this_thread::sleep_for(std::chrono::milliseconds(GlobalVariablePtr->ThreadSleepTime));
    }
}

void BMSECU::canTask()
{
    while (Running)
    {
        float batteryVoltage = BatteryPackPtr->getTotalVoltage();
        CanPtr->sendMessage(0x100, "Voltage: " + std::to_string(batteryVoltage));

        std::this_thread::sleep_for(std::chrono::milliseconds(GlobalVariablePtr->ThreadSleepTime));
    }
}

void BMSECU::setGlobalVariable(GlobalVariables *globalData)
{
    GlobalVariablePtr = globalData;
}

void BMSECU::currentControl(double currentSetPoint, double currentMeasured, BMSEvent bmsEvent)
{
    if (bmsEvent != BMSEvent::STOP)
    {
        Running = true;

        StateMachinePtr->handleEvent(bmsEvent);

        CurrentPIDPtr->reset();
        CurrentPIDPtr->RunPIDController(currentSetPoint, currentMeasured, GlobalVariablePtr->GlobalTimeStep);
        monitorTask();
        safetyTask();
        canTask();
    }
    else
    {
        Running = false;
        StateMachinePtr->handleEvent(bmsEvent);
        BMSECU::~BMSECU();
    }
}
