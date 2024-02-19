
/*
 * SoftwareTimer.cpp
 *
 *  Created on: Jul 29, 2020
 *      Author: hardware
 */


#include "SoftwareTimer.h"


/* TODO: Support for calls from ISR. */


void
SoftwareTimer::timerCallback(TimerHandle_t handle)
{
	reinterpret_cast<SoftwareTimer *>(pvTimerGetTimerID(handle))->run();
}


SoftwareTimer::SoftwareTimer(TickType_t period,
							 SoftwareTimer::Callback callback,
							 bool oneShot, bool autoStart, const char *name)
	: Object(name),
	  callback(callback),
	  period(period),
	  oneShot(oneShot),
	  autoStart(autoStart),
	  handle(nullptr)
{

}


void
SoftwareTimer::onInit()
{
	handle = xTimerCreate(getName(), period,
						  oneShot ? pdFALSE : pdTRUE,
						  this, &SoftwareTimer::timerCallback);

	d_debug_assert(handle != nullptr);
}


void
SoftwareTimer::onStart()
{
	if (autoStart) {
		start();
	}
}


void
SoftwareTimer::run()
{
	if (callback) {
		callback();
	}
}
