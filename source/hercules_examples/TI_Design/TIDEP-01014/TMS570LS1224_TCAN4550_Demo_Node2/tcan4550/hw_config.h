/*
 *  hw_config.h
 *
 *  Created on: Dec 08, 2018 for TMS570 MCU; QJ Wang (qjwang@ti.com)
 *
 */
/*
* Copyright (C) 2009-2015 Texas Instruments Incorporated - www.ti.com
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
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/
#ifndef __TMS570_TCAN45x_H__
#define __TMS570_TCAN45x_H__

/* Device ID of TCAN45x part */
#define TCAN45x_DEVICE_ID0   0x4E414354      //correct ID: 0x4E414354
#define TCAN45x_DEVICE_ID1   0x30353534
#define TCAN45x_DEVICE_REV   0x00110200

//#define FUNCTION_SAFETY    0

/* UART port is used in debug*/
#define UART_BAUDRATE     9600
#define UART              scilinREG   /* Use scilin port to output message */

/* SPI port, chipselect used for TMS570 to communicate with TCAN4550*/
#define SPI_PORT          spiREG3    /*use SPI3 to communicate with TCAN45x device */
#define SPI_CS            2

/**/
#define CAN_nINT_PIN       GIOA0
#define CAN_GPIO2_PIN      GIOA1
#define CAN_nWRKQ_PIN      GIOA2
#define CAN_GPIO1_PIN      GIOA7
#define CAN_RST            GIOB3

#define MCAN_INT1          TCAN45_GPIO1
#define CAN_BUS_INT        TCAN45_GPIO2

/* TCAN device configuration*/
#define TCAN_CANFD_ENABLE          1
#define TCAN_AUTO_RETX_DISABLE     1  /*Disable Automatic Retransmission*/
#define TCAN_CANFD_BRSE_ENABLE     1

#define TCAN_CANFD_DataRate     2000    /* 2000KHz*/
#define TCAN_DataRate            500    /* 500KHz*/

#define TCAN_NominalBitRatePrescaler   1
#define TCAN_NominalTimeSeg1andProp   57
#define TCAN_NominalTimeSeg2          22
#define TCAN_NominalSyncJumpWidth     11

#define TCAN_DataBitRatePrescaler      1
#define TCAN_DataTimeSeg1andProp      14
#define TCAN_DataTimeSeg2              5
#define TCAN_DataSyncJumpWidth         5

/* TCAN MRAM configuration */
#define MRAM_SIDNumElements            1                  //Standard ID number of elements
#define MRAM_XIDNumElements            1                  //Extended ID number of elements
#define MRAM_Rx0NumElements            5                  //RX0 Number of elements
#define MRAM_Rx0ElementSize            MRAM_64_Byte_Data  //RX0 FIFO data payload size (Use the defines)
#define MRAM_Rx1NumElements            0                  //RX1 number of elements
#define MRAM_Rx1ElementSize            MRAM_64_Byte_Data  //RX1 FIFO data payload size (use the defines)
#define MRAM_RxBufNumElements          0                  //RX buffer number of elements
#define MRAM_RxBufElementSize          MRAM_64_Byte_Data  //RX buffer data payload size (use the defines)
#define MRAM_TxEventFIFONumElements    0                  //TX Event FIFO number of elements
#define MRAM_TxBufferNumElements       6                  //TX buffer number of elements
#define MRAM_TxBufferElementSize       MRAM_64_Byte_Data  //TX buffer data payload size (use the defines)




#endif
