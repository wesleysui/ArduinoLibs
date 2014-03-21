/*********************************************************************
Editor: Roy
E-Mail: Roy.yu@dfrobot.com
Date:   2014.1.22
Version: V1.1
Description
   This is a test for Joystick on BLuno Accessory shield
   
Product page: 
   http://www.dfrobot.com/index.php?route=product/product&product_id=1045#.Ut9TcPSS1ok

Update log:
2014.1.22  Add comments for myAccessory.joystickAvailable()

*********************************************************************/

#include "blunoAccessory.h"
#define RIGHT 1
#define UP 2
#define LEFT 3
#define DOWN 4
#define PUSH 5
#define MID 0

blunoAccessory myAccessory;
void setup() {             
  Serial.begin(115200);   
  myAccessory.begin(); 
  Serial.println("blunoAccessory Joystick test!");   
}

// the loop routine runs over and over again forever:
void loop() {
  //if the joystick is changed, joystickAvailable() will return true.
  if (myAccessory.joystickAvailable()){  
    switch (myAccessory.readJoystick()){
      case RIGHT:
      Serial.print("Joystick:");
      Serial.println("RIGHT");
      break;
      case LEFT:
      Serial.print("Joystick:");
      Serial.println("LEFT");
      break;
      case UP:
      Serial.print("Joystick:");
      Serial.println("UP");
      break;
      case DOWN:
      Serial.print("Joystick:");
      Serial.println("DOWN");
      break;
      case PUSH:
      Serial.print("Joystick:");
      Serial.println("PUSH");
      break;
      case MID:
      Serial.print("Joystick:");
      Serial.println("MID");
      break;
      default:
      break;		
    }
  }
}
