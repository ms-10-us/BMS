#include "../include/BMS/BatteryCell.h"
#include "../include/BMS/BatteryCellElectricalModel.h"
#include "../include/BMS/BatteryCellThermalModel.h"
#include "../include/Utilities/CANBus.h"
#include "../include/ECUs/BMSECU.h"
#include "../include/Utilities/PIDController.h"
#include "../include/Utilities/GlobalVariables.h"
#include "../include/Utilities/PlottingTool.h"

#include <iostream>
#include <thread>

using namespace std;

int main()
{

    int totalTimeStepCount = globalData.GlobalSimTime / globalData.GlobalTimeStep;

    double currentSetPoint;
    cout << "\nEnter Current Set Point: ";
    cin >> currentSetPoint;

    double currentKp;
    cout << "\nEnter Current Controller Proportional Gain: ";
    cin >> currentKp;

    double currentKi;
    cout << "\nEnter Current Controller Integral Gain: ";
    cin >> currentKi;

    double currentKd;
    cout << "\nEnter Current Controller Derivative Gain: ";
    cin >> currentKd;

    BatteryPack batteryPack = BatteryPack(7, 8);

    PIDController currentPIDController = PIDController(currentKp, currentKi, currentKd);
    currentPIDController.setSetPointPtr(&currentSetPoint);

    DTCManager dtcManager = DTCManager();

    CANBus canBUS = CANBus();

    BatteryStateMachine batteryStateMachine = BatteryStateMachine();

    BMSECU bmsECU = BMSECU(&batteryPack, &dtcManager, &canBUS, &batteryStateMachine, &currentPIDController);

    PlottingTool pidPlottingTool = PlottingTool("Time [sec]", "Current Command [Amp]", "PID Response Plot");

    for (int i = 0; i <= totalTimeStepCount; i++)
    {
        cout << "Time = " << globalData.GlobalTimeStep * i << " [sec]\n";
        bmsECU.currentControl(BMSEvent::START_DRIVING);
        pidPlottingTool.addPoint(globalData.GlobalTimeStep * i, *currentPIDController.getCommandPtr());
        std::this_thread::sleep_for(std::chrono::milliseconds(globalData.ThreadSleepTime));
    }
    bmsECU.currentControl(BMSEvent::STOP);

    pidPlottingTool.plot();

    return 0;
}