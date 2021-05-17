#include <Wire.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>

#include "message_encoder.h"

// Create the lsm instance
Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();
// Create the message encoder
MessageEncoder enc = MessageEncoder();

void setupSensor();

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  // Set the I2C WIRE
  Wire.setSDA(PB9);
  Wire.setSCL(PB8);
  //activate USB CDC driver
  SerialUSB.begin();

  SerialUSB.println("LSM9DS1 data read demo");
  
  // LSM Begin
  lsm.begin();
  // Setup the sensor
  setupSensor();
}

// the loop function runs over and over again forever
void loop() {
  // Perform read
  lsm.read();
  // Get a new sensor event
  sensors_event_t a, m, g, t;
  lsm.getEvent(&a, &m, &g, &t); 
  // Encode
  uint8_t buffer[MessageEncoder::bufferSize];
  enc.Encode(buffer, &a, &g, &t);
  // Write
  SerialUSB.write(buffer, sizeof(buffer));
  // for (int i = 0; i < MessageEncoder::bufferSize; i++)
  // {
  //   SerialUSB.printf("%d ", buffer[i]);
  // }
  // SerialUSB.print("\n");
  // Toggle and delage
  digitalToggle(LED_BUILTIN);
  delay(200);
}

void setupSensor()
{
  // 1.) Set the accelerometer range
  lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_2G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_4G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_8G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_16G);
  
  // 2.) Set the magnetometer sensitivity
  lsm.setupMag(lsm.LSM9DS1_MAGGAIN_4GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_8GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_12GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_16GAUSS);

  // 3.) Setup the gyroscope
  lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_245DPS);
  //lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_500DPS);
  //lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_2000DPS);
}
