#include <Arduino.h>
#include "motor.h"

void Motor::setPwm()
{
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
    }
}
