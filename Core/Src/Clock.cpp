/*
 * LoraProxy.cpp
 *
 *  Created on: Jan 3, 2023
 *      Author: igor
 */

#include <Clock.h>

extern bool g_data;
extern bool g_power;
extern int g_bit;
extern int g_unit;

Clock::Clock(RTC_HandleTypeDef *hrtc, PWM &clockPeriphPWM, PinController &data, PinController &l1Controller, \
				PinController &l2Controller, PinController &l3Controller, PinController &l4Controller, PinController &l5Controller, PinController &l6Controller, const char *name)
: Task(256, DefaultPriority + 2, name),
  hrtc(hrtc),
  clockPeriphPWM(clockPeriphPWM),
  data(data),
  l1Controller(l1Controller),
  l2Controller(l2Controller),
  l3Controller(l3Controller),
  l4Controller(l4Controller),
  l5Controller(l5Controller),
  l6Controller(l6Controller)
{
  // TODO Auto-generated constructor stub
}

void
Clock::run() {

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};
  sTime.Hours = 17;
  sTime.Minutes = 37;
  sTime.Seconds = 32;

  if (HAL_RTC_SetTime(hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
	  Error_Handler();
  }

  sDate.WeekDay = RTC_WEEKDAY_SUNDAY;
  sDate.Month = RTC_MONTH_JANUARY;
  sDate.Date = 29;
  sDate.Year = 24;

  if (HAL_RTC_SetDate(hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
  {
 	  Error_Handler();
  }

  clockPeriphPWM.set(500);

  for (;;) {

	  RTC_DateTypeDef getDate = {0};
	  RTC_TimeTypeDef getTime = {0};

	  if (HAL_RTC_GetTime(hrtc, &getTime, RTC_FORMAT_BIN) != HAL_OK)
	  {
		  Error_Handler();
	  }

	  if (HAL_RTC_GetDate(hrtc, &getDate, RTC_FORMAT_BIN) != HAL_OK)
	  {
	      Error_Handler();
	  }

	  for(int i = 0; i<11; i++){

		  tenHour[i] = 0;
		  oneHour[i] = 0;
		  tenMin[i] = 0;
		  oneMin[i] = 0;
		  tenSec[i] = 0;
		  oneSec[i] = 0;

		  tenDate[i] = 0;
		  oneDate[i] = 0;
		  tenMonth[i] = 0;
		  oneMonth[i] = 0;
		  tenYear[i] = 0;
		  oneYear[i] = 0;

	  }

	  tenHour[12 - (getTime.Hours / 10)] = 1;
	  oneHour[12 - (getTime.Hours % 10)] = 1;
	  tenMin[12 - (getTime.Minutes / 10)] = 1;
	  oneMin[12 - (getTime.Minutes % 10)] = 1;
	  tenSec[12 - (getTime.Seconds / 10)] = 1;
	  oneSec[12 - (getTime.Seconds % 10)] = 1;

	  tenDate[12 - (getDate.Date / 10)] = 1;
	  oneDate[12 - (getDate.Date % 10)] = 1;
	  tenMonth[12 - (getDate.Month / 10)] = 1;
	  oneMonth[12 - (getDate.Month % 10)] = 1;
	  tenYear[12 - (getDate.Year / 10)] = 1;
	  oneYear[12 - (getDate.Year % 10)] = 1;

	  vTaskDelay(delay);
  }

}

void
Clock::dataSend(){

	if(!g_power){

		if(!g_data){

			switch (dataPos){

			case 0:

				data.set(!oneHour[g_bit]);
				l1Controller.set(SET);
				l6Controller.set(RESET);
				break;

			case 1:

				data.set(tenMin[g_bit]);
				l1Controller.set(RESET);
				l2Controller.set(SET);
				break;

			case 2:

				data.set(oneMin[g_bit]);
				l2Controller.set(RESET);
				l3Controller.set(SET);
				break;

			case 3:

				data.set(tenSec[g_bit]);
				l3Controller.set(RESET);
				l4Controller.set(SET);
				break;

			case 4:

				data.set(oneSec[g_bit]);
				l4Controller.set(RESET);
				l5Controller.set(SET);
				break;

			case 5:

				data.set(tenHour[g_bit]);
				l5Controller.set(RESET);
				l6Controller.set(SET);
				break;

			}

		}
		else {

			switch (dataPos){

			case 0:

				data.set(oneDate[g_bit]);
				l1Controller.set(SET);
				l6Controller.set(RESET);
				break;

			case 1:

				data.set(tenMonth[g_bit]);
				l1Controller.set(RESET);
				l2Controller.set(SET);
				break;

			case 2:

				data.set(oneMonth[g_bit]);
				l2Controller.set(RESET);
				l3Controller.set(SET);
				break;

			case 3:

				data.set(tenYear[g_bit]);
				l3Controller.set(RESET);
				l4Controller.set(SET);
				break;

			case 4:

				data.set(oneYear[g_bit]);
				l4Controller.set(RESET);
				l5Controller.set(SET);
				break;

			case 5:

				data.set(tenDate[g_bit]);
				l5Controller.set(RESET);
				l6Controller.set(SET);
				break;

			}

		}

	}
	if (g_bit == 11){

		if(dataPos < 5) dataPos++;
		else dataPos = 0;

	}

}

