/*
  esp32_mainlogic.ino
  author: emaxlap<lapennaemanuele@outlook.com>
*/

#include "consts.h"

#include <WiFi.h>
#include <WebServer.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

#define DHTModule Serial2
//SoftwareSerial DHTModule(26, 27); // RX, TX
SoftwareSerial LightsModule(32, 33); // RX, TX

WebServer server(80);

float humidity, temperature;

// task definitions
void TaskWebServer(void *pvParams);
void TaskPropagateData(void *pvParams);
void TaskReceiveData(void *pvParams);

// function definitions
void handleRoot();

void setup() {
  ESP_LOGI(TAG, "Setting up");

  ESP_LOGI(TAG, "Starting serial interfaces");
  DHTModule.begin(9600);
  LightsModule.begin(9600);
  //GarageModule.begin(9600);

  ESP_LOGI(TAG, "Connecting to wifi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    ESP_LOGI(TAG, ".");
  }

  ESP_LOGI(TAG, "Connected to %s, IP : %s", SSID, WiFi.localIP().toString());

  ESP_LOGI(TAG, "Initializing tasks");
  xTaskCreate(
    TaskWebServer,
    "Web Server",
    4096,
    NULL,
    1,
    NULL
  );
  xTaskCreate(
    TaskReadData,
    "Read serial data",
    2048,
    NULL,
    0,
    NULL
  );

  ESP_LOGI(TAG, "Ready");
}

void loop() {
  vTaskDelay(5000);
}

// tasks
void TaskWebServer(void *pvParams) {
  server.on("/", []() {
    server.send(200, "text/html", ROOT_PAGE);
  });

  server.on("/style.css", []() {
    server.send(200, "text/css", STYLE);
  });

  server.on("/lights", []() {
    if (server.hasArg("target")) {
      byte b = server.arg("target").toInt();
      LightsModule.write(b);
    }
    server.send(200, "text/html", LIGHTS_PAGE);
  });

  server.on("/temperature", []() {
    String s = String(TEMP_PAGE);
    String h = String(humidity);
    String t = String(temperature);
    s.replace("{humi}", h);
    s.replace("{temp}", t);
    server.send(200, "text/html", s);
  });

  server.onNotFound([]() {
    server.send(404, "text/plain", "404 not found");
  });

  server.begin();

  for (;;) {
    server.handleClient();
  }
}

void TaskReadData(void *pvParams) {
  for (;;) {
    JsonDocument DHTData;
    DeserializationError error = deserializeJson(DHTData, DHTModule);
    if (error) {
      ESP_LOGW(TAG, "Deserialization failed %s", error.f_str());
    }
    else {
      humidity = DHTData["humidity"];
      temperature = DHTData["temperature"];
    }
    vTaskDelay(200);
  }
}