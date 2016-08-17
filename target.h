#ifndef TARGET_H
#define TARGET_H

#include "animation.h"

class Target : public Animation {
public:
	Target(LEDArray *ledarray)
	{
		ledarray->init_ringbow();
		FastLED.show();

	}
	
	void step(LEDArray *ledarray)
	{
		ledarray->explode();
		ledarray->rotate_hue();
		FastLED.show();
		delay(100);
	}
};

Animation * target_factory(LEDArray *ledarray) {
  return new Target(ledarray);  
} 

#endif
