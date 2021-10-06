#include <Wire.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>
#include "message_encoder.h"
#include "sample_buffer.h"

#define SAMPLE_RATE 10
#define SAMPLE_SIZE 20
#define AVG_ENABLE

// Create the lsm instance
Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();
// Create the message encoder
MessageEncoder enc = MessageEncoder();
// Create the ze sample buffer
SampleBuffer sampleBuffer = SampleBuffer(SAMPLE_SIZE);

void setupSensor();

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  // Set the I2C WIRE
  Wire.setSDA(PB9);
  Wire.setSCL(PB8);
  //activate USB CDC driver
  SerialUSB.begin();

  // SerialUSB.println("LSM9DS1");
  
  // LSM Begin
  lsm.begin();
  // Setup the sensor
  setupSensor();
}

// the loop function runs over and over again forever
void loop() {
  // Get a new sensor event
  sensors_event_t a, g;
  lsm.getEvent(&a, NULL, &g, NULL); 
  
  // Serial.print("Accel X: "); Serial.print(a.acceleration.x); Serial.print(" m/s^2");
  // Serial.print("\tY: "); Serial.print(a.acceleration.y);     Serial.print(" m/s^2 ");
  // Serial.print("\tZ: "); Serial.print(a.acceleration.z);     Serial.println(" m/s^2 ");

  // Serial.print("Gyro X: "); Serial.print(g.gyro.x);   Serial.print(" rad/s");
  // Serial.print("\tY: "); Serial.print(g.gyro.y);      Serial.print(" rad/s");
  // Serial.print("\tZ: "); Serial.print(g.gyro.z);      Serial.println(" rad/s");

  #ifdef AVG_ENABLE
    // Buffer and average
    if (sampleBuffer.Add(a, g))
    {
      // Average
      sensor_avg_t avg = sampleBuffer.Average();
      // Write
      Serial.print("Avg Accel X: ");  Serial.print(avg.a_x);  Serial.print(" m/s^2");
      Serial.print("\tY: ");          Serial.print(avg.a_y);  Serial.print(" m/s^2 ");
      Serial.print("\tZ: ");          Serial.print(avg.a_z);  Serial.println(" m/s^2 ");

      Serial.print("Avg Gyro X: ");   Serial.print(avg.g_x);  Serial.print(" rad/s");
      Serial.print("\tY: ");          Serial.print(avg.g_y);  Serial.print(" rad/s");
      Serial.print("\tZ: ");          Serial.print(avg.g_z);  Serial.println(" rad/s");
      // Encode and Write
      // uint8_t buffer[PACKET_SIZE];
      // enc.Encode(buffer, &avg);
      // SerialUSB.write(buffer, sizeof(buffer));
      // Blink
      digitalToggle(LED_BUILTIN);
    }
  #else
    // Encode and Write
    uint8_t buffer[PACKET_SIZE];
    enc.Encode(buffer, &a, &g);
    SerialUSB.write(buffer, sizeof(buffer));
    digitalToggle(LED_BUILTIN);
  #endif

  delay(SAMPLE_RATE);
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
