#ifndef ANIMATION_H
#define ANIMATION_H

#include "ledarray.h"

class Animation
{
/*
** Class that stores all of the animations that are being used in an LED array
** Purpose: Loop only calls Animation.animate: a function that essentailly loops the 
**
*/

public:
	virtual void step(LEDArray *ledarray) = 0;
};

#endif
