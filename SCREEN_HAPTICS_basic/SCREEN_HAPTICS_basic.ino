/***************************************************************************
 * Precision Microdrives
 * SCREEN_HAPTICS for Haptic Feedback Evaluation Kit 2 (HFEK2) and demos
 * by: Tristan Cool
 * August 2019 
 * Arduino MEGA
***************************************************************************/

//include
#include <Wire.h>
#include "Adafruit_DRV2605.h"

//*************************** SETUP **************************************//

Adafruit_DRV2605 drv;

void setup() {
  
  Serial.begin(9600);
  Serial.println("PRECISION MICRODRIVES - SCREEN_HAPTICS_basic DEMO");
  drv.begin();

} //end:SETUP

//*************************** LOOP **************************************//
void loop() {
  // put your main code here, to run repeatedly:

} //end:LOOP
