#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "WiFi.h"
#include <cstdlib>

WiFiServer server(80);
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
    pinMode(LED_ONBOARD, OUTPUT);
    pinMode(LED_OUTSIDE, OUTPUT); // LED TO POWER other esp chips

    digitalWrite(LED_OUTSIDE,HIGH);

    xTaskCreate(blink, "led blink",1028,(void*)(&LED_ONBOARD),1,NULL);


    Serial.print("Wifi name: ");
    String ssid = Serial.readString();
    Serial.print("Wifi password: ");
    String pass = Serial.readString();
    Serial.print("\n");
    WiFi.begin(ssid,pass);
    uint16_t seconds = 0;
    while(WiFi.status() != WL_CONNECTED){
        Serial.printf("Connecting to Wifi... %is\n", (unsigned int)seconds);
        vTaskDelay(1000/portTICK_PERIOD_MS);
        seconds++;
    }
    server.begin();
    Serial.printf("Wifi connected %is\n", seconds);
    Serial.printf("ip: %s\n",WiFi.localIP().toString().c_str());

  // put your setup code here, to run once:S
}

/*
pio run --target upload
pio device monitor -b 115200
*/

void loop() {

    vTaskDelay(5/portTICK_PERIOD_MS);
  // put your main code here, to run repeatedly:
}
