#ifndef DISCO_H
#define DISCO_H

#include "animation.h"

class Disco : public Animation {
public:
	Disco(LEDArray *ledarray)
	{
		ledarray->init_rainbow();
		FastLED.show();

	}
	
	void step(LEDArray *ledarray)
	{
		ledarray->spinterlace();
		FastLED.show();
		delay(200);
	}
};

Animation * disco_factory(LEDArray *ledarray) {
  return new Disco(ledarray);  
} 

#endif
