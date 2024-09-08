#define DEBUGLOG_DEFAULT_LOG_LEVEL_INFO

#include <Arduino.h>
#include <DebugLog.h>

#include "touch.h"

String Touch::toString()
{
    char buffer[1000];

    sprintf(buffer, "touchNr_=%d, touchPin_=%d, threshold_=%d, touchedState_=%s",
            touchNr_,
            touchPin_,
            threshold_,
            touchedState_ ? "true" : "false");

    return buffer;
}

void Touch::setup()
{
    LOG_INFO("this touch: " + this->toString());
    pinMode(touchPin_, GPIO_MODE_INPUT);
}

void Touch::detectTouch(void (*touched)(int), void (*untouched)(int))
{
    touch_value_t currentTouch = touchRead(touchPin_);

    if (currentTouch < threshold_ && touchedState_ == false)
    {
        touchedState_ = true;
        touched(touchPin_);
        LOG_INFO("currentTouch=", currentTouch, ", ", this->toString());
    }
    else if (currentTouch >= threshold_ && touchedState_ == true)
    {
        touchedState_ = false;
        untouched(touchPin_);
        LOG_INFO("currentTouch=", currentTouch, ", ", this->toString());
    }
}
