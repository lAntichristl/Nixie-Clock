
/*
 * GPin.h
 *
 *  Created on: Jul 28, 2020
 *      Author: hardware
 */


#ifndef INC_GPIN_H_
#define INC_GPIN_H_


#include "Pin.h"
#include "main.h"


class GPin : public Pin {


  GPIO_TypeDef *handle;
  uint16_t pin;
  GPIO_PinState activeState;


public:

  explicit GPin(GPIO_TypeDef *handle, uint16_t pin, GPIO_PinState activeState = GPIO_PIN_SET);


protected:

  virtual void turn(bool on) override;


};


#endif /* INC_GPIN_H_ */
