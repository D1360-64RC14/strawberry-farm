#include <Ground.hpp>

Ground::Ground(uint8_t pin) {
    sensor_pin = pin;
    began = false;
}

void Ground::begin(bool pull_up) {
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
    // 0    -> 100%
    // 1023 -> 0%

    long reading = (long) analogRead(sensor_pin);
    return map(reading, 0, 1023, 100, 0);
}