/** @file gio.c 
*   @brief GIO Driver Implementation File
*   @date 15.December.2011
*   @version 03.00.00
*
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */

/* USER CODE BEGIN (0) */

//! \file   ~/drivers/gio/src/32b/hercules/champion/gio.c
//! \brief  Contains the various functions related to the
//!         general input output (GIO) object
//!
//! (C) Copyright 2012, Texas Instruments, Inc.

// **************************************************************************
// the includes

/* USER CODE END */

#include "gio.h"

/* USER CODE BEGIN (1) */

// **************************************************************************
// the defines


// **************************************************************************
// the globals


// **************************************************************************
// the functions


/** @fn void gioNotification(void)
*   @called when a GIO interrupt occurs
*
*   This function is called when a GIO
*   interrupt occurs
*/
void gioNotification(int bit)
{
	return;
}

/* USER CODE END */

/** @fn void gioInit(void)
*   @brief Initializes the GIO Driver
*
*   This function initializes the GIO module and set the GIO ports 
*   to the inital values.
*/
void gioInit(void)
{
/* USER CODE BEGIN (2) */
/* USER CODE END */

    /** bring GIO module out of reset */
    gioREG->GCR0      = 1;
    gioREG->INTENACLR = 0xFF;
    gioREG->LVLCLR    = 0xFF;              

    /** @b initalise @b Port @b A */

    /** - Port A output values */
    gioPORTA->DOUT =  0        /* Bit 0 */
                   | (0 << 1)  /* Bit 1 */
                   | (0 << 2)  /* Bit 2 */
                   | (0 << 3)  /* Bit 3 */
                   | (0 << 4)  /* Bit 4 */
                   | (0 << 5)  /* Bit 5 */
                   | (0 << 6)  /* Bit 6 */
                   | (0 << 7); /* Bit 7 */

    /** - Port A direction */
    gioPORTA->DIR  =  0        /* Bit 0 */
                   | (0 << 1)  /* Bit 1 */
                   | (0 << 2)  /* Bit 2 */
                   | (0 << 3)  /* Bit 3 */
                   | (0 << 4)  /* Bit 4 */
                   | (0 << 5)  /* Bit 5 */
                   | (0 << 6)  /* Bit 6 */
                   | (0 << 7); /* Bit 7 */

    /** - Port A open drain enable */
    gioPORTA->PDR  =  0        /* Bit 0 */
                   | (0 << 1)  /* Bit 1 */
                   | (0 << 2)  /* Bit 2 */
                   | (0 << 3)  /* Bit 3 */
                   | (1 << 4)  /* Bit 4 */
                   | (0 << 5)  /* Bit 5 */
                   | (0 << 6)  /* Bit 6 */
                   | (0 << 7); /* Bit 7 */

    /** - Port A pullup / pulldown selection */
    gioPORTA->PSL  =  0        /* Bit 0 */
                   | (0 << 1)  /* Bit 1 */
                   | (0 << 2)  /* Bit 2 */
                   | (0 << 3)  /* Bit 3 */
                   | (1 << 4)  /* Bit 4 */
                   | (0 << 5)  /* Bit 5 */
                   | (0 << 6)  /* Bit 6 */
                   | (0 << 7); /* Bit 7 */

    /** - Port A pullup / pulldown enable*/
    gioPORTA->PULDIS  =  0        /* Bit 0 */
                      | (0 << 1)  /* Bit 1 */
                      | (0 << 2)  /* Bit 2 */
                      | (0 << 3)  /* Bit 3 */
                      | (0 << 4)  /* Bit 4 */
                      | (0 << 5)  /* Bit 5 */
                      | (0 << 6)  /* Bit 6 */
                      | (0 << 7); /* Bit 7 */

    /** @b initalise @b Port @b B */

    /** - Port B output values */
    gioPORTB->DOUT =  0        /* Bit 0 */
                   | (1 << 1)  /* Bit 1 */
                   | (0 << 2)  /* Bit 2 */
                   | (0 << 3)  /* Bit 3 */
                   | (0 << 4)  /* Bit 4 */
                   | (0 << 5)  /* Bit 5 */
                   | (0 << 6)  /* Bit 6 */
                   | (0 << 7); /* Bit 7 */

    /** - Port B direction */
    gioPORTB->DIR  =  0        /* Bit 0 */
                   | (1 << 1)  /* Bit 1 */
                   | (0 << 2)  /* Bit 2 */
                   | (0 << 3)  /* Bit 3 */
                   | (0 << 4)  /* Bit 4 */
                   | (0 << 5)  /* Bit 5 */
                   | (0 << 6)  /* Bit 6 */
                   | (0 << 7); /* Bit 7 */

    /** - Port B open drain enable */
    gioPORTB->PDR  =  0        /* Bit 0 */
                   | (0 << 1)  /* Bit 1 */
                   | (0 << 2)  /* Bit 2 */
                   | (0 << 3)  /* Bit 3 */
                   | (0 << 4)  /* Bit 4 */
                   | (0 << 5)  /* Bit 5 */
                   | (0 << 6)  /* Bit 6 */
                   | (0 << 7); /* Bit 7 */

    /** - Port B pullup / pulldown selection */
    gioPORTB->PSL  =  0        /* Bit 0 */
                   | (0 << 1)  /* Bit 1 */
                   | (1 << 2)  /* Bit 2 */
                   | (1 << 3)  /* Bit 3 */
                   | (0 << 4)  /* Bit 4 */
                   | (0 << 5)  /* Bit 5 */
                   | (0 << 6)  /* Bit 6 */
                   | (0 << 7); /* Bit 7 */

    /** - Port B pullup / pulldown enable*/
    gioPORTB->PULDIS  =  0        /* Bit 0 */
                      | (0 << 1)  /* Bit 1 */
                      | (0 << 2)  /* Bit 2 */
                      | (0 << 3)  /* Bit 3 */
                      | (0 << 4)  /* Bit 4 */
                      | (0 << 5)  /* Bit 5 */
                      | (0 << 6)  /* Bit 6 */
                      | (0 << 7); /* Bit 7 */

/* USER CODE BEGIN (3) */
/* USER CODE END */

    /** @b initalise @b interrupts */

    /** - interrupt polarity */
    gioREG->POL =  1        /* Bit 0 */
                | (0 << 1)  /* Bit 1 */
                | (0 << 2)  /* Bit 2 */
                | (0 << 3)  /* Bit 3 */
                | (0 << 4)  /* Bit 4 */
                | (1 << 5)  /* Bit 5 */
                | (0 << 6)  /* Bit 6 */
                | (0 << 7)  /* Bit 7 */

                | (0 << 8)  /* Bit 8  */
                | (0 << 9)  /* Bit 9  */
                | (1 << 10) /* Bit 10 */
                | (0 << 11) /* Bit 11 */
                | (0 << 12) /* Bit 12 */
                | (0 << 13) /* Bit 13 */
                | (0 << 14) /* Bit 14 */
                | (0 << 15);/* Bit 15 */


    /** - interrupt level */
    gioREG->LVLSET =  0        /* Bit 0 */
                   | (0 << 1)  /* Bit 1 */
                   | (0 << 2)  /* Bit 2 */
                   | (0 << 3)  /* Bit 3 */
                   | (0 << 4)  /* Bit 4 */
                   | (0 << 5)  /* Bit 5 */
                   | (0 << 6)  /* Bit 6 */
                   | (0 << 7)  /* Bit 7 */

                   | (0 << 8)  /* Bit 8  */
                   | (0 << 9)  /* Bit 9  */
                   | (0 << 10) /* Bit 10 */
                   | (0 << 11) /* Bit 11 */
                   | (0 << 12) /* Bit 12 */
                   | (0 << 13) /* Bit 13 */
                   | (0 << 14) /* Bit 14 */
                   | (0 << 15);/* Bit 15 */

    


    /** - clear all pending interrupts */
    gioREG->FLG = 0xFF;

    /** - enable interrupts */
    gioREG->INTENASET =  0        /* Bit 0 */
                      | (0 << 1)  /* Bit 1 */
                      | (0 << 2)  /* Bit 2 */
                      | (0 << 3)  /* Bit 3 */
                      | (0 << 4)  /* Bit 4 */
                      | (0 << 5)  /* Bit 5 */
                      | (0 << 6)  /* Bit 6 */
                      | (0 << 7)  /* Bit 7 */

                      | (0 << 8)  /* Bit 8  */
                      | (0 << 9)  /* Bit 9  */
                      | (0 << 10) /* Bit 10 */
                      | (0 << 11) /* Bit 11 */
                      | (0 << 12) /* Bit 12 */
                      | (0 << 13) /* Bit 13 */
                      | (0 << 14) /* Bit 14 */
                      | (0 << 15);/* Bit 15 */

/* USER CODE BEGIN (4) */
/* USER CODE END */
}


/** @fn void gioSetDirection(gioPORT_t *port, uint32_t dir)
*   @brief Set Port Direction
*   @param[in] port pointer to GIO port:
*              - gioPORTA: PortA pointer
*              - gioPORTB: PortB pointer
*   @param[in] dir value to write to DIR register
*
*   Set the direction of GIO pins at runtime.
*/
void gioSetDirection(gioPORT_t *port, uint32_t dir)
{
    port->DIR = dir;
}


/** @fn void gioSetBit(gioPORT_t *port, uint32_t bit, uint32_t value)
*   @brief Write Bit
*   @param[in] port pointer to GIO port:
*              - gioPORTA: PortA pointer
*              - gioPORTB: PortB pointer
*   @param[in] bit number 0-7 that specifies the bit to be written to.
*              - 0: LSB
*              - 7: MSB
*   @param[in] value binrary value to write to bit
*
*   Writes a value to the specified pin of the given GIO port
*/
void gioSetBit(gioPORT_t *port, uint32_t bit, uint32_t value)
{
/* USER CODE BEGIN (5) */
/* USER CODE END */

    if (value != 0)
    {
        port->DSET = 1 << bit;
    }
    else
    {
        port->DCLR = 1 << bit;
    }
}


/** @fn void gioSetPort(gioPORT_t *port, uint32_t value)
*   @brief Write Port Value
*   @param[in] port pointer to GIO port:
*              - gioPORTA: PortA pointer
*              - gioPORTB: PortB pointer
*   @param[in] value value to write to port
*
*   Writes a value to all pin of a given GIO port
*/
void gioSetPort(gioPORT_t *port, uint32_t value)
{
/* USER CODE BEGIN (6) */
/* USER CODE END */

    port->DOUT = value;

/* USER CODE BEGIN (7) */
/* USER CODE END */

}


/** @fn uint32_t gioGetBit(gioPORT_t *port, uint32_t bit)
*   @brief Read Bit
*   @param[in] port pointer to GIO port:
*              - gioPORTA: PortA pointer
*              - gioPORTB: PortB pointer
*   @param[in] bit number 0-7 that specifies the bit to be written to.
*              - 0: LSB
*              - 7: MSB
*
*   Reads a the current value from the specified pin of the given GIO port
*/
uint32_t gioGetBit(gioPORT_t *port, uint32_t bit)
{
/* USER CODE BEGIN (8) */
/* USER CODE END */

    return (port->DIN >> bit) & 1U;
}


/** @fn uint32_t gioGetPort(gioPORT_t *port)
*   @brief Read Port Value
*   @param[in] port pointer to GIO port:
*              - gioPORTA: PortA pointer
*              - gioPORTB: PortB pointer
*
*   Reads a the current value of a given GIO port
*/
uint32_t gioGetPort(gioPORT_t *port)
{
/* USER CODE BEGIN (9) */
/* USER CODE END */

    return port->DIN;
}

/** @fn void gioToggleBit(gioPORT_t *port, uint32_t bit)
*   @brief Write Bit
*   @param[in] port pointer to GIO port:
*              - gioPORTA: PortA pointer
*              - gioPORTB: PortB pointer
*   @param[in] bit number 0-7 that specifies the bit to be written to.
*              - 0: LSB
*              - 7: MSB
*
*   Toggle a value to the specified pin of the given GIO port
*/
void gioToggleBit(gioPORT_t *port, uint32_t bit)
{
/* USER CODE BEGIN (10) */
/* USER CODE END */

    if ((port->DIN & (1 << bit)) != 0)
    {
        port->DCLR = 1 << bit;
    }
    else
    {
        port->DSET = 1 << bit;
    }
}

/** @fn void gioEnableNotification(uint32_t bit)
*   @brief Enable Interrupt
*   @param[in] bit interrupt pin to enable
*              - 0: LSB
*              - 7: MSB
*
*   Enables an innterrupt pin of PortA
*/
void gioEnableNotification(uint32_t bit)
{
/* USER CODE BEGIN (11) */
/* USER CODE END */

    gioREG->INTENASET = 1 << bit;
}


/** @fn void gioDisableNotification(uint32_t bit)
*   @brief Disable Interrupt
*   @param[in] bit interrupt pin to enable
*              - 0: LSB
*              - 7: MSB
*
*   Disables an innterrupt pin of PortA
*/
void gioDisableNotification(uint32_t bit)
{
/* USER CODE BEGIN (12) */
/* USER CODE END */

    gioREG->INTENACLR = 1 << bit;
}


/** @fn void gioHighLevelInterrupt(void)
*   @brief GIO Interrupt Handler
*
*   High Level Interrupt handler for GIO pin interrupt 
*
*/
#pragma INTERRUPT(gioHighLevelInterrupt, IRQ)

void gioHighLevelInterrupt(void)
{
    int offset = gioREG->OFFSET0 - 1U;

/* USER CODE BEGIN (13) */
/* USER CODE END */

    if (offset >= 0)
    {
        gioNotification(offset);
    }

/* USER CODE BEGIN (14) */
/* USER CODE END */

}


/** @fn void gioLowLevelInterrupt(void)
*   @brief GIO Interrupt Handler
*
*   Low Level Interrupt handler for GIO pin interrupt 
*
*/
#pragma INTERRUPT(gioLowLevelInterrupt, IRQ)

void gioLowLevelInterrupt(void)
{
    int offset = gioREG->OFFSET1 - 1U;

/* USER CODE BEGIN (15) */
/* USER CODE END */

    if (offset >= 0)
    {
        gioNotification(offset);
    }

/* USER CODE BEGIN (16) */

// end of file

/* USER CODE END */

}



