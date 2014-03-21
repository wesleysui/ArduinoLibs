/*********************************************************************
Editor: Roy
E-Mail: Roy.yu@dfrobot.com
Date:   2014.1.22
Version: V1.1
Description
   This is a test for SSD1306 on BLuno Accessory shield
   SSD1306 OLED driver is based on u8glib.
   You can find u8glib for arduino at:
   https://code.google.com/p/u8glib/
   
Product page: 
   http://www.dfrobot.com/index.php?route=product/product&product_id=1045#.Ut9TcPSS1ok
*********************************************************************/

#include "blunoAccessory.h"
#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);
blunoAccessory myAccessory;

void setup() {
  u8g.setColorIndex(1);             //displayMode : u8g_MODE_BW
  myAccessory.begin();
}

void loop() {
	u8g.firstPage();
	do
	{
		draw();
	}
	while(u8g.nextPage());
	delay(500);
}

//Display function 
//also see https://code.google.com/p/u8glib/wiki/tpictureloop

void draw (void)
{
	u8g.setFont(u8g_font_unifont);
	u8g.drawStr(0,22,"Hello World");
}