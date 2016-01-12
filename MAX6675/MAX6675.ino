// MAX6675.ino
#include "Arduino.h"
#include "PlainProtocol.h"
#include "MAX6675.h"


PlainProtocol myBLUNO(Serial,115200);

//  CS SO SCK
MAX6675 max6675(12,13,11,1);

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

	static unsigned long max6675Timer = millis();       //every 2s update the temperature and humidity from DHT11 sensor
    if (millis() - max6675Timer >= 2000) {
        max6675Timer = millis();
        temperature = max6675.read_temp();
        Serial.println(temperature);
    }


    delay(1000);

}
