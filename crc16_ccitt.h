#ifndef __CRC16_CCITT_H__
#define __CRC16_CCITT_H__

#include <stddef.h>
#include <stdint.h>

///@brief CCITT Polynomial
///
#define POLY 0x1021

///@brief Provides a class to handle CRC16 CCITT (http://automationwiki.com/index.php/CRC-16-CCITT)
///
class CRC16_CCITT {
public:
    ///@brief Construct a crc16 ccitt object
    ///
    CRC16_CCITT();
    ///@brief Destroy the crc16 ccitt object
    ///
    ~CRC16_CCITT();

    ///@brief Takes a single byte and adds it to the internal crc
    ///
    ///@param data The single byte
    ///@return uint16_t (running CRC)
    uint16_t AddByte(uint8_t data);
    ///@brief 
    ///
    ///@param buffer Pointer to the "byte" array
    ///@param length Lenght of the "byte" array
    ///@return uint16_t (running CRC)
    uint16_t AddBuffer(const uint8_t *buffer, uint8_t length);
    ///@brief Getter for internal CRC
    ///
    ///@return uint16_t (running CRC)
    uint16_t Checksum() const;
    ///@brief Resets the internal CRC
    ///
    void Reset();

    ///@brief Converts a CRC (or any uint16) to a "byte" array of the size
    /// of two
    ///
    ///@param crc The CRC that we want to convert
    ///@param buffer The "byte" array reference
    static void ToBuffer(uint16_t crc, uint8_t (&buffer)[2]);
    ///@brief Converts a "byte" array to a CRC (uint16)
    ///
    ///@param buffer The "byte" array reference
    ///@return uint16_t (CRC)
    static uint16_t ToUINT16(const uint8_t (&buffer)[2]);

    ///@brief Provide a equivalent operator for the class
    ///
    ///@param other The other class to compare to
    ///@return true 
    ///@return false 
    bool operator==(const CRC16_CCITT& other);
private:
    ///@brief internal CRC 
    ///
    uint16_t crc;
};	

#endif