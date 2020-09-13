#include "HBridgeController.h"

#include <Arduino.h>

namespace h_bridge_controller
{
    void Motor::setup(int enable, int input1, int input2)
    {
        _enable = enable;
        _input1 = input1;
        _input2 = input2;
        pinMode(_input1, OUTPUT);
        pinMode(_input2, OUTPUT);
        pinMode(_enable, OUTPUT);
    }

    void Motor::setVoltage(int speed, bool reverse)
    {
        analogWrite(_enable, speed);
        digitalWrite(_input1, ! reverse);
        digitalWrite(_input2, reverse);
    }

    void Encoder::setup(unsigned int irq_pin, void (*ISR_callback)(void), unsigned int delay)
    {
        this->_delay = delay;
        attachInterrupt(digitalPinToInterrupt(irq_pin), ISR_callback, RISING);
    }

    void Encoder::count(void)
    {
        unsigned long current = millis();
        if(current - this->_last < this->_delay)
            return;
        
        this->_counter++;  // increase +1 the counter value
        this->_last = current;
    }

    int Encoder::lap(void)
    {
        int times = this->_counter;
        this->_counter = 0;
        return times;
    }
}
