#ifndef GALAXY_H
#define GALAXY_H

#include "animation.h"

class Galaxy : public Animation {
public:
	Galaxy(LEDArray *ledarray)
	{
		ledarray->init_off();
		FastLED.show();

	}
	
	void step(LEDArray *ledarray)
	{
		ledarray->galaxy();
		FastLED.show();
		delay(200);
	}
};

Animation * galaxy_factory(LEDArray *ledarray) {
  return new Galaxy(ledarray);  
} 

#endif
