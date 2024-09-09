#define DEBUGLOG_DEFAULT_LOG_LEVEL_INFO

#include <Arduino.h>
#include <DebugLog.h>

#include "button.h"

const unsigned long DEBOUNCE_MILIS = 200;

String Button::toString()
{
    char buffer[200];

    sprintf(buffer, "buttonNr_=%d, buttonPin_=%d, buttonState_=%s",
            buttonNr_,
            buttonPin_,
            buttonState_ ? "true" : "false");

    return buffer;
}

void Button::setup()
{
    LOG_INFO("button: " + this->toString());
    pinMode(buttonPin_, INPUT_PULLUP);
}

void Button::check(void (*pushed)(int), void (*released)(int))
{
    int currentRead = digitalRead(buttonPin_);

    if (currentRead == 0 && buttonState_ == false)
    {
        if (!debounce())
        {
            buttonState_ = true;
            LOG_INFO("currentRead=", currentRead, ", ", this->toString());
            pushed(buttonPin_);
        }
    }
    else if (currentRead == 1 && buttonState_ == true)
    {
        if (!debounce())
        {
            buttonState_ = false;
            LOG_INFO("currentRead=", currentRead, ", ", this->toString());
            released(buttonPin_);
        }
    }
}

boolean Button::debounce()
{
    unsigned long now = millis();
    LOG_INFO("millis=", now);
    if (lastReadTime_ + DEBOUNCE_MILIS > now)
    {
        return true;
    }
    else
    {
        lastReadTime_ = now;
        return false;
    }
}
