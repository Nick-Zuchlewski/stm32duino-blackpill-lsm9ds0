#include "message_encoder.h"

MessageEncoder::MessageEncoder()
{
    crc16 = CRC16_CCITT();
}

MessageEncoder::~MessageEncoder() {}

void  MessageEncoder::Encode(uint8_t* buffer, const sensors_event_t* a, const sensors_event_t* g) 
{
    // Reset the checksum
    crc16.Reset();
    // Header
    buffer[0] = START_CHAR;
    buffer[1] = MESSAGE_ID;
    buffer[2] = PAYLOAD_SIZE; // Payload size == Message len
    uint8_t index = 3;
    // Accel X, Y, Z
    memcpy((buffer+index), &a->acceleration.x, sizeof(float));
    index +=sizeof(float);
    memcpy((buffer+index), &a->acceleration.y, sizeof(float));
    index +=sizeof(float);
    memcpy((buffer+index), &a->acceleration.z, sizeof(float));
    index +=sizeof(float);
    // Gyro X, Y, Z
    memcpy((buffer+index), &g->gyro.x, sizeof(float));
    index +=sizeof(float);
    memcpy((buffer+index), &g->gyro.y, sizeof(float));
    index +=sizeof(float);
    memcpy((buffer+index), &g->gyro.z, sizeof(float));
    index +=sizeof(float);
    // Add CRC
    uint16_t checksum = crc16.AddBuffer(buffer, (HEADER_SIZE + PAYLOAD_SIZE));
    memcpy((buffer+index), &checksum, sizeof(uint16_t));
}