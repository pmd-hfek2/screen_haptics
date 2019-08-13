/***************************************************************************
 * Precision Microdrives
 * SCREEN_HAPTICS for Haptic Feedback Evaluation Kit 2 (HFEK2) and demos
 * by: Tristan Cool
 * August 2019 
 * Arduino UNO
***************************************************************************/

//*************************** INCLUDE **************************************//
#define __PROG_TYPES_COMPAT__
#include <avr/pgmspace.h>

#include <SPI.h>
#include <mpr121.h>
#include <i2c.h>

// Debug
#include "debug.h"

// Include our headers
#include "Metro.h"
#include "motor.h"

// Init timer for 2s, and auto-reset when we get a positive check
Metro timer( 2000, 1 );
Motor motor = Motor();

//*************************** WIRING  **************************************//
/*
 * PMD Haptic Feedback Evaluation Kit (HFEK) in Developer Mode
 */

//*************************** VARIABLES **************************************//

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
  // Setup serial
  Serial.begin( 9600 );
  Serial.println(F("PRECISION MICRODRIVES - SCREEN_HAPTICS_PMD DEMO"));
  //Serial.print( F("FreeMem=") );
  //Serial.println( freeRAM() );
  
  setupPins();
  i2cInit( 200 );
  
  // Set up the motor
  motor.selectMotor( 6 ); //TacHammer
  motor.autoCalibrate();

  // Ensure any time for calibration is ignored.
  timer.reset();

} //end:SETUP

//*************************** LOOP **************************************//
void loop()
{
//  // Example code - check for some condition
//  // N.B. We play an effect every 2 seconds
//  uint8_t condition = timer.check();
//  if( condition )
//  {
//    // Do an effect
//   condition = 0;
//   motor.playFullHaptic( 1, 53 );
//  }
 
  //Demo effects
  demo();

} //end:LOOP


//*************************** FUNCTIONS **************************************//

void setupPins()
{
    pinMode( DRV_2605_EN,       OUTPUT );   // Output for DRV2605 Enable
    pinMode( PWM_OUT,           OUTPUT );   // Output for PWM
    pinMode( SRC_SEL,           OUTPUT );   // HIGH = DRV, LOW = MOS 
    pinMode( GRIP_SEL,          OUTPUT );   // LOW = Haptic Grip Connected
    pinMode( LRA_SEL,           OUTPUT );   // LOW = Haptic Shield LRA Connected
    pinMode( ERM_SEL,           OUTPUT );   // LOW = Haptic Shield ERM Connected

    pinMode( MOTOR_PIN_0,       OUTPUT );   // Motor select 1
    pinMode( MOTOR_PIN_1,       OUTPUT );   // Motor select 2
    
    digitalWrite( PWM_OUT,      LOW );      // PWM output low
    digitalWrite( SRC_SEL,      HIGH );     // Select DRV
    digitalWrite( GRIP_SEL,     HIGH  );    // Select none 
    digitalWrite( ERM_SEL,      HIGH  );    // Select none
    digitalWrite( LRA_SEL,      HIGH  );    // Select none 
} // setupPins

void PrintEffect(effect &EFFECT)
{
  Serial.print(EFFECT.value);
  Serial.print(F(": "));
  Serial.println(EFFECT.id);
}

void PlayEffect(int effect)
{
    //set and play effect
    motor.playFullHaptic( 1, effect );
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
