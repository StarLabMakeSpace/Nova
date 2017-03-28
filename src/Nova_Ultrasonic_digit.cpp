#include "Nova_Ultrasonic_digit.h"

Ultrasonic_digit::Ultrasonic_digit( uint8_t port)
{
	switch(port)
	  {
	    case S0:
	      _Ultrasonic_pin = S0_PIN;
	    break;
	    case S1:
	      _Ultrasonic_pin = S1_PIN;
	    break;
	    case S2:
	      _Ultrasonic_pin = S2_PIN;
	    break;
	    case S3:
	      _Ultrasonic_pin = S3_PIN;
	    break;
	    case A0:
	      _Ultrasonic_pin = A0;
	    break;
	    case A1:
	      _Ultrasonic_pin = A1;
	    break;
	    case A2:
	      _Ultrasonic_pin = A2;
	    break;
	    case A3:
	      _Ultrasonic_pin = A3;
	    break;
	    
	    default:
	    break;
	  } 
}
long Ultrasonic_digit::measure(unsigned long timeout)
{
  long duration;
  pinMode(_Ultrasonic_pin, OUTPUT);
  digitalWrite(_Ultrasonic_pin,LOW);
  delayMicroseconds(2);
  digitalWrite(_Ultrasonic_pin,HIGH);
  delayMicroseconds(10);
  digitalWrite(_Ultrasonic_pin,LOW);
  pinMode(_Ultrasonic_pin, INPUT);
  duration = pulseIn(_Ultrasonic_pin, HIGH, timeout);
  delayMicroseconds(200);
  return(duration);
}

double Ultrasonic_digit::distance_digit(void)
{
	 long digitdistance = measure(400 * 55 + 200);
     return( (double)digitdistance / 58.0);
}