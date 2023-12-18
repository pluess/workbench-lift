#include <Arduino.h>
#include <WiFi.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include "credentials.h"
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

const char* PARAM_MESSAGE = "message";

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(9600);
  initWiFi();

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("/");
    request->send(200, "text/plain", "Hello, world");
  });

      // Send a GET request to <IP>/get?message=<message>
    server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
        String message;
        if (request->hasParam(PARAM_MESSAGE)) {
            message = request->getParam(PARAM_MESSAGE)->value();
        } else {
            message = "No message sent";
        }
        Serial.println("/get");
        request->send(200, "text/plain", "Hello, GET: " + message);
    });


  server.begin();

}

void loop() {
    Serial.print('=');
    delay(2000);
}