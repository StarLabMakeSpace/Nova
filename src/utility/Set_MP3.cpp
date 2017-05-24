 
#include <utility/Set_MP3.h>

#define USER	0x80
// #define S0	USER+11
// #define S1	USER+12
// #define S2	USER+13
// #define S3	USER+14


//
// Constructor
//
Set_MP3::Set_MP3(uint8_t port, bool inverse_logic /* = false */) : SoftwareSerial(port , port ,inverse_logic)
{
	
}

//
// Destructor
//
Set_MP3::~Set_MP3()
{
  SoftwareSerial::end();
}
