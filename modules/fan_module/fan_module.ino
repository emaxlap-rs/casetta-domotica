#include <DHT.h>

#define DHT_PIN 2
#define FAN_PIN 3
#define DEBUG_LED LED_BUILTIN

const float MAX_TEMP = 25; 

DHT dht(DHT_PIN, DHT11);
bool val = false;

void setup() {
  Serial.begin(9600);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(DEBUG_LED, OUTPUT);
  dht.begin();
}

void loop() {
  if (Serial.available() > 0) {
    val = Serial.read();
  }
  float t = dht.readTemperature();
  if (isnan(t)) {
    for (int i = 0; i < 3; i++) {
      digitalWrite(DEBUG_LED, HIGH);
      delay(200);
      digitalWrite(DEBUG_LED, LOW);
      delay(200);
    }
    delay(500);
    return;
  }
  digitalWrite(FAN_PIN, (t >= MAX_TEMP && val)); 
}
