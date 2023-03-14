/********************************************************************************************************
*
* main.c      : The main file for ethernet bootloader.
* Author         : QJ Wang. qjwang@ti.com
* Date           : 4-25-2021
*/
/* Copyright (C) 2013-2020 Texas Instruments Incorporated - http://www.ti.com/
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
/*---------------------------------------------------------------------------------------------------------------------
* Revision History
*---------------------------------------------------------------------------------------------------------------------
* Version          Date        Author         Description
*---------------------------------------------------------------------------------------------------------------------
* 00.10.00       25/04/2021    QJ Wang        1. Initial Version
***********************************************************************************************************/
/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "HL_sys_common.h"

/* USER CODE BEGIN (1) */
#include "HL_system.h"
#include "HL_gio.h"
#include "HL_sci.h"
#include "lwiplib.h"
#include "bl_tftp.h"
#include "bl_config.h"
#include "uartstdio.h"
#include "ustdlib.h"
#include "HL_esm.h"
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
#define ENABLE_UPDATE_CHECK
#define FORCED_UPDATE_PIN		7

//*****************************************************************************
//
// This holds the current address that is being written to during a download
// command.
//
//*****************************************************************************
uint32_t g_ulTransferAddress;
uint32_t g_pulUpdateSuccess[8] = {0x5A5A5A5A, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
uint32_t g_ulUpdateStatusAddr = APP_STATUS_ADDRESS;
uint32_t g_ulUpdateBufferSize = 32;    /*32 bytes */

void 	IntMasterIRQEnable	(void);
void 	sciDisplayText(sciBASE_t *sci, uint8_t *text,uint32_t length);
uint32_t CheckGPIOForceUpdate(void);

#if 1
extern unsigned int apiLoadStart;
extern unsigned int apiLoadSize;
extern unsigned int apiRunStart;

extern unsigned int constLoadStart;
extern unsigned int constLoadSize;
extern unsigned int constRunStart;
#endif

/* USER CODE END */

uint8_t		emacAddress[6] 	= 	{0x7C, 0xE6, 0xD3, 0x69, 0x8E, 0xD7};

//*****************************************************************************
//
// Display an lwIP type IP Address.
//
//*****************************************************************************
void
DisplayIPAddress(uint32_t ui32Addr)
{
    char pcBuf[16];

    //
    // Convert the IP Address into a string.
    //
#if defined(_TMS570LC43x_)
        usprintf(pcBuf, "%d.%d.%d.%d", (ui32Addr >> 24) & 0xff, (ui32Addr >> 16) & 0xff,
                (ui32Addr >> 8) & 0xff, (ui32Addr >> 0) & 0xff);
#endif
#if defined(_RM57Lx_)
        usprintf(pcBuf, "%d.%d.%d.%d", ui32Addr & 0xff, (ui32Addr >> 8) & 0xff,
                (ui32Addr >> 16) & 0xff, (ui32Addr >> 24) & 0xff);
#endif

    //
    // Display the string.
    //
    UARTprintf(pcBuf);
}

/* This example works for HDK*/
void main(void)
{
	/* USER CODE BEGIN (3) */
    unsigned int ipAddr;

    g_pulUpdateSuccess[1]= APP_START_ADDRESS;
    g_pulUpdateSuccess[3] = 0x20002021;  /*version number, 02.00, in 2021*/

    esmREG->SR1[0] = 0xFFFFFFFF;
    esmREG->SR1[1] = 0xFFFFFFFF;
    esmREG->SR1[2] = 0xFFFFFFFF;
    esmREG->SR4[0] = 0xFFFFFFFF;
    esmREG->EKR = 0x0A;
    esmREG->EKR = 0x00;

    /* Copy the flash APIs to SRAM*/
    memcpy(&apiRunStart, &apiLoadStart, (uint32)&apiLoadSize);

    gioInit();
	sciInit();

	sciSetBaudrate(UART, UART_BAUDRATE);

	/* Enable the interrupt generation in CPSR register */
    _enable_IRQ();

    UARTprintf("Ethernet lwIP Bootloader \n\r");

    // Check if update needed, the following condition is only for HDK
    if(0 == CheckGPIOForceUpdate() && ((*(uint32_t *) APP_STATUS_ADDRESS) == 0x5A5A5A5A))
    {
    	g_ulTransferAddress = (uint32_t)APP_START_ADDRESS;
    	((void (*)(void))g_ulTransferAddress)();
    }

    ipAddr = lwIPInit(0, emacAddress, 0, 0, 0, IPADDR_USE_DHCP);
    /* Uncomment the following if you'd like to assign a static IP address. Change address as required, and uncomment the previous statement. */
     //for TMS570LC43x. If RM57x, swap the bytes (1st/4th, 2nd/3rd)
/*
        uint8 ip_addr[4] = { 192, 168, 86, 121 };
        uint8 netmask[4] = { 255, 255, 255, 0 };
        uint8 gateway[4] = { 192, 168, 86, 137 };
        ipAddr = lwIPInit(0, emacAddress,
                *((uint32_t *)ip_addr),
                *((uint32_t *)netmask),
                *((uint32_t *)gateway),
                IPADDR_USE_STATIC);
*/
    UARTprintf("HDK IP Address: ");
    DisplayIPAddress (ipAddr);
    UARTprintf("    \n\r ");

    TFTPQSInit();

    while(1);
//    g_ulTransferAddress = (uint32_t)APP_START_ADDRESS;
//    ((void (*)(void))g_ulTransferAddress)();

    /* USER CODE END */
}


void sciDisplayText(sciBASE_t *sci, uint8_t *text,uint32_t length)
{
    while(length--)
    {
        while ((sci->FLR & 0x4) == 4);
        sciSendByte(sci,*text++);
    };
}


void IntMasterIRQEnable(void)
{
	_enable_IRQ();
	return;
}

void IntMasterIRQDisable(void)
{
	_disable_IRQ();
	return;
}

unsigned int IntMasterStatusGet(void)
{
    return (0xC0 & _get_CPSR());
}

/*
** Interrupt Handler for Core 0 Receive interrupt
*/
volatile int countEMACCore0RxIsr = 0;
#pragma INTERRUPT(EMACCore0RxIsr, IRQ)
void EMACCore0RxIsr(void)
{
	countEMACCore0RxIsr++;
	lwIPRxIntHandler(0);
}

/*
** Interrupt Handler for Core 0 Transmit interrupt
*/
volatile int countEMACCore0TxIsr = 0;
#pragma INTERRUPT(EMACCore0TxIsr, IRQ)
void EMACCore0TxIsr(void)
{
	countEMACCore0TxIsr++;
    lwIPTxIntHandler(0);
}

//*****************************************************************************
//
// Checks a GPIO for a forced update.
//
// This function checks the state of a GPIO to determine if a update is being
// requested.
//
// \return Returns a non-zero value if an update is being requested and zero
// otherwise.
//
//*****************************************************************************
#ifdef ENABLE_UPDATE_CHECK
uint32_t
CheckGPIOForceUpdate(void)
{
    /** bring GIO module out of reset */
    gioREG->GCR0      = 1;
    gioREG->ENACLR 	  = 0xFF;
    gioREG->LVLCLR    = 0xFF;

    // Set the pin as input
    gioPORTA->DIR &= ~(1 << FORCED_UPDATE_PIN);

    // Enable the pull up/down.
    gioPORTA->PULDIS &= ~(1 << FORCED_UPDATE_PIN);

    // Enable the weak pull up.
    gioPORTA->PSL |= 1 << FORCED_UPDATE_PIN;

    // Check the pin to see if an update is being requested.

    if ((gioPORTA->DIN & (0x1 << FORCED_UPDATE_PIN) ) == 0)
    {
        // Remember that this was a forced update.
        return(1);  //force to update
    }

    // No update is being requested so return 0.
    return(0);
}
#endif

/* USER CODE END */
