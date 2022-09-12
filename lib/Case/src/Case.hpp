#ifndef Case_hpp
#define Case_hpp

#include <Arduino.h>

struct Fan {
    enum States {
        Running = true,
        Stopped = false
    };

    uint8_t pin;

    States state;
    uint8_t speed;
};

class Case {
public:
    Case(Fan fan1, Fan fan2);
    void begin();

    void turnOff();
    void turnOn();
    void setFanSpeed(uint8_t speed);

    static uint8_t limit_speed_range(uint8_t speed);

private:
    Fan fans[2];
};

#endif