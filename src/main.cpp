#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#define LED 23


void blink(void* args){
    while(1){
        digitalWrite(LED, HIGH);
        vTaskDelay(1000/portTICK_PERIOD_MS);
        digitalWrite(LED, LOW);
        Serial.print("LED BLINKED. TESTING.\n");
        vTaskDelay(1000/portTICK_PERIOD_MS);

    }

}


void setup() {
    Serial.begin(115200);
    pinMode(LED, OUTPUT);

    xTaskCreate(blink, "led blink",1028,NULL,1,NULL);
  // put your setup code here, to run once:
}

/*
pio run --target upload
pio device monitor -b 115200
*/

void loop() {


    vTaskDelay(5/portTICK_PERIOD_MS);
  // put your main code here, to run repeatedly:
}
