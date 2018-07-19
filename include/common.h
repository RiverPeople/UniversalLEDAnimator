#ifndef INCLUDE_COMMON_H_
#define INCLUDE_COMMON_H_
//Setup and system variables taken from Funkboxing's example

//SETTINGS
//LED data pin
#define LED_DT 6

//Serial connection parameters
#define SERIAL_BAUDRATE 115200
#define SERIAL_TIMEOUT 5

// BLE pins
#define BLE_REQ   9
#define BLE_RDY  8
#define BLE_RST   5

//Number of LEDs in the setup
#define LED_COUNT 75

//Driver chip type
#define LED_TYPE WS2811

//Driver chip color order
#define COLOR_ORDER GRB

//Driver chip type
#define EVENODD LED_COUNT % 2
#define TOP_INDEX int(LED_COUNT / 2)

//SYSTEM VARIABLES

extern int bottom_index;
extern struct CRGB leds[LED_COUNT];
extern int ledsX[LED_COUNT][3];
extern int ledMode;           //-START IN RAINBOW LOOP

extern int thisdelay;          //-FX LOOPS DELAY VAR
extern int thisstep;           //-FX LOOPS DELAY VAR
extern int thishue;             //-FX LOOPS DELAY VAR
extern int thissat;           //-FX LOOPS DELAY VAR
extern int max_bright;         //-SET MAX BRIGHTNESS TO 1/4

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
