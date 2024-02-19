/*
 * Menu.h
 *
 *  Created on: Nov 24, 2023
 *      Author: ihor_manukov
 */

#ifndef INC_MENU_H_
#define INC_MENU_H_


#include "Task.h"
#include "Serial.h"
#include "string.h"
#include "main.h"
#include "stm32f1xx_hal.h"
#include "stdio.h"
#include "Gpio.h"

class Menu : public Task {
	Gpio &left;
	Gpio &mid;
	Gpio &right;

public:

  Menu(Gpio &left, Gpio &mid, Gpio &right, const char *name);

private:


protected:

  virtual void run() override;
  const int delay = 50;
  bool lastMove = 0;

};




#endif /* INC_MENU_H_ */
