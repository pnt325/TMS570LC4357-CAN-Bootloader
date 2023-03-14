/* --COPYRIGHT--,BSD
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
/** @file I2C.h
*   @brief I2C Driver Definition File
*   @date 15.Feb.2012
*   @version 03.00.01
*   
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */

#ifndef __I2C_H__
#define __I2C_H__


#include "sys_common.h"
#include "gio.h"


/** @enum i2cMode
*   @brief Alias names for i2c modes
*   This enumeration is used to provide alias names for I2C modes:
*/

enum i2cMode
{
    I2C_FD_FORMAT   = 0x0008,  /* Free Data Format    */
    I2C_START_BYTE  = 0x0010,
    I2C_RESET_OUT   = 0x0020,  I2C_RESET_IN   = 0x0000,
    I2C_DLOOPBACK   = 0x0040,    
    I2C_REPEATMODE  = 0x0080,  /* In Master Mode only */ 
    I2C_10BIT_AMODE = 0x0100,  I2C_7BIT_AMODE = 0x0000,
    I2C_TRANSMITTER = 0x0200,  I2C_RECEIVER   = 0x0000,        
    I2C_MASTER      = 0x0400,  I2C_SLAVE      = 0x0000,     
    I2C_STOP_COND   = 0x0800,  /* In Master Mode only */
    I2C_START_COND  = 0x2000,  /* In Master Mode only */    
    I2C_FREE_RUN    = 0x4000,
    I2C_NACK_MODE   = 0x8000
};


/** @enum i2cBitCount
*   @brief Alias names for i2c bit count
*   This enumeration is used to provide alias names for I2C bit count:
*/

enum i2cBitCount
{
    I2C_2_BIT   = 0x1, 
    I2C_3_BIT   = 0x2, 
    I2C_4_BIT   = 0x3, 
    I2C_5_BIT   = 0x4, 
    I2C_6_BIT   = 0x5, 
    I2C_7_BIT   = 0x6,     
    I2C_8_BIT   = 0x7,  
    I2C_9_BIT   = 0x0  	    
};



/** @enum i2cIntFlags
*   @brief Interrupt Flag Definitions
*
*   Used with I2CEnableNotification, I2CDisableNotification
*/
enum i2cIntFlags
{
    I2C_AL_INT     = 0x0001,  /* arbitration lost      */
    I2C_NACK_INT   = 0x0002,  /* no acknowledgement    */
    I2C_ARDY_INT   = 0x0004,  /* access ready          */
    I2C_RX_INT     = 0x0008,  /* receive data ready    */
    I2C_TX_INT     = 0x0010,  /* transmit data ready   */
    I2C_SCD_INT    = 0x0020,  /* stop condition detect */
    I2C_AAS_INT    = 0x0040   /* address as slave      */
};


/** @enum i2cStatFlags
*   @brief Interrupt Status Definitions
*
*/
enum i2cStatFlags
{
    I2C_BUSBUSY    = 0x1000,  /* bus busy     */
    I2C_RXFULL     = 0x0800   /* receive full */
};


/** @enum i2cDMA
*   @brief I2C DMA definitions 
*
*   Used before i2c transfer
*/
enum i2cDMA
{
    I2C_TXDMA   = 0x20, 
    I2C_RXDMA   = 0x10 
};

/** @struct i2cBase
*   @brief I2C Base Register Definition
*
*   This structure is used to access the I2C module egisters.
*/
/** @typedef i2cBASE_t
*   @brief I2C Register Frame Type Definition
*
*   This type is used to access the I2C Registers.
*/
typedef volatile struct i2cBase
{

    uint32_t OAR;           /**<  0x0000 I2C Own Address register               */
    uint32_t IMR;           /**<  0x0004 I2C Interrupt Mask/Status register     */
    uint32_t STR;           /**<  0x0008 I2C Interrupt Status register          */
    uint32_t CLKL;          /**<  0x000C I2C Clock Divider Low register         */
    uint32_t CLKH;          /**<  0x0010 I2C Clock Divider High register        */
    uint32_t CNT;           /**<  0x0014 I2C Data Count register                */
    uint32_t DRR;           /**<  0x0018 I2C Data Receive register              */
    uint32_t SAR;           /**<  0x001C I2C Slave Address register             */
    uint32_t DXR;           /**<  0x0020 I2C Data Transmit register             */
    uint32_t MDR;           /**<  0x0024 I2C Mode register                      */
    uint32_t IVR;           /**<  0x0028 I2C Interrupt Vector register          */
    uint32_t EMDR;          /**<  0x002C I2C Extended Mode register             */
    uint32_t PSC;           /**<  0x0030 I2C Prescaler register                 */
    uint32_t PID11;         /**<  0x0034 I2C Peripheral ID register 1           */
    uint32_t PID12;         /**<  0x0038 I2C Peripheral ID register 2           */
    uint32_t DMAC;          /**<  0x003C I2C DMA Control Register               */
    uint32_t : 32U;         /**<  0x0040 Reserved                               */
    uint32_t : 32U;         /**<  0x0044 Reserved                               */
    uint32_t FUN;           /**<  0x0048 Pin Function Register                  */
    uint32_t DIR;           /**<  0x004C Pin Direction Register                 */
    uint32_t DIN;           /**<  0x0050 Pin Data In Register                   */
    uint32_t DOUT;          /**<  0x0054 Pin Data Out Register                  */
    uint32_t SET;           /**<  0x0058 Pin Data Set Register                  */
    uint32_t CLR;           /**<  0x005C Pin Data Clr Register                  */
    uint32_t ODR;           /**<  0x0060 Pin Open Drain Output Enable Register  */
    uint32_t PD;            /**<  0x0064 Pin Pullup/Pulldown Disable Register   */
    uint32_t PSL;           /**<  0x0068 Pin Pullup/Pulldown Selection Register */
} i2cBASE_t;


/** @def i2cREG1
*   @brief I2C Register Frame Pointer
*
*   This pointer is used by the I2C driver to access the I2C module registers.
*/
#define i2cREG1 ((i2cBASE_t *)0xFFF7D400U)

/* USER CODE BEGIN (0) */
/* USER CODE END */


/** @def i2cPORT
*   @brief I2C GIO Port Register Pointer
*
*   Pointer used by the GIO driver to access I/O PORT of I2C
*   (use the GIO drivers to access the port pins).
*/
#define i2cPORT1 ((gioPORT_t *)0xFFF7D44CU)

/* I2C Interface Functions */
void i2cInit(void);
void i2cSetOwnAdd(i2cBASE_t *i2c, uint32_t oadd);
void i2cSetSlaveAdd(i2cBASE_t *i2c, uint32_t sadd);
void i2cSetBaudrate(i2cBASE_t *i2c, uint32_t baud);
uint32_t  i2cIsTxReady(i2cBASE_t *i2c);
void i2cSendByte(i2cBASE_t *i2c, uint8_t byte);
void i2cSend(i2cBASE_t *i2c, uint32_t length, uint8_t *data);
uint32_t  i2cIsRxReady(i2cBASE_t *i2c);
void i2cClearSCD(i2cBASE_t *i2c);
uint32_t  i2cRxError(i2cBASE_t *i2c);
uint32_t  i2cReceiveByte(i2cBASE_t *i2c);
void i2cReceive(i2cBASE_t *i2c, uint32_t length, uint8_t *data);
void i2cEnableNotification(i2cBASE_t *i2c, uint32_t flags);
void i2cDisableNotification(i2cBASE_t *i2c, uint32_t flags);
void i2cSetStart(i2cBASE_t *i2c);
void i2cSetStop(i2cBASE_t *i2c);
void i2cSetCount(i2cBASE_t *i2c ,uint32_t cnt);


/** @fn void i2cNotification(i2cBASE_t *i2c, uint32_t flags)
*   @brief Interrupt callback
*   @param[in] i2c   - I2C module base address
*   @param[in] flags - copy of error interrupt flags
*
* This is a callback that is provided by the application and is called apon
* an interrupt.  The parameter passed to the callback is a copy of the 
* interrupt flag register.
*/
void i2cNotification(i2cBASE_t *i2c, uint32_t flags);

#endif
