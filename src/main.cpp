#include <Arduino.h>
#include <WiFi.h>
#include <SPIFFS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <DebugLog.h>
#include <array>

#include "credentials.h"
#include "motor.h"

#define NOF_MOTORS 4

const char *PARAM_PWM = "pwm";
const char *PARAM_DIRECTION = "direction";
const char *PARAM_MOTOR = "motor";

const int FREQUENCY = 5000;
const int BIT_RESOLUTION = 10;

const int DEFAULT_PWM = 0;

// GPIO 0 and 2 should not be used
// see https://docs.espressif.com/projects/esptool/en/latest/esp32/advanced-topics/boot-mode-selection.html#manual-bootloader
const int MOTOR1_BW_PIN = 15;
const int MOTOR1_FW_PIN = 4;
const int MOTOR2_BW_PIN = 16;
const int MOTOR2_FW_PIN = 17;
const int MOTOR3_BW_PIN = 5;
const int MOTOR3_FW_PIN = 18;
const int MOTOR4_BW_PIN = 19;
const int MOTOR4_FW_PIN = 21;

AsyncWebServer server(80);

std::array<Motor, NOF_MOTORS> motorArray = {
    Motor(1, 0, 1, DEFAULT_PWM),
    Motor(2, 2, 3, DEFAULT_PWM),
    Motor(3, 4, 5, DEFAULT_PWM),
    Motor(4, 6, 7, DEFAULT_PWM)};

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

class RequestHander : public AsyncWebHandler
{
public:
    RequestHander(std::array<Motor, NOF_MOTORS> &motorArray) : motorArray_(motorArray) {}
    virtual ~RequestHander() {}

    bool canHandle(AsyncWebServerRequest *request)
    {
        int args = request->args();
        LOG_INFO("URL=", request->url());
        for (int i = 0; i < args; i++)
        {
            LOG_INFO("ARG ", request->argName(i).c_str(), "=", request->arg(i).c_str());
        }
        if (request->url() == "/setpwm" || request->url() == "/motor")
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void handleRequest(AsyncWebServerRequest *request)
    {
        if (request->url() == "/setpwm")
        {
            handleSetpwm(request);
        }
        else if (request->url() == "/motor")
        {
            handleMotor(request);
        }
        else
        {
            LOG_ERROR("Unknown request url: " + request->url());
            request->send(404);
        }
    }

private:
    std::array<Motor, NOF_MOTORS> &motorArray_;

    void handleSetpwm(AsyncWebServerRequest *request)
    {
        String pwm;
        String motor;
        if (request->hasParam(PARAM_PWM))
        {
            pwm = request->getParam(PARAM_PWM)->value();
        }
        if (request->hasParam(PARAM_MOTOR))
        {
            motor = request->getParam(PARAM_MOTOR)->value();
        }
        int motorIdx = motor.toInt() - 1;
        LOG_INFO("pwm=", pwm, "motorStr=[", motor, "],motor=", motorIdx);
        LOG_INFO("motorObj: " + motorArray[motorIdx].toString());
        motorArray[motorIdx].setCurrentPwm(pwm.toInt());

        request->send(200);
    }

    void handleMotor(AsyncWebServerRequest *request)
    {
        String direction;
        String motor;
        if (request->hasParam(PARAM_DIRECTION))
        {
            direction = request->getParam(PARAM_DIRECTION)->value();
        }
        if (request->hasParam(PARAM_MOTOR))
        {
            motor = request->getParam(PARAM_MOTOR)->value();
        }
        int motorIdx = motor.toInt() - 1;
        LOG_INFO("direction=", direction, "motorStr=[", motor, "], motorIdx=", motorIdx);
        LOG_INFO("motorObj: " + motorArray[motorIdx].toString());
        motorArray[motorIdx].setDirection(Motor::stringToDirection(direction));

        request->send(200);
    }
};

void setup()
{
    SPIFFS.begin();
    Serial.begin(9600);
    initWiFi();

    server.serveStatic("/index", SPIFFS, "/index.html");
    server.serveStatic("/index.js", SPIFFS, "/index.js");

    pinMode(MOTOR1_BW_PIN, OUTPUT);
    pinMode(MOTOR1_FW_PIN, OUTPUT);
    ledcSetup(0, FREQUENCY, BIT_RESOLUTION);
    ledcAttachPin(MOTOR1_BW_PIN, 0);
    ledcSetup(1, FREQUENCY, BIT_RESOLUTION);
    ledcAttachPin(MOTOR1_FW_PIN, 1);

    pinMode(MOTOR2_BW_PIN, OUTPUT);
    pinMode(MOTOR2_FW_PIN, OUTPUT);
    ledcSetup(2, FREQUENCY, BIT_RESOLUTION);
    ledcAttachPin(MOTOR2_BW_PIN, 2);
    ledcSetup(3, FREQUENCY, BIT_RESOLUTION);
    ledcAttachPin(MOTOR2_FW_PIN, 3);

    pinMode(MOTOR3_BW_PIN, OUTPUT);
    pinMode(MOTOR3_FW_PIN, OUTPUT);
    ledcSetup(4, FREQUENCY, BIT_RESOLUTION);
    ledcAttachPin(MOTOR3_BW_PIN, 4);
    ledcSetup(5, FREQUENCY, BIT_RESOLUTION);
    ledcAttachPin(MOTOR3_FW_PIN, 5);

    pinMode(MOTOR4_BW_PIN, OUTPUT);
    pinMode(MOTOR4_FW_PIN, OUTPUT);
    ledcSetup(6, FREQUENCY, BIT_RESOLUTION);
    ledcAttachPin(MOTOR4_BW_PIN, 6);
    ledcSetup(7, FREQUENCY, BIT_RESOLUTION);
    ledcAttachPin(MOTOR4_FW_PIN, 7);

    for (int i = 0; i < motorArray.size(); i++)
    {
        LOG_INFO("motorArray[", String(i), "]: ", motorArray[i].toString());
    }

    // LOG_INFO("motorArray[1]: ", motorArray[1].toString());

    server.begin();

    server.addHandler(new RequestHander(motorArray));
}

void loop()
{
    Serial.print('=');
    delay(2000);
}