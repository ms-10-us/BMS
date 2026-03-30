#ifndef BATTERYSTATEMACHINE_H
#define BATTERYSTATEMACHINE_H

enum class BMSState
{
    IDLE,
    CHARGING,
    DRIVING,
    FAULT
};

class BatteryStateMachine
{
private:
    BMSState currentBatteryState;

public:
    BatteryStateMachine();

    void setState(BMSState newState);

    BMSState getState() const;

    void printState() const;
};

#endif