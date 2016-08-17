#include <FastLED.h>
#include <PacketSerial.h>
#define LED_TYPE    NEOPIXEL
#define COLOR_ORDER RGB
#define framerate   500
//#define COLOR_CORRECTION CRGB(255,172,240)
#define BRIGHTNESS  128
#define NUM_STRIPS 8
#define NUM_LEDS_PER_STRIP 5
#define NUM_LEDS 40
CRGB leds[NUM_LEDS];

#include "ledarray.h"
#include "animation.h"

//library of animations
#include "noise.h"
#include "off.h"
#include "starfield.h"
#include "disco.h"
#include "galaxy.h"
#include "rainbowgears.h"
#include "target.h"

#define NUM_ANIMATIONS 7
Animation * current_animation;
Animation *(*animation_factories[NUM_ANIMATIONS])(LEDArray * ledarray);
LEDArray *ledarray;

boolean next_animation;
int animation_num=NUM_ANIMATIONS-1;


void button() {
  next_animation=true;
}

void setup() {
  
   // power-up sanity delay
  pinMode(12, INPUT); 
  
  //delay( 3000 );
  
  // tell FastLED about the LEDs
  FastLED.addLeds<NEOPIXEL, 6>(leds, 0*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, 5>(leds, 1*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, 7>(leds, 2*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, 3>(leds, 3*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, 4>(leds, 4*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, 10>(leds, 5*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, 8>(leds, 6*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, 9>(leds, 7*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
  
  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
  fill_solid(leds,NUM_LEDS,CHSV(128,255,128));
  FastLED.show();
  ledarray=new LEDArray(leds,NUM_LEDS);
  
  animation_factories[0] = &noise_factory;
  animation_factories[1] = &off_factory;
  animation_factories[2] = &starfield_factory;
  animation_factories[3] = &disco_factory;
  animation_factories[4] = &galaxy_factory;
  animation_factories[5] = &rainbowgears_factory;
  animation_factories[6] = &target_factory;
  
  current_animation = animation_factories[animation_num](ledarray);
  next_animation= false;
  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), button, RISING);
}


// loop is called repeatedly forever
void loop()
{
  current_animation->step(ledarray); 

  if(next_animation){
    animation_num=(animation_num+1)%NUM_ANIMATIONS;
    current_animation = animation_factories[animation_num](ledarray);
    next_animation=false;
    delay(250);
  }
  /*
  if(random(255)==0){
    animation_num=random(NUM_ANIMATIONS);
    current_animation = animation_factories[animation_num](ledarray);
  }
  */
}


