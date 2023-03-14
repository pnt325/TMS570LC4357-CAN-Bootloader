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
/** @file rtp.c
*   @brief RTP Driver Implementation File
*   @date 15.December.2011
*   @version 03.00.00
*
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */

/* USER CODE BEGIN (0) */

//! \file   ~/drivers/rtp/src/32b/hercules/tms570ls3137/rtp.c
//! \brief  Contains the various functions related to the
//!         rtp peripheral
//!
//! (C) Copyright 2012, Texas Instruments, Inc.

// **************************************************************************
// the includes

/* USER CODE END */

#include "rtp.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */

/** @fn void rtpInit(void)
*   @brief Initializes the RTP Driver
*
*   This function initializes the RTP module.
*/
void rtpInit(void)
{

/* USER CODE BEGIN (2) */
/* USER CODE END */

    /** @b intalise @b RTP */

    /** @b initalise @b RTP @b Port */

    /** - RTP Port output values */
    rtpREG->PC3 =  0           /* DATA[0] */
                | (0 << 1)     /* DATA[1] */
                | (0 << 2)     /* DATA[2] */
                | (0 << 3)     /* DATA[3] */
                | (0 << 4)     /* DATA[4] */
                | (0 << 5)     /* DATA[5] */
                | (0 << 6)     /* DATA[6] */
                | (0 << 7)     /* DATA[7] */
                | (0 << 8)     /* DATA[8] */
                | (0 << 9)     /* DATA[9] */
                | (0 << 10)    /* DATA[10] */
                | (0 << 11)    /* DATA[11] */
                | (0 << 12)    /* DATA[12] */
                | (0 << 13)    /* DATA[13] */
                | (0 << 14)    /* DATA[14] */
                | (0 << 15)    /* DATA[15] */
                | (0 << 16)    /* RTP SYNC */
                | (0 << 17)    /* RTP CLK */
                | (0 << 18);   /* RTP ENA */

    /** - RTP Port direction */
    rtpREG->PC1 =  1           /* DATA[0] */
                | (1 << 1)     /* DATA[1] */
                | (1 << 2)     /* DATA[2] */
                | (1 << 3)     /* DATA[3] */
                | (0 << 4)     /* DATA[4] */
                | (1 << 5)     /* DATA[5] */
                | (1 << 6)     /* DATA[6] */
                | (0 << 7)     /* DATA[7] */
                | (0 << 8)     /* DATA[8] */
                | (1 << 9)     /* DATA[9] */
                | (1 << 10)    /* DATA[10] */
                | (0 << 11)    /* DATA[11] */
                | (0 << 12)    /* DATA[12] */
                | (1 << 13)    /* DATA[13] */
                | (1 << 14)    /* DATA[14] */
                | (0 << 15)    /* DATA[15] */
                | (0 << 16)    /* RTP SYNC */
                | (1 << 17)    /* RTP CLK */
                | (1 << 18);   /* RTP ENA */

    /** - RTP Port open drain enable */
    rtpREG->PC6 =  0           /* DATA[0] */
                | (0 << 1)     /* DATA[1] */
                | (0 << 2)     /* DATA[2] */
                | (0 << 3)     /* DATA[3] */
                | (0 << 4)     /* DATA[4] */
                | (0 << 5)     /* DATA[5] */
                | (0 << 6)     /* DATA[6] */
                | (0 << 7)     /* DATA[7] */
                | (0 << 8)     /* DATA[8] */
                | (0 << 9)     /* DATA[9] */
                | (0 << 10)    /* DATA[10] */
                | (0 << 11)    /* DATA[11] */
                | (0 << 12)    /* DATA[12] */
                | (0 << 13)    /* DATA[13] */
                | (0 << 14)    /* DATA[14] */
                | (0 << 15)    /* DATA[15] */
                | (0 << 16)    /* RTP SYNC */
                | (0 << 17)    /* RTP CLK */
                | (0 << 18);   /* RTP ENA */


    /** - RTP Port pullup / pulldown selection */
    rtpREG->PC8 =  1           /* DATA[0] */
                | (1 << 1)     /* DATA[1] */
                | (1 << 2)     /* DATA[2] */
                | (1 << 3)     /* DATA[3] */
                | (1 << 4)     /* DATA[4] */
                | (1 << 5)     /* DATA[5] */
                | (1 << 6)     /* DATA[6] */
                | (1 << 7)     /* DATA[7] */
                | (1 << 8)     /* DATA[8] */
                | (1 << 9)     /* DATA[9] */
                | (1 << 10)    /* DATA[10] */
                | (1 << 11)    /* DATA[11] */
                | (1 << 12)    /* DATA[12] */
                | (1 << 13)    /* DATA[13] */
                | (1 << 14)    /* DATA[14] */
                | (1 << 15)    /* DATA[15] */
                | (1 << 16)    /* RTP SYNC */
                | (1 << 17)    /* RTP CLK */
                | (1 << 18);   /* RTP ENA */


    /** - RTP Port pullup / pulldown enable*/
    rtpREG->PC7 =  0           /* DATA[0] */
                | (0 << 1)     /* DATA[1] */
                | (0 << 2)     /* DATA[2] */
                | (0 << 3)     /* DATA[3] */
                | (0 << 4)     /* DATA[4] */
                | (0 << 5)     /* DATA[5] */
                | (0 << 6)     /* DATA[6] */
                | (0 << 7)     /* DATA[7] */
                | (0 << 8)     /* DATA[8] */
                | (0 << 9)     /* DATA[9] */
                | (0 << 10)    /* DATA[10] */
                | (0 << 11)    /* DATA[11] */
                | (0 << 12)    /* DATA[12] */
                | (0 << 13)    /* DATA[13] */
                | (0 << 14)    /* DATA[14] */
                | (0 << 15)    /* DATA[15] */
                | (0 << 16)    /* RTP SYNC */
                | (0 << 17)    /* RTP CLK */
                | (0 << 18);   /* RTP ENA */

    /* RTP set all pins to functional */
    rtpREG->PC0 =  1           /* DATA[0] */
                | (1 << 1)     /* DATA[1] */
                | (1 << 2)     /* DATA[2] */
                | (1 << 3)     /* DATA[3] */
                | (1 << 4)     /* DATA[4] */
                | (1 << 5)     /* DATA[5] */
                | (1 << 6)     /* DATA[6] */
                | (1 << 7)     /* DATA[7] */
                | (1 << 8)     /* DATA[8] */
                | (1 << 9)     /* DATA[9] */
                | (1 << 10)    /* DATA[10] */
                | (1 << 11)    /* DATA[11] */
                | (1 << 12)    /* DATA[12] */
                | (1 << 13)    /* DATA[13] */
                | (1 << 14)    /* DATA[14] */
                | (1 << 15)    /* DATA[15] */
                | (1 << 16)    /* RTP SYNC */
                | (1 << 17)    /* RTP CLK */
                | (1 << 18);   /* RTP ENA */

/* USER CODE BEGIN (3) */

// end of file

/* USER CODE END */

}

 
