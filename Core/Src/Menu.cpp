/*
 * Menu.cpp
 *
 *  Created on: Nov 24, 2023
 *      Author: ihor_manukov
 */


#include <Menu.h>

extern bool g_power;
extern bool g_data;
extern bool g_menu;
extern int g_unit;

Menu::Menu(Gpio &left, Gpio &mid, Gpio &right, const char *name)
: Task(256, DefaultPriority + 2, name),
  left(left),
  mid(mid),
  right(right)
{
  // TODO Auto-generated constructor stub
}

void
Menu::run() {

  for (;;) {

	  if(mid.getState()){

	      if(mid.getState()){

	    	  if(mid.getState()){

	    		  g_power = !g_power;

	    	  }

	      }

	      else{



	      }
	  }

	  else {

		  if(left.getState() || right.getState()){

			  g_data = !g_data;

		  }

	  }

      vTaskDelay(delay);
  }

}



