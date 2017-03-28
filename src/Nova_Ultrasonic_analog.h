#ifndef _NOVA_ULTRASONIC_ANALOG_H_
#define _NOVA_ULTRASONIC_ANALOG_H_
#include "Arduino.h"
#include "Nova.h"
class Ultrasonic_analog
{
public:
	Ultrasonic_analog(uint8_t pin);
	int distance_analog(void);
private:
    uint8_t _Ultrasonic_analog_pin;

};


#endif