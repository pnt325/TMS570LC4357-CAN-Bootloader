/** @file rtp.c
*   @brief RTP Driver Implementation File
*   @date 15.December.2011
*   @version 03.00.00
*
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */

/* USER CODE BEGIN (0) */

//! \file   ~/drivers/rtp/src/32b/hercules/champion/rtp.c
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

 
