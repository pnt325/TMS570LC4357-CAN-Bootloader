/*
 * Application_Types.h
 *
 *  Created on: Dec 26, 2013
 *      Author: a0131910
 */

#ifndef APPLICATION_TYPES_H_
#define APPLICATION_TYPES_H_

/***************************************************************
* INCLUDE FILES
****************************************************************/
#include "HL_gio.h"

typedef enum _button_EVENT
{
	NONE,
	SHORT_PRESS
}button;
#define USER1_BUTTON_GPIOPORT     gioPORTB
#define USER1_BUTTON_GPIOPIN      4
#define USER2_BUTTON_GPIOPORT     gioPORTB
#define USER2_BUTTON_GPIOPIN      5
#define LED1_GPIOPORT             gioPORTB
#define LED1_GPIOPIN              6
#define LED2_GPIOPORT             gioPORTB
#define LED2_GPIOPIN              7

#endif /* APPLICATION_TYPES_H_ */
