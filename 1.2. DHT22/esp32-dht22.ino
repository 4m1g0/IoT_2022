#include "DHTesp.h"
#include <WiFi.h>
 
const int DHT_PIN = 15;
 
DHTesp dhtSensor;
 
void setup() {
  Serial.begin(115200);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
 
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
  float temperature = dhtSensor.getTemperature();
  float humidity = dhtSensor.getHumidity();
  Serial.println("Temp: " + String(temperature, 2) + "°C");
  Serial.println("Humidity: " + String(humidity, 1) + "%");
  Serial.println("---");
  delay(1000);
}
