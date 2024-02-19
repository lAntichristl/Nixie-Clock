/*
 * Object.cpp
 *
 *  Created on: Apr 16, 2020
 *      Author: hardware
 */


#include "d_debug.h"
#include "Object.h"


Object *Object::objects[MaxObjectsCount];
bool Object::connected = false;


void
Object::start(const char *portName, unsigned int spinTimeout)
{
	for (int i = 0; i < MaxObjectsCount; i++) {
		if (objects[i] != nullptr) {
		  objects[i]->onInit();
		}
	}

	for (int i = 0; i < MaxObjectsCount; i++) {
		if (objects[i] != nullptr) {
			objects[i]->onStart();
		}
	}
}

Object::~Object()
{
	d_debug_assert(0);
}


Object::Object(const char *name)
	: name(name),
	  memoryCorrupt(this)
{
	int i;

	for (i = 0; i < MaxObjectsCount && objects[i] != nullptr; i++);
	d_debug_assert(i != MaxObjectsCount);

	objects[i] = this;
}


void
Object::onStart() {

}

void Object::onInit() {

}
