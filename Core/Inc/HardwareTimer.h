
/*
 * HardwareTimer.h
 *
 *  Created on: Jun 23, 2020
 *      Author: hardware
 */


#ifndef INC_HARDWARETIMER_H_
#define INC_HARDWARETIMER_H_


#include "main.h"
#include "d_debug.h"


class HardwareTimer {


public:


	static inline double
	calcTickPeriod(TIM_HandleTypeDef *htim)
	{
		if (htim->Instance == TIM1) {
			return static_cast<double>(htim->Init.Prescaler + 1) * 1000000. /
					static_cast<double>(HAL_RCC_GetPCLK2Freq());
		} else {
			return 1000000. * static_cast<double>(htim->Init.Prescaler + 1) /
					static_cast<double>(HAL_RCC_GetPCLK1Freq()) / 2.;
		}
	}


	static inline double
	calcPeriod(TIM_HandleTypeDef *htim)
	{
		return calcTickPeriod(htim) * (__HAL_TIM_GET_AUTORELOAD(htim) + 1);
	}


	static inline uint32_t
	getActiveChannel(TIM_HandleTypeDef *htim)
	{
		switch (htim->Channel) {


		case HAL_TIM_ACTIVE_CHANNEL_1:

			return TIM_CHANNEL_1;


		case HAL_TIM_ACTIVE_CHANNEL_2:

			return TIM_CHANNEL_2;


		case HAL_TIM_ACTIVE_CHANNEL_3:

			return TIM_CHANNEL_3;


		case HAL_TIM_ACTIVE_CHANNEL_4:

			return TIM_CHANNEL_4;


		default:

			d_debug_assert(0);

			return TIM_CHANNEL_ALL;


		}
	}


};


#endif /* INC_HARDWARETIMER_H_ */
