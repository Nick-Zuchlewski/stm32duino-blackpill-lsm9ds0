# stm32duino-blackpill-lsm9ds0

The purpose of this project is tp provide accelerometer and gyro data to an RPI4 via serial (USB CDC VCOM). Although the project is named with a `lsm9ds0`, I am acutally using a `lsm9ds1`.

## Parts

This project uses a [Adafruit 9-DOF Accel/Mag/Gyro+Temp Breakout Board](https://www.adafruit.com/product/3387) and a [STM32F411 "BlackPill"](https://www.adafruit.com/product/4877). Both products can be purchased on Adafruit.

## Development

This porject uses [stm32duino](https://github.com/stm32duino/Arduino_Core_STM32), [Adafruit LSM9DS1](https://github.com/adafruit/Adafruit_LSM9DS1), and [VSCode IDE](https://code.visualstudio.com/) with the Arduino plugin. I am using the i2c (Wire) configuration. The encoding of the serial data use Little-Endian for floats. The frame is as follows:

    * Start - 0xFF
    * Message ID - 0x0B
    * Message Sequence ID - 1 byte
    * Message Len - 0x18
    * Accel X - 4 bytes (float)
    * Accel Y - 4 bytes (float)
    * Accel Z - 4 bytes (float)
    * Gyro X - 4 bytes (float)
    * Gyro Y - 4 bytes (float)
    * Gyro Z - 4 bytes (float)
    * CRC CCITT - 2 bytes (uint16)
