#include <DHT.h>
#include <ArduinoJson.h>

#define DHTTYPE DHT11
#define DHTPIN 2

DHT dht(DHTPIN, DHTTYPE);

float humidity = 0, temperature = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float _humidity = dht.readHumidity();
  if (!isnan(_humidity) && _humidity != humidity) humidity = _humidity;
  float _temperature = dht.readTemperature();
  if (!isnan(_temperature) && _temperature != temperature) temperature = _temperature;

  JsonDocument data;
  data["humidity"] = humidity;
  data["temperature"] = temperature;
  
  serializeJson(data, Serial);
}
