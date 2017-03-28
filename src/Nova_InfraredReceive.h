#ifndef _Nova_INFRAREDRECEIVE_H_
#define _Nova_INFRAREDRECEIVE_H_
#include "Arduino.h"
// #include "Nova.h"

// #define IR_BUTTON_0 79
// #define IR_BUTTON_1 255
// #define IR_BUTTON_2 127
// #define IR_BUTTON_3 191
// #define IR_BUTTON_4 223
// #define IR_BUTTON_5 95
// #define IR_BUTTON_6 159
// #define IR_BUTTON_7 239
// #define IR_BUTTON_8 111
// #define IR_BUTTON_9 175
// #define IR_BUTTON_OK 87
// #define IR_BUTTON_UP 119
// #define IR_BUTTON_DOWN 103
// #define IR_BUTTON_LEFT 215
// #define IR_BUTTON_RIGHT 151
// #define IR_BUTTON_SPARK 207
// #define IR_BUTTON_POUND 143

// #define BUTTON_0 79
// #define BUTTON_1 255
// #define BUTTON_2 127
// #define BUTTON_3 191
// #define BUTTON_4 223
// #define BUTTON_5 95
// #define BUTTON_6 159
// #define BUTTON_7 239
// #define BUTTON_8 111
// #define BUTTON_9 175
// #define BUTTON_OK 87
// #define BUTTON_UP 119
// #define BUTTON_DOWN 103
// #define BUTTON_LEFT 215
// #define BUTTON_RIGHT 151
// #define BUTTON_SPARK 207
// #define BUTTON_POUND 143

#define IICaddr 0

class InfraredReceive
{
public:

	InfraredReceive(uint8_t port);
	uint8_t readvalue();
	
private:
	uint8_t data;
	uint8_t readSTM8(uint8_t address, uint8_t *buf, uint8_t count);
	uint8_t i2c_addr;
	uint8_t SCL_pin,SDA_pin;
	void IICbegin();
	void IICACK(void);
	bool IICstart(uint8_t addr);
	bool IICrestart(uint8_t addr);
	void IICstop();
	uint8_t IICread(uint8_t last);
	bool IICwrite(uint8_t data);
	void value();
};

#endif