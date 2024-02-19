
#ifndef _D_LED_INCLUDED_
#define _D_LED_INCLUDED_


/*
 * For this code to work the led pin has to be set in STM32CubeMX as 
 * output Push/Pull pin with user label D_LED.
 * The LED itself should be pulled to 3.3V and its cathode should go
 * to D_LED pin through a resistor.
 * Change `D_LED_ON_STATE` and `D_LED_OFF_STATE` if that is not the case.
 */


#ifdef D_LED_Pin


#    include <stm32f1xx_hal.h>


#    define D_LED_ON_STATE   GPIO_PIN_RESET
#    define D_LED_OFF_STATE  GPIO_PIN_SET


#    define d_led_on()                                                    \
          HAL_GPIO_WritePin(D_LED_GPIO_Port, D_LED_Pin, D_LED_ON_STATE)


#    define d_led_off()                                                   \
          HAL_GPIO_WritePin(D_LED_GPIO_Port, D_LED_Pin, D_LED_OFF_STATE) 


#    define d_led_set(value)                                              \
          HAL_GPIO_WritePin(D_LED_GPIO_Port, D_LED_Pin,                   \
                  (value) ? D_LED_ON_STATE : D_LED_OFF_STATE)


#    define d_led_toggle()                                                \
        HAL_GPIO_TogglePin(D_LED_GPIO_Port, D_LED_Pin)


#else


#    warning "D_LED pin is not set. d_led interface will not be available"


#    define d_led_on()


#    define d_led_off()


#    define d_led_set(value)


#    define d_led_toggle()


#endif /* D_LED_Pin */


#endif /* _D_LED_INCLUDED_ */
