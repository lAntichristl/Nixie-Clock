
/*
 * Gpio.cpp
 *
 *  Created on: Jul 30, 2020
 *      Author: hardware
 */


#include "Gpio.h"


Gpio *Gpio::openHandles[Gpio::MaxOpenHandlesCount];
Gpio::Static Gpio::s;


Gpio::Static::Static()
{
	for (int i = 0; i < MaxOpenHandlesCount; i++) {
		openHandles[i] = nullptr;
	}
}


Gpio::Gpio(GPIO_TypeDef *handle, uint16_t pin, ExtiCallback extiCallback)
  : handle(handle),
    pin(pin),
    extiCallback(extiCallback),
    next(nullptr)
{
  if (useExti()) {
    auto index = pinToIndex(pin);

    if (openHandles[index] == nullptr) {
      openHandles[index] = this;
    } else {
      auto gpio = openHandles[index];

      for (; gpio->next != nullptr; gpio = gpio->next);

      gpio->next = this;
    }
  }
}

bool
Gpio::getState()
{
  return HAL_GPIO_ReadPin(handle, pin);
}


void
Gpio::onExti()
{
  if (extiCallback) {
	  extiCallback();
  }
}


extern "C" {


void
HAL_GPIO_EXTI_Callback(uint16_t pin)
{
  auto gpio = Gpio::openHandles[Gpio::pinToIndex(pin)];

  for (; gpio != nullptr; gpio = gpio->next) {
    if (gpio->useExti()) {
      gpio->onExti();
    }
  }

  if(pin == BUTTON_LEFT_Pin)
  {



  }

  if(pin == BUTTON_MIDDLE_Pin)
  {



  }

  if(pin == BUTTON_RIGHT_Pin)
  {



  }


}
}
