/*
 * PWM.cpp
 *
 *  Created on: Nov 24, 2023
 *      Author: ihor_manukov
 */



#include "d_debug.h"
#include "PWM.h"


PWM::PWM(TIM_HandleTypeDef *htim, int ch, const char *name)
: Object(name),
  htim(htim),
  ch(ch)
{

}


void
PWM::onStart()
{
  d_debug_assert_hok(HAL_TIM_PWM_Start(htim, ch));
}


void
PWM::set(float pwm)
{

  __HAL_TIM_SET_COMPARE(htim, ch, (uint16_t)pwm);

}

