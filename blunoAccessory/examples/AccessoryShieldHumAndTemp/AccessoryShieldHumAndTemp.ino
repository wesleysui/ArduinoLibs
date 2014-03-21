/*********************************************************************
Editor: Roy
E-Mail: Roy.yu@dfrobot.com
Date:   2014.1.22
Version: V1.1
Description
   This is a test for DHT11 on BLuno Accessory shield
   
Product page: 
   http://www.dfrobot.com/index.php?route=product/product&product_id=1045#.Ut9TcPSS1ok
*********************************************************************/

#include "blunoAccessory.h"
blunoAccessory myAccessory;
void setup() {             
	Serial.begin(115200);   
  myAccessory.begin(); 
  Serial.println("blunoAccessory H/T test!");   
}

// the loop routine runs over and over again forever:
void loop() {
  float h = myAccessory.readHumidity();
  float t = myAccessory.readTemperature();
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.println(" *C");
  delay(2000);                   // wait for a second 
}