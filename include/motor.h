#include <Arduino.h>

#ifndef MOTOR_H
#define MOTOR_H

enum class Direction
{
    Backward,
    Forward,
    Off
};

class Motor
{
public:
    Motor(int motorNr,
          int bwPwmChannel,
          int fwPwmChannel,
          int defaultPwm) : motorNr_(motorNr),
                            bwPwmChannel_(bwPwmChannel),
                            fwPwmChannel_(fwPwmChannel),
                            defaultPwm_(defaultPwm),
                            currentPwm_(defaultPwm),
                            currentDirection_(Direction::Off) {}

    int const motorNr() const { return motorNr_; }

    int defaultPwm() const { return defaultPwm_; }

    int currentPwm() const { return currentPwm_; }
    void setCurrentPwm(int currentPwm)
    {
        currentPwm_ = currentPwm;
        drive();
    }

    void resetPwn() { currentPwm_ = defaultPwm_; }

    void setDirection(const Direction direction)
    {
        currentDirection_ = direction;
        drive();
    }

    String toString();

    static String directionToString(Direction direction);
    static Direction stringToDirection(String s);

private:
    int motorNr_;
    int defaultPwm_;
    int currentPwm_;
    int bwPwmChannel_;
    int fwPwmChannel_;
    Direction currentDirection_;

    void drive();
};

#endif