/*
 * Object.h
 *
 *  Created on: Apr 16, 2020
 *      Author: hardware
 */


#ifndef SRC_OBJECT_H_
#define SRC_OBJECT_H_


class Object {


	static const int MaxObjectsCount = 56;

	static Object *objects[MaxObjectsCount];
	static bool connected;


	const char *name;
	Object *memoryCorrupt;


public:

	static void start(const char *portName, unsigned int spinTimeout);

	static inline bool
	isConnected()
	{
		return connected;
	}


	inline const char *
	getName() const
	{
		return name;
	}


	virtual ~Object();


protected:

	Object(const char *name = "Object");


	virtual void onInit();
	virtual void onStart();


};


#endif /* SRC_OBJECT_H_ */
