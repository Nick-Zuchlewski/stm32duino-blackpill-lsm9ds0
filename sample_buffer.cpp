#include "sample_buffer.h"

SampleBuffer::SampleBuffer(uint8_t capacity):
    capacity(capacity)
{}

SampleBuffer::~SampleBuffer()
{
    Reset();
}

uint8_t SampleBuffer::Reset() 
{
    // Get the last index and reset
    uint8_t lastSize = size;
    size = 0;
    full = false;
    // Clear the buffers
    a_buffer_x.clear();
    a_buffer_y.clear();
    a_buffer_z.clear();
    g_buffer_x.clear();
    g_buffer_y.clear();
    g_buffer_z.clear();
    return lastSize;
}

bool SampleBuffer::Add(sensors_event_t const& a, sensors_event_t const& g)
{
    full = false;
    // Check if the sample buffers are full
    if (size >= capacity) 
    {
        return full = true;
    }
    // Add samples to buffer and increment the index
    a_buffer_x.push_back(a.acceleration.x);
    a_buffer_y.push_back(a.acceleration.y);
    a_buffer_z.push_back(a.acceleration.z);
    g_buffer_x.push_back(a.gyro.x);
    g_buffer_y.push_back(a.gyro.y);
    g_buffer_z.push_back(a.gyro.z);
    // Check if the sample buffers are full
    if (size >= ++capacity) full = true;
    return full;
}

sensor_avg_t SampleBuffer::Average() 
{
    sensor_avg_t sensor_avg;
    // Average each
    sensor_avg.a_x = AverageBuffer(a_buffer_x);
    sensor_avg.a_y = AverageBuffer(a_buffer_y);
    sensor_avg.a_z = AverageBuffer(a_buffer_z);
    sensor_avg.g_x = AverageBuffer(g_buffer_x);
    sensor_avg.g_y = AverageBuffer(g_buffer_y);
    sensor_avg.g_z = AverageBuffer(g_buffer_z);
    // Reset
    Reset();
}

float SampleBuffer::AverageBuffer(std::vector<float> const& buffer)
{
    float avg = 0;
    // Check if empty
    if (buffer.empty()) return avg;
    // Average
    avg = std::accumulate(buffer.begin(), buffer.end(), 0.0) / size;
    return avg;
}