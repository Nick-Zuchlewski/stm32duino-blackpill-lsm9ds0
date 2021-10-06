#ifndef __SAMPLEBUFFER_H__
#define __SAMPLEBUFFER_H__

#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>
#include <vector>
#include <numeric>

typedef struct {
    float a_x;
    float a_y;
    float a_z;
    float g_x;
    float g_y;
    float g_z;
} sensor_avg_t;

class SampleBuffer
{
private:
    std::vector<float> a_buffer_x;
    std::vector<float> a_buffer_y;
    std::vector<float> a_buffer_z;
    std::vector<float> g_buffer_x;
    std::vector<float> g_buffer_y;
    std::vector<float> g_buffer_z;
    uint8_t capacity;
    uint8_t size;
    bool full;
    float AverageBuffer(std::vector<float> const& buffer);
public:
    SampleBuffer(uint8_t bufferSize);
    ~SampleBuffer();
    uint8_t Reset();
    bool Add(sensors_event_t const& a, sensors_event_t const& g);
    sensor_avg_t Average();
};

#endif