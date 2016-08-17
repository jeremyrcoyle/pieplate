#ifndef OFF_H
#define OFF_H

#include "animation.h"

class Off : public Animation {
public:
	Off(LEDArray *ledarray)
	{
		ledarray->init_off();
		FastLED.show();

	}
	
	void step(LEDArray *ledarray)
	{
	}
};

Animation * off_factory(LEDArray *ledarray) {
  return new Off(ledarray);  
} 

#endif
