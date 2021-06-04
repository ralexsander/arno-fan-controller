/**
 *  This example will turn on and off the fan every 10 secs
 *  Este exemplo vai ligar e desligar o ventilador a cada 10 segundos
 */
#include "ArnoController.h"
#define RF_PIN 25
#define DEVICE_ID 4

ArnoController controller (RF_PIN, DEVICE_ID);

void setup() {}

void loop() {
    // Power on/off the light
    controller.send (LIGHT);
    delay (10000);
}
