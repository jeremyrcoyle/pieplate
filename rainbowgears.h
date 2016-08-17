#ifndef RAINBOWGEARS_H
#define RAINBOWGEARS_H

#include "animation.h"

class RainbowGears : public Animation {
public:
	RainbowGears(LEDArray *ledarray)
	{
		ledarray->init_rainbow();
		FastLED.show();

	}
	
	void step(LEDArray *ledarray)
	{
		ledarray->gears();
		FastLED.show();
		delay(20);
	}
};

Animation * rainbowgears_factory(LEDArray *ledarray) {
  return new RainbowGears(ledarray);  
} 

#endif
