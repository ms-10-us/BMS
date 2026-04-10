#include "../include/BMS/BatteryCell.h"
#include "../include/BMS/BatteryCellElectricalModel.h"
#include "../include/BMS/BatteryCellThermalModel.h"
#include "../include/Utilities/CANBus.h"
#include "../include/ECUs/BMSECU.h"
#include "../include/Utilities/PIDController.h"
#include "../include/Utilities/GlobalVariables.h"
#include "../include/Utilities/PlottingTool.h"
#include "../include/Utilities/PlottingToolAsync.h"

#include <iostream>
#include <thread>

int main()
{

    int totalTimeStepCount = globalData.GlobalSimTime / globalData.GlobalTimeStep;

    double currentSetPoint;
    std::cout << "\nEnter Current Set Point: ";
    std::cin >> currentSetPoint;

    double currentKp;
    std::cout << "\nEnter Current Controller Proportional Gain: ";
    std::cin >> currentKp;

    double currentKi;
    std::cout << "\nEnter Current Controller Integral Gain: ";
    std::cin >> currentKi;

    double currentKd;
    std::cout << "\nEnter Current Controller Derivative Gain: ";
    std::cin >> currentKd;

    BatteryPack batteryPack = BatteryPack(7, 8);

    PIDController currentPIDController = PIDController(currentKp, currentKi, currentKd);
    currentPIDController.setSetPointPtr(&currentSetPoint);

    DTCManager dtcManager = DTCManager();

    CANBus canBUS = CANBus();

    BatteryStateMachine batteryStateMachine = BatteryStateMachine();

    BMSECU bmsECU = BMSECU(&batteryPack, &dtcManager, &canBUS, &batteryStateMachine, &currentPIDController);

    PlottingTool pidPlottingTool = PlottingTool("Time [sec]", "Current Command [Amp]", "PID Response Plot", "b-", 1);
    auto pidPlottingToolPtr = std::make_shared<PlottingTool>(pidPlottingTool);
    PlottingTool voltagePlottingTool = PlottingTool("Time [sec]", "Battery Voltage [V]", "Battery Pack Average Voltage", "r-", 2);
    auto voltagePlottingToolPtr = std::make_shared<PlottingTool>(voltagePlottingTool);
    PlottingTool socPlottingTool = PlottingTool("Time [sec]", "Battery SOC", "Battery Pack Average SOC [%]", "o-", 3);
    auto socPlottingToolPtr = std::make_shared<PlottingTool>(socPlottingTool);
    PlottingTool temperaturePlottingTool = PlottingTool("Time [sec]", "Battery Average Temperature", "Battery Pack Average Temeprature [degC]", "g-", 4);
    auto temperaturePlottingToolPtr = std::make_shared<PlottingTool>(temperaturePlottingTool);

    std::vector<std::shared_ptr<PlottingTool>> currentPlottingTool;
    currentPlottingTool.push_back(pidPlottingToolPtr);
    currentPlottingTool.push_back(voltagePlottingToolPtr);
    currentPlottingTool.push_back(socPlottingToolPtr);
    currentPlottingTool.push_back(temperaturePlottingToolPtr);

    for (int i = 0; i <= totalTimeStepCount; i++)
    {
        std::cout << "Time = " << globalData.GlobalTimeStep * i << " [sec]\n";
        bmsECU.currentControl(BMSEvent::START_DRIVING);

        pidPlottingToolPtr->addPoint(globalData.GlobalTimeStep * i, *currentPIDController.getCommandPtr());
        voltagePlottingToolPtr->addPoint(globalData.GlobalTimeStep * i, batteryPack.getTotalVoltage());
        socPlottingToolPtr->addPoint(globalData.GlobalTimeStep * i, batteryPack.getAverageSOC());
        temperaturePlottingToolPtr->addPoint(globalData.GlobalTimeStep * i, batteryPack.getAverageTemperature());

        PlottingToolAsync plottingToolAsync = PlottingToolAsync(currentPlottingTool);
        plottingToolAsync.PlotMultiplePlotsAsync();

        std::this_thread::sleep_for(std::chrono::milliseconds(globalData.ThreadSleepTime));
    }
    bmsECU.currentControl(BMSEvent::STOP);

    std::cin.get();

    return 0;
}