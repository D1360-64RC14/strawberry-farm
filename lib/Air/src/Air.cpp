#include <Air.hpp>

Air::Air(uint8_t pin, uint8_t sensor_type): dht(pin, sensor_type) {
    last_temperature = 0;
    last_humidity = 0;
}

void Air::begin() {
    dht.begin();
}

float Air::getTemperature() {
    float actual_temperature = dht.readTemperature();

    if(isnan(actual_temperature)) {
        return last_temperature;
    }

    last_temperature = actual_temperature;
    return actual_temperature;
}

float Air::getHumidity() {
    float actual_humidity = dht.readHumidity();

    if(isnan(actual_humidity)) {
        return last_humidity;
    }

    last_humidity = actual_humidity;
    return actual_humidity;
}