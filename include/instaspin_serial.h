//
// Created by donghoonpark on 16. 8. 2.
//

#ifndef INSTASPIN_ROS_INSTASPIN_SERIAL_H
#define INSTASPIN_ROS_INSTASPIN_SERIAL_H

#include "ros/ros.h"
#include "serial/serial.h"
#include <thread>


#define TYPE_QVALUE 0x04
#define TYPE_INT    0x7B
#define TYPE_BOOL   0x23
#define TYPE_FLOAT  0x18

class InstaspinSerial:public serial::Serial{
public:
    InstaspinSerial(const std::string& port, uint32_t baud_rate);
    ~InstaspinSerial();
    void setValue(uint8_t id, uint8_t type, void* value);
private :
    void decode();
    uint8_t send_buffer[8];
    uint8_t receive_buffer[8];
};

#endif //INSTASPIN_ROS_INSTASPIN_SERIAL_H
