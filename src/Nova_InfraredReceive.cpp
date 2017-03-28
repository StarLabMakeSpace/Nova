#include "Nova_InfraredReceive.h"

uint8_t const I2C_READ = 1;
uint8_t const I2C_WRITE = 0;
uint8_t const I2C_DELAY_USEC = 4;

#define USER  0x80
#define C0	USER+1
#define C1	USER+2

#define S0	USER+11
#define S1	USER+12
#define S2	USER+13
#define S3	USER+14
#define S4	USER+15
#define S5	USER+16

#define M0	USER+21
#define M1	USER+22
#define M2	S4
#define M3	S5

//pin define
#define C0_PIN_0	0
#define C0_PIN_1	1

// 位置后面需要改回来
#define C1_PIN_0	A5	//SCL
#define C1_PIN_1	A4	//SDA

#define S0_PIN	2
#define S1_PIN	9
#define S2_PIN	10
#define S3_PIN	13

#define S4_PIN_0	11
#define S4_PIN_1	12
#define S5_PIN_0	3
#define S5_PIN_1	4

#define M0_PIN_0	5
#define M0_PIN_1	7
#define M1_PIN_0	6
#define M1_PIN_1	8

#define M2_PIN_0	S4_PIN_0
#define M2_PIN_1	S4_PIN_1
#define M3_PIN_0	S5_PIN_0
#define M3_PIN_1	S5_PIN_1

InfraredReceive::InfraredReceive(uint8_t port)
{
	switch(port)
	{
	    case C0:
		    SCL_pin = C0_PIN_1;
			SDA_pin = C0_PIN_0;
		break;
		case C1:
			SCL_pin = C1_PIN_0;
			SDA_pin = C1_PIN_1;
		break;
		case S4:
			SCL_pin = S4_PIN_1;
			SDA_pin = S4_PIN_0;
		break;
		case S5:
			SCL_pin = S5_PIN_1;
			SDA_pin = S5_PIN_0;
		break;
        case M0:
			SCL_pin = M0_PIN_1;
			SDA_pin = M0_PIN_0;
		break;
        case M1:
			SCL_pin = M1_PIN_1;
			SDA_pin = M1_PIN_0;
		break;
	}
    //IICstart(); 
	IICbegin();	
	i2c_addr = 0x50;
 
}

// void InfraredReceive::transmission()
// {
	// //IICstart();
	// IICstart(i2c_addr | I2C_WRITE);
	// IICACK();
	// IICwrite(1);
	// IICACK();
	// IICstop();
	// // delay(1);
// }

 void InfraredReceive::value()
 {
	 uint8_t r[1];
    
     if (!readSTM8(1, r, 1)) 
     {
         return;
     }
	 data	   = r[0];
 }

uint8_t InfraredReceive::readvalue()
{   
    // uint8_t addr;
    value();
	return data;
}

uint8_t InfraredReceive::readSTM8(uint8_t address, uint8_t *buf, uint8_t count) {
  // issue a start condition, send device address and write direction bit
  if (!IICstart(i2c_addr | I2C_WRITE)) return false;
	IICACK();
	 // if (!IICwrite(0)) return false;
	// IICACK();
   if (!IICwrite(address)) return false;
	 IICACK();
  // issue a repeated start condition, send device address and read direction bit
  if (!IICrestart(i2c_addr | I2C_READ))return false;
	IICACK();
	delayMicroseconds(5000000);
  // read data from the STM8
  for (uint8_t i = 0; i < count; i++) {
    // send Ack until last byte then send Ack
    buf[i] = IICread(i == (count-1));
	//IICACK();
  }
  // issue a stop condition
  IICstop();
  return true;
}
void InfraredReceive::IICbegin(void)
{
	pinMode(SCL_pin,OUTPUT);
	pinMode(SDA_pin,OUTPUT);	//set SDA_pin output
	digitalWrite(SCL_pin,HIGH);
	digitalWrite(SDA_pin,HIGH);
	delayMicroseconds(I2C_DELAY_USEC);
	digitalWrite(SDA_pin,LOW);
	delayMicroseconds(I2C_DELAY_USEC);
}
bool InfraredReceive::IICstart(uint8_t addr)
{
	digitalWrite(SDA_pin, LOW);
	delayMicroseconds(I2C_DELAY_USEC);
	digitalWrite(SCL_pin, LOW);
	IICwrite(addr);
}
void InfraredReceive::IICACK(void)
{
	pinMode(SDA_pin,INPUT);			//set SDA_pin input	
	digitalWrite(SCL_pin,HIGH);
	delayMicroseconds(I2C_DELAY_USEC);
	digitalWrite(SCL_pin,LOW);
	delayMicroseconds(I2C_DELAY_USEC);
	pinMode(SDA_pin,OUTPUT);
	//delayMicroseconds(I2C_DELAY_USEC);
}
bool InfraredReceive::IICrestart(uint8_t addr)
{
	digitalWrite(SDA_pin, HIGH);
	digitalWrite(SCL_pin, HIGH);
	delayMicroseconds(I2C_DELAY_USEC);
	return IICstart(addr);
}
void InfraredReceive::IICstop()
{
	digitalWrite(SDA_pin,LOW);
	delayMicroseconds(I2C_DELAY_USEC);
	digitalWrite(SCL_pin,HIGH);
	delayMicroseconds(I2C_DELAY_USEC);
	digitalWrite(SDA_pin,HIGH);
	delayMicroseconds(I2C_DELAY_USEC);
}
uint8_t InfraredReceive::IICread(uint8_t last) {
  uint8_t b = 0;
  // make sure pull-up enabled
  digitalWrite(SCL_pin, LOW);
  delayMicroseconds(I2C_DELAY_USEC);
  digitalWrite(SDA_pin, HIGH);
  delayMicroseconds(I2C_DELAY_USEC);
  pinMode(SDA_pin, INPUT);
  // read byte
  for (uint8_t i = 0; i < 8; i++) {
    // don't change this loop unless you verify the change with a scope
    b <<= 1;
    
    digitalWrite(SCL_pin, HIGH);
	delayMicroseconds(I2C_DELAY_USEC);
    if (digitalRead(SDA_pin)) {b |= 1;}
	//else b &= 0;
    digitalWrite(SCL_pin, LOW);
	delayMicroseconds(I2C_DELAY_USEC);
  }
  // send Ack or Nak
  pinMode(SDA_pin, OUTPUT);
  digitalWrite(SDA_pin, last);
  digitalWrite(SCL_pin, HIGH);
  delayMicroseconds(I2C_DELAY_USEC);
  digitalWrite(SCL_pin, LOW);
  digitalWrite(SDA_pin, LOW);
  return b;
}
//------------------------------------------------------------------------------
/**
 * Write a byte.
 *
 * \param[in] data The byte to send.
 *
 * \return The value true, 1, if the slave returned an Ack or false for Nak.
 */
bool InfraredReceive::IICwrite(uint8_t data) {
  // write byte
  digitalWrite(SCL_pin, LOW);
  for (uint8_t m = 0X80; m != 0; m >>= 1) {
    // don't change this loop unless you verify the change with a scope
    digitalWrite(SDA_pin, m & data);
    digitalWrite(SCL_pin, HIGH);
    delayMicroseconds(I2C_DELAY_USEC);
    digitalWrite(SCL_pin, LOW);
  }
  digitalWrite(SDA_pin,HIGH);
}
