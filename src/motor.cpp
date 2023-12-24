#include <Arduino.h>
#include <DebugLog.h>

#include "motor.h"

String Motor::toString()
{
    char buffer[1024];
    void *self = this;

    sprintf(buffer, "adr=%d, motorNr_=%d, currentDirection_=%s, currentPwm_=%d",
            self,
            motorNr_,
            directionToString(currentDirection_),
            currentPwm_);

    return buffer;
}

void Motor::drive()
{
    LOG_INFO("this motor: " + this->toString());
    switch (currentDirection_)
    {
    case (Direction::Backward):
        ledcWrite(bwPwmChannel_, currentPwm_);
        ledcWrite(fwPwmChannel_, 0);
        break;
    case (Direction::Forward):
        ledcWrite(bwPwmChannel_, 0);
        ledcWrite(fwPwmChannel_, currentPwm_);
        break;
    case (Direction::Off):
        ledcWrite(bwPwmChannel_, 0);
        ledcWrite(fwPwmChannel_, 0);
        break;
    default:
        LOG_ERROR("No currentDirection_ set.");
        break;
    }
}

String Motor::directionToString(Direction direction)
{
    switch (direction)
    {
    case (Direction::Backward):
        return "Backward";
    case (Direction::Forward):
        return "Forward";
    case (Direction::Off):
        return "Off";
    }
    return "undefined Direction enum";
}

Direction Motor::stringToDirection(String s)
{
    if (s == "Forward")
    {
        return Direction::Forward;
    }
    else if (s == "Backward")
    {
        return Direction::Backward;
    }
    else if (s == "Off")
    {
        return Direction::Off;
    }
    else
    {
        LOG_ERROR("No Direction defined for " + s);
        return Direction::Off;
    }
}
