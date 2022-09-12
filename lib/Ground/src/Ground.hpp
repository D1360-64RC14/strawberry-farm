#ifndef Ground_hpp
#define Ground_hpp

#include <Arduino.h>

class Ground {
public:
    Ground(uint8_t pin);
    void begin(bool pull_up = false);

    float getHumidity();

private:
    bool    began;
    uint8_t sensor_pin;
};

#endif