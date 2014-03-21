
/* blunoAccessory library 

written by DFrobot Roy
*/

#ifndef blunoAccessory_H
#define blunoAccessory_H
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif


// how many timing transitions we need to keep track of. 2 * number bits + extra
#define MAXTIMINGS 85

#define DHT11 11
#define DHT22 22
#define DHT21 21
#define AM2301 21
#define dhtPin 2
#define dhtType DHT11
#define dhtCount 6

#define joystickPin 0
#define knobPin 1
#define relayPin 11
#define buzzerPin 8
#define redLedPin 9
#define greenLedPin 10
#define blueLedPin 3

#define RES 6    //LED reset pin PIN6
#define DC 7     //LED DC pin PIN3

class blunoAccessory {
 private:
  uint8_t data[6];
  boolean joystickChange;
  boolean dhtRead(void);
  void ledBegin(void);
  void dhtBegin(void); 
  float convertCtoF(float);
  unsigned long _lastreadtime;
  boolean firstreading;

 public:
  void begin(void);
  float readTemperature(bool S=false);
  float readHumidity(void);
  int readKnob(void);
  int readJoystick(void);
  void setRelay(bool value=true);
  void setBuzzer(bool value=true);
  void setRGBLed(int red=255, int green=255, int blue=255);
  boolean joystickAvailable(void);
};
#endif
