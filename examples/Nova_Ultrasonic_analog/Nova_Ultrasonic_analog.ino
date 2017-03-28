 /*
Nova_Button

Serial port will print distance.

Created 15 Dec 2015
By Blue

http://easy.cc
*/

#include <Nova.h>

Ultrasonic_analog myUltrasonic = Ultrasonic_analog(A0);

void setup() {
Serial.begin(9600);
}

void loop() {
Serial.println(myUltrasonic.distance_analog());//get distance
delay(100);
}
