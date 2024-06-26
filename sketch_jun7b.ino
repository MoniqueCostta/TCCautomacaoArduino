#include <DHT.h>

#define LED_RED_PIN   9  // Pino PWM para o LED vermelho
#define LED_GREEN_PIN 10 // Pino PWM para o LED verde
#define LED_BLUE_PIN  11 // Pino PWM para o LED azul

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define SENSOR_PIN A0 // Pino comum para sensor de gás e fumaça
#define BUZZER_PIN 5
#define CHAMA_SENSOR_PIN A0
bool chamasDetected = false;
bool fumacaDetected = false;
bool gasDetected = false;

void setup() {
  Serial.begin(115200);  // Inicializa a comunicação serial
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  dht.begin();
}

void loop() {
  // Leitura dos sensores
  float umidade = dht.readHumidity();
  float temperatura = dht.readTemperature();
  if (isnan(umidade) || isnan(temperatura)) {
    Serial.println("Erro ao ler o sensor DHT");
  } else {
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" °C");
    Serial.print("Umidade: ");
    Serial.print(umidade);
    Serial.println(" %");

    // Envia os dados de temperatura e umidade para o ESP32
    Serial.println("DHT," + String(temperatura) + "," + String(umidade)); 
  }

  int sensorValue = analogRead(SENSOR_PIN);

  // Lógica para determinar se é fumaça ou gás
  if (sensorValue > 300 && !gasDetected) { // Ajuste o valor de 300 conforme necessário
    Serial.println("gasDetected"); // Envia mensagem para o ESP32
    digitalWrite(BUZZER_PIN, HIGH);
    gasDetected = true;
  } else if (sensorValue < 300 && !fumacaDetected) { // Ajuste o valor conforme necessário para detectar fumaça
    Serial.println("fumacaDetected"); // Envia mensagem para o ESP32
    fumacaDetected = true;
  } else {
    gasDetected = false;
    fumacaDetected = false;
    digitalWrite(BUZZER_PIN, LOW);
  }

  int chamas = digitalRead(CHAMA_SENSOR_PIN);
  if (chamas == LOW && !chamasDetected) {
    Serial.println("chamasDetected"); // Envia mensagem para o ESP32
    digitalWrite(BUZZER_PIN, HIGH);
    chamasDetected = true;
  } else {
    chamasDetected = false;
  }

  // Recebe comandos de cor via serial e ajusta os LEDs
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n'); // Leitura da linha de comando

    int commaIndex1 = command.indexOf(',');
    int commaIndex2 = command.indexOf(',', commaIndex1 + 1);

    if (commaIndex1 != -1 && commaIndex2 != -1) {
      int redValue = command.substring(0, commaIndex1).toInt();
      int greenValue = command.substring(commaIndex1 + 1, commaIndex2).toInt();
      int blueValue = command.substring(commaIndex2 + 1).toInt();
      setColor(redValue, greenValue, blueValue);
    } else {
      Serial.println("Comando inválido");
    }
  }

  delay(1000); // Ajuste conforme necessário
}

void setColor(int red, int green, int blue) {
  analogWrite(LED_RED_PIN, red);    // Ajusta a intensidade do vermelho
  analogWrite(LED_GREEN_PIN, green);  // Ajusta a intensidade do verde
  analogWrite(LED_BLUE_PIN, blue);   // Ajusta a intensidade do azul
}
