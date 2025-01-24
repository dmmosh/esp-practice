#include <Arduino.h>
#include <stdio.h>
#include "driver/gpio.h"
#include "serial"




void app_main(void) {
    
    gpio_reset_pin(GPIO_NUM_2);
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);

    while(1){
        Serial.print
        printf("On\n");
        vTaskDelay(1000/portTICK_PERIOD_MS);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}