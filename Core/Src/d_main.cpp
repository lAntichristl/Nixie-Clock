/*
 * d_main.cpp
 *
 *  Created on: Jun 22, 2020
 *      Author: hardware
 */


#include <Clock.h>
#include <FreeRTOS.h>
#include <task.h>

#include "d_debug.h"
#include "Object.h"
#include "Task.h"
#include "Gpio.h"
#include "GPin.h"
#include "d_main.h"
#include "rtc.h"
#include "PinController.h"
#include "PWM.h"
#include "Clock.h"
#include "Menu.h"


extern TIM_HandleTypeDef htim1;

extern RTC_HandleTypeDef hrtc;


PWM clockPeriphPWM(&htim1, TIM_CHANNEL_2, "clockPeriphPWM");

GPin L1(L1_GPIO_Port, L1_Pin, GPIO_PIN_SET);
PinController l1Controller(L1, "l1_control");
GPin L2(L2_GPIO_Port, L2_Pin, GPIO_PIN_SET);
PinController l2Controller(L2, "l2_control");
GPin L3(L3_GPIO_Port, L3_Pin, GPIO_PIN_SET);
PinController l3Controller(L3, "l3_control");
GPin L4(L4_GPIO_Port, L4_Pin, GPIO_PIN_SET);
PinController l4Controller(L4, "l4_control");
GPin L5(L5_GPIO_Port, L5_Pin, GPIO_PIN_SET);
PinController l5Controller(L5, "l5_control");
GPin L6(L6_GPIO_Port, L6_Pin, GPIO_PIN_SET);
PinController l6Controller(L6, "l6_control");
GPin DATA(DATA_GPIO_Port, DATA_Pin, GPIO_PIN_RESET);
PinController dataController(DATA, "data_control");

Gpio buttonLeft(BUTTON_LEFT_GPIO_Port, BUTTON_LEFT_Pin);
Gpio buttonMid(BUTTON_MIDDLE_GPIO_Port, BUTTON_MIDDLE_Pin);
Gpio buttonRight(BUTTON_RIGHT_GPIO_Port, BUTTON_RIGHT_Pin);

Menu menu(buttonLeft, buttonMid, buttonRight, "menu");

Clock clock(&hrtc, clockPeriphPWM, dataController, l1Controller, l2Controller, l3Controller, l4Controller, l5Controller, l6Controller, "clock");

/* TODO: not a single class here frees resources upon destruction. */

static const int UpdatePeriod = 100;           /* ms */


static void d_main_task(void *);


extern "C" {

void
d_main()
{
  auto rc = xTaskCreate(d_main_task, "d_main_task", 352, NULL, Task::DefaultPriority, NULL);
  d_debug_assert(rc == pdPASS);
  vTaskDelete(NULL);
}


int8_t
d_main_usb_recv_handler(uint8_t *buffer, uint32_t length)
{
	return 1;
}


HAL_StatusTypeDef
d_main_debug_write(const char *buffer, size_t length)
{

  return HAL_OK;
}


}

void
clockControl(){
	clock.dataSend();
}


static void
d_main_task(void *)
{
  d_debug_init();
  Object::start(nullptr, UpdatePeriod);

  for (;;)
  {
	  vTaskDelay(1000);
  }
}
