/*
 * d_main.h
 *
 *  Created on: Jun 22, 2020
 *      Author: hardware
 */

#ifndef INC_D_MAIN_H_
#define INC_D_MAIN_H_


#include <stdint.h>

#include "main.h"


#ifdef __cplusplus
extern "C" {
#endif

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void d_main();
int8_t d_main_usb_recv_handler(uint8_t *buffer, uint32_t length);
HAL_StatusTypeDef d_main_debug_write(const char *buffer, size_t length);

void clockControl();



#ifdef __cplusplus
}
#endif


#endif /* INC_D_MAIN_H_ */
