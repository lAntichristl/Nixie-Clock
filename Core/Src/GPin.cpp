
/*
 * HLGPin.cpp
 *
 *  Created on: Jul 28, 2020
 *      Author: hardware
 */


#include <GPin.h>


GPin::GPin(GPIO_TypeDef *handle, uint16_t pin, GPIO_PinState activeState)
  : Pin(),
    handle(handle),
    pin(pin),
    activeState(activeState)
{

}


void
GPin::turn(bool on)
{
  Pin::turn(on);

  auto inactiveState = activeState == GPIO_PIN_SET ? GPIO_PIN_RESET : GPIO_PIN_SET;

  auto state = on ? activeState : inactiveState;

  HAL_GPIO_WritePin(handle, pin, state);
}
