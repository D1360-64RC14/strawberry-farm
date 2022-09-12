#include <Case.hpp>

Case::Case(Fan fan1, Fan fan2) {
    fans[0] = fan1;
    fans[1] = fan2;
}

void Case::begin() {
    for(Fan fan : fans) {
        pinMode(fan.pin, OUTPUT);
    }
}

void Case::turnOn() {
    for(Fan fan : fans) {
        uint8_t l_speed = limit_speed_range(fan.speed);
        analogWrite(fan.pin, l_speed);
        fan.state = Fan::Running;
    }
}

void Case::turnOff() {
    for(Fan fan : fans) {
        analogWrite(fan.pin, 0);
        fan.state = Fan::Stopped;
    }
}

void Case::setFanSpeed(uint8_t speed) {
    uint8_t l_speed = Case::limit_speed_range(speed);

    for(Fan fan : fans) {
        analogWrite(fan.pin, l_speed);
        fan.speed = speed;
    }
}

#define FAN_SPEED_MAX 255
#define FAN_SPEED_MIN 128
uint8_t Case::limit_speed_range(uint8_t speed) {
    // Motores não trabalham bem
    // com tensões muito baixas.
    // lr = limited range
    uint8_t lr_speed = (uint8_t) map(speed, 0, 255, FAN_SPEED_MIN, FAN_SPEED_MAX);

    if(lr_speed == FAN_SPEED_MIN) {
        lr_speed = 0;
    }

    return lr_speed;
}