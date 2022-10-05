#include "DHTesp.h"
#include <WiFi.h>
#include <PubSubClient.h>

const int DHT_PIN = 15;
const int BLUE_LED = 32;
const int RED_LED = 33;

DHTesp dhtSensor;
WiFiClient espClient;
PubSubClient client(espClient);

char* USERNAME = "****";
char* PASSWORD = "****";

unsigned long temperatureLastMillis = 0;

void setup() {
  Serial.begin(115200);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  // mqtt configuration
  client.setServer("tokio.****", 1883);

  // Conectando a la Wifi:
  Serial.print("Connecting to WiFi");
  WiFi.begin("Wokwi-GUEST", "");
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println(" Connected!");

  delay(3000); // esperamos 3 segundos para que se vea el print anterior
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
 
  client.loop();
 
  if (millis() - temperatureLastMillis > 1000) {
    temperatureLastMillis = millis();
    TempAndHumidity data = dhtSensor.getTempAndHumidity();
    Serial.println("Temp: " + String(data.temperature, 2) + "°C");
    Serial.println("Humidity: " + String(data.humidity, 1) + "%");
    Serial.println("---");
 
    client.publish("simulador/temperatura", String(data.temperature, 2).c_str());
    client.publish("simulador/humedad", String(data.humidity, 1).c_str());
  }
  delay(10);
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(String(esp_random()).c_str(), USERNAME, PASSWORD)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}