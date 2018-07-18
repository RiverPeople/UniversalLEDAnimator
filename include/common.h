/*
 * common.h
 *
 *  Created on: Jul 4, 2018
 *      Author: ab
 */

#ifndef INCLUDE_COMMON_H_
#define INCLUDE_COMMON_H_

#define LED_COUNT 60 //FOR TESTING w/ SIGN
#define LED_DT 6 //SERIAL DATA PIN
#define DATA_PIN 6
#define LED_TYPE WS2811
#define COLOR_ORDER GRB
#define EVENODD LED_COUNT % 2
#define TOP_INDEX int(LED_COUNT / 2)

//---SERIAL/SOFTWARE SERIAL SETUP STUFF
//#define SERIAL_BAUDRATE 9600
//#define SERIAL_BAUDRATE 57600
#define SERIAL_BAUDRATE 115200
#define SERIAL_TIMEOUT 5

#define SOFT_RX_PIN 2         // BTCHIP-TX -> NANO-SOFT-RX (2)
#define SOFT_TX_PIN 3         // BTCHIP-RX -> NANO-SOFT-TX (3)


extern int bottom_index;
extern struct CRGB leds[LED_COUNT];
extern int ledsX[LED_COUNT][3];     //-ARRAY FOR COPYING WHATS IN THE LED STRIP CURRENTLY (FOR CELL-AUTOMATA, MARCH, ETC)
extern int ledMode;           //-START IN RAINBOW LOOP
//extern int ledMode = 888;         //-START IN DEMO MODE
//extern int ledMode = 6;             //-MODE TESTING
//extern int ledMode = 29;             //-MODE TESTING

extern int thisdelay;          //-FX LOOPS DELAY VAR
extern int thisstep;           //-FX LOOPS DELAY VAR
extern int thishue;             //-FX LOOPS DELAY VAR
extern int thissat;           //-FX LOOPS DELAY VAR
extern int max_bright;         //-SET MAX BRIGHTNESS TO 1/4

extern int thisindex;           //-SET SINGLE LED VAR
extern int thisRED;
extern int thisGRN;
extern int thisBLU;

extern int btBOOL;              //-ACTIVATE BLUETOOTH OR NOT

//---LED FX VARS
extern int idex;                //-LED INDEX (0 to LED_COUNT-1
extern int ihue;                //-HUE (0-255)
extern int ibright;             //-BRIGHTNESS (0-255)
extern int isat;                //-SATURATION (0-255)
extern int bouncedirection;     //-SWITCH FOR COLOR BOUNCE (0-1)
extern float tcount;          //-INC VAR FOR SIN LOOPS
extern int lcount;              //-ANOTHER COUNTING VAR
extern int r, g, b;



#endif /* INCLUDE_COMMON_H_ */
