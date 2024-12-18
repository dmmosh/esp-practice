#include <Arduino.h>
#include "freertos/FreeRTOS.h"



void setup() {
    Serial.begin(115200);
    
  // put your setup code here, to run once:
}

/*
pio run --target upload
pio device monitor -b 115200
*/

void loop() {
    Serial.print("fdksjljd");
    vTaskDelay(1000/portTICK_PERIOD_MS);
  // put your main code here, to run repeatedly:
}
