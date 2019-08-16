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
/* PMD Haptic Feedback Evaluation Kit (HFEK) in Developer Mode
 * 
 * Button1 --> ARD D5
 * Button2 --> ARD D8
 * Button3 --> ARD D10
 */

//*************************** VARIABLES **************************************//

const int pinButton1 = 5;   //D5
int Button1 = 0;
int prevButton1 = 0;
const int pinButton2 = 8;   //D8
int Button2 = 0;
int prevButton2 = 0;
const int pinButton3 = 10;  //D10
int Button3 = 0;
int prevButton3 = 0;

typedef struct{
  int value;
  String id;
} effect;

//single-click(strong,medium), double-click(strong,medium), ramp-up(short,medium,long), ramp-down(short,medium,long)
effect EFFECT[10] = {{5,"single-click sharp"},{25,"single-tick sharp"},
                     {35,"double-tick sharp"},{36,"double-click sharp"},
                     {87,"ramp-up short"},{85,"ramp-up medium"},{83,"ramp-up long"},
                     {75,"ramp-down short"},{73,"ramp-down medium"},{71,"ramp-down long"}};

int index = 0;

//*************************** SETUP **************************************//
void setup()
{
  // setup Serial
  Serial.begin( 9600 );
  Serial.println(F("PRECISION MICRODRIVES - SCREEN_HAPTICS_PMD DEMO"));
  //Serial.print( F("FreeMem=") );
  //Serial.println( freeRAM() );

  //init Buttons
  pinMode(pinButton1, INPUT);
  pinMode(pinButton2, INPUT);
  pinMode(pinButton3, INPUT);

  //init DRV
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
  //============= ORIGINAL CODE ====================
//  // Example code - check for some condition
//  // N.B. We play an effect every 2 seconds
//  uint8_t condition = timer.check();
//  if( condition )
//  {
//    // Do an effect
//   condition = 0;
//   motor.playFullHaptic( 1, 53 );
//  }

  //============= DEMO CODE =======================
  //Demo effects
  //demo();

  //============= APPLICATION CODE ================
  //read buttons
  Button1 = digitalRead(pinButton1);
  Button2 = digitalRead(pinButton2);
  Button3 = digitalRead(pinButton3);

  //Button1 is used to play effect
  //Button1 is used to play effect
  if(Button1)
  {
    Serial.println(index);
    PrintEffect(EFFECT[index]);
    PlayEffect(EFFECT[index].value);
  }

  //Button2 is used to increment effect
  if(Button2 != prevButton2){
    if(Button2)
    {
     index++;
     if(index>9)
      index=9; 
     Serial.println(index);
    }
    delay(50);
  }
  prevButton2 = Button2;

  //Button3 is used to decrement effect
  if(Button3 != prevButton3){
    if(Button3)
    {
      index--;
      if(index<0)
        index=0;
      Serial.println(index);
    }
    delay(50);
  }
  prevButton3 = Button3;

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
