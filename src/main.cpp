#include <Arduino.h>

#include <Air.hpp>
#include <Ground.hpp>

/*
--- Temperatura ----
  28°C: Alerta! Temperaturas acima de 25°C podem prejudicar o desenvolvimento de morangos.
  25°C: Fan no máximo
  20°C: Fan no mínimo
  15°C: Fan desligado
  12°C: Alerta! Temperaturas abaixo de 15°C podem prejudicar o desenvolvimento de morangos.
*/

/*
--- Humidade ---
  95%: Alerta! Um solo muito húmido é prejudicial ao morango.
 >90% por 20 minutos: Alerta! Morangos não toleram solo alagado.
  50%: Alerta! Solos secos podem prejudicar o desenvolvimento de morangos.
*/

// DHT sensor Lib: https://github.com/adafruit/DHT-sensor-library

#define HYGROMETER_PIN A0
#define DHT_TYPE       DHT11
#define DHT_PIN        A1

Air    air(DHT_PIN, DHT_TYPE);
Ground ground(HYGROMETER_PIN);

void setup() {
    Serial.begin(9600);

    air.begin();
    ground.begin();
}

void loop() {
    
}