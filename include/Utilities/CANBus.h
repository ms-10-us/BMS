#ifndef CANBUS_H
#define CANBUS_H

#include <string>

class CANBus
{
public:
    CANBus();

    void sendMessage(int id, const float *data);
};

#endif