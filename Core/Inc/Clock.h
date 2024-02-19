/*
 * LoraProxy.h
 *
 *  Created on: Jan 3, 2023
 *      Author: igor
 */

#ifndef INC_CLOCK_H_
#define INC_CLOCK_H_


#include "Task.h"
#include "Serial.h"
#include "string.h"
#include "main.h"
#include "stm32f1xx_hal.h"
#include "stdio.h"
#include "PWM.h"
#include "PinController.h"

class Clock : public Task {
	RTC_HandleTypeDef *hrtc;
	PWM &clockPeriphPWM;
	PinController &data;
	PinController &l1Controller;
	PinController &l2Controller;
	PinController &l3Controller;
	PinController &l4Controller;
	PinController &l5Controller;
	PinController &l6Controller;
public:

  Clock(RTC_HandleTypeDef *hrtc, PWM &clockPeriphPWM, PinController &data, PinController &l1Controller, \
		  PinController &l2Controller, PinController &l3Controller, PinController &l4Controller, PinController &l5Controller, PinController &l6Controller, const char *name);

  void dataSend();

private:

  int delay = 100;

protected:

  int tenHour[12] = {0};
  int oneHour[12] = {0};
  int tenMin[12] = {0};
  int oneMin[12] = {0};
  int tenSec[12] = {0};
  int oneSec[12] = {0};

  int tenDate[12] = {0};
  int oneDate[12] = {0};
  int tenMonth[12] = {0};
  int oneMonth[12] = {0};
  int tenYear[12] = {0};
  int oneYear[12] = {0};

  int dataPos = 0;
  virtual void run() override;


};


#endif /* INC_CLOCK_H_ */
