/*
 * effects.h
 *
 *  Created on: Jul 4, 2018
 *      Author: ab
 */

#ifndef EFFECTS_H_
#define EFFECTS_H_



#include <FastLED.h>
#include <Arduino.h>
#include "common.h"


int bottom_index = 0;
struct CRGB leds[LED_COUNT];
int ledsX[LED_COUNT][3];     //-ARRAY FOR COPYING WHATS IN THE LED STRIP CURRENTLY (FOR CELL-AUTOMATA, MARCH, ETC)
int ledMode = 3;           //-START IN RAINBOW LOOP
//int ledMode = 888;         //-START IN DEMO MODE
//int ledMode = 6;             //-MODE TESTING
//int ledMode = 29;             //-MODE TESTING

int thisdelay = 50;          //-FX LOOPS DELAY VAR
int thisstep = 10;           //-FX LOOPS DELAY VAR
int thishue = 95;             //-FX LOOPS DELAY VAR
int thissat = 255;           //-FX LOOPS DELAY VAR
int max_bright = 10;         //-SET MAX BRIGHTNESS TO 1/4

int thisindex = 0;           //-SET SINGLE LED VAR
int thisRED = 0;
int thisGRN = 0;
int thisBLU = 0;

int btBOOL = 0;              //-ACTIVATE BLUETOOTH OR NOT

//---LED FX VARS
int idex = 0;                //-LED INDEX (0 to LED_COUNT-1
int ihue = 0;                //-HUE (0-255)
int ibright = 0;             //-BRIGHTNESS (0-255)
int isat = 0;                //-SATURATION (0-255)
int bouncedirection = 0;     //-SWITCH FOR COLOR BOUNCE (0-1)
float tcount = 0.0;          //-INC VAR FOR SIN LOOPS
int lcount = 0;              //-ANOTHER COUNTING VAR





//------------------------------------- UTILITY FXNS --------------------------------------
//---SET THE COLOR OF A SINGLE RGB LED
void set_color_led(int adex, int cred, int cgrn, int cblu);

//---FIND INDEX OF HORIZONAL OPPOSITE LED
int horizontal_index(int i);

//---FIND INDEX OF ANTIPODAL OPPOSITE LED
int antipodal_index(int i);

//---FIND ADJACENT INDEX CLOCKWISE
int adjacent_cw(int i);

//---FIND ADJACENT INDEX COUNTER-CLOCKWISE
int adjacent_ccw(int i);

void copy_led_array();



//------------------------LED EFFECT FUNCTIONS------------------------
void one_color_all(int cred, int cgrn, int cblu);       //-SET ALL LEDS TO ONE COLOR


void one_color_allHSV(int ahue);    //-SET ALL LEDS TO ONE COLOR (HSV)


void rainbow_fade();                         //-m2-FADE ALL LEDS THROUGH HSV RAINBOW

void rainbow_loop();                        //-m3-LOOP HSV RAINBOW

void random_burst();                         //-m4-RANDOM INDEX/COLOR

void color_bounce();                        //-m5-BOUNCE COLOR (SINGLE LED)


void color_bounceFADE();                    //-m6-BOUNCE COLOR (SIMPLE MULTI-LED FADE)


void ems_lightsONE();                    //-m7-EMERGENCY LIGHTS (TWO COLOR SINGLE LED)


void ems_lightsALL();                  //-m8-EMERGENCY LIGHTS (TWO COLOR SOLID)


void flicker();                          //-m9-FLICKER EFFECT

void pulse_one_color_all();              //-m10-PULSE BRIGHTNESS ON ALL LEDS TO ONE COLOR


void pulse_one_color_all_rev();          //-m11-PULSE SATURATION ON ALL LEDS TO ONE COLOR


void fade_vertical();                    //-m12-FADE 'UP' THE LOOP


void random_red();                       //QUICK 'N DIRTY RANDOMIZE TO GET CELL AUTOMATA STARTED


void rule30();                          //-m13-1D CELLULAR AUTOMATA - RULE 30 (RED FOR NOW)}


void random_march();                   //-m14-RANDOM MARCH CCW


void rwb_march();                   //-m15-R,W,B MARCH CCW


void radiation();                   //-m16-SORT OF RADIATION SYMBOLISH-


void color_loop_vardelay();                    //-m17-COLOR LOOP (SINGLE LED) w/ VARIABLE DELAY


void white_temps();                            //-m18-SHOW A SAMPLE OF BLACK BODY RADIATION COLOR TEMPERATURES


void sin_bright_wave();        //-m19-BRIGHTNESS SINE WAVE


void pop_horizontal();        //-m20-POP FROM LEFT TO RIGHT UP THE RING


void quad_bright_curve();      //-m21-QUADRATIC BRIGHTNESS CURVER


void flame();                                  //-m22-FLAMEISH EFFECT


void rainbow_vertical();                        //-m23-RAINBOW 'UP' THE LOOP


void pacman();                                  //-m24-REALLY TERRIBLE PACMAN CHOMPING EFFECT

void random_color_pop();                        //-m25-RANDOM COLOR POP


void ems_lightsSTROBE();                  //-m26-EMERGENCY LIGHTS (STROBE LEFT/RIGHT)


void matrix();                                   //-m29-ONE LINE MATRIX

void config_mode(/*int cred, int cgrn, int cblu*/);       //-SET ALL LEDS TO ONE COLOR





#endif /* EFFECTS_H_ */
