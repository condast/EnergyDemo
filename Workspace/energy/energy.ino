#include "SPI.h"

#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "Adafruit_FT6206.h"

#include "Wizard.h"
#include "Interrupts.h"
#include "Calendar.h"
#include "Weather.h"
#include "Generator.h"
#include "Lights.h"
#include "Motors.h"

#define REFRESH 10

static Interrupts interrupt;
static Wizard wizard;
static Calendar calendar;
static Generator generator;
static Weather weather;
static Lights lights;
static Motors motors;

int load;
byte result;
int test;

void setup() {
  Serial.begin(9600);
  Serial.println(F("SETUP ENERGY TRANSITION DEMO"));
  interrupt.setup();
  lights.setup();
  motors.setup();
  calendar.setup();
  weather.setup();
  generator.setup( HOUSES_AREA1, HOUSES_AREA2, HOUSES_AREA3 );
  result = View::Event::NONE;
  wizard.setup();
}

void loop() {
  wizard.loop();
  //calendar.loop();
  //generator.loop();
  //useage.loop();
  //factsView.loop( 7 ); //One week
  if ( interrupt.getSecondsFlank()) {
    interrupt.clear();
    load = ( load + 1 ) % 120;
    int balance = load % REFRESH;
    //Serial.println( balance );
    switch ( balance ) {
      case 0:
        wizard.update();
        //Serial.println(F("LOOP LEDS: "));
        //lights.led(0, HIGH);
        break;
      case 1:
        //Serial.println( "LOGGER SETUP COMPLETE" );
        break;
      case 2:
        //Serial.println( "Aquabots message" );
        break;
      case 9:
        //Serial.println( "OPTIONS RECEIVED" );
        break;
      default:
        break;
    }
    //Serial.println( "\n\nUPDATING MODEL" );
  }
}
