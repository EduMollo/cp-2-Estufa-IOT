Monitoramento Inteligente de Estufa com IoT
Descrição do projeto
Este projeto realiza o monitoramento em tempo real de uma estufa utilizando um ESP32 conectado a sensores físicos. Os dados coletados de temperatura, umidade e luminosidade são enviados via MQTT para o Node-RED, onde são processados, exibidos em dashboard e armazenados em banco de dados MySQL. O sistema também consome dados de uma API externa de clima, exibindo informações complementares no painel.

Objetivo
Desenvolver uma solução de monitoramento inteligente utilizando conceitos de Internet das Coisas (IoT), integração de sistemas e visualização de dados em tempo real.

Componentes utilizados
ESP32
Sensor DHT22
Sensor LDR
Protoboard e jumpers
Resistor de 10kΩ
Broker MQTT (HiveMQ)
Node-RED
MySQL
API OpenWeatherMap
Sensores
DHT22: mede temperatura e umidade
LDR: mede luminosidade
Comunicação MQTT
Os dados são enviados pelo ESP32 utilizando o protocolo MQTT.

Tópico utilizado
estufa1/sensores

Exemplo de payload
{
  "temperatura": 26.4,
  "umidade": 67.8,
  "luminosidade": 1450
}
Arquitetura da solução
Sensores → ESP32 → MQTT Broker → Node-RED → Dashboard / MySQL / API Externa

Banco de dados
Os dados recebidos são armazenados em uma tabela chamada leituras.

Dashboard
O dashboard desenvolvido no Node-RED apresenta:

temperatura interna
umidade interna
luminosidade
gráficos históricos
temperatura externa
umidade externa
condição climática
API externa
Foi utilizada a API OpenWeatherMap para obter informações climáticas externas da cidade configurada.

Estrutura do repositório
cp-2-Estufa-IOT/
├── esp32/
│   └── esp32_estufa.ino
├── node-red/
│   └── fluxo_node_red.json
├── database/
│   └── banco.sql
└── README.md
Como executar
1. Hardware
Conecte o DHT22 e o LDR ao ESP32.

2. Código do ESP32
Abra o arquivo esp32_estufa.ino na Arduino IDE
Configure SSID e senha do Wi‑Fi
Faça upload para o ESP32
3. Banco de dados
Execute o script banco.sql no MySQL
4. Node-RED
Importe o arquivo fluxo_node_red.json
Configure a conexão com MySQL
Configure sua chave da API OpenWeatherMap
Faça o deploy
5. Dashboard
Abra: http://localhost:1880/ui

Resultado esperado
O sistema exibirá em tempo real os dados dos sensores e do clima externo, além de registrar as leituras no banco de dados.
