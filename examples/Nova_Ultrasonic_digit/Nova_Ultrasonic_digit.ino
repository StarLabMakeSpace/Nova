 /*
Nova_Button

Serial port will print distance.

Created 15 Dec 2015
By Blue

http://easy.cc
*/

#include <Nova.h>

Ultrasonic_digit myUltrasonic = Ultrasonic_digit(S0);

void setup() {
//pinMode(2,OUTPUT);
Serial.begin(9600);
}

void loop() {
Serial.println(myUltrasonic.distance_digit());//get distance
delay(100);
}
