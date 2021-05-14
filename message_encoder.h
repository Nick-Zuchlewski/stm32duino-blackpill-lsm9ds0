#ifndef __MESSAGEENCODER_H__
#define __MESSAGEENCODER_H__

#include <Adafruit_Sensor.h>
#include <Adafruit_LSM9DS0.h>
#include "crc16_ccitt.h"

#define START_CHAR 0xFF
#define MESSAGE_ID 0x06
#define MESSAGE_LEN 0x19
#define HEADER_SIZE 0x03
#define PAYLOAD_SIZE MESSAGE_LEN

// Am lazy...
typedef Adafruit_LSM9DS0::lsm9ds0Vector_t vector_t; 

class MessageEncoder
{
private:
    CRC16_CCITT crc16;
public:
    MessageEncoder();
    ~MessageEncoder();

    void Encode(uint8_t* buffer, const vector_t* accelData, const vector_t* gyroData, const int16_t* temperature);

    static constexpr uint8_t bufferSize = HEADER_SIZE + PAYLOAD_SIZE + 2;
};

#endif