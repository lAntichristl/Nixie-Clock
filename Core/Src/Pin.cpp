
/*
 * Pin.cpp
 *
 *  Created on: Apr 17, 2020
 *      Author: hardware
 */


#include "Pin.h"


void
Pin::onTimeout()
{
	auto blinking = isBlinking();

	if (blinking) {
		turn(!isOn());
	} else if (blinking != lastBlinking) {
		turn(defaultState);
	}

	lastBlinking = blinking;
}


Pin::Pin(unsigned int blinkPeriod)
	: on(false),
	  blinking(false),
	  blinkPeriod(blinkPeriod),
	  timer(SoftwareTimer::ticksFromMs(blinkPeriod),
			std::bind(&Pin::onTimeout, this))
{

}


void
Pin::onStart()
{
	defaultState = isOn();
	lastBlinking = isBlinking();
}


void
Pin::turn(bool on)
{
	this->on = on;
}
