#ifndef STARFIELD_H
#define STARFIELD_H

#include "animation.h"

class Starfield : public Animation {
public:
	Starfield(LEDArray *ledarray)
	{
		ledarray->init_off();
		FastLED.show();

	}
	
	void step(LEDArray *ledarray)
	{
		ledarray->explode();
		ledarray->generate_starfield();
		FastLED.show();
		delay(200);
	}
};

Animation * starfield_factory(LEDArray *ledarray) {
  return new Starfield(ledarray);  
} 

#endif
