#include <Arduino.h>

uint8_t percentToSpeed(long percent) {
    return map(percent, 0, 100, 0, 255);
}