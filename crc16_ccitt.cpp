#include "crc16_ccitt.h"

CRC16_CCITT::CRC16_CCITT() {
	crc = 0;
}

CRC16_CCITT::~CRC16_CCITT() {}

uint16_t CRC16_CCITT::AddByte(uint8_t data) 
{
    uint8_t i;
    crc = crc ^ ((uint16_t)data << 8);
    for (i = 0; i < 8; i++) 
    {
        if (crc & 0x8000)
            crc = (crc << 1) ^ POLY;
        else
            crc <<= 1;
    }
    return crc;
}

uint16_t CRC16_CCITT::AddBuffer(const uint8_t *data_p, uint8_t length) 
{
    while(length--) 
    {
        AddByte(*data_p++);
    }
    return crc;
}

uint16_t CRC16_CCITT::Checksum() const { return crc; }

void CRC16_CCITT::Reset() { crc = 0; }

void CRC16_CCITT::ToBuffer(uint16_t crc, uint8_t (&buffer)[2])
{
    buffer[0] = (crc & 0xFF);
    buffer[1] = (crc >> 8);
}

uint16_t CRC16_CCITT::ToUINT16(const uint8_t (&buffer)[2]){
    return ((uint16_t)buffer[1] << 8 | buffer[0]);
}

bool CRC16_CCITT::operator==(const CRC16_CCITT& other)
{
    return crc == other.crc;
}