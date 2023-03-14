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
/** @file i2c.c 
*   @brief I2C Driver Implementation File
*   @date 10.February.2012
*   @version 03.00.01
*
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */

/* USER CODE BEGIN (0) */
/* USER CODE END */

#include "i2c.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */

/** @struct g_I2CTransfer
*   @brief Interrupt mode globals
*
*/
struct g_i2cTransfer
{
    uint32_t  mode;
    uint32_t  length;
    uint8_t   *data;
} g_i2cTransfer[2];

/* USER CODE BEGIN (2) */
/* USER CODE END */

/** @fn void i2cInit(void)
*   @brief Initializes the i2c Driver
*
*   This function initializes the i2c module.
*/
void i2cInit(void)
{
/* USER CODE BEGIN (3) */
/* USER CODE END */
    uint32_t bit_count = I2C_2_BIT;


    /** @b intialize @b I2C */

    /** - i2c out of reset */
    i2cREG1->MDR = (1 << 5);

    /** - set i2c mode */
    i2cREG1->MDR = /* nack mode                         */   (0 << 15)                           
                   /* free running                      */ | (0 << 14)                           
                   /* start condtion - master mode only */ |  0                           
                   /* stop condtion                     */ | (1 <<11)
                   /* Master/Slave mode                 */ | (1 <<10)
                   /* Transmitter/receiver              */ | (I2C_TRANSMITTER)    
                   /* xpanded address                   */ | (I2C_7BIT_AMODE)
                   /* repeat mode                       */ | (0 << 7)
                   /* digital loopback                  */ | (0 << 6)                           
                   /* start byte - master only          */ | (0 << 4)
                   /* free data format                  */ | (0)
                   /* bit count                         */ | (bit_count);


    /** - set i2c extended mode */
    i2cREG1->EMDR = (0 << 25);

    /** - set i2c data count */
    i2cREG1->CNT = 8;

    /** - disable all interrupts */
    i2cREG1->IMR = 0x00U;    

    /** - set prescale */
    i2cREG1->PSC = 9;

    /** - set clock rate */
    i2cREG1->CLKH = 35;
    i2cREG1->CLKL = 35;

    /** - set i2c pins functional mode */
    i2cREG1->FUN = (1 );

    /** - set i2c pins default output value */
    i2cREG1->DOUT = (0 << 1) /* sda pin */
                  | (0);     /* scl pin */

    /** - set i2c pins output direction */
    i2cREG1->DIR = (0 << 1)   /* sda pin */
                 | (0);       /* scl pin */

    /** - set i2c pins open drain enable */
    i2cREG1->ODR = (0 << 1)   /* sda pin */
                 | (0);       /* scl pin */

    /** - set i2c pins pullup/pulldown enable */
    i2cREG1->PD = (0 << 1)  /* sda pin */
                | (0);      /* scl pin */

    /** - set i2c pins pullup/pulldown select */
    i2cREG1->PSL = (1 << 1)    /* sda pin */
                 | (1);        /* scl pin */

    /** - set interrupt enable */
    i2cREG1->IMR    = (0 << 6)           /* Address as slave interrupt      */
                    | (0 << 5)           /* Stop Condition detect interrupt */
                    | (0 << 4)  /* Transmit data ready interrupt   */
                    | (0 << 3)  /* Receive data ready interrupt    */
                    | (0 << 2)    /* Register Access ready interrupt */
                    | (0 << 1)    /* No Acknowledgement interrupt    */
                    | (0);          /* Arbitration Lost interrupt      */
    
    i2cREG1->MDR |= I2C_RESET_OUT; /* i2c out of reset */ 
	
	/** - inialise global transfer variables */
    g_i2cTransfer[1].mode   = 0 << 8;
    g_i2cTransfer[1].length = 0;

/* USER CODE BEGIN (4) */
/* USER CODE END */

}

/** @fn void i2cSetOwnAdd(i2cBASE_t *i2c, uint32_t oadd)
*   @brief Set I2C Own Address
*   @param[in] oadd - I2C Own address (7-bit or 10 -bit address)
*   @param[in] i2c  - i2c module base address
*   Set the Own address of the I2C module.
*/
void i2cSetOwnAdd(i2cBASE_t *i2c, uint32_t oadd)
{
    i2cREG1->OAR = oadd;  /* set own address */
}

/** @fn void i2cSetSlaveAdd(i2cBASE_t *i2c, uint32_t sadd)
*   @brief Set Port Direction
*   @param[in] sadd - I2C Slave address
*   @param[in] i2c  - i2c module base address
*   Set the Slave address to communicate which is must in Master mode.
*/
void i2cSetSlaveAdd(i2cBASE_t *i2c, uint32_t sadd)
{
    i2cREG1->SAR = sadd;  /* set slave address */
}

/** @fn void i2cSetBaudrate(i2cBASE_t *i2c, uint32_t baud)
*   @brief Change baudrate at runtime.
*   @param[in] i2c  - i2c module base address
*   @param[in] baud - baudrate in KHz
*
*   Change the i2c baudrate at runtime.
*/
void i2cSetBaudrate(i2cBASE_t *i2c, uint32_t baud)
{
    uint32_t prescale;
    uint32_t d;    
    uint32_t ck;    
    double   vclk = 80.000 * 1000000.0;

/* USER CODE BEGIN (5) */
/* USER CODE END */
    prescale = (uint32_t) ((vclk /8000000) - 1);

    if(prescale>=2)
    {
	d = 5;
    }
    else
    {
	d = prescale ? 6 : 7;
    }

    ck = ((vclk)/(2*baud*1000*(prescale+1)))-d;

    i2cREG1->PSC  = prescale;
    i2cREG1->CLKH = ck;
    i2cREG1->CLKL = ck;    

/* USER CODE BEGIN (6) */
/* USER CODE END */

}

/** @fn void i2cSetStart(i2cBASE_t *i2c)
*   @brief Set i2c start condition
*   @param[in] i2c  - i2c module base address
*   Set i2c to generate a start bit (Only in Master mode)
*/
void i2cSetStart(i2cBASE_t *i2c)
{
/* USER CODE BEGIN (7) */
/* USER CODE END */

	i2cREG1->MDR |= I2C_START_COND;  /* set start condition */

/* USER CODE BEGIN (8) */
/* USER CODE END */
}

/** @fn void i2cSetStop(i2cBASE_t *i2c)
*   @brief Set i2c stop condition
*   @param[in] i2c  - i2c module base address
*   Set i2c to generate a stop bit (Only in Master mode)
*/
void i2cSetStop(i2cBASE_t *i2c)
{
/* USER CODE BEGIN (9) */
/* USER CODE END */

	i2cREG1->MDR |= I2C_STOP_COND;  /* generate stop condition */

/* USER CODE BEGIN (10) */
/* USER CODE END */
}

/** @fn void i2cSetCount(i2cBASE_t *i2c,uint32_t cnt)
*   @brief Set i2c data count
*   @param[in] i2c  - i2c module base address
*   @param[in] cnt  - data count
*   Set i2c count to a transfer value after which the stop condition needs to be generated.
*   (Only in Master Mode)
*/
void i2cSetCount(i2cBASE_t *i2c ,uint32_t cnt)
{
/* USER CODE BEGIN (11) */
/* USER CODE END */

	i2cREG1->CNT = cnt;  /* set i2c count  */

/* USER CODE BEGIN (12) */
/* USER CODE END */
}

/** @fn uint32_t i2cIsTxReady(i2cBASE_t *i2c)
*   @brief Check if Tx buffer empty
*   @param[in] i2c - i2c module base address
*
*   @return The TX ready flag
*
*   Checks to see if the Tx buffer ready flag is set, returns
*   0 is flags not set otherwise will return the Tx flag itself.
*/
uint32_t i2cIsTxReady(i2cBASE_t *i2c)
{
/* USER CODE BEGIN (13) */
/* USER CODE END */

    return i2cREG1->STR & I2C_TX_INT;

/* USER CODE BEGIN (14) */
/* USER CODE END */
}

/** @fn void i2cSendByte(i2cBASE_t *i2c, uint8_t byte)
*   @brief Send Byte
*   @param[in] i2c  - i2c module base address
*   @param[in] byte - byte to transfer
*
*   Sends a single byte in polling mode, will wait in the
*   routine until the transmit buffer is empty before sending
*   the byte.  Use i2cIsTxReady to check for Tx buffer empty
*   before calling i2cSendByte to avoid waiting.
*/
void i2cSendByte(i2cBASE_t *i2c, uint8_t byte)
{
/* USER CODE BEGIN (15) */
/* USER CODE END */

    while ((i2cREG1->STR & I2C_TX_INT) == 0) { /* wait */ };
    i2cREG1->DXR = byte;

/* USER CODE BEGIN (16) */
/* USER CODE END */
}

/** @fn void i2cSend(i2cBASE_t *i2c, uint32_t length, uint8_t *data)
*   @brief Send Data
*   @param[in] i2c    - i2c module base address
*   @param[in] length - number of data words to transfer
*   @param[in] data   - pointer to data to send
*
*   Send a block of data pointed to by 'data' and 'length' bytes
*   long.  If interrupts have been enabled the data is sent using
*   interrupt mode, otherwise polling mode is used.  In interrupt
*   mode transmition of the first byte is started and the routine
*   returns imediatly, i2cSend must not be called again until the
*   transfer is complete, when the i2cNotification callback will
*   be called.  In polling mode, i2cSend will not return  until 
*   the transfer is complete.
*
*   @note if data word is less than 8 bits, then the data must be left
*         aligned in the data byte.
*/
void i2cSend(i2cBASE_t *i2c, uint32_t length, uint8_t *data)
{
    uint32_t index = i2c == i2cREG1 ? 0 : 1;

/* USER CODE BEGIN (17) */
/* USER CODE END */

    if ((g_i2cTransfer[index].mode & I2C_TX_INT) != 0)
    {
        /* we are in interrupt mode */
        
        g_i2cTransfer[index].length = length;
        g_i2cTransfer[index].data   = data;

        /* start transmit by sending first byte */        
        i2cREG1->DXR = *g_i2cTransfer[index].data++;
        i2cREG1->IMR = I2C_TX_INT;
    }
    else
    {
        /* send the data */
        while (length-- > 0)
        {
            while ((i2cREG1->STR & I2C_TX_INT) == 0) { /* wait */ };
            i2cREG1->DXR = *data++;
        }
    }
/* USER CODE BEGIN (18) */
/* USER CODE END */
}

/** @fn uint32_t i2cIsRxReady(i2cBASE_t *i2c)
*   @brief Check if Rx buffer full
*   @param[in] i2c - i2c module base address
*
*   @return The Rx ready flag
*
*   Checks to see if the Rx buffer full flag is set, returns
*   0 is flags not set otherwise will return the Rx flag itself.
*/
uint32_t i2cIsRxReady(i2cBASE_t *i2c)
{
/* USER CODE BEGIN (19) */
/* USER CODE END */

    return i2cREG1->STR & I2C_RX_INT;

/* USER CODE BEGIN (20) */
/* USER CODE END */
}


/** @fn uint32_t i2cRxError(i2cBASE_t *i2c)
*   @brief Return Rx Error flags
*   @param[in] i2c - i2c module base address
*
*   @return The Rx error flags
*
*   Returns the Rx framing, overun and parity errors flags,
*   also clears the error flags before returning.
*/
uint32_t i2cRxError(i2cBASE_t *i2c)
{
    uint32_t status = i2cREG1->STR & (I2C_AL_INT | I2C_NACK_INT);

/* USER CODE BEGIN (21) */
/* USER CODE END */

    i2cREG1->STR = I2C_AL_INT | I2C_NACK_INT;
	
/* USER CODE BEGIN (22) */
/* USER CODE END */
    
	return status;

}

/** @fn void i2cClearSCD(i2cBASE_t *i2c)
*   @brief Clears the Stop condition detect flags.
*   @param[in] i2c - i2c module base address
*
*   This sunction is called to clear the Stop condition detect(SCD) flag
*/
void i2cClearSCD(i2cBASE_t *i2c)
{
/* USER CODE BEGIN (23) */
/* USER CODE END */

    i2cREG1->STR = I2C_SCD_INT;
	
/* USER CODE BEGIN (24) */
/* USER CODE END */
}

/** @fn uint32_t i2cReceiveByte(i2cBASE_t *i2c)
*   @brief Receive Byte
*   @param[in] i2c - i2c module base address
*
*   @return Received byte
*
*    Recieves a single byte in polling mode.  If there is
*    not a byte in the receive buffer the routine will wait
*    until one is received.   Use i2cIsRxReady to check to
*    see if the buffer is full to avoid waiting.
*/
uint32_t i2cReceiveByte(i2cBASE_t *i2c)
{
    while ((i2cREG1->STR & I2C_RX_INT) == 0) { /* wait */ };

/* USER CODE BEGIN (25) */
/* USER CODE END */

    return i2cREG1->DRR;
}

/** @fn void i2cReceive(i2cBASE_t *i2c, uint32_t length, uint8_t *data)
*   @brief Receive Data
*   @param[in] i2c    - i2c module base address
*   @param[in] length - number of data words to transfer
*   @param[in] data   - pointer to data buffer
*
*   Receive a block of 'length' bytes long and place it into the 
*   data buffer pointed to by 'data'.  If interrupts have been 
*   enabled the data is received using interrupt mode, otherwise
*   polling mode is used.  In interrupt mode receive is setup and
*   the routine returns imediatly, i2cReceive must not be called 
*   again until the transfer is complete, when the i2cNotification 
*   callback will be called.  In polling mode, i2cReceive will not
*   return  until the transfer is complete.
*/
void i2cReceive(i2cBASE_t *i2c, uint32_t length, uint8_t *data)
{

/* USER CODE BEGIN (26) */
/* USER CODE END */
    if ((i2cREG1->IMR & I2C_RX_INT) != 0)
    {
        /* we are in interrupt mode */
        uint32_t index = i2c == i2cREG1 ? 0 : 1;
        
        /* clear error flags */
        i2cREG1->STR = I2C_AL_INT | I2C_NACK_INT;

        g_i2cTransfer[index].length = length;
        g_i2cTransfer[index].data   = data;
    }
    else
    {   
        while (length-- > 0)
        {
            while ((i2cREG1->STR & I2C_RX_INT) == 0) { /* wait */ };
            *data++ = i2cREG1->DRR;
        }
    }

/* USER CODE BEGIN (27) */
/* USER CODE END */
}

/** @fn i2cEnableNotification(i2cBASE_t *i2c, uint32_t flags)
*   @brief Enable interrupts
*   @param[in] i2c   - i2c module base address
*   @param[in] flags - Interrupts to be enabled, can be ored value of:
*                      i2c_FE_INT    - framming error,
*                      i2c_OE_INT    - overrun error,
*                      i2c_PE_INT    - parity error,
*                      i2c_RX_INT    - receive buffer ready,
*                      i2c_TX_INT    - transmit buffer ready,
*                      i2c_WAKE_INT  - wakeup,
*                      i2c_BREAK_INT - break detect
*/
void i2cEnableNotification(i2cBASE_t *i2c, uint32_t flags)
{
    uint32_t index = i2c == i2cREG1 ? 0 : 1;

/* USER CODE BEGIN (28) */
/* USER CODE END */

    g_i2cTransfer[index].mode |= (flags & I2C_TX_INT);
    i2cREG1->IMR            = (flags & ~I2C_TX_INT);
}

/** @fn i2cDisableNotification(i2cBASE_t *i2c, uint32_t flags)
*   @brief Disable interrupts
*   @param[in] i2c   - i2c module base address
*   @param[in] flags - Interrupts to be disabled, can be ored value of:
*                      i2c_FE_INT    - framming error,
*                      i2c_OE_INT    - overrun error,
*                      i2c_PE_INT    - parity error,
*                      i2c_RX_INT    - receive buffer ready,
*                      i2c_TX_INT    - transmit buffer ready,
*                      i2c_WAKE_INT  - wakeup,
*                      i2c_BREAK_INT - break detect
*/
void i2cDisableNotification(i2cBASE_t *i2c, uint32_t flags)
{
    uint32_t index = i2c == i2cREG1 ? 0 : 1;

/* USER CODE BEGIN (29) */
/* USER CODE END */

    g_i2cTransfer[index].mode &= ~(flags & I2C_TX_INT);
    i2cREG1->IMR                = (flags & ~I2C_TX_INT);
}

/** @fn void i2cInterrupt(void)
*   @brief Interrupt for I2C
*/
#pragma INTERRUPT(i2cInterrupt, IRQ)

void i2cInterrupt(void)
{
    uint32_t vec = (i2cREG1->IVR & 0x00000007);

/* USER CODE BEGIN (30) */
/* USER CODE END */

    switch (vec)
    {
    case 1:
/* USER CODE BEGIN (31) */
/* USER CODE END */
        i2cNotification(i2cREG1, I2C_AL_INT);
        break;
    case 2:
/* USER CODE BEGIN (32) */
/* USER CODE END */
        i2cNotification(i2cREG1, I2C_NACK_INT);
        break;
    case 3:
/* USER CODE BEGIN (33) */
/* USER CODE END */
        i2cNotification(i2cREG1, I2C_ARDY_INT);
        break;
    case 4:
/* USER CODE BEGIN (34) */
/* USER CODE END */
        /* receive */
        {   uint32_t byte = i2cREG1->DRR;

            if (g_i2cTransfer[0].length > 0)
            {
                *g_i2cTransfer[0].data++ = byte;
                g_i2cTransfer[0].length--;
                if (g_i2cTransfer[0].length == 0)
                {
                    i2cNotification(i2cREG1, I2C_RX_INT);
                }
            }
        }
        break;
    case 5:
/* USER CODE BEGIN (35) */
/* USER CODE END */
        /* transmit */
        if (--g_i2cTransfer[0].length > 0)
        {
            i2cREG1->DXR = *g_i2cTransfer[0].data++;
        }
        else
        {
            i2cREG1->STR = I2C_TX_INT;
            i2cNotification(i2cREG1, I2C_TX_INT);
        }
        break;


    case 6:
/* USER CODE BEGIN (36) */
/* USER CODE END */
        /* transmit */	
        i2cNotification(i2cREG1, I2C_SCD_INT);
        break;

    case 7:
/* USER CODE BEGIN (37) */
/* USER CODE END */
        i2cNotification(i2cREG1, I2C_AAS_INT);
        break;

    default:
/* USER CODE BEGIN (38) */
/* USER CODE END */
        /* phantom interrupt, clear flags and return */
        i2cREG1->STR = 0x000007FF;
        break;
    }
/* USER CODE BEGIN (39) */
/* USER CODE END */
}


