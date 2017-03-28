#ifndef _NOVA_ULTRASONIC_DIGIT_H_
#define _NOVA_ULTRASONIC_DIGIT_H_
#include "Arduino.h"
#include "Nova.h"
class Ultrasonic_digit
{
public:
	Ultrasonic_digit( uint8_t port);
	double distance_digit(void);
private:
	uint8_t _Ultrasonic_pin;
	long measure(unsigned long timeout);

};


#endif