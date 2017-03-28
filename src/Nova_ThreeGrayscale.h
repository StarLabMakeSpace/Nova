#ifndef _Nova_THREEGRAYSCALE_H_
#define _Nova_THREEGRAYSCALE_H_
#include "Arduino.h"

#define IICaddr 0
#define LEFT 1
#define MID 2
#define RIGHT 3
#define LEFT_STATE 4
#define MID_STATE 5
#define RIGHT_STATE 6

class ThreeGrayscale
{
public:

	ThreeGrayscale(uint8_t port);
	//void init(uint8_t a);
	//void begin(uint8_t _addr);
	void set_value(uint8_t a, uint8_t b, uint8_t c);
	uint8_t readvalue(uint8_t num);
	// int value(uint8_t a);
	
private:
	// uint8_t _adc_pin;
	// uint8_t SCL_pin,SDA_pin;
	uint8_t date;
	uint8_t readSTM8(uint8_t address, uint8_t *buf, uint8_t count);
	uint8_t i2c_addr;
	uint8_t SCL_pin,SDA_pin;
	    uint16_t data;
	void IICbegin();
	void IICACK(void);
	bool IICstart(uint8_t addr);
	bool IICrestart(uint8_t addr);
	void IICstop();
	uint8_t IICread(uint8_t last);
	bool IICwrite(uint8_t data);
	void value(uint8_t addr);
};

#endif