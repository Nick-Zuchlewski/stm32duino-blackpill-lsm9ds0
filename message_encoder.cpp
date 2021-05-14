#include "message_encoder.h"

MessageEncoder::MessageEncoder()
{
    crc16 = CRC16_CCITT();
}

MessageEncoder::~MessageEncoder() {}

void  MessageEncoder::Encode(uint8_t* buffer, const vector_t* accelData, const vector_t* gyroData, const int16_t* temperature) 
{
    // Reset the checksum
    crc16.Reset();
    // Header
    buffer[0] = START_CHAR;
    buffer[1] = MESSAGE_ID;
    buffer[2] = MESSAGE_LEN;
    uint8_t index = 3;
    // Accel X, Y, Z
    memcpy((buffer+index), &accelData->x, sizeof(float));
    index +=sizeof(float);
    memcpy((buffer+index), &accelData->y, sizeof(float));
    index +=sizeof(float);
    memcpy((buffer+index), &accelData->z, sizeof(float));
    index +=sizeof(float);
    // Gyro X, Y, Z
    memcpy((buffer+index), &gyroData->x, sizeof(float));
    index +=sizeof(float);
    memcpy((buffer+index), &gyroData->y, sizeof(float));
    index +=sizeof(float);
    memcpy((buffer+index), &gyroData->z, sizeof(float));
    index +=sizeof(float);
    // Temp
    memcpy((buffer+index), temperature, sizeof(int16_t));
    index +=sizeof(int16_t);
    // Add CRC
    uint16_t checksum = crc16.AddBuffer(buffer, PAYLOAD_SIZE);
    memcpy((buffer+index), &checksum, sizeof(uint16_t));
}