#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "HTTPClient.h"
#include "WiFi.h"

WiFiClient server(80);
String input;


String input_string(const bool pass){
    String out;
    while(1){
        if(Serial.available() >0){
            char curr = Serial.read();
            //str.trim();

            switch(curr){
                case '\n':
                    Serial.println();
                    return out;
                break;
                case '\b':
                    Serial.print('\b');
                    Serial.print(' ');
                    Serial.print('\b');
                    out.remove(input.length()-1);
                break;
                default:
                    out += curr;
                    Serial.print((pass) ? '*' : curr);
            }
        }
    }
}

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(10);

  String input1 = input_string(true);
  Serial.println(input1);
  String input2 = input_string(false);
  Serial.println(input2);
  
}
void loop() {



}

// void setup() {
//     Serial.begin(115200);
//     Serial.setTimeout(10);
//     Serial.println("Wifi name: ");
//     String name = Serial.readString();
//     while(*name.end() != '\n'){
//         vTaskDelay(5/portTICK_PERIOD_MS);
//     }   

//     Serial.println("Wifi password: ");
//     String pass = Serial.readString();
//     while(*pass.end() != '\n'){
//         vTaskDelay(5/portTICK_PERIOD_MS);
//     }   

//     WiFi.begin(name,pass);
//     uint16_t seconds = 0;
//     while(WiFi.status() != WL_CONNECTED){
//         Serial.printf("Connecting... %is\n", seconds);
//         seconds++;
//         vTaskDelay(1000/portTICK_PERIOD_MS);
//     }
//     Serial.println("WiFi connected %is\n");
//     Serial.println("ip: ");
//     Serial.println(WiFi.localIP());
// }

// void loop() {
//     if(WiFi.status() != WL_CONNECTED){
//         Serial.println("WiFi disconnected.\n");
//         vTaskDelay(1000/portTICK_PERIOD_MS);
//         return;
//     }



//     Serial.print("hi ");

//     vTaskDelay(1000/portTICK_PERIOD_MS);
// }
