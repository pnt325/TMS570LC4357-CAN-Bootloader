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
#include "spi.h"
#include "sys_dma.h"
#include "rti.h"
#include <stdio.h>
#include <string.h>

void loadDataPattern(uint32 psize, uint16* pptr);
void dmaConfigCtrlRxPacket(uint32 sadd, uint32 dadd, uint16 dsize, uint16 BlockSize);
void dmaConfigCtrlTxPacket(uint32 sadd, uint32 dadd, uint16 dsize, uint16 BlockSize);
unsigned int SPI_TestVerify();

/* example data Pattern configuration */
//#define SPI1_RXBUF     0xFFF7F442
//#define SPI3_TXBUF     0xFFF7F83E
#define SPI3_TX_ADDR ((uint32_t)(&(spiREG3->DAT1)) + 2)
#define SPI1_RX_ADDR ((uint32_t)(&(spiREG1->BUF)) + 2)


unsigned int BlockSize = 100;

unsigned short TX_DATA[100];
unsigned short RX_DATA[100] = {0};
unsigned int SPI3_HBCFlag = 0;
unsigned int SPI3_BTCFlag = 0;

unsigned int txrx_error;

g_dmaCTRL g_dmaCTRLPKT_TX, g_dmaCTRLPKT_RX;     /* dma control packet configuration stack */
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
uint64_t   micro_seconds = 0;
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    int i=0, data1;

    rtiInit();

    /* Enable RTI Compare 0 interrupt notification */
    rtiEnableNotification(rtiNOTIFICATION_COMPARE0);

    /* Enable IRQ - Clear I flag in CPS register */
    /* Note: This is usually done by the OS or in an svc dispatcher */
    _enable_IRQ();

    /* Start RTI Counter Block 0 */
    rtiStartCounter(rtiCOUNTER_BLOCK0);

    data1 = *(unsigned int*)(0x8000);

    do
    {
       /* - creating a data chunk in system ram to start with ... */
       loadDataPattern(BlockSize, &TX_DATA[0]);

       /* - initializing mibspi*/
       spiInit();
       spiREG3->PC0 =  0
                     | (1<<11)   //SOMI[0] as functional pin
                     | (1<<10)   //SIMO[0] as functional pin
                     | (1 << 9)  //CLK as functional pin
                     | (0);      //CS as GIO pin
       spiREG3->PC1 = 0x01;  //CS[0] as output
       spiREG3->PC3 = 0x00;  //CS[0]=0

       /* - enabling dma module */
       dmaEnable();

       /* Enable Interrupt after reception of data */
       //dmaEnableInterrupt(DMA_CH0, FTC);     //Frame transfer complete
       dmaEnableInterrupt(DMA_CH0, BTC);     //Block transfer complete
       dmaEnableInterrupt(DMA_CH0, HBC);     //Half block transfer complete

       /* - assigning dma request: channel-0 with request line - 0/15 */
       /* Request line 0: SPI1 Receive */
       /* Request line 1: SPI1 Transmit */
       /* Request line 14: SPI3 Receive */
       /* Request line 15: SPI3 Transmit */
       dmaReqAssign(DMA_CH0, 0);     //SPI1 RX
       dmaReqAssign(DMA_CH1, 15);    //SPI3 TX

       /* - configuring dma TX control packets   */
       dmaConfigCtrlTxPacket((unsigned int)&TX_DATA, SPI3_TX_ADDR, 1, BlockSize);
       dmaSetCtrlPacket(DMA_CH1, g_dmaCTRLPKT_TX);

       /* - configuring dma RX control packets   */
       /* dmaConfigCtrlRxPacket(uint32 sadd, uint32 dadd, uint32 dsize)  */
       dmaConfigCtrlRxPacket(SPI1_RX_ADDR, (unsigned int)&RX_DATA, 1, BlockSize);
       dmaSetCtrlPacket(DMA_CH0, g_dmaCTRLPKT_RX);

       /* - setting the dma channel to trigger on h/w request */
       dmaSetChEnable(DMA_CH0, DMA_HW);    //SPI1 RX, hardware triggering
       dmaSetChEnable(DMA_CH1, DMA_HW);    //SPI3 TX, hardware triggering


       //For efficient behavior during DMA operations, the transmitter empty and receive-buffer full interrupts can be disabled
       //The first TX_DMA_REQ pulse is generated when either of the following is true:
       // 1. DMAREQEN (SPIINT0[16]) is set to 1 while SPIEN (SPIGCR1[24]) is already 1.
       // 2. SPIEN (SPIGCR1[24]) is set to 1 while DMAREQEN (SPIINT0[16]) is already 1.
       spiREG1->GCR1 = (spiREG1->GCR1 & 0xFFFFFFFFU) | (0x1 << 24);  //Enable SPI
       spiREG1->INT0 = (0x1 << 16); //SPI_DMAREQ; Enable DMA REQ only after setting the SPIEN bit to 1.
       spiREG3->GCR1 = (spiREG3->GCR1 & 0xFFFFFFFFU) | (0x1 << 24);  //Enable SPI
       spiREG3->INT0 = (0x1 << 16); //SPI_DMAREQ; Enable DMA REQ only after setting the SPIEN bit to 1.

       while( SPI3_BTCFlag == 0 ){    //DMA block complete interrupt
       }

       if (SPI3_BTCFlag == 1){
           spiREG3->PC3 = 0x01;  //CS[0]=1
           txrx_error = SPI_TestVerify(); //to check if rxed data is same as the txed data
       }
       if (txrx_error == 0){
           printf("RX data = TX data ! \n");
       }else{
           printf("RX data != TX data ! \n");
       }
    }while(txrx_error > 0);  //if RX data is not equal to TX data, try again.

    /* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
void rtiNotification(uint32 notification)
{
    micro_seconds += 100;
}

void dmaGroupANotification(dmaInterrupt_t inttype, uint32 channel)
{
    if (inttype == HBC) {
        SPI3_HBCFlag = 1;
     }
    else if (inttype == BTC){
        SPI3_BTCFlag = 1;
    }
}

void dmaConfigCtrlRxPacket(uint32 sadd, uint32 dadd, uint16 ElmntCnt, uint16 FrameCnt)
{
      g_dmaCTRLPKT_RX.SADD      = sadd;               /* source address             */
      g_dmaCTRLPKT_RX.DADD      = dadd;               /* destination  address       */
      g_dmaCTRLPKT_RX.CHCTRL    = 0;                  /* channel control            */
      g_dmaCTRLPKT_RX.FRCNT     = FrameCnt;           /* frame count                */
      g_dmaCTRLPKT_RX.ELCNT     = ElmntCnt;           /* element count              */
      g_dmaCTRLPKT_RX.ELDOFFSET = 0;                  /* element destination offset */
      g_dmaCTRLPKT_RX.ELSOFFSET = 0;                  /* element destination offset */
      g_dmaCTRLPKT_RX.FRDOFFSET = 0;                  /* frame destination offset   */
      g_dmaCTRLPKT_RX.FRSOFFSET = 0;                  /* frame destination offset   */
      g_dmaCTRLPKT_RX.PORTASGN  = 4;                  /* port b                     */
      g_dmaCTRLPKT_RX.RDSIZE    = ACCESS_16_BIT;      /* read size                  */
      g_dmaCTRLPKT_RX.WRSIZE    = ACCESS_16_BIT;      /* write size                 */
      g_dmaCTRLPKT_RX.TTYPE     = FRAME_TRANSFER;     /* transfer type              */
      g_dmaCTRLPKT_RX.ADDMODERD = ADDR_FIXED;         /* address mode read          */
      g_dmaCTRLPKT_RX.ADDMODEWR = ADDR_INC1;          /* address mode write         */
      g_dmaCTRLPKT_RX.AUTOINIT  = AUTOINIT_ON;        /* autoinit                   */
}

void dmaConfigCtrlTxPacket(uint32 sadd, uint32 dadd, uint16 ElmntCnt, uint16 FrameCnt)
{
      g_dmaCTRLPKT_TX.SADD      = sadd;               /* source address             */
      g_dmaCTRLPKT_TX.DADD      = dadd;               /* destination  address       */
      g_dmaCTRLPKT_TX.CHCTRL    = 0;                  /* channel control            */
      g_dmaCTRLPKT_TX.FRCNT     = FrameCnt;           /* frame count                */
      g_dmaCTRLPKT_TX.ELCNT     = ElmntCnt;           /* element count              */
      g_dmaCTRLPKT_TX.ELDOFFSET = 0;                  /* element destination offset */
      g_dmaCTRLPKT_TX.ELSOFFSET = 0;                  /* element destination offset */
      g_dmaCTRLPKT_TX.FRDOFFSET = 0;                  /* frame destination offset   */
      g_dmaCTRLPKT_TX.FRSOFFSET = 0;                  /* frame destination offset   */
      g_dmaCTRLPKT_TX.PORTASGN  = 4;                  /* port b                     */
      g_dmaCTRLPKT_TX.RDSIZE    = ACCESS_16_BIT;      /* read size                  */
      g_dmaCTRLPKT_TX.WRSIZE    = ACCESS_16_BIT;      /* write size                 */
      g_dmaCTRLPKT_TX.TTYPE     = FRAME_TRANSFER;     /* transfer type              */
      g_dmaCTRLPKT_TX.ADDMODERD = ADDR_INC1;          /* address mode read          */
      g_dmaCTRLPKT_TX.ADDMODEWR = ADDR_FIXED;         /* address mode write         */
      g_dmaCTRLPKT_TX.AUTOINIT  = AUTOINIT_ON;        /* autoinit                   */
}

void loadDataPattern(uint32 psize, uint16* pptr)
{
    *pptr = 0x0;
    while(psize--)
    {
        // *pptr = 0x1111 + *pptr++;
         *pptr++ = psize + 0x5A00;
    }
 }

unsigned int SPI_TestVerify()
{
     register unsigned short i;
     register unsigned int error;
     register unsigned short  * dst_address;

     //Checking the received data with transmitted data
     error = 0;

     if(SPI3_HBCFlag > 0)
     {
        dst_address = RX_DATA;
        for(i=0;i<50; i++)      {
            if( *dst_address++  != TX_DATA[i])          {
                error ++;
            }
        }
     } else
     {
        dst_address = &RX_DATA[50];
        for(i=50; i<100; i++)       {
            if( *dst_address++  != TX_DATA[i])          {
                error ++;
            }
        }
     }
     return error;
}

/* USER CODE END */
