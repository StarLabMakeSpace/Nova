#include <Nova.h>

InfraredReceive myInfraredReceive = InfraredReceive(C1);// C0、C1、M0、M1、M2、M3

void setup() {
  Serial.begin(9600);
}

void loop() {
//  Serial.println(myInfraredReceive.readvalue());
switch(myInfraredReceive.readvalue())
        {
            case 87: Serial.println("Press Ok.");break;
            case 119: Serial.println("Press Up.");break;
            case 103: Serial.println("Press Down.");break;
            case 215: Serial.println("Press Left.");break;
            case 151: Serial.println("Press Right.");break;
            case 207: Serial.println("Press *.");break;
            case 143: Serial.println("Press #.");break;
            case 79: Serial.println("Press 0.");break;
            case 255: Serial.println("Press 1.");break;
            case 127: Serial.println("Press 2.");break;
            case 191: Serial.println("Press 3.");break;
            case 223: Serial.println("Press 4.");break;
            case 95: Serial.println("Press 5.");break;
            case 159: Serial.println("Press 6.");break;
            case 239: Serial.println("Press 7.");break;
            case 111: Serial.println("Press 8.");break;
            case 175: Serial.println("Press 9.");break;
            default:break;
         }
//         delay(100);
}
