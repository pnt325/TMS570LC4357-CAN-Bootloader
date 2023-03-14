/** @file HL_sys_main.c 
*   @brief Application main file
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com  
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
*
*/


/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "HL_sys_common.h"

/* USER CODE BEGIN (1) */
#include "uartstdio.h"
//#include <stdio.h>
#include "HL_sci.h"
#include "HL_mibspi.h"
#include "HL_sys_dma.h"
#include "HL_sys_core.h"
#include "HL_rti.h"
#include "diskio.h"

/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
int SD_Test(void);

#pragma SET_DATA_SECTION("SD_RDATA_SECTION")

/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    sciInit();

    /** - Configure GIO for LED demo Software */
//    gioInit();

    /* Initialize RTI driver */
    rtiInit();

    /* Enable RTI Compare 0 interrupt notification */
    rtiEnableNotification(rtiREG1,rtiNOTIFICATION_COMPARE0);

    _cacheDisable_();

    _enable_IRQ();


    dmaEnable();
    dmaEnableInterrupt(DMA_CH0, BTC, DMA_INTA);     //Half block transfer complete

    /** - Configure MibSPI3 for SD card application */
    mibspiInit();

    UARTprintf("\r Hercules HDK SD CARD Demo ");
    UARTprintf("\r Type \'help\' for help.");
    UARTprintf("\r\r Catalog MCU, qjwang@ti.com \r\r");

    /* Start RTI Counter Block 0 */
    rtiStartCounter(rtiREG1,rtiCOUNTER_BLOCK0);

    SD_Test();
/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
/* Note-You need to remove rtiNotification from notification.c to avoid redefinition */
void rtiNotification(rtiBASE_t *rtiREG, uint32 notification)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
    disk_timerproc();
}
/* USER CODE END */
