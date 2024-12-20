#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "HTTPClient.h"
#include "WiFi.h"

WiFiClient client(80);
String input;


inline String input_string(){
    String out;
    while(1){
        if(Serial.available() >0){
            char curr = Serial.read();
            //str.trim();
            switch(curr){
                case '\n':
                    if(out.length()>1){

                        Serial.println();
                        return out;
                    }
                    out = "";
                break;
                case '\b':
                    out.remove(out.length()-1);
                    Serial.print('\b');
                    Serial.print(' ');
                    Serial.print('\b');
                break;
                default:
                    out += curr;
                    Serial.print(curr);
                break;
            }
        }
    }
}


void setup() {
    Serial.begin(115200);
    Serial.setTimeout(10);
    Serial.print("Wifi name: ");
    String name = input_string();
    Serial.print(name);

    Serial.print("Wifi password: ");
    String pass = input_string();
    Serial.print(pass);

    WiFi.begin(name.c_str(),pass.c_str());
    uint16_t seconds = 0;
    while(WiFi.status() != WL_CONNECTED){
        Serial.printf("Connecting... %is\n", seconds);
        seconds++;
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    Serial.println("WiFi connected %is\n");
    Serial.println("ip: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    if(WiFi.status() != WL_CONNECTED){
        Serial.println("WiFi disconnected.\n");
        vTaskDelay(1000/portTICK_PERIOD_MS);
        return;
    }



    Serial.print("hi ");

    vTaskDelay(1000/portTICK_PERIOD_MS);
}
