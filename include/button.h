#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button
{
public:
    Button(int buttonNr,
           int buttonPin) : buttonNr_(buttonNr),
                            buttonPin_(buttonPin),
                            buttonState_(false),
                            lastReadTime_(0) {}

    void setup();
    void check(void (*touched)(int), void (*untouched)(int));
    String toString();

private:
    int buttonNr_;
    int buttonPin_;
    boolean buttonState_;
    unsigned long lastReadTime_;

    boolean debounce();
};

#endif
