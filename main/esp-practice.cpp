#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "driver/gpio.h"


extern "C"{
    void app_main(void);
}

void app_main(void)
{
    gpio_reset_pin(GPIO_NUM_2);
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);

    while(1){
        printf("On!\n");
        gpio_set_level(GPIO_NUM_2, 1);
        vTaskDelay(1000/portTICK_PERIOD_MS);
        printf("Off!\n");
        gpio_set_level(GPIO_NUM_2, 0);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}