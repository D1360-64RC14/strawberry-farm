#ifndef Case_hpp
#define Case_hpp

#include <Arduino.h>

#define ON 1
#define OFF 0

class Fan {
public:
    Fan(uint8_t fan_pin);

    enum States {
        Running = true,
        Stopped = false
    };

    uint8_t pin;
    uint8_t speed;
    States state;
};

class Case {
public:
    Case(Fan *fan1, Fan *fan2, uint8_t red_led_pin, uint8_t yellow_led_pin, uint8_t buzzer_pin);
    void begin();

    // Fans
    void turnFansOff();
    void turnFansOn();
    void setFanSpeed(uint8_t speed);

    static uint8_t limit_speed_range(uint8_t speed);

    // LEDs
    void turnRedLed(bool state);
    void turnYellowLed(bool state);

    // Buzzer
    void bipBuzzer();

private:
    // Fans
    Fan *fans;
    uint8_t fan_count;

    // LEDs
    uint8_t red_led_pin;
    uint8_t yellow_led_pin;

    // Buzzer
    uint8_t buzzer_pin;
};

#endif