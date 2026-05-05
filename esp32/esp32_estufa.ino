#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

const char* ssid = "SEU_WIFI";
const char* password = "SUA_SENHA";

const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_topic = "estufa1/sensores";

WiFiClient espClient;
PubSubClient client(espClient);

#define DHTPIN 4
#define DHTTYPE DHT22
#define LDR_PIN 34

DHT dht(DHTPIN, DHTTYPE);

unsigned long ultimoEnvio = 0;
const long intervalo = 5000;

void conectarWiFi() {
  Serial.print("Conectando ao WiFi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void conectarMQTT() {
  while (!client.connected()) {
    Serial.print("Conectando ao broker MQTT...");
    String clientId = "ESP32Client-" + String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println(" conectado!");
    } else {
      Serial.print(" falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5s");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  conectarWiFi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    conectarMQTT();
  }

  client.loop();

  unsigned long agora = millis();
  if (agora - ultimoEnvio >= intervalo) {
    ultimoEnvio = agora;

    float temperatura = dht.readTemperature();
    float umidade = dht.readHumidity();
    int luminosidade = analogRead(LDR_PIN);

    if (isnan(temperatura) || isnan(umidade)) {
      Serial.println("Erro ao ler o DHT22");
      return;
    }

    String payload = "{";
    payload += "\"temperatura\":" + String(temperatura, 1) + ",";
    payload += "\"umidade\":" + String(umidade, 1) + ",";
    payload += "\"luminosidade\":" + String(luminosidade);
    payload += "}";

    Serial.println("Enviando: " + payload);
    client.publish(mqtt_topic, payload.c_str());
  }
}
