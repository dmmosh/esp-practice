#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "HTTPClient.h"
#include "WiFi.h"
#include "ArduinoJson.h"
#include "../.pio/wifi_pass.h" // wifi pass, in .gitignore

WiFiClient server(80);


String input_string(){
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

    

    WiFi.begin(WIFI_NAME,WIFI_PASS);
    uint16_t seconds = 0;
    while(WiFi.status() != WL_CONNECTED){
        Serial.printf("Connecting... %is\n", seconds);
        seconds++;
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    Serial.printf("WiFi connected %is\n", seconds);
    Serial.print("ip: ");
    Serial.println(WiFi.localIP());

    JsonDocument doc;

    HTTPClient http;

    http.begin("https://httpbin.org/ip");
    uint16_t code = http.GET();
    if (code == 200){
        deserializeJson(doc, http.getString());
    }
    Serial.println((const char* )doc["origin"]);

    http.end();

    
    http.begin("https://api.open-meteo.com/v1/forecast?latitude=25.794588&longitude=-80.13483&hourly=temperature_2m");
    code = http.GET();

    if (code == 200)  {
        deserializeJson(doc,http.getString());
    }

    http.end();

    Serial.print((const char*)doc["timezone"]);
}

void loop() {
    if(WiFi.status() != WL_CONNECTED){
        Serial.println("WiFi disconnected.\n");
        vTaskDelay(1000/portTICK_PERIOD_MS);
        return;
    }
    


    vTaskDelay(1000/portTICK_PERIOD_MS);
}
