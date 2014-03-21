// MAX6675.ino
#include "Arduino.h"
#include "PlainProtocol.h"
#include "MAX6675.h"


PlainProtocol myBLUNO(Serial,115200);

//  CS 
//  SO
//  SCK
MAX6675 temp0(11,12,10,1);

float temperature = 0.0f;

void setup() {
	myBLUNO.init();
}

void loop() {

	if (myBLUNO.available()) {
		if (myBLUNO.equals("TEMP")) {
			myBLUNO.write("TEMP", temperature);
        }
	}

	myBLUNO.write("TEMP", temperature);//
	temperature = temp0.read_temp();
	// Serial.println(temperature);
	delay(1000);

}
