/** @file sys_main.c 
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

#include "sys_common.h"

/* USER CODE BEGIN (1) */
#include "can.h"
#include "esm.h"
#include "sys_core.h"


#define D_COUNT  8

uint32 cnt=0, error =0;
uint8 tx_data[D_COUNT][8] = {0};
uint8 rx_data[D_COUNT][8] = {0};
uint8 *tx_ptr = &tx_data[0][0];
uint8 *rx_ptr = &rx_data[0][0];
uint8 *dptr=0;

void dumpSomeData();

/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
uint32 checkPackets(uint8 *src_packet,uint8 *dst_packet,uint32 psize);
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */

    /** - writing a random data in RAM - to transmit */
    dumpSomeData();

    /** - configuring CAN1 MB1,Msg ID-1 to transmit and CAN2 MB1 to receive */
    /*CAN1 transmits 2 remote frames from msgbox1 (ID=0x123) and msgbox2(ID=0x985). The remote object is RX.*/
    /*CAN2 msg box1 and msg2 receive the remote frames and transmit the requested data. The request data object is TX*/
    canInit();

    /*Write data to CAN2 message object 1 which contains the requested data for remote frame 1*/
    canFillMessageObjectData(canREG2, canMESSAGE_BOX1, tx_ptr);
    /*Transmit the CAN1 remote frame which requests a data frame from other CAN nodes */
    canSendRemoteFrame(canREG1, canMESSAGE_BOX1);
    while(!canIsRxMessageArrived(canREG1, canMESSAGE_BOX1));
    /*Read the received the requested data*/
    canGetData(canREG1, canMESSAGE_BOX1, rx_ptr); /* copy to RAM */
    /*Check if the RXed data os correct */
    for(cnt=0; cnt < 8; cnt++)
     {
          if(*tx_ptr++ != *rx_ptr++)
          {
               error++; /* data error */
          }
     }

    /*Write data to CAN2 message object 2 which contains the requested data for remote frame 2*/
    canFillMessageObjectData(canREG2, canMESSAGE_BOX2, tx_ptr);
    /*Transmit the CAN1 remote frame which requests a data frame from other CAN nodes */
    canSendRemoteFrame(canREG1, canMESSAGE_BOX2);
    while(!canIsRxMessageArrived(canREG1, canMESSAGE_BOX2));
    /*Read the received the requested data*/
    canGetData(canREG1, canMESSAGE_BOX2, rx_ptr); /* copy to RAM */
    /*Check if the RXed data os correct */
    for(cnt=0; cnt < 8; cnt++)
     {
          if(*tx_ptr++ != *rx_ptr++)
          {
               error++; /* data error */
          }
     }

    /* transmit a data frame on can1 */
    canTransmit(canREG1, canMESSAGE_BOX3, tx_ptr);
    /*... wait until message receive on can2 */
    while(!canIsRxMessageArrived(canREG2, canMESSAGE_BOX3));
    canGetData(canREG2, canMESSAGE_BOX3, rx_ptr);  /* receive on can2  */
    /* check received data patterns */
    error = checkPackets(tx_ptr, rx_ptr, 8);

    while(1); /* wait forever after tx-rx complete. */

/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */

/* writing some data to ram  */
void dumpSomeData()
{
     uint32 tmp = 0x11;

     cnt = (D_COUNT*8)-1;
     dptr = &tx_data[0][0];
     *dptr = tmp;

     while(cnt--)
     {
        tmp = *dptr++;
        *dptr = tmp + 0x11;
     }
}

uint32 checkPackets(uint8 *src_packet,uint8 *dst_packet,uint32 psize)
{
   uint32 err=0;
   uint32 cnt=psize;

   while(cnt--)
   {
     if((*src_packet++) != (*dst_packet++))
     {
        err++;           /*  data error  */
     }
   }
   return (err);
}
/* USER CODE END */
