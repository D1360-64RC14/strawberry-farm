#ifndef Air_hpp
#define Air_hpp

#include <Arduino.h>
#include <DHT.h>

class Air {
public:
    Air(uint8_t pin, uint8_t sensor_type);
    void begin();

    float getTemperature();
    float getHumidity();

private:
    DHT dht;

    float last_temperature;
    float last_humidity;
};

#endif