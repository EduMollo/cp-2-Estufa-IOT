#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <ArduinoJson.h>

// Configurações Wi-Fi
const char* ssid     = "SEU_SSID";
const char* password = "SUA_SENHA";

// Configurações MQTT (HiveMQ público)
const char* mqtt_server = "broker.hivemq.com";
const int   mqtt_port   = 1883;
const char* mqtt_topic  = "estufa1/sensores";

// Pinos dos sensores
#define DHTPIN  4
#define DHTTYPE DHT22
#define LDR_PIN 34   // pino analógico

DHT dht(DHTPIN, DHTTYPE);
WiFiClient   espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.print("Conectando ao Wi-Fi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado. IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao broker MQTT...");
    String clientId = "ESP32Estufa-" + String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("conectado.");
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" – tentando novamente em 5 s");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  float temperatura  = dht.readTemperature();
  float umidade      = dht.readHumidity();
  int   ldrRaw       = analogRead(LDR_PIN);
  int   luminosidade = map(ldrRaw, 0, 4095, 0, 10000); // converte para lux aprox.

  if (isnan(temperatura) || isnan(umidade)) {
    Serial.println("Erro ao ler DHT22!");
    delay(2000);
    return;
  }

  StaticJsonDocument<128> doc;
  doc["temperatura"]  = temperatura;
  doc["umidade"]      = umidade;
  doc["luminosidade"] = luminosidade;

  char payload[128];
  serializeJson(doc, payload);

  Serial.print("Publicando: ");
  Serial.println(payload);
  client.publish(mqtt_topic, payload);

  delay(5000); // aguarda 5 segundos antes da próxima leitura
}
