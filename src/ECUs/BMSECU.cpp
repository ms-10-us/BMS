#include "../../include/ECUs/BMSECU.h"

#include <iostream>
#include <chrono>

BMSECU::BMSECU(BatteryPack &batteryPackReference,
               DTCManager &dtcManagerReference,
               CANBus &canBusReference,
               BatteryStateMachine &batteryStateMachineReference,
               PIDController &currentPIDReference,
               ExtendedKalmanFilter &socEKFReference)
    : BatteryPackReference(batteryPackReference),
      DTCManagerReference(dtcManagerReference),
      CanReference(canBusReference),
      StateMachineReference(batteryStateMachineReference),
      CurrentPIDReference(currentPIDReference),
      SOCEKFReference(SOCEKFReference)
{
    globalData.RunningBMS = false;
}

BMSECU::~BMSECU()
{
    StopAllTasks();
}

void BMSECU::monitorTask()
{
    BatteryPackReference.printStatus();
}

void BMSECU::safetyTask()
{

    float batteryVoltage = BatteryPackReference.getTotalVoltage();
    float batteryTemperature = BatteryPackReference.getAverageTemperature();

    DTCManagerReference.clearDTCs();

    if (batteryTemperature >= 60.0)
    {
        DTCManagerReference.addDTCCode(DTCCode::OverTemperature);
    }

    if (batteryVoltage < 30.0)
    {
        DTCManagerReference.addDTCCode(DTCCode::UnderVoltage);
    }

    if (batteryVoltage > 100)
    {
        DTCManagerReference.addDTCCode(DTCCode::OverVoltage);
    }

    if (DTCManagerReference.hasFault())
    {
        StateMachineReference.handleEvent(BMSEvent::FAULT_DETECTED);
    }
    else
    {
        StateMachineReference.handleEvent(BMSEvent::FAULT_CLEARED);
    }
}

void BMSECU::canTask()
{
    float batteryVoltage = BatteryPackReference.getTotalVoltage();
    CanReference.sendMessage(0x100, batteryVoltage);
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

        StateMachineReference.handleEvent(bmsEvent);

        CurrentPIDReference.RunPIDController(CurrentPIDReference.getSetPoint(), CurrentPIDReference.getCommand(), globalData.GlobalTimeStep);
        CurrentPIDReference.ClampPIDCommand(globalData.GlobalPIDCurrentMinCommand, globalData.GlobalPIDCurrentMaxCommand);
        CurrentPIDReference.printCommand();
        BatteryPackReference.calculateCellVoltage(CurrentPIDReference.getCommand());
        BatteryPackReference.claculateAverageTemperature(CurrentPIDReference.getCommand());
        monitorTask();
        safetyTask();
        canTask();
    }
    else
    {
        globalData.RunningBMS = false;
        StateMachineReference.handleEvent(bmsEvent);
        BMSECU::~BMSECU();
    }
}
