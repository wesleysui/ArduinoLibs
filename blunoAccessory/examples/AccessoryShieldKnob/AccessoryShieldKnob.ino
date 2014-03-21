/*********************************************************************
Editor: Roy
E-Mail: Roy.yu@dfrobot.com
Date:   2014.1.22
Version: V1.1
Description
   This is a test for Knob on BLuno Accessory shield
   
Product page: 
   http://www.dfrobot.com/index.php?route=product/product&product_id=1045#.Ut9TcPSS1ok
*********************************************************************/

#include "blunoAccessory.h"
blunoAccessory myAccessory;
void setup() {             
  Serial.begin(115200);   
  myAccessory.begin(); 
  Serial.println("blunoAccessory Knob test!");   
}

// the loop routine runs over and over again forever:
void loop() {
  Serial.println(myAccessory.readKnob()); 
  delay(1000);
}