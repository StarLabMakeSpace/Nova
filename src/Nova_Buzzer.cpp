#include "Nova_Buzzer.h"

Buzzer::Buzzer(uint8_t port)
{
	switch(port)
	{
		case S0:
			_Buzzer_pin = S0_PIN;
		break;
		case S1:
			_Buzzer_pin = S1_PIN;
		break;
		case S2:
			_Buzzer_pin = S2_PIN;
		break;
		case S3:
			_Buzzer_pin = S3_PIN;
		break;
		case A0:
	      _Buzzer_pin = A0;
	    break;
	    case A1:
	      _Buzzer_pin = A1;
	    break;
	    case A2:
	      _Buzzer_pin = A2;
	    break;
	    case A3:
	      _Buzzer_pin = A3;
	    break;
	    
	    default:
	    break;
	}
	
	pinMode(_Buzzer_pin, OUTPUT);
	// int A=0;
	// int C=1;
}

// void Buzzer::tone(uint16_t frequency) 
// {
  // int period = 1000000L / frequency;
  // int pulse = period / 2;
  // // int A,B,C;
    // // A = 0;
  // // C =1;
  // pinMode(_Buzzer_pin, OUTPUT);
  // for (long i = 0; i < (1000 * 1000L); i += period)  
  // {
  // B = micros();
	 // if((B-A) >=pulse)
	 // {
		 // C =C*(-1);
		 // if(C==-1)
		 // {
			 // digitalWrite(_Buzzer_pin, HIGH); 
		 // }
		 // else{
			// digitalWrite(_Buzzer_pin, LOW); 
		 // }
		 // A = B;
	 // }
  
   // micros() ==0;
	// A = micros();
	// while(A <=pulse)
	// {
		// digitalWrite(_Buzzer_pin, HIGH);
	// }
	 // micros() ==0;
	 // B = micros();
	// while(B <=pulse)
	// {
		// digitalWrite(_Buzzer_pin, LOW);
	// } 
   // B = micros();
	 // if((B-A) >=pulse)
	 // {
		 // C =C*(-1);
		 // if(C==-1)
		 // {
			 // digitalWrite(_Buzzer_pin, HIGH); 
		 // }
		 // else{
			// digitalWrite(_Buzzer_pin, LOW); 
		 // }
		 // A = B;
	 // }
	// digitalWrite(_Buzzer_pin, HIGH);
    // delayMicroseconds(pulse);
    // digitalWrite(_Buzzer_pin, LOW);
    // delayMicroseconds(pulse);

  // // }
 // }

void Buzzer::tone(uint16_t frequency, uint32_t duration) 
{
  int period = 1000000L / frequency;
  int pulse = period / 2;
  // int A,B,C;
  // A = 0;
  // C =1;
  pinMode(_Buzzer_pin, OUTPUT); 
  
  for (long i = 0; i < duration * 1000L; i += period) 
  {
	  
	  //111111111
	// micros() ==0;
	// A = micros();
	// while(A <=pulse)
	// {
		// digitalWrite(_Buzzer_pin, HIGH);
	// }
	 // micros() ==0;
	 // B = micros();
	// while(B <=pulse)
	// {
		// digitalWrite(_Buzzer_pin, LOW);
	// } 
	
	//22222222222222
	
     // B = micros();
	 // if((B-A) >=pulse)
	 // {
		 // C =C*(-1);
		 // if(C==-1)
		 // {
			 // digitalWrite(_Buzzer_pin, HIGH); 
		 // }
		 // else{
			// digitalWrite(_Buzzer_pin, LOW); 
		 // }
		 // A = B;
	 // }

	//3333333333333
	digitalWrite(_Buzzer_pin, HIGH);
    delayMicroseconds(pulse);
    digitalWrite(_Buzzer_pin, LOW);
    delayMicroseconds(pulse);
  }
}

void Buzzer::noTone()
{
  pinMode(_Buzzer_pin, OUTPUT);
  digitalWrite(_Buzzer_pin, HIGH);
}