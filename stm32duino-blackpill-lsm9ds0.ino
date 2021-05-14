#include <Wire.h>
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_Sensor.h>

#include "message_encoder.h"

// Create the lsm instance
Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0();
// Create the message encoder
MessageEncoder enc = MessageEncoder();

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
   //activate USB CDC driver
  SerialUSB.begin();

    // 1.) Set the accelerometer range
  lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_2G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_4G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_6G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_8G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_16G);
  
  // 2.) Set the magnetometer sensitivity
  lsm.setupMag(lsm.LSM9DS0_MAGGAIN_2GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_4GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_8GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_12GAUSS);

  // 3.) Setup the gyroscope
  lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_245DPS);
  //lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_500DPS);
  //lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_2000DPS);
}

// the loop function runs over and over again forever
void loop() {
  // Perform read
  lsm.read();
  // Encode
  uint8_t buffer[MessageEncoder::bufferSize];
  enc.Encode(buffer, &lsm.accelData, &lsm.gyroData, &lsm.temperature);
  // Write
  SerialUSB.write(buffer, sizeof(buffer));
  // Toggle and delage
  digitalToggle(LED_BUILTIN);
  delay(100);
}
