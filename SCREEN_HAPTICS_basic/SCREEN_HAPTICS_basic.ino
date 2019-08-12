/***************************************************************************
 * Precision Microdrives
 * SCREEN_HAPTICS for Haptic Feedback Evaluation Kit 2 (HFEK2) and demos
 * by: Tristan Cool
 * August 2019 
 * Arduino UNO
***************************************************************************/

//*************************** INCLUDE **************************************//
#include <Wire.h>
#include "Adafruit_DRV2605.h"


//*************************** WIRING  **************************************//
/* DRV2605 VIN --> ARD 5V
 * DRV2605 GND --> ARD GND
 * DRV2605 SCL --> ARD A5 (Mega D21, Micro D3)
 * DRV2605 SDA --> ARD A4 (Mega D20, Micro D2)
 */
 
//*************************** VARIABLES **************************************//

Adafruit_DRV2605 drv;

typedef struct{
  int value;
  String id;
} effect;

//single-click(strong,medium), double-click(strong,medium), ramp-up(short,medium,long), ramp-down(short,medium,long)
effect EFFECT[10] = {{5,"single-click sharp"},{25,"single-tick sharp"},
                     {35,"double-tick sharp"},{36,"double-click sharp"},
                     {87,"ramp-up short"},{85,"ramp-up medium"},{83,"ramp-up long"},
                     {75,"ramp-down short"},{73,"ramp-down medium"},{71,"ramp-down long"}};


//*************************** SETUP **************************************//
void setup() 
{
  Serial.begin(9600);
  Serial.println(F("PRECISION MICRODRIVES - SCREEN_HAPTICS_basic DEMO"));
  drv.begin();

} //end:SETUP

//*************************** LOOP **************************************//
void loop() 
{
  //Demo effects
  demo();

} //end:LOOP


//*************************** FUNCTIONS **************************************//

void PrintEffect(effect &EFFECT)
{
  Serial.print(EFFECT.value);
  Serial.print(F(": "));
  Serial.println(EFFECT.id);
}

void PlayEffect(int effect)
{
    //set the effect to play
    drv.setWaveform(0, effect);  // play effect 
    drv.setWaveform(1, 0);       // end waveform
    //play the effect!
    drv.go();
    delay(1000);
}

void demo()
{
  for(int i = 0; i < sizeof(EFFECT)/sizeof(effect); i++)
  {
    PrintEffect(EFFECT[i]);
    PlayEffect(EFFECT[i].value);
    delay(1000);
  }
}
