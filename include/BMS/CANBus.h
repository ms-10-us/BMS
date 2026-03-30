#ifndef CANBUS_H
#define CANBUS_H

#include <string>

class CANBus
{
public:
    void sendMessage(int id, const std::string &data);
};

#endif