#include "instaspin_serial.h"

InstaspinSerial::InstaspinSerial(const std::string &port, uint32_t baud_rate):serial::Serial() {
    this->setPort(port);
    this->setBaudrate(baud_rate);
    this->setTimeout(1,100,1,1,1);
}

InstaspinSerial::~InstaspinSerial() {

}

void InstaspinSerial::setValue(uint8_t id, uint8_t type, void* value) {
    uint8_t checksum = 0x00;
    bool data_bool = *((bool*)value);
    float data_qv = *((float*)value);
    int data = (int)(16777216 * data_qv);
    size_t written_size = 0;
    switch (type){
        case TYPE_BOOL:
            this->send_buffer[0] = 0xFF;
            this->send_buffer[1] = id;
            this->send_buffer[2] = (uint8_t)data_bool;
            this->send_buffer[3] = 0x00;
            this->send_buffer[4] = 0x00;
            this->send_buffer[5] = 0x00;
            this->send_buffer[6] = TYPE_BOOL;
            checksum=this->send_buffer[0]^this->send_buffer[1]^this->send_buffer[2]^this->send_buffer[3]^this->send_buffer[4]^this->send_buffer[5]^this->send_buffer[6];
            this->send_buffer[7] = checksum;
            written_size = this->write(this->send_buffer, 8);
            break;
        case TYPE_FLOAT:
            break;
        case TYPE_QVALUE:
            this->send_buffer[0] = 0xFF;
            this->send_buffer[1] = id;
            this->send_buffer[2] = (uint8_t)((data&(0x000000FF)));
            this->send_buffer[3] = (uint8_t)((data&(0x0000FF00))>>8);
            this->send_buffer[4] = (uint8_t)((data&(0x00FF0000))>>16);
            this->send_buffer[5] = (uint8_t)((data&(0xFF000000))>>24);
            this->send_buffer[6] = TYPE_QVALUE;
            for(int i=0; i<7; i++) checksum^=this->send_buffer[i];
            this->send_buffer[7] = checksum;
            this->write(this->send_buffer, 8);
            break;
        default:
            ROS_ERROR("Wrong type inserted");
            break;
    }
}