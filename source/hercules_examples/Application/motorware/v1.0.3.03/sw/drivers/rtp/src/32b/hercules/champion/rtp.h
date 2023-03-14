/** @file rtp.h
*   @brief RTP Driver Definition File
*   @date 15.December.2011
*   @version 03.00.00
*   
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */


#ifndef __RTP_H__
#define __RTP_H__

#include "sys_common.h"
#include "gio.h"


/* USER CODE BEGIN (0) */

//! \file   ~/drivers/rtp/src/32b/hercules/champion/rtp.h
//! \brief  Contains public interface to various functions related
//!         to the rtp peripheral
//!
//! (C) Copyright 2012, Texas Instruments, Inc.

// **************************************************************************
// the includes

// drivers


// modules


//!
//! \defgroup RTP

//!
//! \ingroup RTP
//@{


#ifdef __cplusplus
extern "C" {
#endif


// **************************************************************************
// the defines

/* USER CODE END */


/** @struct rtpBase
*   @brief RTP Base Register Definition
*
*   This structure is used to access the RTP module egisters.
*/
/** @typedef rtpBASE_t
*   @brief RTP Register Frame Type Definition
*
*   This type is used to access the RTP Registers.
*/
typedef volatile struct rtpBase
{
    uint32_t  GLBCTRL;   /**< 0x0000: RTP Global Control Register             */
    uint32_t  TRENA;     /**< 0x0004: RTP Trace Enable Register               */	
    uint32_t  GSR;       /**< 0x0008: RTP Global Status Register              */
    uint32_t  RAM1REG1;  /**< 0x000C: RTP RAM 1 Trace Region 1 Register       */
    uint32_t  RAM1REG2;  /**< 0x0010: RTP RAM 1 Trace Region 2 Register       */
    uint32_t  RAM2REG1;  /**< 0x0014: RTP RAM 2 Trace Region 1  Register      */
    uint32_t  RAM2REG2;	 /**< 0x0018: RTP RAM 2 Trace Region 2  Register      */
    uint32_t  : 32;      /**< 0x001C: Reserved																																*/
    uint32_t  : 32;      /**< 0x0020: Reserved                                */
    uint32_t  ERREG1;    /**< 0x0024: RTP Peripheral Trace Region 1 Register  */
    uint32_t  ERREG2;    /**< 0x0028: RTP Peripheral Trace Region 2 Register  */
    uint32_t  DDMW;      /**< 0x002C: RTP Direct Data Mode Write Register     */
    uint32_t  : 32;      /**< 0x0030: Reserved                                */
    uint32_t  PC0;       /**< 0x0034: RTP Pin Control 0 Register              */
    uint32_t  PC1;       /**< 0x0038: RTP Pin Control 1 Register              */
    uint32_t  PC2;       /**< 0x003C: RTP Pin Control 2 Register              */
    uint32_t  PC3;       /**< 0x0040: RTP Pin Control 3 Register              */
    uint32_t  PC4;       /**< 0x0044: RTP Pin Control 4 Register              */
    uint32_t  PC5;       /**< 0x0048: RTP Pin Control 5 Register              */
    uint32_t  PC6;       /**< 0x004C: RTP Pin Control 6 Register              */
    uint32_t  PC7;       /**< 0x0050: RTP Pin Control 7 Register              */
    uint32_t  PC8;       /**< 0x0054: RTP Pin Control 8 Register              */
} rtpBASE_t;


/** @def rtpREG
*   @brief RTP Register Frame Pointer
*
*   This pointer is used by the RTP driver to access the RTP module registers.
*/
#define rtpREG ((rtpBASE_t *)0xFFFFFA00U)

/** @def rtpPORT
*   @brief RTP Port Register Pointer
*
*   Pointer used by the GIO driver to access I/O PORT of RTP
*   (use the GIO drivers to access the port pins).
*/
#define rtpPORT ((gioPORT_t *)0xFFFFFA38U)


/* RTP Interface Functions */
void rtpInit(void);


/* USER CODE BEGIN (1) */

#ifdef __cplusplus
}
#endif // extern "C"

//@}  // ingroup

/* USER CODE END */

#endif
