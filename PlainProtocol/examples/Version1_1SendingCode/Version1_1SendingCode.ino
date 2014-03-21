#include <PlainProtocol.h>

PlainProtocol mytest(Serial);

void setup() {
  mytest.begin(57600);
}

void loop() {
  mytest.write("speed",100);          //set the speed to 100
  mytest.write("destination", 23, 56); //set the destination to (23,56)
  mytest.write("display","Hello World!",10,35);//show the string on display at (10,35)
  delay(2000);
}