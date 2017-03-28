#include "Nova_RTC.h"
#include "string.h"

uint8_t const I2C_READ = 1;
uint8_t const I2C_WRITE = 0;
uint8_t const I2C_DELAY_USEC = 4;

#define USER	0x80
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

uint8_t RTC::decToBcd(uint8_t val)
{
	return ( (val/10*16) + (val%10) );
}

//Convert binary coded decimal to normal decimal numbers
uint8_t RTC::bcdToDec(uint8_t val)
{
	return ( (val/16*10) + (val%16) );
}

RTC::RTC(uint8_t port)
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

    IICbegin(SDA_pin, SCL_pin);
}

/*
 * Read 'count' bytes from the DS1307 starting at 'address'
 */
uint8_t RTC::readDS1307(uint8_t address, uint8_t *buf, uint8_t count) {
  // issue a start condition, send device address and write direction bit
  if (!IICstart(DS1307ADDR | I2C_WRITE)) return false;

  // send the DS1307 address
  if (!IICwrite(address)) return false;

  // issue a repeated start condition, send device address and read direction bit
  if (!IICrestart(DS1307ADDR | I2C_READ))return false;

  // read data from the DS1307
  for (uint8_t i = 0; i < count; i++) {

    // send Ack until last byte then send Ack
    buf[i] = IICread(i == (count-1));
  }

  // issue a stop condition
  IICstop();
  return true;
}
//------------------------------------------------------------------------------
/*
 * write 'count' bytes to DS1307 starting at 'address'
 */
uint8_t RTC::writeDS1307(uint8_t address, uint8_t *buf, uint8_t count) {
  // issue a start condition, send device address and write direction bit
  if (!IICstart(DS1307ADDR | I2C_WRITE)) return false;

  // send the DS1307 address
  if (!IICwrite(address)) return false;

  // send data to the DS1307
  for (uint8_t i = 0; i < count; i++) {
    if (!IICwrite(buf[i])) return false;
  }

  // issue a stop condition
  IICstop();
  return true;
}

/****************************************************************/
/*Function: Read time and date from RTC	*/
void RTC::getTime()
{
    uint8_t r[8];
    
    if (!readDS1307(0, r, 7)) 
    {
        return;
    }
  
	second	   = bcdToDec(r[0] & 0x7f);
	minute	   = bcdToDec(r[1]);
	hour	   = bcdToDec(r[2] & 0x3f);// Need to change this if 12 hour am/pm
	week  	   = bcdToDec(r[3]);
	day        = bcdToDec(r[4]);
	month      = bcdToDec(r[5]);
	year	   = bcdToDec(r[6]);
}

/*******************************************************************/


void RTC::fillByHMS(uint8_t _hour, uint8_t _minute, uint8_t _second)
{
    uint8_t r[3];
	// assign variables
	r[2] = decToBcd(_hour);
	r[1] = decToBcd(_minute);
	r[0] = decToBcd(_second);
	  
    if (!writeDS1307(0, r, 3)) 
    {
        return;
    }
}

void RTC::fillByYMD(uint16_t _year, uint8_t _month, uint8_t _day)
{ 
    uint8_t r[3];
	// assign variables
	r[2] = decToBcd(_year-2000);
	r[1] = decToBcd(_month);
	r[0] = decToBcd(_day);
	  
    if (!writeDS1307(4, r, 3)) 
    {
        return;
    }  
}

void RTC::fillByWeek(uint8_t _week)
{
    uint8_t r[1];
    
	r[0] = decToBcd(_week);
	  
    if (!writeDS1307(3, r, 1)) 
    {
        return;
    } 
}

uint8_t RTC::getSecond(void)
{
    getTime();
	return second;
}
uint8_t RTC::getMinute(void)
{
    getTime();
	return minute;
}
uint8_t RTC::getHour(void)
{
    getTime();
	return hour;
}
uint8_t RTC::getWeek(void)
{
    getTime();
	return week;
}
uint8_t RTC::getDay(void)
{
    getTime();
	return day;
}
uint8_t RTC::getMonth(void)
{
    getTime();
	return month;
}
uint16_t RTC::getYear(void)
{
    getTime();
	return year+2000;
}

void RTC::IICbegin(uint8_t sdapin,uint8_t sclpin)
{
	SDA_pin = sdapin;
	pinMode(SDA_pin,OUTPUT);
	digitalWrite(SDA_pin,HIGH);
	SCL_pin = sclpin;
	pinMode(SCL_pin,OUTPUT);
	digitalWrite(SCL_pin,HIGH);
}
bool RTC::IICstart(uint8_t addr)
{
	digitalWrite(SDA_pin, LOW);
	delayMicroseconds(I2C_DELAY_USEC);
	digitalWrite(SCL_pin, LOW);
	return IICwrite(addr);
}
bool RTC::IICrestart(uint8_t addr)
{
	digitalWrite(SDA_pin, HIGH);
	digitalWrite(SCL_pin, HIGH);
	delayMicroseconds(I2C_DELAY_USEC);
	return IICstart(addr);
}
void RTC::IICstop()
{
	digitalWrite(SDA_pin,LOW);
	delayMicroseconds(I2C_DELAY_USEC);
	digitalWrite(SCL_pin,HIGH);
	delayMicroseconds(I2C_DELAY_USEC);
	digitalWrite(SDA_pin,HIGH);
	delayMicroseconds(I2C_DELAY_USEC);
}
uint8_t RTC::IICread(uint8_t last) {
  uint8_t b = 0;
  // make sure pull-up enabled
  digitalWrite(SDA_pin, HIGH);
  pinMode(SDA_pin, INPUT);
  // read byte
  for (uint8_t i = 0; i < 8; i++) {
    // don't change this loop unless you verify the change with a scope
    b <<= 1;
    delayMicroseconds(I2C_DELAY_USEC);
    digitalWrite(SCL_pin, HIGH);
    if (digitalRead(SDA_pin)) {b |= 1;}
	//else b &= 0;
    digitalWrite(SCL_pin, LOW);
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
bool RTC::IICwrite(uint8_t data) {
  // write byte
  for (uint8_t m = 0X80; m != 0; m >>= 1) {
    // don't change this loop unless you verify the change with a scope
    digitalWrite(SDA_pin, m & data);
    digitalWrite(SCL_pin, HIGH);
    delayMicroseconds(I2C_DELAY_USEC);
    digitalWrite(SCL_pin, LOW);
  }
  // get Ack or Nak
  pinMode(SDA_pin, INPUT);
  // enable pullup
  digitalWrite(SDA_pin, HIGH);
  digitalWrite(SCL_pin, HIGH);
  uint8_t rtn = digitalRead(SDA_pin);
  digitalWrite(SCL_pin, LOW);
  pinMode(SDA_pin, OUTPUT);
  digitalWrite(SDA_pin, LOW);
  return rtn == 0;
}