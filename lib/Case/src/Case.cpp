#include <Case.hpp>

Fan::Fan(uint8_t fan_pin): pin(fan_pin), speed(0), state(Stopped) {}

Case::Case(Fan *fan1, Fan *fan2, uint8_t _red_led_pin, uint8_t _yellow_led_pin, uint8_t _buzzer_pin) {
    fans[0] = *fan1;
    fans[1] = *fan2;
    fan_count = 2;

    red_led_pin = _red_led_pin;
    yellow_led_pin = _yellow_led_pin;
    buzzer_pin = _buzzer_pin;
}

void Case::begin() {
    for (uint8_t i; i < fan_count; i++) {
        auto fan = fans[i];

        pinMode(fan.pin, OUTPUT);
    }

    pinMode(red_led_pin, OUTPUT);
    pinMode(yellow_led_pin, OUTPUT);
    pinMode(buzzer_pin, OUTPUT);
}

void Case::turnFansOn() {
    for (uint8_t i; i < fan_count; i++) {
        auto fan = fans[i];
        
        uint8_t l_speed = limit_speed_range(fan.speed);
        analogWrite(fan.pin, l_speed);
        fan.state = Fan::Running;
    }
}

void Case::turnFansOff() {
    for (uint8_t i; i < fan_count; i++) {
        auto fan = fans[i];

        analogWrite(fan.pin, 0);
        fan.state = Fan::Stopped;
    }
}

void Case::setFanSpeed(uint8_t speed) {
    uint8_t l_speed = Case::limit_speed_range(speed);

    for (uint8_t i; i < fan_count; i++) {
        auto fan = fans[i];

        analogWrite(fan.pin, l_speed);
        fan.speed = speed;
        fan.state = Fan::Running;
    }
}

#define FAN_SPEED_MAX 255
#define FAN_SPEED_MIN 83
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

void Case::turnRedLed(bool state) {
    if (state == ON) {
        digitalWrite(red_led_pin, HIGH);
    } else {
        digitalWrite(red_led_pin, LOW);
    }
}

void Case::turnYellowLed(bool state) {
    if (state == ON) {
        digitalWrite(yellow_led_pin, HIGH);
    } else {
        digitalWrite(yellow_led_pin, LOW);
    }
}

void Case::bipBuzzer() {
    tone(buzzer_pin, 1670, 200);
}