/*
 * PinController.h
 *
 *  Created on: Apr 21, 2020
 *      Author: hardware
 */


#ifndef SRC_PINCONTROLLER_H_
#define SRC_PINCONTROLLER_H_


#include <Pin.h>

#include "Object.h"


class PinController : public Object{


	static const int MaxTopicLength = 32;


	Pin &pin;
	char onTopicName[MaxTopicLength];
	char blinkingTopicName[MaxTopicLength];
	bool onSubscriber;
	bool blinkingSubscriber;


public:

	explicit PinController(Pin &pin, const char *name);

	void set(bool state);



};



#endif /* SRC_PINCONTROLLER_H_ */
