#include <Nova.h>

ThreeGrayscale myThreeGrayscale = ThreeGrayscale(M2);// C0、C1、M0、M1、M2、M3

void setup() {

  Serial.begin(9600);
  myThreeGrayscale.set_value(50,50,50);//set comparative value(left,middle,right)
  delay(100);
}

void loop() {
  Serial.print("left=");
  Serial.print(myThreeGrayscale.readvalue(LEFT));//LEFT:left Grayscale(0-255)  //MID:middle Grayscale(0-255)  //RIGHT:right Grayscale(0-255)//LEFT_STATE:left Grayscale(0,1) //MID_STATE:middle Grayscale(0,1) //RIGHT_STATE:right Grayscale(0,1)
  Serial.print(",");   
  Serial.print("middle=");
  Serial.print(myThreeGrayscale.readvalue(MID));//LEFT:left Grayscale(0-255)  //MID:middle Grayscale(0-255)  //RIGHT:right Grayscale(0-255)//LEFT_STATE:left Grayscale(0,1) //MID_STATE:middle Grayscale(0,1) //RIGHT_STATE:right Grayscale(0,1)
  Serial.print(","); 
  Serial.print("right=");
  Serial.print(myThreeGrayscale.readvalue(RIGHT));
  Serial.print(","); 
  Serial.print("left_state=");
  Serial.print(myThreeGrayscale.readvalue(LEFT_STATE));//LEFT:left Grayscale(0-255)  //MID:middle Grayscale(0-255)  //RIGHT:right Grayscale(0-255)//LEFT_STATE:left Grayscale(0,1) //MID_STATE:middle Grayscale(0,1) //RIGHT_STATE:right Grayscale(0,1)
  Serial.print(",");   
  Serial.print("middle_state=");
  Serial.print(myThreeGrayscale.readvalue(MID_STATE));//LEFT:left Grayscale(0-255)  //MID:middle Grayscale(0-255)  //RIGHT:right Grayscale(0-255)//LEFT_STATE:left Grayscale(0,1) //MID_STATE:middle Grayscale(0,1) //RIGHT_STATE:right Grayscale(0,1)
  Serial.print(","); 
  Serial.print("right_state=");
  Serial.println(myThreeGrayscale.readvalue(RIGHT_STATE));
  delay(100);
}
