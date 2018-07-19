/*------------------------------------#
#----- FASTSPI2 EFFECTS EXAMPLES -----#
#-------------- v0.51 ----------------#
#------------ teldredge --------------#set
#-------- www.funkboxing.com ---------#
#------ teldredge1979@gmail.com ------#
#-------------------------------------#
### THESE EFFECTS ARE MOSTLY DESIGNED FOR A LOOP/RING OF LEDS
### BUT PLENTY USEFUL FOR OTHER CONFIGURATIONS
### RECENT CHANGES v0.51
    -ADDED SOFTWARE SERIAL FOR BLUETOOTH CONTROL
    -ADDED (z) SHOW LED COMMAND (FOR BETTER SERIAL CONTROL)
    -ADDED SET (a)ll LEDS TO COLOR HSV (0-255)
    -ADDED (c)lear FUNCTION
    -ADDED (v) SET INDIVIDUAL LED HSV FUNCTION
    -ADDED (Q)UERY VERSION NUMBER FUNCTION
### NOTES
    -MAKE SURE YOU ARE USING FAST_SPI RC3 OR LATER
    -THIS IS AN EXAMPLE LIBRARY SO YOU'LL PRABALY WANT TO EDIT TO DO ANYTHING USEFUL WITH IT
    -GOTO FUNKBOXING FAST_SPI2 COMMENTS PAGE FOR HELP
    -DEMO MODE BLOCKS SERIAL COMMANDS
### LICENSE:::USE FOR WHATEVER YOU WANT, WHENEVER YOU WANT, HOWEVER YOU WANT, WHYEVER YOU WANT
### BUT YOU MUST YODEL ONCE FOR FREEDOM AND MAYBE DONATE TO SOMETHING WORTHWHILE

Modified by Monika Gal for element14's Bluetooth Unleashed Design Challenge, June-July 2018.

|-----------------------------------------------------|
|                                                     |
|           FROM THE FAST_SPI2 EXAMPLE FILE           |
|                                                     |
|----------------------------------------------------*/
// Uncomment this line if you have any interrupts that are changing pins - this causes the library to be a little bit more cautious
// #define FAST_SPI_INTERRUPTS_WRITE_PINS 1

// Uncomment this line to force always using software, instead of hardware, SPI (why?)
// #define FORCE_SOFTWARE_SPI 1

// Uncomment this line if you want to talk to DMX controllers
// #define FASTSPI_USE_DMX_SIMPLE 1
//-----------------------------------------------------


#include <FastLED.h>
#include "include/effects.h"
#include "include/common.h"
#include <SPI.h>
#include <BLEPeripheral.h>
#include "BLESerial.h"


FASTLED_USING_NAMESPACE

#define VERSION_NUMBER 0.51


byte inbyte;                 //-SERIAL INPUT BYTE
int thisarg;                 //-SERIAL INPUT ARG


// create BLE serial instance
BLESerial BLESerial(BLE_REQ, BLE_RDY, BLE_RST);



long BLEparseInt()
{
	//optimised integer parsing taken from:
	//https://gist.github.com/focalintent/957250a916331e96718c
	// don't call the skipChar version, that is just dumb
	long value = 0;
	char c = BLESerial.read();
	if(c<0) return 0;

	// check if we're negative, and if so, skip to the next character
	bool isNegative = (c=='-');
	if(isNegative) { BLESerial.read(); c = BLESerial.read(); }

	while( isdigit(c)) {
	value = (value * 10) + (c - '0');
	c = BLESerial.read();
	}

	if(isNegative) value = -value;
	return value;
}

void change_mode(int newmode){
  thissat = 255;
  switch (newmode) {
    //all modes are taken from Funkboxing's examples, mostly unmodified.
    case 0: one_color_all(0,0,0); LEDS.show(); break;   //---ALL OFF
    case 1: one_color_all(255,255,255); LEDS.show(); break;   //---ALL ON
    case 2: thisdelay = 20; break;                      //---STRIP RAINBOW FADE
    case 3: thisdelay = 20; thisstep = 10; break;       //---RAINBOW LOOP
    case 4: thisdelay = 20; break;                      //---RANDOM BURST
    case 5: thisdelay = 20; thishue = 0; break;         //---CYLON v1
    case 6: thisdelay = 40; thishue = 0; break;         //---CYLON v2
    case 7: thisdelay = 40; thishue = 0; break;         //---POLICE LIGHTS SINGLE
    case 8: thisdelay = 40; thishue = 0; break;         //---POLICE LIGHTS SOLID
    case 9: thishue = 160; thissat = 50; break;         //---STRIP FLICKER
    case 10: thisdelay = 15; thishue = 0; break;        //---PULSE COLOR BRIGHTNESS
    case 11: thisdelay = 15; thishue = 0; break;        //---PULSE COLOR SATURATION
    case 12: thisdelay = 60; thishue = 180; break;      //---VERTICAL SOMETHING
  }
  bouncedirection = 0;
  one_color_all(0,0,0);
  ledMode = newmode;
}


//------------------SETUP------------------
void setup()
{
  Serial.begin(SERIAL_BAUDRATE);      // SETUP HARDWARE SERIAL (USB)
  //while(!Serial);
  Serial.setTimeout(SERIAL_TIMEOUT);
  Serial.println(F("program starts ."));

  BLESerial.setLocalName("UART");

  // Init. and start BLE library.
  BLESerial.begin();

  LEDS.setBrightness(max_bright);
  LEDS.addLeds<WS2811, LED_DT, GRB>(leds, LED_COUNT);

  one_color_all(0,0,0); //-CLEAR STRIP
  LEDS.show();
  Serial.println(F("setup done."));
}


//------------------MAIN LOOP------------------
void loop() {
	BLESerial.poll();
    switch (ledMode) {
      case 999: break;
      case  1: one_color_allHSV(thishue); break;
      case  2: rainbow_fade(); break;
      case  3: rainbow_loop(); break;
      case  4: random_burst(); break;
      case  5: color_bounce(); break;
      case  6: color_bounceFADE(); break;
      case  7: ems_lightsONE(); break;
      case  8: random_color_pop(); break;
      case  9: flicker(); break;
      case 10: pulse_one_color_all(); break;
      case 11: flame(); break;
      case 12: rainbow_vertical(); break;
    }
    //---PROCESS HARDWARE SERIAL COMMANDS AND ARGS
    while (BLESerial.available() > 0) {
      inbyte = BLESerial.read();
      switch (inbyte) {
        case 59: break; //---BREAK IF INBYTE = ';'
        case 100:      //---"d" - SET DELAY VAR
          thisarg = BLEparseInt();
          Serial.print(F("delay:"));
          Serial.println(thisarg);
          thisdelay = thisarg;
          break;
        case 115:      //---"s" - SET STEP VAR
          thisarg = BLEparseInt();
          thisstep = thisarg;
          break;
        case 104:      //---"h" - SET HUE VAR
          thisarg = BLEparseInt();
          thishue = thisarg;
          thisarg = BLEparseInt();
          thissat = thisarg;
          Serial.print(F("H:"));
          Serial.print(thishue);
          Serial.print(F(" S:"));
          Serial.println(thissat);
          //change_mode(0);
          break;
        case 98:      //---"b" - SET MAX BRIGHTNESS
          max_bright = BLEparseInt();
          LEDS.setBrightness(max_bright);
          Serial.print(F("brightness change:"));
          Serial.println(max_bright);
          break;
        case 109:      //---"m" - SET MODE
          thisarg = BLEparseInt();
          change_mode(thisarg);
          Serial.print(F("mode change:"));
          Serial.println(thisarg);
          break;
        case 81:      //---"Q" - COMMAND RETURN VERSION NUMBER
          Serial.print(VERSION_NUMBER);
          break;
      }
    }
}
