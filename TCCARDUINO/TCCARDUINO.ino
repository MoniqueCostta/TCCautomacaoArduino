//Código arduino para ESP32 com comunicação serial

#include<DHT.h>

#define DHTPIN 2 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define CHAMA_SENSOR_PIN A0
#define FUMACA_SENSOR_PIN A1
#define BUZZER_PIN 5

bool chamasDetected = false;
bool fumacaDetected = false;
bool gasDetected = false;

void setup(){
  Serial.begin(9600);
  pinMode(CHAMA_SENSOR_PIN, INPUT_PULLUP);
  pinMode(FUMACA_SENSOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  dht.begin();
}

void loop(){
  float umidade = dht.readHumidity();
  float temperatura = dht.readTemperature();

 if (isnan(umidade) || isnan(temperatura)) {
 Serial.println("dhtError");
  } else {
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" °C");
    Serial.print("Umidade: ");
    Serial.print(umidade);
    Serial.println(" %");
  }
 int chamas = digitalRead(CHAMA_SENSOR_PIN);
  if(chamas == LOW && !chamasDetected) {
    Serial.println("Atenção! Há chamas no ambiente!");
    digitalWrite(BUZZER_PIN, HIGH);
    chamasDetected = true;
  } else {
    chamasDetected = false;
  }
 int fumaca = digitalRead(FUMACA_SENSOR_PIN);
  if(fumaca == LOW && !fumacaDetected) {
    Serial.println("Fumaça detectada! Verifique o ambiente.");
    fumacaDetected = true;
  } else {
    fumacaDetected = false;
  }

  int gas = analogRead(FUMACA_SENSOR_PIN);
  if (gas > 200 && !gasDetected) {
    Serial.println("Atenção! Há vazamento de gás no ambiente, verifique o local.");
    digitalWrite(BUZZER_PIN, HIGH);
    gasDetected = true;
  } else {
    gasDetected = false;
  }
  if(!chamasDetected && !fumacaDetected && !gasDetected){
    digitalWrite(BUZZER_PIN, LOW);
  }
delay(1000);
}
