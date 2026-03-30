#include "../include/BMS/BatteryStateMachine.h"
#include <iostream>

using namespace std;

BatteryStateMachine::BatteryStateMachine()
{
    currentBatteryState = BMSState::IDLE;
}

void BatteryStateMachine::setState(BMSState newState)
{
    currentBatteryState = newState;
}

BMSState BatteryStateMachine::getState() const
{
    return currentBatteryState;
}

void BatteryStateMachine::printState() const
{
    switch (currentBatteryState)
    {
    case BMSState::IDLE:
        cout << "State IDLE\n";
        break;
    case BMSState::CHARGING:
        cout << "State Charging\n";
        break;
    case BMSState::DRIVING:
        cout << "State Driving\n";
        break;
    case BMSState::FAULT:
        cout << "State Fault\n";
        break;
    }
}