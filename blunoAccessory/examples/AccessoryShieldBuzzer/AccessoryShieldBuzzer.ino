/*********************************************************************
Editor: Roy
E-Mail: Roy.yu@dfrobot.com
Date:   2014.1.22
Version: V1.1
Description
   This is a test for Buzzer on BLuno Accessory shield
   
Product page: 
   http://www.dfrobot.com/index.php?route=product/product&product_id=1045#.Ut9TcPSS1ok
*********************************************************************/

#include "blunoAccessory.h"
blunoAccessory myAccessory;
void setup() {                
  myAccessory.begin();    
}

// the loop routine runs over and over again forever:
void loop() {
  myAccessory.setBuzzer(true);   // turn the LED on (HIGH is the voltage level)
  delay(2000);                   // wait for a second
  myAccessory.setBuzzer(false);  // turn the LED off by making the voltage LOW
  delay(2000);                   // wait for a second 
}