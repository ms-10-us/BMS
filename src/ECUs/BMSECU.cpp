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
}

BMSECU::~BMSECU()
{
    StopAllTasks();
}

void BMSECU::monitorTask()
{
    while (Running)
    {
        if (BatteryPackPtr)
        {
            BatteryPackPtr->printStatus();
            // std::this_thread::sleep_for(std::chrono::milliseconds(globalData.ThreadSleepTime));
        }
    }
}

void BMSECU::safetyTask()
{
    while (Running)
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

            // std::this_thread::sleep_for(std::chrono::milliseconds(globalData.ThreadSleepTime));
        }
    }
}

void BMSECU::canTask()
{
    while (Running)
    {
        if (BatteryPackPtr)
        {
            float batteryVoltage = BatteryPackPtr->getTotalVoltage();
            CanPtr->sendMessage(0x100, &batteryVoltage);

            // std::this_thread::sleep_for(std::chrono::milliseconds(globalData.ThreadSleepTime));
        }
    }
}

void BMSECU::StartAllTasks()
{
    if (!Running)
    {
        return;
    }

    if (!currentPIDThread.joinable())
    {
        currentPIDThread = std::thread(&PIDController::RunPIDController,
                                       CurrentPIDPtr,
                                       CurrentPIDPtr->getSetPointPtr(),
                                       CurrentPIDPtr->getCommandPtr(),
                                       globalData.GlobalTimeStep);
    }

    if (!batteryPackThread.joinable())
    {
        batteryPackThread = std::thread(&BatteryPack::calculateCellVoltage,
                                        BatteryPackPtr,
                                        CurrentPIDPtr->getCommandPtr());
    }

    if (!monitorTaskThread.joinable())
    {
        monitorTaskThread = std::thread(&BMSECU::monitorTask, this);
    }

    if (!safetyTaskThread.joinable())
    {
        safetyTaskThread = std::thread(&BMSECU::safetyTask, this);
    }

    if (!canTaskThread.joinable())
    {
        canTaskThread = std::thread(&BMSECU::canTask, this);
    }
}

void BMSECU::StopAllTasks()
{
    Running = false;

    if (currentPIDThread.joinable())
    {
        currentPIDThread.join();
    }

    if (batteryPackThread.joinable())
    {
        batteryPackThread.join();
    }

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
}

void BMSECU::currentControl(double *currentCommand, BMSEvent bmsEvent)
{
    if (bmsEvent != BMSEvent::STOP)
    {
        Running = true;

        StateMachinePtr->handleEvent(bmsEvent);

        if (currentCommand)
        {
            StartAllTasks();
        }
    }
    else
    {
        Running = false;
        StateMachinePtr->handleEvent(bmsEvent);
        BMSECU::~BMSECU();
    }
}
