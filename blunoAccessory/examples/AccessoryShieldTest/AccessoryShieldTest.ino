/*********************************************************************
Editor: Roy
E-Mail: Roy.yu@dfrobot.com
Date:   2014.1.22
Version: V1.1
Description
   This is a test for our Bluno Accessory Shield
   SSD1306 OLED driver is based on u8glib.
   You can find u8glib for arduino at:
   https://code.google.com/p/u8glib/
   
Product page: 
   http://www.dfrobot.com/index.php?route=product/product&product_id=1045#.Ut9TcPSS1ok

Update log:
2014.1.22 Change the joystick number to RIGHT,UP and etc
          Change from "long int time=0" to "unsigned long time=0"


*********************************************************************/

#include "blunoAccessory.h"
#include "U8glib.h"
blunoAccessory myAccessory;
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);
#define RIGHT 1
#define UP 2
#define LEFT 3
#define DOWN 4
#define PUSH 5
#define MID 0

float h,t;                           //Humidity&Temperature

int ledR,ledG,ledB,brightness;
bool relayState,buzzerState;
void setup() {
  Serial.begin(115200);             
  u8g.setColorIndex(1);             //displayMode : u8g_MODE_BW
  myAccessory.begin();
  h = myAccessory.readHumidity();
  t = myAccessory.readTemperature();
}

void loop() {
  unsigned long time=0;
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  if(millis()-time>=2000){
  h = myAccessory.readHumidity();
  t = myAccessory.readTemperature();
  time=millis();
  }
  //ReadJoystick state
  switch (myAccessory.readJoystick()){
    case DOWN:
    if (myAccessory.joystickAvailable()){
    relayState=!relayState;
    }
    break;
		
    case PUSH:
    if (myAccessory.joystickAvailable()){
    buzzerState=!buzzerState;
    }
    break;
		
    case LEFT:
    ledR=map(myAccessory.readKnob(),0,1023,0,255);	 
    break;
	 
    case UP:
    ledG=map(myAccessory.readKnob(),0,1023,0,255);	 
    break;
		
    case RIGHT:
    ledB=map(myAccessory.readKnob(),0,1023,0,255);	 
    break;
		
    case MID:
    brightness=map(myAccessory.readKnob(),0,1023,0,100);
    default:
    break; 				
  }
  //Set RGB LED
  myAccessory.setRGBLed(ledR*brightness/100, ledG*brightness/100, ledB*brightness/100);
  //Set Relay
  myAccessory.setRelay(relayState);
  //Set Buzzer
  myAccessory.setBuzzer(buzzerState);
  
  u8g.firstPage();
  do{
    draw();
  }
  while(u8g.nextPage());
}
/*********************************************************************
Display function 
also see https://code.google.com/p/u8glib/wiki/tpictureloop
*********************************************************************/
void draw (void)
{
  u8g.setFont(u8g_font_unifont);

  u8g.setPrintPos(10,16);
  u8g.print("H:"); 
  u8g.print(h);
  u8g.print("%");
  
  u8g.setPrintPos(88,16);  
  u8g.print("R:");
  u8g.print(ledR);
  u8g.setPrintPos(88,32);
  u8g.print("G:");
  u8g.print(ledG);
  u8g.setPrintPos(88,48);
  u8g.print("B:");
  u8g.print(ledB);
  
  u8g.setPrintPos(10,32);
  u8g.print("T:"); 
  u8g.print(t);
  u8g.print("C");
  u8g.setPrintPos(10,48);
  
  u8g.print("Knob:"); 
  u8g.print(myAccessory.readKnob());
  u8g.setPrintPos(10,60);
  
  u8g.print("Joystick:");
  switch (myAccessory.readJoystick()){
    case MID:
    u8g.print("Bright");
    break;
    case RIGHT:
    u8g.print("Blue");
    break;
    case UP:
    u8g.print("Green");
    break;
    case LEFT:
    u8g.print("Red");
    break;
    case DOWN:
    u8g.print("Relay");
    break;
    case PUSH:
    u8g.print("Buzzer");
    break;
    default:
    break;
  }
  
}
