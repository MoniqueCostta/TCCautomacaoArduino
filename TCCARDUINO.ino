#include <DHT.h>
 
#define LED_RED_PIN   9  // Pino PWM para o LED vermelho
#define LED_GREEN_PIN 10 // Pino PWM para o LED verde
#define LED_BLUE_PIN  11 // Pino PWM para o LED azul
 
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
 
#define CHAMA_SENSOR_PIN A0
#define FUMACA_SENSOR_PIN A1
#define BUZZER_PIN 5
 
bool chamasDetected = false;
bool fumacaDetected = false;
bool gasDetected = false;
 
void setup() {
  Serial.begin(115200);  // Inicializa a comunicação serial
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);
  pinMode(CHAMA_SENSOR_PIN, INPUT_PULLUP);
  pinMode(FUMACA_SENSOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  dht.begin();
}
 
void loop() {
  // Leitura dos sensores
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
  if (chamas == LOW && !chamasDetected) {
    Serial.println("Atenção! Há chamas no ambiente!");
    digitalWrite(BUZZER_PIN, HIGH);
    chamasDetected = true;
  } else {
    chamasDetected = false;
  }
 
  int fumaca = digitalRead(FUMACA_SENSOR_PIN);
  if (fumaca == LOW && !fumacaDetected) {
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
 
  if (!chamasDetected && !fumacaDetected && !gasDetected) {
    digitalWrite(BUZZER_PIN, LOW);
  }
 
  // Recebe comandos de cor via serial e ajusta os LEDs
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n'); // Leitura da linha de comando
 
    int commaIndex1 = command.indexOf(',');
    int commaIndex2 = command.indexOf(',', commaIndex1 + 1);
 
    int redValue = command.substring(0, commaIndex1).toInt();
    int greenValue = command.substring(commaIndex1 + 1, commaIndex2).toInt();
    int blueValue = command.substring(commaIndex2 + 1).toInt();
 
    setColor(redValue, greenValue, blueValue);
  }
 
  delay(1000); // Ajuste conforme necessário
}
 
void setColor(int red, int green, int blue) {
  analogWrite(LED_RED_PIN, red);    // Ajusta a intensidade do vermelho
  analogWrite(LED_GREEN_PIN, green);  // Ajusta a intensidade do verde
  analogWrite(LED_BLUE_PIN, blue);   // Ajusta a intensidade do azul
}
