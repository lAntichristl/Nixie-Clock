/*
 * PWM.h
 *
 *  Created on: Nov 24, 2023
 *      Author: ihor_manukov
 */

#ifndef INC_PWM_H_
#define INC_PWM_H_


#include "main.h"
#include "Object.h"


class PWM : Object{

  static constexpr float MaxPWM = 1000.0;

  TIM_HandleTypeDef *htim;
  int ch;


public:

  explicit PWM(TIM_HandleTypeDef *htim, int ch, const char *name);
  void set(float pwm);

protected:

  virtual void onStart() override;


};



#endif /* INC_PWM_H_ */
