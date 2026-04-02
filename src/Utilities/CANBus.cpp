#include "../../include/BMS/CANBus.h"
#include <iostream>

using namespace std;

void CANBus::sendMessage(int id, const std::string &data)
{
    cout << "[CAN] ID: " << id << "Data: " << data << endl;
}