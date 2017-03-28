#include "Nova_Ultrasonic_analog.h"

Ultrasonic_analog::Ultrasonic_analog(uint8_t pin)
{
	_Ultrasonic_analog_pin = pin;
}

int Ultrasonic_analog::distance_analog(void)
{
	float   n = analogRead(_Ultrasonic_analog_pin);    //读取A0口的电压值
 
 	float vol = ((n/1024))*200+1; 
 	return (int)vol;
}


