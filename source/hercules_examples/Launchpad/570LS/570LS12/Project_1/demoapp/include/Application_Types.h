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
#include "gio.h"

typedef enum _button_EVENT
{
	NONE,
	SHORT_PRESS
}button;
#define USER1_BUTTON_GPIOPORT     MibSPI3CS0      //S3
#define USER1_BUTTON_GPIOPIN      2
#define USER2_BUTTON_GPIOPORT     hetPORT1       //S4
#define USER2_BUTTON_GPIOPIN      15
#define LED2_GPIOPORT             gioPORTB       //LED 2 or LED A
#define LED2_GPIOPIN              1
#define LED3_GPIOPORT             gioPORTB       //LED 3 or LED B
#define LED3_GPIOPIN              2

#endif /* APPLICATION_TYPES_H_ */
