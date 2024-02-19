/*
 * PinController.cpp
 *
 *  Created on: Apr 21, 2020
 *      Author: hardware
 */


#include <PinController.h>
#include <cstdio>

#include "d_debug.h"



PinController::PinController(Pin &pin, const char *name)
	: Object(name),
	  pin(pin)
{
}

void
PinController::set(bool state) {
	pin.setOn(state);
}

