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
    Motor(int motor,
          int bwPwmChannel,
          int fwPwmChannel,
          int defaultPwm) : motor_(motor),
                            bwPwmChannel_(bwPwmChannel),
                            fwPwmChannel_(fwPwmChannel),
                            defaultPwm_(defaultPwm),
                            currentPwm_(defaultPwm) {}

    int const motor() const { return motor_; }

    int defaultPwm() const { return defaultPwm_; }

    int currentPwm() const { return currentPwm_; }
    void setCurrentPwm(int currentPwm)
    {
        currentPwm_ = currentPwm;
        setPwm();
    }

    void resetPwn() { currentPwm_ = defaultPwm_; }

    void setDirection(const Direction direction)
    {
        currentDirection_ = direction;
        setPwm();
    }

private:
    int motor_;
    int defaultPwm_;
    int currentPwm_;
    int bwPwmChannel_;
    int fwPwmChannel_;
    Direction currentDirection_;

    void setPwm();
};

#endif