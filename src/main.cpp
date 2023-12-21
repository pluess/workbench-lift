#include <Arduino.h>
#include <WiFi.h>
#include <SPIFFS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <DebugLog.h>
#include "credentials.h"
#include "motorhandler.h"

AsyncWebServer server(80);

const char *PARAM_PWM = "pwm";
const char *PARAM_MODE = "mode";
const char *PARAM_MOTOR = "motor";

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
    LOG_DEBUG("URL=", request->url());
    for (int i = 0; i < args; i++)
    {
        LOG_DEBUG("ARG ", request->argName(i).c_str(), "=", request->arg(i).c_str());
    }
}

void setup()
{
    SPIFFS.begin();
    Serial.begin(9600);
    initWiFi();

    server.serveStatic("/index", SPIFFS, "/index.html");
    server.serveStatic("/index.js", SPIFFS, "/index.js");

    server.on("/setpwm", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        String pwm;
        String mode;
        String motor;
        debugRequest(request);
        if (request->hasParam(PARAM_PWM)) {
            pwm = request->getParam(PARAM_PWM)->value();
        } 
        if (request->hasParam(PARAM_MODE)) {
            mode = request->getParam(PARAM_MODE)->value();
        } 
        if (request->hasParam(PARAM_MOTOR)) {
            motor = request->getParam(PARAM_MOTOR)->value();
        } 
        LOG_INFO("pwm=", pwm, ", mode=", mode, ", motor=", motor);

       request->send(200); });

    server.on("/motor", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        String mode;
        String motor;
        debugRequest(request);
        if (request->hasParam(PARAM_MODE)) {
            mode = request->getParam(PARAM_MODE)->value();
        } 
        if (request->hasParam(PARAM_MOTOR)) {
            motor = request->getParam(PARAM_MOTOR)->value();
        } 
        LOG_INFO("mode=", mode, ", motor=", motor);

       request->send(200); });

    server.begin();
}

void loop()
{
    Serial.print('=');
    delay(2000);
}