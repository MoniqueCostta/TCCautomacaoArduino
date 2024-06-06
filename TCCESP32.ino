// Código ESP32 com comunicação Wifi para o Blynk
#define BLYNK_TEMPLATE_ID "TMPL2KqGawTHM"
#define BLYNK_TEMPLATE_NAME "TCCarduinoCozinha"
#define BLYNK_AUTH_TOKEN "fJ4Z9g4gXqzDlfePQKmvxEEhEuoI5FZs"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
 
char auth[] = "fJ4Z9g4gXqzDlfePQKmvxEEhEuoI5FZs";
char ssid[] = "JOSELI";
char pass[] = "030879jo ";


 BlynkTimer timer;

 void setup(){
   Serial.begin(9600);
   Blynk.begin(auth, ssid, pass);
   timer.setInterval(1000L, checkSerial);
 }
 void loop(){
   Blynk.run();
   timer.run();
 }
 void checkSerial(){
   while(Serial.available()){
     String message = Serial.readStringUntil('\n');
     if(message.startsWith("DHT,")){
int commaIndex = message.indexOf(',');
int secondCommaIndex = message.indexOf(',', commaIndex + 1);
float temperatura = message.substring(commaIndex + 1, secondCommaIndex).toFloat();
float umidade = message.substring(secondCommaIndex + 1).toFloat();
      Blynk.virtualWrite(V1, temperatura);
      Blynk.virtualWrite(V0, umidade);
     } else if(message == "chamasDetected"){
       Blynk.logEvent("Atenção! Há chamas no ambiente.");
       Blynk.virtualWrite(V2,1);
     }else if(message == "fumacaDetected"){
      Blynk.logEvent("Atenção! Fumaça detectada, verifique o ambiente.");
      Blynk.virtualWrite(V3, 1);
     }else if(message == "gasDetected"){
      Blynk.logEvent("Atenção! Há vazamento de gás no ambiente, verifique o local.");
      Blynk.virtualWrite(V7, 1);
     }
     }
   }
 
