#include "header.h"

void blink(){
    while(1){
        
        printf("On!\n");
        gpio_set_level(GPIO_NUM_2, 1);
        vTaskDelay(1000/portTICK_PERIOD_MS);
        printf("Off!\n");
        gpio_set_level(GPIO_NUM_2, 0);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}