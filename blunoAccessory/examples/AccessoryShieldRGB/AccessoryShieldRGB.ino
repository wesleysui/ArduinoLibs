/*********************************************************************
Editor: Roy
E-Mail: Roy.yu@dfrobot.com
Date:   2014.1.22
Version: V1.1
Description
   This is a test for RGB¡¡LED on BLuno Accessory shield
   
Product page: 
   http://www.dfrobot.com/index.php?route=product/product&product_id=1045#.Ut9TcPSS1ok
*********************************************************************/

#include "blunoAccessory.h"
blunoAccessory myAccessory;
void setup() {
  Serial.begin(115200);             
  myAccessory.begin();
}

void loop(){
   for (int i=0;i<255;i++)
   {
     myAccessory.setRGBLed(i, 0, 255-i);
     delay (10);
   }
   for (int i=0;i<255;i++)
   {
     myAccessory.setRGBLed(255-i, i, 0);
     delay (10);
   }
   for (int i=0;i<255;i++)
   {
     myAccessory.setRGBLed(0, 255-i, i);
     delay (10);
   }
}