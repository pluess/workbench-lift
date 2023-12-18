#include <Arduino.h>
#include <WiFi.h>
#include <SPIFFS.h>
#include <AsyncTCP.h>
#include "credentials.h"
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

const char *PARAM_PWM = "pwm";
const char *PARAM_MODE = "mode";

void initWiFi()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi ..");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print('.');
        delay(1000);
    }
    Serial.println(WiFi.localIP());
}

void debugRequest(AsyncWebServerRequest *request)
{
    int args = request->args();
    Serial.println();
    Serial.println(request->url());
    for (int i = 0; i < args; i++)
    {
        Serial.printf("ARG[%s]: %s\n", request->argName(i).c_str(), request->arg(i).c_str());
    }
}

void setup()
{
    SPIFFS.begin();
    Serial.begin(9600);
    initWiFi();

    server.serveStatic("/index", SPIFFS, "/index.html");

    server.on("/set-pwm-allpwm", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        String pwm;
        String mode;
        debugRequest(request);
        if (request->hasParam(PARAM_PWM)) {
            pwm = request->getParam(PARAM_PWM)->value();
        } 
        if (request->hasParam(PARAM_MODE)) {
            mode = request->getParam(PARAM_MODE)->value();
        } 
        
       Serial.println("pwm="+pwm);
       Serial.println("mode="+mode);
       request->send(200); });

    server.on("/set-pwm-motor", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        String pwm;
        String mode;
        debugRequest(request);
        if (request->hasParam(PARAM_PWM)) {
            pwm = request->getParam(PARAM_PWM)->value();
        } 
        if (request->hasParam(PARAM_MODE)) {
            mode = request->getParam(PARAM_MODE)->value();
        } 
        
       Serial.println("pwm="+pwm);
       Serial.println("mode="+mode);
       request->send(200); });

    server.begin();
}

void loop()
{
    Serial.print('=');
    delay(2000);
}