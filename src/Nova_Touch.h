#ifndef _NOVA_Touch_H_
#define _NOVA_Touch_H_
#include "Arduino.h"
#include "Nova.h"

class Touch
{
public:
	Touch(uint8_t pin);
	bool state(void);
	uint8_t read();
private:
	uint8_t _Touch_pin;
};

#endif
