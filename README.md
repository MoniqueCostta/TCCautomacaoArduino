Automacao Residencial com ESP32

📌 Descrição

Este projeto de automação residencial utiliza o ESP32 para monitoramento e controle remoto de ambientes domésticos. A proposta é aumentar a segurança e conforto através da integração de sensores e atuadores controlados pelo aplicativo Blynk.

🚀 Funcionalidades

📡 Monitoramento remoto via Blynk.

🔥 Detecção de fogo e gás para segurança do ambiente.

🌡 Medição de temperatura e umidade em tempo real.

💡 Controle de LEDs RGB e comuns para iluminação automatizada.

🚨 Alarme sonoro acionado em caso de anomalias detectadas.

🛠 Tecnologias Utilizadas

ESP32 – Microcontrolador principal

Sensores:

MQ-2 (detecção de gás)

Sensor de fogo

DHT11/DHT22 (temperatura e umidade)

Aplicativo Blynk – Interface para monitoramento e controle

Fonte de alimentação ajustável

⚙️ Como Funciona

Leitura de Sensores: O ESP32 recebe os dados dos sensores (fogo, gás, temperatura e umidade).

Processamento: Caso seja detectada alguma anormalidade, o sistema aciona um alarme.

Controle de Iluminação: O usuário pode ligar/desligar LEDs RGB e comuns pelo app Blynk.

Envio de Dados para o Blynk: O ESP32 se comunica via Wi-Fi para atualizar as informações em tempo real.

📦 Instalação e Uso

Pré-requisitos

ESP32 configurado com o Arduino IDE ou PlatformIO.

Conta no Blynk com um projeto configurado.

Sensores e atuadores conectados corretamente.

Passos

Clone este repositório:

git clone https://github.com/MoniqueCostta/TCCautomacaoArduino,git

Instale as bibliotecas necessárias na Arduino IDE:

BlynkSimpleEsp32.h

DHT.h

WiFi.h

Configure o código com as credenciais Wi-Fi e o token do Blynk.

Compile e carregue o código no ESP32.

Abra o Blynk App e comece a monitorar e controlar seu ambiente.

🖼 Demonstração

(Adicione imagens ou GIFs mostrando o funcionamento do sistema)

📄 Licença

Este projeto está sob a licença MIT - veja o arquivo LICENSE para mais detalhes.
