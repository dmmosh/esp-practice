#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "HTTPClient.h"
#include "WiFi.h"

WiFiClient server(80);
String input;

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(10);
}
void loop() {

  if (Serial.available() > 0) {
    input += Serial.readString();
    //str.trim();
    switch(*(input.end()-1))

    Serial.print('*');



    if (*(input.end()-1) == '\n'){
        Serial.print(input);
        input="";
    }
  }

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
