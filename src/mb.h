#ifndef _mb_h_
#define _mb_h_
#include "Arduino.h"
//#include"Nova.h"
#include <utility/SoftwareSerial.h>
#define x_axis 1
#define y_axis 2

#define led_on 3
#define led_off 4

#define RX_PIN 11
#define TX_PIN 12


//uint8_t _tx,_rx;
//void makerbus_setup(uint8_t rx, uint8_t tx);

//void mb_setup(uint8_t rx, uint8_t tx);

class makerbus //: public SoftwareSerial
{
public:
	//makerbus(uint8_t rx,uint8_t tx);
	//void begin(long baud);
	//void makerbus_setup(uint8_t rx, uint8_t tx);
	unsigned char ReceivePacket(void);
	void Mencpy(unsigned char *from, unsigned char *to, int n);
private:
	unsigned char SumCheck(unsigned char *p, int len);
};

class MbGet : public makerbus
{
public:
	MbGet(uint8_t id);
	//void begin(long baud);
	//void setup(uint8_t rx, uint8_t tx);
	//uint8_t mb_available(void);
	//uint8_t state(void);
	uint16_t getvalue(void);
	uint16_t getvalue(int axis);
	void ParsePacket(void);
    //uint16_t intValue(void);
	//int floatValue(void);
   // int floatValue(int axis);
    //char charValue(void);
private:
	uint8_t UserData[6];
	uint16_t val;
	float value;
	uint8_t _id;
	unsigned char _Rcv = 0;
	unsigned char _count = 0;
};
/*class MbSet : public SoftwareSerial
{
public:
	float val;
	float value;
	MbGet(uint8_t rx, uint8_t tx, uint8_t id);
	void begin(long baud);
	uint8_t mb_available(void);
	uint8_t state(void);
    uint16_t intValue(void);
    int floatValue(void);
    char charValue(void);
private:
	uint8_t _id;
	uint8_t _tx;
	uint8_t _rx;
	unsigned char Buf[255];
	unsigned char _Rcv = 0;
	unsigned char _count = 0;	
};*/
#endif
