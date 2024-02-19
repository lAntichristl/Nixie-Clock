
/*
 * SoftwareTimer.h
 *
 *  Created on: Jul 24, 2020
 *      Author: hardware
 */


#ifndef INC_SOFTWARETIMER_H_
#define INC_SOFTWARETIMER_H_


#include <algorithm>
#include <functional>
#include <FreeRTOS.h>
#include <timers.h>

#include "d_debug.h"
#include "Object.h"


class SoftwareTimer : public Object {


public:


	using Callback = std::function<void()>;


	static inline const constexpr TickType_t
	ticksFromMs(unsigned int ms, TickType_t minTicks = 1)
	{
		return std::max(minTicks, pdMS_TO_TICKS(ms));
	}


	static inline const constexpr TickType_t
	ticksFromSecs(float secs, TickType_t minTicks = 1)
	{
		return ticksFromMs(secs * 1000, minTicks);
	}


	inline void
	setPeriod(TickType_t period)
	{
		d_debug_assert(handle != nullptr);

		this->period = period;
		auto rc = xTimerChangePeriod(handle, period, 0);

		d_debug_assert(rc == pdPASS);
	}


	inline void
	start(TickType_t timeout = portMAX_DELAY)
	{
		d_debug_assert(handle != nullptr);

		xTimerStart(handle, timeout);
	}


	inline void
	stop(TickType_t timeout = portMAX_DELAY)
	{
		d_debug_assert(handle != nullptr);

		xTimerStop(handle, timeout);
	}


	inline void
	reset(TickType_t timeout = portMAX_DELAY)
	{
		d_debug_assert(handle != nullptr);

		xTimerReset(handle, timeout);
	}


	inline TickType_t
	getPeriod() const
	{
		return period;
	}


	inline bool
	isActive()
	{
		return xTimerIsTimerActive(handle) != pdFALSE;
	}


private:

	Callback callback;
	TickType_t period;
	bool oneShot;
	bool autoStart;
	TimerHandle_t handle;


	static void timerCallback(TimerHandle_t handle);


public:

	explicit SoftwareTimer(TickType_t period, Callback callback = nullptr,
						   bool oneShot = false,
						   bool autoStart = true,
						   const char *name = "SoftwareTimer");


protected:

	void onInit();
	void onStart();

	virtual void run();


};


#endif /* INC_SOFTWARETIMER_H_ */
