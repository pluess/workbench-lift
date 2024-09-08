#ifndef TOUCH_H
#define TOUCH_H

#include <Arduino.h>

class Touch
{
public:
    Touch(int touchNr,
          int touchPin,
          touch_value_t threshold) : touchNr_(touchNr),
                                     touchPin_(touchPin),
                                     threshold_(threshold),
                                     touchedState_(false) {}

    void setup();
    void detectTouch(void (*touched)(int), void (*untouched)(int));
    String toString();

private:
    int touchNr_;
    int touchPin_;
    touch_value_t threshold_;
    boolean touchedState_;
};

#endif
