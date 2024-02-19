/*
 * Task.cpp
 *
 *  Created on: Apr 16, 2020
 *      Author: hardware
 */


#include "FreeRTOS.h"
#include "task.h"

#include "d_debug.h"
#include "Task.h"

bool g_data = 0;
bool g_menu = 0;
bool g_power = 0;
int g_unit = 0;

Task::Task(unsigned int stackSize, unsigned int priority, const char *name)
	: Object(name),
	  stackSize(stackSize),
	  priority(priority)
{

}


void
Task::onStart()
{
	auto rc = xTaskCreate(&Task::task, getName(), stackSize,
			this, priority, NULL);

	d_debug_assert(rc == pdPASS);
}


void
Task::task(void * thiz)
{
	auto task = reinterpret_cast<Task *>(thiz);

	task->run();
}
