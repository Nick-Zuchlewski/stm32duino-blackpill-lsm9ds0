#ifndef __MESSAGEENCODER_H__
#define __MESSAGEENCODER_H__

#include <Adafruit_Sensor.h>
#include <Adafruit_LSM9DS0.h>
#include "crc16_ccitt.h"
#include "sample_buffer.h"

#define START_CHAR 0xFF
#define MESSAGE_ID 0x0B
#define PAYLOAD_SIZE 0x18
#define HEADER_SIZE 0x04
#define CRC_SIZE 0x02
#define PACKET_SIZE (HEADER_SIZE + PAYLOAD_SIZE + CRC_SIZE)

class MessageEncoder
{
private:
    CRC16_CCITT crc16;
    uint8_t sequenceID;
public:
    MessageEncoder();
    ~MessageEncoder();

    void Encode(uint8_t* buffer, const sensors_event_t* a, const sensors_event_t* g);
    void Encode(uint8_t* buffer, const sensor_avg_t* avg);
};

#endif