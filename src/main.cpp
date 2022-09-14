#include <Arduino.h>

#include <Air.hpp>
#include <Ground.hpp>
#include <Case.hpp>

#include <tools.hpp>

/*
--- Temperatura ----
  28°C: Alerta! Temperaturas acima de 25°C podem prejudicar o desenvolvimento de morangos.
  25°C: Fan no máximo
  20°C: Fan no mínimo
  15°C: Fan desligado
  12°C: Alerta! Temperaturas abaixo de 15°C podem prejudicar o desenvolvimento de morangos.
*/

/*
--- Humidade do Solo ---
 >=95%: Alerta! Um solo muito húmido é prejudicial ao morango.
 >=90% por 20 minutos: Alerta! Morangos não toleram solo alagado.
 <=50%: Alerta! Solos secos podem prejudicar o desenvolvimento de morangos.
*/

// DHT sensor Lib: https://github.com/adafruit/DHT-sensor-library

// Pins
#define HYGROMETER_PIN A0
#define DHT_PIN        A1
#define FAN_LEFT_PIN   5
#define FAN_RIGHT_PIN  6
#define RED_LED_PIN    2
#define BUZZER_PIN     3
#define YELLOW_LED_PIN 4

#define DHT_TYPE       DHT11

Fan fan1(FAN_LEFT_PIN);
Fan fan2(FAN_RIGHT_PIN);

Air    air(DHT_PIN, DHT_TYPE);
Ground ground(HYGROMETER_PIN);
Case   casing(&fan1, &fan2, RED_LED_PIN, YELLOW_LED_PIN, BUZZER_PIN);

void setup() {
    Serial.begin(9600);

    air.begin();
    ground.begin();
    casing.begin();

    delay(500);

    // Initialization
    casing.turnRedLed(ON);
    casing.turnYellowLed(ON);
    casing.setFanSpeed(255);
    casing.bipBuzzer();

    delay(100);

    casing.turnRedLed(OFF);
    casing.turnYellowLed(OFF);

    delay(1000);

    casing.turnFansOff();

    delay(500);
}

uint64_t time_flooded_ground = 0;
bool ground_got_flood = false;

void loop() {
    float g_humidity = ground.getHumidity();
    float a_temperature = air.getTemperature();

    { // >= 95%: Alerta! Um solo muito húmido é prejudicial ao morango.
        if (g_humidity >= 95.0f || g_humidity <= 50.0f) {
            casing.turnRedLed(ON);
            casing.bipBuzzer();
        }
    }

    { // >= 90% por 20 minutos: Alerta! Morangos não toleram solo alagado.
        if (g_humidity >= 91.0f) {
            if (!ground_got_flood) {
                ground_got_flood = true;
                time_flooded_ground = millis();
            } else {
                // If time flooded bigger than 20 minutes
                if (millis() - time_flooded_ground >= 1000u * 60 * 20) {
                    casing.turnRedLed(ON);
                    casing.bipBuzzer();

                    ground_got_flood = false;
                }
            }
        }

        if (g_humidity < 89.0f) {
            ground_got_flood = false;
            casing.turnRedLed(OFF);
        }
    }

    { // <= 50%: Alerta! Solos secos podem prejudicar o desenvolvimento de morangos.
        if (g_humidity <= 49.0f) {
            casing.turnRedLed(ON);
            casing.bipBuzzer();
        }
        if (g_humidity >= 51.0f) {
            casing.turnRedLed(OFF);
        }
    }

    { // >= 25°C: Alerta! Temperaturas acima de 25°C podem prejudicar o desenvolvimento de morangos.
        if (a_temperature >= 26.0f) {
            casing.turnYellowLed(ON);
            casing.bipBuzzer();
        }
        if (a_temperature <= 24.0f) {
            casing.turnYellowLed(OFF);
        }
    }

    { // 25°C: Fan no máximo; 20°C: Fan no mínimo; 15°C: Fan desligado
        // Bellow 20°C fan will stay off
        uint8_t fan_speed = round(constrain(map(a_temperature, 20, 25, 0, 255), 0, 255));

        casing.setFanSpeed(fan_speed);
    }

    { // <= 15°C: Alerta! Temperaturas abaixo de 15°C podem prejudicar o desenvolvimento de morangos.
        if (a_temperature <= 14.0f) {
            casing.bipBuzzer();
            casing.turnYellowLed(ON);
        }
        if (a_temperature >= 15.0f) {
            casing.turnYellowLed(OFF);
        }
    }

    // Waits 1 minute.
    delay(1000u * 60 * 1);
}