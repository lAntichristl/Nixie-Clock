/*
 * Pin.h
 *
 *  Created on: Apr 17, 2020
 *      Author: hardware
 */


#ifndef SRC_PIN_H_
#define SRC_PIN_H_


#include "Object.h"
#include "SoftwareTimer.h"


/* TODO: has to be rewritten using timers. */


class Pin : public Object {


	volatile bool on;
	volatile bool blinking;
	unsigned int blinkPeriod;
	SoftwareTimer timer;
	bool defaultState;
	bool lastBlinking;


	void onTimeout();


public:

	static const unsigned int DefaultBlinkPeriod = 500; /* ms */


	explicit Pin(unsigned int blinkPeriod = DefaultBlinkPeriod);

	void onStart();

	inline bool
	isOn() const
	{
		return static_cast<bool>(on);
	}


	inline void
	setOn(bool on)
	{
		turn(on);
	}


	inline void
	toggle()
	{
		setOn(!isOn());
	}


	inline bool
	isBlinking() const
	{
		return static_cast<bool>(blinking);
	}


	inline void
	setBlinking(bool blinking)
	{
		this->blinking = blinking;
	}


	inline unsigned int
	getBlinkPeriod() const
	{
		return blinkPeriod;
	}


	inline void
	setBlinkPeriod(unsigned int blinkPeriod)
	{
		this->blinkPeriod = blinkPeriod;

		timer.setPeriod(SoftwareTimer::ticksFromMs(blinkPeriod));
	}


protected:


	virtual void turn(bool on);


};


#endif /* SRC_PIN_H_ */
