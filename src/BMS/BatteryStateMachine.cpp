#include "../../include/BMS/BatteryStateMachine.h"
#include <iostream>

using namespace std;

BatteryStateMachine::BatteryStateMachine()
{
    CurrentBatteryState = BMSState::IDLE;

    TransitionTable[{BMSState::IDLE, BMSEvent::START_CHARGING}] = BMSState::CHARGING;
    TransitionTable[{BMSState::IDLE, BMSEvent::START_DRIVING}] = BMSState::DRIVING;

    TransitionTable[{BMSState::CHARGING, BMSEvent::STOP}] = BMSState::IDLE;
    TransitionTable[{BMSState::DRIVING, BMSEvent::STOP}] = BMSState::IDLE;

    TransitionTable[{BMSState::IDLE, BMSEvent::FAULT_DETECTED}] = BMSState::FAULT;
    TransitionTable[{BMSState::CHARGING, BMSEvent::FAULT_DETECTED}] = BMSState::FAULT;
    TransitionTable[{BMSState::DRIVING, BMSEvent::FAULT_DETECTED}] = BMSState::FAULT;

    TransitionTable[{BMSState::FAULT, BMSEvent::FAULT_CLEARED}] = BMSState::IDLE;
}

void BatteryStateMachine::handleEvent(BMSEvent event)
{
    auto key = std::make_pair(CurrentBatteryState, event);
    if (TransitionTable.find(key) != TransitionTable.end())
    {
        CurrentBatteryState = TransitionTable[key];
        printState();
    }
}

BMSState BatteryStateMachine::getState() const
{
    return CurrentBatteryState;
}

void BatteryStateMachine::printState() const
{
    switch (CurrentBatteryState)
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