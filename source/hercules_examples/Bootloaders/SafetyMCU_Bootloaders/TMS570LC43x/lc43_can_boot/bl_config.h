/*****************************************************************************
*
* bl_config.h - The configurable parameters of the boot loader.
* Author    : QJ Wang. qjwang@ti.com
* Date      : 5-25-2019
*/
/* Copyright (C) 2013-2019 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#ifndef __BL_CONFIG_H__
#define __BL_CONFIG_H__

//*****************************************************************************
//
// The following defines are used to configure the operation of the boot
// loader.  For each define, its interactions with other defines are described.
// First is the dependencies (in other words, the defines that must also be
// defined if it is defined), next are the exclusives (in other words, the
// defines that can not be defined if it is defined), and finally are the
// requirements (in other words, the defines that must be defined if it is
// defined).
//
// The following defines must be defined in order for the boot loader to
// operate:
//
//     One of CAN_ENABLE_UPDATE, SPI_ENABLE_UPDATE, SCI_ENABLE_UPDATE
//     APP_START_ADDRESS
//
//*****************************************************************************

//*****************************************************************************
//
// The frequency (MHz) of the crystal used to clock the microcontroller.
//
// This defines the crystal frequency used by the microcontroller running the
// boot loader.
//
// Depends on: None
// Exclusive of: None
// Requires: None
//
//*****************************************************************************
//#define TMS570LC43
//#define RM57
//#define TMS570LS31
//#define RM48
//#define TMS570LS12
//#define RM46
//#define TMS570LS07
//#define RM44
//#define TMS570LS04
//#define RM42

#define   TMS570LC43

/* 150MHz is used in this example. If you like to use different speed, please change the PLL configuration in HALCoGen*/
#define SYS_CLK_FREQ            150            //MHz, HCLK

//*****************************************************************************
// Selects the UART as the port for communicating with the boot loader.
// Exclusive of: CAN_ENABLE_UPDATE, SPI_ENABLE_UPDATE,
// Requires: UART_FIXED_BAUDRATE, BUFFER_SIZE
//*****************************************************************************
//#define UART_ENABLE_UPDATE
//#define SPI_ENABLE_UPDATE
#define CAN_ENABLE_UPDATE

//*****************************************************************************
// The starting address of the application.  This must be a multiple of 32K(sector size)
// bytes (making it aligned to a page boundary), and can not be 0 (the first sector is 
// boot loader). 
//
// The flash image of the boot loader must not be larger than this value.
//*****************************************************************************
#define APP_START_ADDRESS       0x00010020

//*****************************************************************************
// The address to store the update status of the application image
// It contains Application Start Address, Application Image Size, etc
//
//*****************************************************************************
#define APP_STATUS_ADDRESS       0x00010000   /* This is must the starting address of one of flash sectors */

/* UART is used in all the boot modes*/
//#if defined (UART_ENABLE_UPDATE)
#define UART_BAUDRATE     115200
#define UART              sciREG1   /* Use UART port 1 for UART boot */
//#endif

#if defined (SPI_ENABLE_UPDATE)
#define SPI_PORT              spiREG2    /*use SPI2 for SPI boot*/
#endif

#if defined (CAN_ENABLE_UPDATE)
/* CAN1 is use in CAN bootloader example code. The baudrate is 500kbps, if you want to use other baudrate,
 * please configure it using HALCoGen.
 *
 * CAN Port used: DCAN1. Please configure MSG for RX, and LSG 2 for TX
 * Baudrate used: 500 kbps.
 * */
#define CAN_PORT                 canREG1
#endif

#define BUFFER_SIZE             64       /*words in the data buffer used for receiving packets*/

//*****************************************************************************
// Enables the pin-based forced update check.  When enabled, the boot loader
// will go into update mode instead of calling the application if a pin is read
// at a particular polarity, forcing an update operation.  In either case, the
// application is still able to return control to the boot loader in order to
// start an update. 
//
// Requires: FORCED_UPDATE_PERIPH, FORCED_UPDATE_PORT, FORCED_UPDATE_PIN,
//           FORCED_UPDATE_POLARITY
//*****************************************************************************
#define ENABLE_UPDATE_CHECK

#if defined (ENABLE_UPDATE_CHECK)
//*****************************************************************************
//
// The GPIO port to check for a forced update.  This will be one of the
// GPIO_PORTx_BASE values, where "x" is replaced with the port name (A or B).
// Depends on: ENABLE_UPDATE_CHECK
//*****************************************************************************
#define FORCED_UPDATE_PORT      GPIO_PORTA_BASE

//*****************************************************************************
// The pin to check for a forced update.  This is a value between 0 and 7.
//
// Depends on: ENABLE_UPDATE_CHECK
//*****************************************************************************
#define FORCED_UPDATE_PIN       7

#endif

//#define   DEBUG_MSG_L3
#endif // __BL_CONFIG_H__
