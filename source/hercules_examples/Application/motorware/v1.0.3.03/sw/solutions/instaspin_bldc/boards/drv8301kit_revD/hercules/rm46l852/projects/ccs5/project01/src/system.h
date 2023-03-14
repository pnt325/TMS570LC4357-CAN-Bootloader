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
/** @file system.h
*   @brief System Driver Header File
*   @date 15.December.2011
*   @version 03.00.00
*   
*   This file contains:
*   - Definitions
*   - Types
*   .
*   which are relevant for the System driver.
*/

/* (c) Texas Instruments 2009-2011, All rights reserved. */

#ifndef __SYS_SYSTEM_H__
#define __SYS_SYSTEM_H__

#include "sys_common.h"
#include "gio.h"


/* USER CODE BEGIN (0) */

//! \file   ~/solutions/instaspin_bldc/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src/system.h
//! \brief  Contains the public interface to the
//!         types definitions
//!
//! (C) Copyright 2012, Texas Instruments, Inc.


// **************************************************************************
// the includes

//!
//! \defgroup SYS

//!
//! \ingroup SYS
//@{


#ifdef __cplusplus
extern "C" {
#endif


// **************************************************************************
// the function prototypes

/* USER CODE END */


/* System General Definitions */

/** @enum systemInterrupt
*   @brief Alias names for clock sources
*
*   This enumeration is used to provide alias names for the clock sources:
*     - IRQ
*     - FIQ
*/
enum systemInterrupt
{
    SYS_IRQ, /**< Alias for IRQ interrupt */
    SYS_FIQ  /**< Alias for FIQ interrupt */
};

/** @enum systemClockSource
*   @brief Alias names for clock sources
*
*   This enumeration is used to provide alias names for the clock sources:
*     - Oscillator
*     - Pll1
*     - External1
*     - Low Power Oscillator Low
*     - Low Power Oscillator High
*     - PLL2
*     - External2
*     - Synchronous VCLK1
*/
enum systemClockSource
{
    SYS_OSC       		= 0,  /**< Alias for oscillator clock Source                */
    SYS_PLL1      		= 1,  /**< Alias for Pll1 clock Source                      */
    SYS_EXTERNAL1  		= 3, /**< Alias for external clock Source                  */
    SYS_LPO_LOW   		= 4,  /**< Alias for low power oscillator low clock Source  */
    SYS_LPO_HIGH  		= 5,  /**< Alias for low power oscillator high clock Source */
    SYS_PLL2    		= 6,			 /**< Alias for Pll2 clock Source                      */
    SYS_EXTERNAL2 		= 7,  /**< Alias for external 2 clock Source                */
    SYS_VCLK      		= 9   /**< Alias for synchronous VCLK1 clock Source         */
};

#define SYS_DOZE_MODE   0x000F3F02U
#define SYS_SNOOZE_MODE 0x000F3F03U
#define SYS_SLEEP_MODE  0x000FFFFFU
#define LPO_TRIM_VALUE  (((*(uint32_t   *)0xF00801B4U) & 0xFFFF0000)>>16)

/** @def OSC_FREQ
*   @brief Oscillator clock source exported from HALCoGen GUI
*
*   Oscillator clock source exported from HALCoGen GUI
*/
#define OSC_FREQ     16.0

/** @def PLL1_FREQ
*   @brief PLL 1 clock source exported from HALCoGen GUI
*
*   PLL 1 clock source exported from HALCoGen GUI
*/
#define PLL1_FREQ    160.00

/** @def LPO_LF_FREQ
*   @brief LPO Low Freq Oscillator source exported from HALCoGen GUI
*
*   LPO Low Freq Oscillator source exported from HALCoGen GUI
*/
#define LPO_LF_FREQ  0.080

/** @def LPO_HF_FREQ
*   @brief LPO High Freq Oscillator source exported from HALCoGen GUI
*
*   LPO High Freq Oscillator source exported from HALCoGen GUI
*/
#define LPO_HF_FREQ  10.000

/** @def PLL1_FREQ
*   @brief PLL 2 clock source exported from HALCoGen GUI
*
*   PLL 2 clock source exported from HALCoGen GUI
*/
#define PLL2_FREQ    160.00

/** @def GCLK_FREQ
*   @brief GCLK domain frequency exported from HALCoGen GUI
*
*   GCLK domain frequency exported from HALCoGen GUI
*/
#define GCLK_FREQ    160.000

/** @def HCLK_FREQ
*   @brief HCLK domain frequency exported from HALCoGen GUI
*
*   HCLK domain frequency exported from HALCoGen GUI
*/
#define HCLK_FREQ    160.000

/** @def RTI_FREQ
*   @brief RTI Clock frequency exported from HALCoGen GUI
*
*   RTI Clock frequency exported from HALCoGen GUI
*/
#define RTI_FREQ     80.000

/** @def AVCLK1_FREQ
*   @brief AVCLK1 Domain frequency exported from HALCoGen GUI
*
*   AVCLK Domain frequency exported from HALCoGen GUI
*/
#define AVCLK1_FREQ  80.000

/** @def AVCLK2_FREQ
*   @brief AVCLK2 Domain frequency exported from HALCoGen GUI
*
*   AVCLK2 Domain frequency exported from HALCoGen GUI
*/
#define AVCLK2_FREQ  80.000

/** @def AVCLK3_FREQ
*   @brief AVCLK3 Domain frequency exported from HALCoGen GUI
*
*   AVCLK3 Domain frequency exported from HALCoGen GUI
*/
#define AVCLK3_FREQ  80.000

/** @def VCLK1_FREQ
*   @brief VCLK1 Domain frequency exported from HALCoGen GUI
*
*   VCLK1 Domain frequency exported from HALCoGen GUI
*/
#define VCLK1_FREQ   80.000

/** @def VCLK2_FREQ
*   @brief VCLK2 Domain frequency exported from HALCoGen GUI
*
*   VCLK2 Domain frequency exported from HALCoGen GUI
*/
#define VCLK2_FREQ   80.000


/** @def SYS_PRE1
*   @brief Alias name for RTI1CLK PRE clock source
*
*   This is an alias name for the RTI1CLK pre clock source.
*   This can be either:
*     - Oscillator
*     - Pll
*     - 32 kHz Oscillator
*     - External
*     - Low Power Oscillator Low
*     - Low Power Oscillator High
*     - Flexray Pll
*/
#define SYS_PRE1 SYS_PLL1

/** @def SYS_PRE2
*   @brief Alias name for RTI2CLK pre clock source
*
*   This is an alias name for the RTI2CLK pre clock source.
*   This can be either:
*     - Oscillator
*     - Pll
*     - 32 kHz Oscillator
*     - External
*     - Low Power Oscillator Low
*     - Low Power Oscillator High
*     - Flexray Pll
*/
#define SYS_PRE2 SYS_PLL1

/* USER CODE BEGIN (1) */
/* USER CODE END */


/* System Register Frame 1 Definition */
/** @struct systemBase1
*   @brief System Register Frame 1 Definition
*
*   This type is used to access the System 1 Registers.
*/
/** @typedef systemBASE1_t
*   @brief System Register Frame 1 Type Definition
*
*   This type is used to access the System 1 Registers.
*/
typedef volatile struct systemBase1
{
    uint32_t SYSPC1;                 /* 0x0000 */
    uint32_t SYSPC2;                 /* 0x0004 */
    uint32_t SYSPC3;                 /* 0x0008 */
    uint32_t SYSPC4;                 /* 0x000C */
    uint32_t SYSPC5;                 /* 0x0010 */
    uint32_t SYSPC6;                 /* 0x0014 */
    uint32_t SYSPC7;                 /* 0x0018 */
    uint32_t SYSPC8;                 /* 0x001C */
    uint32_t SYSPC9;                 /* 0x0020 */
    uint32_t SSWPLL1;                /* 0x0024 */
    uint32_t SSWPLL2;                /* 0x0028 */
    uint32_t SSWPLL3;                /* 0x002C */
    uint32_t CSDIS;                  /* 0x0030 */
    uint32_t CSDISSET;               /* 0x0034 */
    uint32_t CSDISCLR;               /* 0x0038 */
    uint32_t CDDIS;                  /* 0x003C */
    uint32_t CDDISSET;               /* 0x0040 */
    uint32_t CDDISCLR;               /* 0x0044 */
    uint32_t GHVSRC;                 /* 0x0048 */
    uint32_t VCLKASRC;               /* 0x004C */
    uint32_t RCLKSRC;                /* 0x0050 */
    uint32_t CSVSTAT;                /* 0x0054 */
    uint32_t MSTGCR;                 /* 0x0058 */
    uint32_t MINITGCR;               /* 0x005C */
    uint32_t MSINENA;                /* 0x0060 */
    uint32_t MSTFAIL;                /* 0x0064 */
    uint32_t MSTCGSTAT;              /* 0x0068 */
    uint32_t MINISTAT;               /* 0x006C */
    uint32_t PLLCTL1;                /* 0x0070 */
    uint32_t PLLCTL2;                /* 0x0074 */
    uint32_t UERFLAG;                /* 0x0078 */
    uint32_t DIEIDL;                 /* 0x007C */
    uint32_t DIEIDH;                 /* 0x0080 */
    uint32_t VRCTL;                  /* 0x0084 */
    uint32_t LPOMONCTL;              /* 0x0088 */
    uint32_t CLKTEST;                /* 0x008C */
    uint32_t DFTCTRLREG1;            /* 0x0090 */
    uint32_t DFTCTRLREG2;            /* 0x0094 */
    uint32_t : 32U;                  /* 0x0098 */
    uint32_t : 32U;                  /* 0x009C */
    uint32_t GPREG1;                 /* 0x00A0 */
    uint32_t BTRMSEL;                /* 0x00A4 */
    uint32_t IMPFASTS;               /* 0x00A8 */
    uint32_t IMPFTADD;               /* 0x00AC */
    uint32_t SSISR1;                 /* 0x00B0 */
    uint32_t SSISR2;                 /* 0x00B4 */
    uint32_t SSISR3;                 /* 0x00B8 */
    uint32_t SSISR4;                 /* 0x00BC */
    uint32_t RAMGCR;                 /* 0x00C0 */
    uint32_t BMMCR1;                 /* 0x00C4 */
    uint32_t BMMCR2;                 /* 0x00C8 */
    uint32_t MMUGCR;                 /* 0x00CC */
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
    uint32_t        : 8U;            /* 0x00D0 */
    uint32_t PENA   : 1U;            /* 0x00D0 */
    uint32_t        : 7U;            /* 0x00D0 */
    uint32_t VCLKR  : 4U;            /* 0x00D0 */
    uint32_t        : 4U;            /* 0x00D0 */
    uint32_t VCLK2R : 4U;            /* 0x00D0 */
    uint32_t        : 4U;            /* 0x00D0 */
#else
    uint32_t        : 4U;            /* 0x00D0 */
    uint32_t VCLK2R : 4U;            /* 0x00D0 */
    uint32_t        : 4U;            /* 0x00D0 */
    uint32_t VCLKR  : 4U;            /* 0x00D0 */
    uint32_t        : 7U;            /* 0x00D0 */
    uint32_t PENA   : 1U;            /* 0x00D0 */
    uint32_t        : 8U;            /* 0x00D0 */
#endif
    uint32_t ECPCNTL;                /* 0x00D4 */
    uint32_t DSPGCR;                 /* 0x00D8 */
    uint32_t DEVCR1;                 /* 0x00DC */
    uint32_t SYSECR;                 /* 0x00E0 */
    uint32_t SYSESR;                 /* 0x00E4 */
    uint32_t ITIFLAG;                /* 0x00E8 */
    uint32_t GBLSTAT;                /* 0x00EC */
    uint32_t DEV;                    /* 0x00F0 */
    uint32_t SSIVEC;                 /* 0x00F4 */
    uint32_t SSIF;                   /* 0x00F8 */
} systemBASE1_t;


/** @def systemREG1
*   @brief System Register Frame 1 Pointer
*
*   This pointer is used by the system driver to access the system frame 1 registers.
*/
#define systemREG1 ((systemBASE1_t *)0xFFFFFF00U)

/** @def systemPORT
*   @brief ECLK GIO Port Register Pointer
*
*   Pointer used by the GIO driver to access I/O PORT of System/Eclk
*   (use the GIO drivers to access the port pins).
*/
#define systemPORT ((gioPORT_t *)0xFFFFFF04U)

/* USER CODE BEGIN (2) */
/* USER CODE END */


/* System Register Frame 2 Definition */
/** @struct systemBase2
*   @brief System Register Frame 2 Definition
*
*   This type is used to access the System 2 Registers.
*/
/** @typedef systemBASE2_t
*   @brief System Register Frame 2 Type Definition
*
*   This type is used to access the System 2 Registers.
*/
typedef volatile struct systemBase2
{
    uint32_t PLLCTL3;        /* 0x0000 */
    uint32_t : 32U;          /* 0x0004 */
    uint32_t STCCLKDIV;      /* 0x0008 */
    uint32_t : 32U;          /* 0x000C */
    uint32_t : 32U;          /* 0x0010 */
    uint32_t : 32U;          /* 0x0014 */
    uint32_t : 32U;          /* 0x0018 */
    uint32_t : 32U;          /* 0x001C */
    uint32_t : 32U;          /* 0x0020 */
    uint32_t ECPCNTRL0;      /* 0x0024 */
    uint32_t : 32U;          /* 0x0028 */
    uint32_t : 32U;          /* 0x002C */
    uint32_t : 32U;          /* 0x0030 */
    uint32_t : 32U;          /* 0x0034 */
    uint32_t : 32U;          /* 0x0038 */
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
    uint32_t VCLK3R : 4U;    /* 0x003C */
    uint32_t        : 4U;    /* 0x003C */
    uint32_t VCLK4R : 4U;    /* 0x003C */
    uint32_t        : 20U;   /* 0x003C */
#else
    uint32_t        : 20U;   /* 0x003C */
    uint32_t VCLK4R : 4U;    /* 0x003C */
    uint32_t        : 4U;    /* 0x003C */
    uint32_t VCLK3R : 4U;    /* 0x003C */
#endif	
    uint32_t VCLKACON1;      /* 0x0040 */
    uint32_t : 32U;          /* 0x0044 */
    uint32_t : 32U;          /* 0x0048*/
    uint32_t : 32U;          /* 0x004C */
    uint32_t : 32U;          /* 0x0050 */
    uint32_t : 32U;          /* 0x0054 */
    uint32_t : 32U;          /* 0x0058 */
    uint32_t : 32U;          /* 0x005C */
    uint32_t : 32U;          /* 0x0060 */
    uint32_t : 32U;          /* 0x0064 */
    uint32_t : 32U;       	  /* 0x0068 */
    uint32_t : 32U;       	  /* 0x006C */
    uint32_t  CLKSLIP;       /* 0x0070 */
    uint32_t : 32U;   	      /* 0x0074 */
    uint32_t : 32U;  		      /* 0x0078*/
    uint32_t : 32U;      	   /* 0x007C */
    uint32_t : 32U;          /* 0x0080 */
    uint32_t : 32U;          /* 0x0084 */
    uint32_t : 32U;       	  /* 0x0088 */
    uint32_t : 32U;      	   /* 0x008C */
    uint32_t : 32U;          /* 0x0090 */
    uint32_t : 32U;          /* 0x0094 */
    uint32_t : 32U;       	  /* 0x0098 */
    uint32_t : 32U;       	  /* 0x009C */
    uint32_t : 32U;          /* 0x00A0 */
    uint32_t : 32U;          /* 0x00A4 */
    uint32_t : 32U;       	  /* 0x00A8 */
    uint32_t : 32U;       	  /* 0x00AC */
    uint32_t : 32U;          /* 0x00B0 */
    uint32_t : 32U;          /* 0x00B4 */
    uint32_t : 32U;       	  /* 0x00B8 */
    uint32_t : 32U;       	  /* 0x00BC */
    uint32_t : 32U;          /* 0x00C0 */
    uint32_t : 32U;          /* 0x00C4 */
    uint32_t : 32U;       	  /* 0x00C8 */
    uint32_t : 32U;       	  /* 0x00CC */
    uint32_t : 32U;          /* 0x00D0 */
    uint32_t : 32U;          /* 0x00D4 */
    uint32_t : 32U;       	  /* 0x00D8 */
    uint32_t : 32U;       	  /* 0x00DC */
    uint32_t : 32U;          /* 0x00E0 */
    uint32_t : 32U;          /* 0x00E4 */
    uint32_t : 32U;       	  /* 0x00E8 */
    uint32_t  EFC_CTLEN;     /* 0x00EC */
    uint32_t  DIEIDL_REG0;   /* 0x00F0 */
    uint32_t  DIEIDH_REG1;   /* 0x00F4 */
    uint32_t  DIEIDL_REG2;   /* 0x00F8 */
    uint32_t  DIEIDH_REG3;   /* 0x00FC */
} systemBASE2_t;


/** @def systemREG2
*   @brief System Register Frame 2 Pointer
*
*   This pointer is used by the system driver to access the system frame 2 registers.
*/
#define systemREG2 ((systemBASE2_t *)0xFFFFE100U)

/* USER CODE BEGIN (3) */
/* USER CODE END */


/** @struct pcrBase
*   @brief Pcr Register Frame Definition
*
*   This type is used to access the Pcr Registers.
*/
/** @typedef pcrBASE_t
*   @brief PCR Register Frame Type Definition
*
*   This type is used to access the PCR Registers.
*/
typedef volatile struct pcrBase
{
    uint32_t PMPROTSET0;    /* 0x0000 */
    uint32_t PMPROTSET1;    /* 0x0004 */
    uint32_t : 32U;         /* 0x0008 */
    uint32_t : 32U;         /* 0x000C */
    uint32_t PMPROTCLR0;    /* 0x0010 */
    uint32_t PMPROTCLR1;    /* 0x0014 */
    uint32_t : 32U;         /* 0x0018 */
    uint32_t : 32U;         /* 0x001C */
    uint32_t PPROTSET0;     /* 0x0020 */
    uint32_t PPROTSET1;     /* 0x0024 */
    uint32_t PPROTSET2;     /* 0x0028 */
    uint32_t PPROTSET3;     /* 0x002C */
    uint32_t : 32U;         /* 0x0030 */
    uint32_t : 32U;         /* 0x0034 */
    uint32_t : 32U;         /* 0x0038 */
    uint32_t : 32U;         /* 0x003C */
    uint32_t PPROTCLR0;     /* 0x0040 */
    uint32_t PPROTCLR1;     /* 0x0044 */
    uint32_t PPROTCLR2;     /* 0x0048 */
    uint32_t PPROTCLR3;     /* 0x004C */
    uint32_t : 32U;         /* 0x0050 */
    uint32_t : 32U;         /* 0x0054 */
    uint32_t : 32U;         /* 0x0058 */
    uint32_t : 32U;         /* 0x005C */
    uint32_t PCSPWRDWNSET0; /* 0x0060 */
    uint32_t PCSPWRDWNSET1; /* 0x0064 */
    uint32_t : 32U;         /* 0x0068 */
    uint32_t : 32U;         /* 0x006C */
    uint32_t PCSPWRDWNCLR0; /* 0x0070 */
    uint32_t PCSPWRDWNCLR1; /* 0x0074 */
    uint32_t : 32U;         /* 0x0078 */
    uint32_t : 32U;         /* 0x007C */
    uint32_t PSPWRDWNSET0;  /* 0x0080 */
    uint32_t PSPWRDWNSET1;  /* 0x0084 */
    uint32_t PSPWRDWNSET2;  /* 0x0088 */
    uint32_t PSPWRDWNSET3;  /* 0x008C */
    uint32_t : 32U;         /* 0x0090 */
    uint32_t : 32U;         /* 0x0094 */
    uint32_t : 32U;         /* 0x0098 */
    uint32_t : 32U;         /* 0x009C */
    uint32_t PSPWRDWNCLR0;  /* 0x00A0 */
    uint32_t PSPWRDWNCLR1;  /* 0x00A4 */
    uint32_t PSPWRDWNCLR2;  /* 0x00A8 */
    uint32_t PSPWRDWNCLR3;  /* 0x00AC */
} pcrBASE_t;

/** @def pcrREG
*   @brief Pcr Register Frame Pointer
*
*   This pointer is used by the system driver to access the Pcr registers.
*/
#define pcrREG ((pcrBASE_t *)0xFFFFE000U)

/* USER CODE BEGIN (4) */
/* USER CODE END */


/* FlashW General Definitions */


/** @enum flashWPowerModes
*   @brief Alias names for flash bank power modes
*
*   This enumeration is used to provide alias names for the flash bank power modes:
*     - sleep
*     - standby
*     - active
*/
enum flashWPowerModes
{
    SYS_SLEEP   = 0U, /**< Alias for flash bank power mode sleep   */
    SYS_STANDBY = 1U, /**< Alias for flash bank power mode standby */
    SYS_ACTIVE  = 3U  /**< Alias for flash bank power mode active  */
};

/* USER CODE BEGIN (5) */
/* USER CODE END */


/** @struct flashWBase
*   @brief Flash Wrapper Register Frame Definition
*
*   This type is used to access the Flash Wrapper Registers.
*/
/** @typedef flashWBASE_t
*   @brief Flash Wrapper Register Frame Type Definition
*
*   This type is used to access the Flash Wrapper Registers.
*/
typedef volatile struct flashWBase
{
    uint32_t FRDCNTL;     /* 0x0000 */
    uint32_t FSPRD;       /* 0x0004 */
    uint32_t FEDACCTRL1;  /* 0x0008 */
    uint32_t FEDACCTRL2;  /* 0x000C */
    uint32_t FCORERRCNT;  /* 0x0010 */
    uint32_t FCORERRADD;  /* 0x0014 */
    uint32_t FCORERRPOS;  /* 0x0018 */
    uint32_t FEDACSTATUS; /* 0x001C */
    uint32_t FUNCERRADD;  /* 0x0020 */
    uint32_t FEDACSDIS;   /* 0x0024 */
    uint32_t FPRIMADDTAG; /* 0x0028 */
    uint32_t FREDUADDTAG; /* 0x002C */
    uint32_t FBPROT;      /* 0x0030 */
    uint32_t FBSE;        /* 0x0034 */
    uint32_t FBBUSY;      /* 0x0038 */
    uint32_t FBAC;        /* 0x003C */
    uint32_t FBFALLBACK;  /* 0x0040 */
    uint32_t FBPRDY;      /* 0x0044 */
    uint32_t FPAC1;       /* 0x0048 */
    uint32_t FPAC2;       /* 0x004C */
    uint32_t FMAC;        /* 0x0050 */
    uint32_t FMSTAT;      /* 0x0054 */
    uint32_t FEMUDMSW;    /* 0x0058 */
    uint32_t FEMUDLSW;    /* 0x005C */
    uint32_t FEMUECC;     /* 0x0060 */
    uint32_t FLOCK;       /* 0x0064 */
    uint32_t FEMUADDR;    /* 0x0068 */
    uint32_t FDIAGCTRL;   /* 0x006C */
    uint32_t FRAWDATAH;   /* 0x0070 */
    uint32_t FRAWDATAL;   /* 0x0074 */
    uint32_t FRAWECC;     /* 0x0078 */
    uint32_t FPAROVR;     /* 0x007C */
    uint32_t FVREADCT;    /* 0x0080 */
    uint32_t FVHVCT1;     /* 0x0084 */
    uint32_t FVHVCT2;     /* 0x0088 */
    uint32_t FVNVCT;      /* 0x008C */
    uint32_t FVPPCT;      /* 0x0090 */
    uint32_t FVWLCT;      /* 0x0094 */
    uint32_t FEFUSE;      /* 0x0098 */
    uint32_t : 32U;       /* 0x009C */
    uint32_t : 32U;       /* 0x00A0 */
    uint32_t : 32U;       /* 0x00A4 */
    uint32_t : 32U;       /* 0x00A8 */
    uint32_t : 32U;       /* 0x00AC */
    uint32_t : 32U;       /* 0x00B0 */
    uint32_t : 32U;       /* 0x00B4 */
    uint32_t : 32U;       /* 0x00B8 */
    uint32_t : 32U;       /* 0x00BC */
    uint32_t FEDACSDIS2;  /* 0x00C0 */
    uint32_t : 32U;       /* 0x00C4 */
    uint32_t : 32U;       /* 0x00C8 */
    uint32_t : 32U;       /* 0x00CC */
    uint32_t : 32U;       /* 0x00D0 */
    uint32_t : 32U;       /* 0x00D4 */
    uint32_t : 32U;       /* 0x00D8 */
    uint32_t : 32U;       /* 0x00DC */
    uint32_t : 32U;       /* 0x00E0 */
    uint32_t : 32U;       /* 0x00E4 */
    uint32_t : 32U;       /* 0x00E8 */
    uint32_t : 32U;       /* 0x00EC */
    uint32_t : 32U;       /* 0x00F0 */
    uint32_t : 32U;       /* 0x00F4 */
    uint32_t : 32U;       /* 0x00F8 */
    uint32_t : 32U;       /* 0x00FC */
    uint32_t FBSTROBES;   /* 0x0100 */
    uint32_t FPSTROBES;   /* 0x0104 */
    uint32_t FBMODE;      /* 0x0108 */
    uint32_t FTCR;        /* 0x010C */
    uint32_t FADDR;       /* 0x0110 */
    uint32_t FWRITE;      /* 0x0114 */
    uint32_t FCBITSEL;    /* 0x0118 */
    uint32_t FTCTRL;      /* 0x011C */
    uint32_t FWPWRITE0;   /* 0x0120 */
    uint32_t FWPWRITE1;   /* 0x0124 */
    uint32_t FWPWRITE2;   /* 0x0128 */
    uint32_t FWPWRITE3;   /* 0x012C */
    uint32_t FWPWRITE4;   /* 0x0130 */
} flashWBASE_t;

/** @def flashWREG
*   @brief Flash Wrapper Register Frame Pointer
*
*   This pointer is used by the system driver to access the flash wrapper registers.
*/
#define flashWREG ((flashWBASE_t *)(0xFFF87000U))

/* USER CODE BEGIN (6) */
/* USER CODE END */


/* System Interface Functions */
void systemInit(void);
void systemPowerDown(uint32_t mode);

/* USER CODE BEGIN (7) */

#ifdef __cplusplus
}
#endif /* extern "C" */

//@}  // ingroup

/* USER CODE END */

#endif
