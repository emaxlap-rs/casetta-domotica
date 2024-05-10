#include "consts.h"
#include "rfid.h"

#include <ArduinoJson.h>
#include <WiFi.h>
#include <WebServer.h>
#include <SoftwareSerial.h>

SoftwareSerial LightsModule(NULL, 32); // RX, TX
SoftwareSerial GarageModule(NULL, 33);
SoftwareSerial FanModule(NULL, 25);
SoftwareSerial PumpModule(NULL, 26);
SoftwareSerial DoorModule(NULL, 27);

struct Status {
  bool lights[8];
  bool garage;
  bool fan;
  bool pump;
  bool door;
}status;

WebServer server(80);

void initModules() {
  LightsModule.begin(9600);
  LightsModule.write((byte)0);
  GarageModule.begin(9600);
  GarageModule.write((byte)0);
  FanModule.begin(9600);
  FanModule.write((byte)0);
  PumpModule.begin(9600);
  PumpModule.write((byte)0);
  DoorModule.begin(9600);
  DoorModule.write((byte)1);
  RFIDInit();
}
void initStatus() {
  for (int i = 0; i < 8; i++) {
    status.lights[i] = false;
  }
  status.garage = false;
  status.fan = false;
  status.pump = false;
  status.door = true;
}
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {}
}
void initWebServer() {
  server.on("/", []() {
    server.send(200, "text/html", INDEX);
  });

  server.on("/index.js", []() {
    server.send(200, "application/javascript", SCRIPT);
  });

  server.on("/style.css", []() {
    server.send(200, "text/css", STYLE);
  });

  server.on("/grid.css", []() {
    server.send(200, "text/css", GRID);
  });

  server.on("/switch.css", []() {
    server.send(200, "text/css", SWITCH);
  });

  server.on("/status.json", []() {
    if (server.args() > 0) {
      for (int i = 0; i < 8; i++) {
        if (!server.hasArg(String(i))) continue;
        if (server.arg(String(i)) == "true") status.lights[i] = true;
        else status.lights[i] = false;
      }
      status.garage = server.hasArg("garage") ? server.arg("garage") == "true" : status.garage;
      status.fan = server.hasArg("fan") ? server.arg("fan") == "true" : status.fan;
      status.pump = server.hasArg("pump") ? server.arg("pump") == "true" : status.pump;

      applyChanges();
    }
    
    String s = String("");
    JsonDocument doc;
    JsonArray lights = doc["lights"].to<JsonArray>();
    for (int i = 0; i < 8; i++) {
      lights.add(status.lights[i]);
    }
    doc["garage"] = status.garage;
    doc["fan"] = status.fan;
    doc["pump"] = status.pump;
    doc["door"] = status.door;
    serializeJson(doc, s);

    server.send(200, "application/json", s);
  });

  server.onNotFound([]() {
    server.send(404, "text/plain", "404 not found");
  });

  server.begin();
}

void setup() {
  Serial.begin(115200);
  char* t = "Initializing Modules";
  ESP_LOGI(TAG, "%s", t);
  initModules();
  ESP_LOGI(t, "OK");

  t = "Initializing data";
  ESP_LOGI(TAG, "%s", t);
  initStatus();
  ESP_LOGI(t, "OK");

  t = "Connecting to WiFi";
  ESP_LOGI(TAG, "%s", t);
  initWiFi();
  ESP_LOGI(t, "OK");

  t = "Initializing Webserver";
  ESP_LOGI(TAG, "%s", t);
  initWebServer();
  ESP_LOGI(t, "IP: %s", WiFi.localIP().toString().c_str());
  ESP_LOGI(t, "OK");
}

void applyChanges() {
  byte lights_byte = 0;
  for (int i = 0; i < 8; i++) {
    lights_byte |= ((status.lights[i] ? 1 : 0) << i);
  }
  LightsModule.write(lights_byte);
  GarageModule.write(status.garage ? (byte)1 : (byte)0);
  FanModule.write(status.fan ? (byte)1 : (byte)0);
  PumpModule.write(status.pump ? (byte)1 : (byte)0);
  DoorModule.write(status.door ? (byte)1 : (byte)0);
  ESP_LOGI(TAG, "Lights: 0x%X, Garage: 0x%X, Fan: 0x%X, Pump: 0x%X, Door: 0x%X", lights_byte, status.garage, status.fan, status.pump, status.door);
}

void loop() {
  server.handleClient();
  if (TryReceiveTag()) {
    LastTag().print();
    switch (LastTag().data()) {
      case OPEN_TAG:
        status.door = true;
        applyChanges();
        break;
      case CLOSE_TAG:
        status.door = false;
        applyChanges();
        break;
    }
  }
}
