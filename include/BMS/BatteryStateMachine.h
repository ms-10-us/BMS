#ifndef BATTERYSTATEMACHINE_H
#define BATTERYSTATEMACHINE_H

#include <map>

enum class BMSState
{
    IDLE,
    CHARGING,
    DRIVING,
    FAULT
};

enum class BMSEvent
{
    START_CHARGING,
    START_DRIVING,
    STOP,
    FAULT_DETECTED,
    FAULT_CLEARED
};

class BatteryStateMachine
{
private:
    BMSState CurrentBatteryState;

    std::map<std::pair<BMSState, BMSEvent>, BMSState> TransitionTable;

public:
    BatteryStateMachine();

    void handleEvent(BMSEvent event);

    BMSState getState() const;

    void printState() const;
};

#endif