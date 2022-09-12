#include <Arduino.h>
#include <Ground.hpp>

Ground::Ground(uint8_t pin) {
    sensor_pin = pin;
    began = false;
}

void Ground::begin(bool pull_up = false) {
    began = true;

    if(began) {
        return;
    }

    if(pull_up) {
        pinMode(sensor_pin, INPUT_PULLUP);
    } else {
        pinMode(sensor_pin, INPUT);
    }
}

float Ground::getHumidity() {
    // read -> 100%
    // 1023 -> x%

    double reading = (double) analogRead(sensor_pin);
    return 100.0f - (float)(reading * 100.0 / 1023.0);
}