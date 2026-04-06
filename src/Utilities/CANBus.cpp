#include "../../include/Utilities/CANBus.h"
#include <iostream>

using namespace std;

CANBus::CANBus()
{
}

void CANBus::sendMessage(int id, const float *data)
{
    cout << "[CAN] ID: " << id << " Data: " << *data << endl;
    cout << "\n";
}