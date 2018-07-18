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
//"RBL_nRF8001.h/spi.h/boards.h" is needed in every new project
#include <SPI.h>
#include <BLEPeripheral.h>
#include "BLESerial.h"


FASTLED_USING_NAMESPACE

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define VERSION_NUMBER 0.51



//---SERIAL/SOFTWARE SERIAL SETUP STUFF
//#define SERIAL_BAUDRATE 9600
//#define SERIAL_BAUDRATE 57600
//#define SERIAL_BAUDRATE 115200
#define SERIAL_TIMEOUT 5

#define SOFT_RX_PIN 2         // BTCHIP-TX -> NANO-SOFT-RX (2)
#define SOFT_TX_PIN 3         // BTCHIP-RX -> NANO-SOFT-TX (3)

byte inbyte;                 //-SERIAL INPUT BYTE
int thisarg;                 //-SERIAL INPUT ARG

// define pins (varies per shield/board)
#define BLE_REQ   9
#define BLE_RDY  8
#define BLE_RST   5

// create ble serial instance, see pinouts above
BLESerial BLESerial(BLE_REQ, BLE_RDY, BLE_RST);



long BLEparseInt()
{
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
    case 13: thisdelay = 100; break;                    //---CELL AUTO - RULE 30 (RED)
    case 14: thisdelay = 40; break;                     //---MARCH RANDOM COLORS
    case 15: thisdelay = 80; break;                     //---MARCH RWB COLORS
    case 16: thisdelay = 60; thishue = 95; break;       //---RADIATION SYMBOL
    //---PLACEHOLDER FOR COLOR LOOP VAR DELAY VARS
    case 19: thisdelay = 35; thishue = 180; break;      //---SIN WAVE BRIGHTNESS
    case 20: thisdelay = 100; thishue = 0; break;       //---POP LEFT/RIGHT
    case 21: thisdelay = 100; thishue = 180; break;     //---QUADRATIC BRIGHTNESS CURVE
    //---PLACEHOLDER FOR FLAME VARS
    case 23: thisdelay = 50; thisstep = 15; break;      //---VERITCAL RAINBOW
    case 24: thisdelay = 50; break;                     //---PACMAN
    case 25: thisdelay = 35; break;                     //---RANDOM COLOR POP
    case 26: thisdelay = 25; thishue = 0; break;        //---EMERGECNY STROBE
    case 27: thisdelay = 25; thishue = 0; break;        //---RGB PROPELLER
    case 28: thisdelay = 100; thishue = 0; break;       //---KITT
    case 29: thisdelay = 50; thishue = 95; break;       //---MATRIX RAIN
    case 50: thisdelay = 100; break;                    //---MARCH STRIP NOW CCW
    case 51: thisdelay = 100; break;                    //---MARCH STRIP NOW CCW
    case 88: thisdelay = 5; break;                      //---NEW RAINBOW LOOP
    case 101: one_color_all(255,0,0); LEDS.show(); break;   //---ALL RED
    case 102: one_color_all(0,255,0); LEDS.show(); break;   //---ALL GREEN
    case 103: one_color_all(0,0,255); LEDS.show(); break;   //---ALL BLUE
    case 104: one_color_all(255,255,0); LEDS.show(); break;   //---ALL COLOR X
    case 105: one_color_all(0,255,255); LEDS.show(); break;   //---ALL COLOR Y
    case 106: one_color_all(255,0,255); LEDS.show(); break;   //---ALL COLOR Z
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
    }
    //---PROCESS HARDWARE SERIAL COMMANDS AND ARGS
    while (BLESerial.available() > 0) {
      inbyte = BLESerial.read();
      switch (inbyte) {
        case 59: break; //---BREAK IF INBYTE = ';'
        case 108:      //---"l" - SET SINGLE LED VALUE RGB
          thisindex = BLEparseInt();
          thisRED = BLEparseInt();
          thisGRN = BLEparseInt();
          thisBLU = BLEparseInt();
          if (ledMode != 999) {
            ledMode = 999;
            one_color_all(0, 0, 0);
          }
          leds[thisindex].setRGB( thisRED, thisGRN, thisBLU);
          break;
        case 118:      //---"v" - SET SINGLE LED VALUE HSV
          thisindex = BLEparseInt();
          thishue = BLEparseInt();
          thissat = BLEparseInt();
          //thisVAL = BLEparseInt();
          if (ledMode != 999) {
            ledMode = 999;
            one_color_all(0, 0, 0);
          }
          leds[thisindex] = CHSV(thishue, thissat, 255);
          break;
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
          /*inbyte = BLESerial.read();
          Serial.print(inbyte);
          if(inbyte == 't'){
              Serial.print(F(","));
              thisarg = BLEparseInt();
              thissat = thisarg;
          }*/
          Serial.print(F("H:"));
          Serial.print(thishue);
          Serial.print(F(" S:"));
          Serial.println(thissat);
          //change_mode(0);
          break;
        case 116:      //---"t" - SET SATURATION VAR
          //thisarg = BLEparseInt();
          //thissat = thisarg;
          //Serial.print(F(" S:"));
          //Serial.println(thissat);
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
        case 99:      //---"c" - CLEAR STRIP
          one_color_all(0, 0, 0);
          break;
        case 97:      //---"a" - SET ALL TO ONE COLOR BY HSV 0-255
          thisarg = BLEparseInt();
          one_color_allHSV(thisarg);
          break;
        case 122:      //---"z" - COMMAND TO 'SHOW' LEDS
          LEDS.show();
          break;
        case 81:      //---"Q" - COMMAND RETURN VERSION NUMBER
          Serial.print(VERSION_NUMBER);
          break;
        case 67:      //---"C" - CONFIG MODE
          change_mode(109);
          break;
      }
    }
}
