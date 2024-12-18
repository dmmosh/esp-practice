#include <Arduino.h>
#include "freertos/FreeRTOS.h"
const int8_t LED_ONBOARD = 2;
const int8_t LED_OUTSIDE = 15;

void blink(void* light){
    while(1){
        digitalWrite(*(int8_t*)light, HIGH);
        vTaskDelay(1000/portTICK_PERIOD_MS);
        digitalWrite(*(int8_t*)light, LOW);
        Serial.printf("LED NUM %i BLINKED\n", *(int*)light);
        vTaskDelay(1000/portTICK_PERIOD_MS);

    }

}


void setup() {
    Serial.begin(115200);
    pinMode(23, OUTPUT); // LED TO POWER other lights
    pinMode(LED_ONBOARD, OUTPUT);

    xTaskCreate(blink, "led blink",1028,(void*)(&LED_ONBOARD),1,NULL);
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
