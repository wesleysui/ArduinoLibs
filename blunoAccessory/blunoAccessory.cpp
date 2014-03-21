/*********************************************************************
Editor: Roy
E-Mail: Roy.yu@dfrobot.com
Date:   2014.1.22
Version: V1.1
Description
	Improve the library to work with Bluno Accessory Shield

This is a library for our Bluno Accessory Shield
*********************************************************************/

#include "blunoAccessory.h"

/*********************************************************************
blunoAccessory Initialization
*********************************************************************/
void blunoAccessory::begin(void) {
  dhtBegin();
  ledBegin();
}

/*********************************************************************
LED Screen Initialization
*********************************************************************/
void blunoAccessory::ledBegin(void) { 
  pinMode(DC,OUTPUT);
  digitalWrite(DC,LOW);             //DC=0
  pinMode(RES,OUTPUT);
  digitalWrite(RES,HIGH);   delay(100);
  digitalWrite(RES,LOW);    delay(100);
  digitalWrite(RES,HIGH);   delay(100);
}            

/*********************************************************************
If the joystick's state is changed,it will retrun true
*********************************************************************/
boolean blunoAccessory::joystickAvailable(void){
	readJoystick();
	boolean temp=joystickChange;
	joystickChange=false;
	return temp;
}

/*********************************************************************
Return the state of Joystick
value 1: right
      2: up
      3: left
      4: down
      5: push
*********************************************************************/
int blunoAccessory::readJoystick(void){
	int key_value=0;
	int stickRaw=analogRead(joystickPin);
	static int keyValueLast=0; 
  if(stickRaw<70)
      key_value=1;  //right
  else if(70<=stickRaw&&stickRaw<235)
      key_value=5;  //push
  else if(235<=stickRaw&&stickRaw<420)
      key_value=2;  //up
  else if(420<=stickRaw&&stickRaw<620)
      key_value=3;  //left
  else if(620<=stickRaw&&stickRaw<900)
      key_value=4;  //dowm
  else
      key_value=0;
  if (keyValueLast!=key_value){joystickChange=true;keyValueLast=key_value;}
  return key_value;
}

/*********************************************************************
Return the value of Knob
value :0-1023
*********************************************************************/
int blunoAccessory::readKnob(void){
	return (1023-analogRead(knobPin));
}

/*********************************************************************
Set the state of the Relay
state :true or false
*********************************************************************/
void blunoAccessory::setRelay(bool value){
	pinMode(relayPin,OUTPUT);
	digitalWrite(relayPin,value);
}

/*********************************************************************
Set the state of the Buzzer
state :true or false
*********************************************************************/
void blunoAccessory::setBuzzer(bool value){
	pinMode(buzzerPin,OUTPUT);
	digitalWrite(buzzerPin,value);
}

/*********************************************************************
Set the value of the RGB LED
value  R : 0-255
       G : 0-255
       B : 0-255
*********************************************************************/
void blunoAccessory::setRGBLed(int red, int green, int blue){
	analogWrite(redLedPin,255-red);
	analogWrite(greenLedPin,255-green);
	analogWrite(blueLedPin,255-blue);
}

/*********************************************************************
DHT Initialization
*********************************************************************/
void blunoAccessory::dhtBegin(void) {             
  // set up the pins!
  pinMode(dhtPin, INPUT);
  digitalWrite(dhtPin, HIGH);
  _lastreadtime = 0;
  firstreading = true;
}

/*********************************************************************
Return the value of Temperature
boolean S : Scale.  True == Farenheit; False == Celcius
*********************************************************************/
float blunoAccessory::readTemperature(bool S) {
  float f;

  if (dhtRead()) {
    switch (dhtType) {
    case DHT11:
      f = data[2];
      if(S)
      	f = convertCtoF(f);
      	
      return f;
    case DHT22:
    case DHT21:
      f = data[2] & 0x7F;
      f *= 256;
      f += data[3];
      f /= 10;
      if (data[2] & 0x80)
	f *= -1;
      if(S)
	f = convertCtoF(f);

      return f;
    }
  }
  Serial.print("Read fail");
  return NAN;
}

/*********************************************************************
private
convert Celsius to Fahrenheit
*********************************************************************/
float blunoAccessory::convertCtoF(float c) {
	return c * 9 / 5 + 32;
}

/*********************************************************************
Return the value of Humidity
value: 0-100%
*********************************************************************/
float blunoAccessory::readHumidity(void) {
  float f;
  if (dhtRead()) {
    switch (dhtType) {
    case DHT11:
      f = data[0];
      return f;
    case DHT22:
    case DHT21:
      f = data[0];
      f *= 256;
      f += data[1];
      f /= 10;
      return f;
    }
  }
  Serial.print("Read fail");
  return NAN;
}

/*********************************************************************
private
DHT read date
*********************************************************************/
boolean blunoAccessory::dhtRead(void) {
  uint8_t laststate = HIGH;
  uint8_t counter = 0;
  uint8_t j = 0, i;
  unsigned long currenttime;

  digitalWrite(dhtPin, HIGH);
//  delay(250);

  currenttime = millis();
  if (currenttime < _lastreadtime) {
    // ie there was a rollover
    _lastreadtime = 0;
  }
  if (!firstreading && ((currenttime - _lastreadtime) < 2000)) {
    return true; // return last correct measurement
    //delay(2000 - (currenttime - _lastreadtime));
  }
  firstreading = false;
  /*
    Serial.print("Currtime: "); Serial.print(currenttime);
    Serial.print(" Lasttime: "); Serial.print(_lastreadtime);
  */
  _lastreadtime = millis();

  data[0] = data[1] = data[2] = data[3] = data[4] = 0;
  
  // now pull it low for ~20 milliseconds
  pinMode(dhtPin, OUTPUT);
  digitalWrite(dhtPin, LOW);
  delay(20);
  cli();
  digitalWrite(dhtPin, HIGH);
  delayMicroseconds(40);
  pinMode(dhtPin, INPUT);

  // read in timings
  for ( i=0; i< MAXTIMINGS; i++) {
    counter = 0;
    while (digitalRead(dhtPin) == laststate) {
      counter++;
      delayMicroseconds(1);
      if (counter == 255) {
        break;
      }
    }
    laststate = digitalRead(dhtPin);
    if (counter == 255) break;
    // ignore first 3 transitions
    if ((i >= 4) && (i%2 == 0)) {
      // shove each bit into the storage bytes
      data[j/8] <<= 1;
      if (counter > dhtCount)
        data[j/8] |= 1;
      j++;
    }
  }
  sei();
  // check we read 40 bits and that the checksum matches
  if ((j >= 40) && 
      (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) ) {
    return true;
  }
  return false;
}
