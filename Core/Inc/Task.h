/*
 * Task.h
 *
 *  Created on: Apr 16, 2020
 *      Author: hardware
 */


#ifndef SRC_TASK_H_
#define SRC_TASK_H_


#include "FreeRTOS.h"
#include "task.h"

#include "Object.h"


class Task : public Object {

	unsigned int stackSize;
	unsigned int priority;


public:

	static const unsigned int DefaultPriority = 5;




protected:

	explicit Task(unsigned int stackSize,
			unsigned int priority = DefaultPriority, const char *name = "Task");

	virtual void run() = 0;

	virtual void onStart() override;

private:

	static void task(void * thiz);


};


#endif /* SRC_TASK_H_ */
