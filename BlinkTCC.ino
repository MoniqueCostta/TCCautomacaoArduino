

#define BLYNK_TEMPLATE_ID "TMPL2RdDZOazj"
#define BLYNK_TEMPLATE_NAME "TccDomotica ArduinoCozinha"

#include <BlynkSimpleStream.h> // Biblioteca do Blynk
#include <DHT.h> // Biblioteca do DHT11

// Definindo as variáveis do Blynk para os sensores
BlynkTimer timer;

// Pins virtuais
int pinTemp = V1;   // Sensor de temperatura
int pinUmi = V0;    // Sensor de umidade
int pinFumaca = V3; // Sensor de fumaça
int pinChamas = V2; // Sensor de chamas
int alertaChamas = V4; // Buzzer que emitirá alerta sonoro em caso de presença de chamas
int pinGas = V7;    // Sensor de gás
int pinVermelho = V5; // Pin virtual do Blynk do led vermelho da fita 
int pinAzul = V6;  // led azul
int pinVerde = V9; // led verde

// Pins físicos
int buzzerPin = 5;     // Pin do alarme para ativar o buzzer
int chamasSensor = A0; // Pin do sensor de chamas
int dhtPin = 2;     // Pin do sensor DHT11
int gasFumacaSensorPin = A1; // Pin do sensor de gás
int ledRedPin  = 9; // Pin do led vermelho da fita RGB
int ledGreenPin = 10; // Pin do led verde da fita RGB
int ledBluePin = 11; // Pin do led azul da fita RGB

// Variáveis para controle de notificação
bool fogoFlag = false;
bool fumacaFlag = false;
bool gasFlag = false;

// Inicialização do sensor DHT
#define DHTTYPE DHT11
DHT dht(dhtPin, DHTTYPE);

void setup() {
  // Configuração dos pinos como saída ou entrada
  pinMode(buzzerPin, OUTPUT);
  pinMode(chamasSensor, INPUT_PULLUP);
  pinMode(gasFumacaSensorPin, INPUT);

  // Inicia a comunicação serial
  Serial.begin(9600);

  // Inicia o sensor DHT
  dht.begin();

  // Configuração do Blynk
  Blynk.begin(Serial, "fl4Z9g4gXqzDlfePQmvxEEhEuol5FZs");

  // Timer para leitura dos sensores
  timer.setInterval(1000L, leituraSensores);
}

void loop() {
  Blynk.run();
  timer.run(); // Executa as funções do timer
}

void leituraSensores() {
  // Leitura do sensor DHT (umidade e temperatura)
  float umidade = dht.readHumidity();
  float temperatura = dht.readTemperature();
  
  // Verifica se a leitura do sensor DHT falhou
  if (isnan(umidade) || isnan(temperatura)) {
    Blynk.virtualWrite(alertaChamas, "Falha ao ler do sensor de temperatura! Verifique se o componente está ligado corretamente");
    return;
  }

  // Envia as leituras para o Blynk
  Blynk.virtualWrite(pinTemp, temperatura);
  Blynk.virtualWrite(pinUmi, umidade);
  
  // Leitura do sensor de fumaça
  int fumaca = digitalRead(gasFumacaSensorPin);
  if (fumaca == HIGH && !fumacaFlag) {
    Blynk.logEvent("alerta_fumaca", "Alerta! Fumaça Detectada");
    fumacaFlag = true;
  } else if (fumaca == LOW) {
    fumacaFlag = false;
  }
  Blynk.virtualWrite(pinFumaca, fumaca);
  
  // Leitura do sensor de chamas
  int chamas = digitalRead(chamasSensor);
  if (chamas == HIGH && !fogoFlag) {
    Blynk.logEvent("alerta_fogo", "Alerta! Chamas Detectadas");
    fogoFlag = true;
    digitalWrite(buzzerPin, HIGH); // Ativa o alarme
  } else if (chamas == LOW) {
    fogoFlag = false;
  }
  Blynk.virtualWrite(pinChamas, chamas);

  // Leitura do sensor de gás
  int gas = analogRead(gasFumacaSensorPin);
  if (gas > 400 && !gasFlag) { // Supondo que 400 seja o limite para detecção de gás
    Blynk.logEvent("alerta_gas", "Alerta! Gás Detectado");
    gasFlag = true;
    digitalWrite(buzzerPin, HIGH); // Ativa o alarme
  } else if (gas <= 400) {
    gasFlag = false;
  }
  Blynk.virtualWrite(pinGas, gas);

  // Desativa o alarme se nenhuma condição perigosa for detectada
  if (!fumacaFlag && !fogoFlag && !gasFlag) {
    digitalWrite(buzzerPin, LOW);
  }
}

BLYNK_WRITE(pinVermelho) {
  int vermelhointensidade = param.asInt();
  analogWrite(ledRedPin, vermelhointensidade);
}

BLYNK_WRITE(pinAzul) {
  int azulintensidade = param.asInt();
  analogWrite(ledBluePin, azulintensidade);
}

BLYNK_WRITE(pinVerde) {
  int verdeintensidade = param.asInt();
  analogWrite(ledGreenPin, verdeintensidade);
}
