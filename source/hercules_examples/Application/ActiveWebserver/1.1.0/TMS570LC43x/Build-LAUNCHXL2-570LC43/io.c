//*****************************************************************************
//
// io.c - I/O routines for the example application.
//
// Copyright (c) 2013-2014 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.1.0.12573 of the EK-TM4C1294XL Firmware Package.
//
//*****************************************************************************
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "HL_gio.h"
#include "HL_rti.h"
#include "io.h"

//*****************************************************************************
//
// The current speed of the on-screen animation expressed as a percentage.
//
//*****************************************************************************
volatile unsigned long g_ulAnimSpeed = 10;
unsigned long rtiCOMPARE2_PER;

//*****************************************************************************
//
// Set the timer used to pace the animation.  We scale the timer timeout such
// that a speed of 100% causes the timer to tick once every 20 mS (50Hz).
//
//*****************************************************************************
static void
io_set_timer(unsigned long ulSpeedPercent)
{
    unsigned long ulTimeout;


    //
    // If the speed is non-zero, we reset the timeout.  If it is zero, we
    // just leave the timer disabled.
    //
    if(ulSpeedPercent)
    {
        //
        // Set Timeout
        //
        ulTimeout = (rtiCOMPARE2_PER * 100 ) / ulSpeedPercent;
        rtiSetPeriod(rtiREG1,rtiCOMPARE2,ulTimeout);
    }
}

//*****************************************************************************
//
// Initialize the IO used in this demo
//
//*****************************************************************************
void
io_init(void)
{


    //
    // Initialize LED to OFF (0)
    //
	gioSetBit(LED_PORT_BASE, LED_PIN, 0);

    //
    // Initialize animation LED to OFF (0)
    //
	gioSetBit(LED_ANIM_PORT_BASE, LED_ANIM_PIN, 0);
    //
    // Set the timer for the current animation speed.  This enables the
    // timer as a side effect.
    //
    rtiCOMPARE2_PER = rtiGetPeriod(rtiREG1,rtiCOMPARE2);
    io_set_timer(g_ulAnimSpeed);

}

//*****************************************************************************
//
// Set the status LED on or off.
//
//*****************************************************************************
void
io_set_led(bool bOn)
{
    //
    // Turn the LED on or off as requested.
    //
	gioSetBit(LED_PORT_BASE, LED_PIN, bOn ? LED_PIN : 0);
}

//*****************************************************************************
//
// Return LED state
//
//*****************************************************************************
void
io_get_ledstate(char * pcBuf, int iBufLen)
{
    //
    // Get the state of the LED
    //
    if(gioGetBit(LED_PORT_BASE,LED_PIN))
    {
        snprintf(pcBuf, iBufLen, "ON");
    }
    else
    {
        snprintf(pcBuf, iBufLen, "OFF");
    }

}

//*****************************************************************************
//
// Return LED state as an integer, 1 on, 0 off.
//
//*****************************************************************************
int
io_is_led_on(void)
{
    //
    // Get the state of the LED
    //
    if(gioGetBit(LED_PORT_BASE, LED_PIN))
    {
        return(true);
    }
    else
    {
        return(0);
    }
}

//*****************************************************************************
//
// Set the speed of the animation shown on the display.  In this version, the
// speed is described as a decimal number encoded as an ASCII string.
//
//*****************************************************************************
void
io_set_animation_speed_string(char *pcBuf)
{
    unsigned long ulSpeed;

    //
    // Parse the passed parameter as a decimal number.
    //
    ulSpeed = 0;
    while((*pcBuf >= '0') && (*pcBuf <= '9'))
    {
        ulSpeed *= 10;
        ulSpeed += (*pcBuf - '0');
        pcBuf++;
    }

    //
    // If the number is valid, set the new speed.
    //
    if(ulSpeed <= 100)
    {
        g_ulAnimSpeed = ulSpeed;
        io_set_timer(g_ulAnimSpeed);
    }
}

//*****************************************************************************
//
// Set the speed of the animation shown on the display.
//
//*****************************************************************************
void
io_set_animation_speed(unsigned long ulSpeed)
{
    //
    // If the number is valid, set the new speed.
    //
    if(ulSpeed <= 100)
    {
        g_ulAnimSpeed = ulSpeed;
        io_set_timer(g_ulAnimSpeed);
    }
}

//*****************************************************************************
//
// Get the current animation speed as an ASCII string.
//
//*****************************************************************************
void
io_get_animation_speed_string(char *pcBuf, int iBufLen)
{
    snprintf(pcBuf, iBufLen, "%d%%", g_ulAnimSpeed);
}

//*****************************************************************************
//
// Get the current animation speed as a number.
//
//*****************************************************************************
unsigned long
io_get_animation_speed(void)
{
    return(g_ulAnimSpeed);
}
