#include <DHT.h>
#include <SoftwareSerial.h>

#define DHT_PIN 3
#define FAN_PIN 4

SoftwareSerial esp(2, NULL);

const float MAX_TEMP = 26; 
float last_temp = 0;

DHT dht(DHT_PIN, DHT11);
bool val = false;

void setup() {
  Serial.begin(9600);
  esp.begin(9600);
  pinMode(FAN_PIN, OUTPUT);
  dht.begin();
}

void loop() {
  if (esp.available() > 0) {
    val = esp.read();
    Serial.print("[SoftwareSerial] Received: 0x");
    Serial.println(val, HEX);
  }
  float t = dht.readTemperature();
  if (isnan(t)) {
    Serial.println("[Error] DHT sensor unavailable");
    delay(500);
    return;
  }
  digitalWrite(FAN_PIN, (t >= MAX_TEMP && val));
  if (last_temp != t) {
    Serial.print("[Update] Temperature: ");
    Serial.println(t);
    last_temp = t;
  }
}
