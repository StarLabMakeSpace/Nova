#include"mb.h"
//#include <utility/SoftwareSerial.h>

// Macro for Timing
#define TIMEOUT 80   // 5(ms)

#define send_state 0x00
#define send_int   0x01
#define send_float 0x02
#define send_char  0x03

#define rec_state 0x80
#define rec_int   0x81
#define rec_float 0x82
#define rec_char  0x83

#define HEAD rec_buf[0]
#define TYPE rec_buf[1]
#define ADDR rec_buf[2]
#define LEN  rec_buf[3]
#define DATA rec_buf[4]
#define CS   rec_buf[LEN + 4]

unsigned char rec_buf[255+5];

/*void mb_setup(uint8_t rx, uint8_t tx)
{
		SoftwareSerial::SoftwareSerial(rx,tx,false);
}
uint8_t makerbus::mb_available()
{
	return SoftwareSerial::available();
}
unsigned char makerbus::mb_read()
{
	return SoftwareSerial::read();
}
*/
/*makerbus::makerbus(uint8_t rx,uint8_t tx):SoftwareSerial(rx,tx,false)
{
	//SoftwareSerial:
}
makerbus::begin(long baud)
{
	SoftwareSerial::begin(baud);
}
*/
unsigned char makerbus::ReceivePacket(void)
{
	//SoftwareSerial::SoftwareSerial(11,12,false);
	SoftwareSerial mbr_t(RX_PIN,TX_PIN,false);
	mbr_t.begin(9600);
	unsigned char rcv = 0;
	static unsigned char count = 0;
	long delayStart = 0;
	delayStart = millis();
	while (1)
	{
		if (mbr_t.available())
		{
			rcv = mbr_t.read();
			if (count == 0)
			{
				if (rcv == 0xFE)
				{
					rec_buf[count++] = rcv;
				}
				else
				{
					count = 0;
				}
			}
			else
			{
				rec_buf[count++] = rcv;

				if (count > 5)
				{
					if (count >= (rec_buf[3] + 5))
					{
						// Sum Check
						if (CS == SumCheck(rec_buf, 4 + LEN))
						{
							count = 0;
							return 1;
						}
						else
						{
							count = 0;
							return 0;
						}	
					}
				}
			}
		}
	
		if ((millis() - delayStart) > TIMEOUT)
		{
			return 0;  
		}  
	}
}

unsigned char makerbus::SumCheck(unsigned char *p, int len)
{
	unsigned char check = 0;
	unsigned char i;

	for (i = 0; i < len; i++)
	{
	check += *p++;
	}

	return check;
}

void makerbus::Mencpy(unsigned char *from, unsigned char *to, int n)
{
 	while (n--)
  	{
		*to++ = *from++;
  	}
}
/*void makerbus::begin(long baud)
{
	//dealy(100);
	SoftwareSerial::begin(baud);
}
*/
//--------------------------------------makerbus rec-------------------------------------------------------//

MbGet::MbGet(uint8_t id)
{
	_id = id;	
}

/*void MbGet::begin(long baud)
{
	
	makerbus::begin(baud);
}*/
//void MbGet::setup(uint8_t rx, uint8_t tx)
//{
//	mb_setup(rx,tx);
//}
void MbGet::ParsePacket(void)
{
	//unsigned char UserData[LEN];
	if (ADDR == _id)
	{
		Mencpy(&TYPE,UserData,LEN+3);
	}
}
uint16_t MbGet::getvalue(void)
{
	if (ReceivePacket())
	{
		ParsePacket();
		if(UserData[0] == rec_state)
		{
			value = UserData[3];
		}
		else if(UserData[0] == rec_int)
		{
			val = (UserData[3]<<8);
			val += UserData[4];
			value = val/100;
		}
		else if(UserData[0] == rec_float)
		{
			if(UserData[2] == 2)
			{
				val = ((UserData[3]&0x7F)<<8);
				val += UserData[4];
				value = val/100;
				if((UserData[3]&0x80) == 0x80) 
				{
					value =  -value;
				}
			}
		}
	}
	return value;
}
uint16_t MbGet::getvalue(int axis)
{
	if (ReceivePacket())
	{
		ParsePacket();
		if(UserData[0] == rec_float)
		{
			if(UserData[2] == 4)
			{
				if(axis == x_axis)
				{
					val = ((UserData[3]&0x7F)<<8);
					val += UserData[4];
					value = val/100;
					if((UserData[3]&0x80) == 0x80) 
					{
						value =  -value;
					}
				}
				else if(axis == y_axis)
				{
					val = ((UserData[5]&0x7F)<<8);
					val += UserData[6];
					value = val/100;
					if((UserData[5]&0x80) == 0x80) 
					{
						value =  -value;
					}
				}
			}
		}
	}
	return value;
}
/*uint16_t MbGet::readinteger(void)
{  
	if (ReceivePacket())
	{
		//unsigned char UserData[LEN];
		ParsePacket();
		val = (UserData[0]<<8);
		val += UserData[1];
		return val/100;
	}
	return val/100;
}
/*int MbGet::floatValue(uint8_t _id)
{
	if (mb_available())
	{   
		if(Buf[2] == _id)
		{ 
			//if(Buf[3] == 2)
			//{
				val = ((Buf[4]&0x7F)<<8);
				val += Buf[5];
				value = val/100;
				if((Buf[4]&0x80) == 0x80) 
				{
					value =  -value;
				}
				return value;
				//rx_date[0] = value;
			//}
		}
	}
	return value;
}
int MbGet::floatValue(uint8_t _id, int axis)
{
	if (mb_available())
	{   
		if(Buf[2] == _id)
		{ 
			if(Buf[3] == 2)
			{
				float_val_x = ((Buf[4]&0x7F)<<8);
				float_val_x += Buf[5];
				float_value_x = float_value_x/100;
				if((Buf[4]&0x80) == 0x80)  
				{
					float_value_x =  -float_value_x;
				}
				//rx_date[0] = float_value_x;
			}
			if(Buf[3] == 4)
			{
				float_val_x = ((Buf[4]&0x7F)<<8);
				float_val_x += Buf[5];
				float_value_x = float_val_x/100;
				if((Buf[4]&0x80) == 0x80) 
				{
					float_value_x =  -float_value_x;
				}
				//rx_date[0] = float_value_x;
				for(int a=0;a<7;a++)
				{
					;
				}
				float_val_y = ((Buf[6]&0x7F)<<8);
				float_val_y += Buf[7];
				float_value_y = float_val_y/100;
				if((Buf[6]&0x80) == 0x80) 
				{
					float_value_y =  -float_value_y;
				}
				//rx_date[1] = float_value_y;
				for(int a=0;a<7;a++)
				{
					;
				}
				
			}
			
		}
		if(axis == x_axis)
				{
					return float_value_x;
				}
				else if(axis == y_axis)
				{
					return float_value_y;
				}
	}
	
	//return rx_date[0];
	
	//return *rx_date;
}
/*char MbGet::charValue(void)
{
	if (mb_available())
  {   
    if(Buf[2] == _id)// ADD = 1
    { 
      if(Buf[3] == 2)
	  {
		  val = ((Buf[4]&0x7F)<<8);
		  val += Buf[5];
	  }
    }
  }
  if(Buf[4]&0x80 == 0x80)
		  {
			  return Buf[4];
			  //return -(val/100);
		  }
		  else return Buf[5];//val/100;
}
*/
/*uint8_t MbGet::mb_available(void)
{
	if (SoftwareSerial::available())
	{
		_Rcv = SoftwareSerial::read();
		if (_count == 0)
		{
			if (_Rcv == 0xFE)
			{
				Buf[_count++] = _Rcv;
			}
			else
			{
				_count = 0;
			}	
		}
		else
		{
			Buf[_count++] = _Rcv;
			if (_count > 5)
			{   
				if (_count >= (Buf[3] + 5))
				{
					if (Buf[Buf[3] + 4] == SumCheck(Buf, Buf[3] + 4))
					{
						_count = 0;
						if ((Buf[1] & 0x80) == 0x80)
						{ 
							return 1;
						}
					}
					else
					{
						_count = 0;
					}
				}
			}
		}
	}
}

*/


