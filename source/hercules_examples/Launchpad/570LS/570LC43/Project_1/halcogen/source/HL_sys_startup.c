/** @file HL_sys_startup.c 
*   @brief Startup Source File
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   This file contains:
*   - Include Files
*   - Type Definitions
*   - External Functions
*   - VIM RAM Setup
*   - Startup Routine
*   .
*   which are relevant for the Startup.
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

#include "HL_sys_common.h"
#include "HL_system.h"
#include "HL_sys_vim.h"
#include "HL_sys_core.h"
#include "HL_esm.h"
#include "HL_sys_mpu.h"
#include "HL_errata_SSWF021_45.h"

/* USER CODE BEGIN (1) */
#include "HL_reg_stc.h"
#include "HL_mibspi.h"
#include "HL_epc.h"
#include "sl_api.h"
#include "reg_bitdefn_dma.h"
#include "esm_application_callback.h"
/* USER CODE END */

/* USER CODE BEGIN (2) */
volatile uint64 crcAtInit_VIMRAM = 0;
volatile uint64 crcAtInit_FLASH = 0;
/* USER CODE END */

/* External Functions */

/*SAFETYMCUSW 218 S MR:20.2 <APPROVED> "Functions from library" */
extern void __TI_auto_init(void);
/*SAFETYMCUSW 354 S MR:NA <APPROVED> " Startup code(main should be declared by the user)" */
extern int main(void);
/*SAFETYMCUSW 122 S MR:20.11 <APPROVED> "Startup code(exit and abort need to be present)" */
/*SAFETYMCUSW 354 S MR:NA <APPROVED> " Startup code(Extern declaration present in the library)" */
extern void exit(int _status);


/* USER CODE BEGIN (3) */
void afterSTC(void);
SL_ResetReason     resetReason;        /* Reset reason */
/* USER CODE END */
void handlePLLLockFail(void);
/* Startup Routine */
void _c_int00(void);
#define PLL_RETRIES 5U
/* USER CODE BEGIN (4) */
extern uint32                ulHighHandlerLoadStart;
extern uint32                ulHighHandlerLoadEnd;
extern uint32                ulHighHandlerSize;
extern uint32                ulHighHandlerStartAddr;
extern uint32                ulHighHandlerEndAddr;
extern void _SL_HoldNClear_nError();
extern void epcCAMInit();
/* USER CODE END */

#pragma CODE_STATE(_c_int00, 32)
#pragma INTERRUPT(_c_int00, RESET)
#pragma WEAK(_c_int00)

/* SourceId : STARTUP_SourceId_001 */
/* DesignId : STARTUP_DesignId_001 */
/* Requirements : HL_CONQ_STARTUP_SR1 */
void _c_int00(void)
{
	register resetSource_t rstSrc;
/* USER CODE BEGIN (5) */
        SL_STC_Config                 stcSelfTestConfig;  /* STC Configuration */

        /* Initialize L2RAM to avoid ECC errors right after power on */
        _memInit_();

        /* Initialize Core Registers to avoid CCM Error */
        SL_Init_R5Registers();

        /* Initialize Stack Pointers */
        SL_Init_StackPointers();

        /* Enable CPU Event Export */
        /* This allows the CPU to signal any single-bit or double-bit errors detected
         * by its ECC logic for accesses to program flash or data RAM.
         */
        _coreEnableEventBusExport_();

        resetReason = SL_Init_ResetReason();

        if((RESET_TYPE_POWERON == resetReason) || (RESET_TYPE_EXTRST == resetReason))
        {
        }
    #if 0
    /* USER CODE END */

    /* Initialize Core Registers to avoid CCM Error */
    _coreInitRegisters_();
	
    /* Initialize Stack Pointers */
    _coreInitStackPointer_();

    /* Reset handler: the following instructions read from the system exception status register
     * to identify the cause of the CPU reset.
     */
	rstSrc = getResetSource();
    switch(rstSrc)
    {
        case POWERON_RESET:
		/* Initialize L2RAM to avoid ECC errors right after power on */
		_memInit_();

		/* Add condition to check whether PLL can be started successfully */
        if (_errata_SSWF021_45_both_plls(PLL_RETRIES) != 0U)
		{
			/* Put system in a safe state */
			handlePLLLockFail();
		}
		
/*SAFETYMCUSW 62 S MR:15.2, 15.5 <APPROVED> "Need to continue to handle POWERON Reset" */
        case DEBUG_RESET:
        case EXT_RESET:

/* USER CODE BEGIN (6) */
    /* USER CODE END */

        /* Initialize L2RAM to avoid ECC errors right after power on */
		if(rstSrc != POWERON_RESET)
		{
			_memInit_();
		}

/* USER CODE BEGIN (7) */
    /* USER CODE END */

/* USER CODE BEGIN (8) */
    /* USER CODE END */


/* USER CODE BEGIN (9) */
    /* USER CODE END */

        /* Enable CPU Event Export */
        /* This allows the CPU to signal any single-bit or double-bit errors detected
         * by its ECC logic for accesses to program flash or data RAM.
         */
        _coreEnableEventBusExport_();

/* USER CODE BEGIN (10) */
    /* USER CODE END */

        /* Check if there were ESM group3 errors during power-up.
         * These could occur during eFuse auto-load or during reads from flash OTP
         * during power-up. Device operation is not reliable and not recommended
         * in this case. */
        if ((esmREG->SR1[2]) != 0U)
        {
           esmGroup3Notification(esmREG,esmREG->SR1[2]);               
        }
	
        /* Initialize System - Clock, Flash settings with Efuse self check */
        systemInit();

/* USER CODE BEGIN (11) */
    /* USER CODE END */

        /* Enable IRQ offset via Vic controller */
        _coreEnableIrqVicOffset_();
            
        /* Initialize VIM table */
	    vimInit();

/* USER CODE BEGIN (12) */
    /* USER CODE END */
        /* Configure system response to error conditions signaled to the ESM group1 */
        /* This function can be configured from the ESM tab of HALCoGen */
        esmInit();

/* USER CODE BEGIN (13) */
            /* Initialize EPC */
            epcInit();
    /* USER CODE END */

        break;

        case OSC_FAILURE_RESET:
/* USER CODE BEGIN (14) */
    /* USER CODE END */
        break;
		
        case WATCHDOG_RESET:
        case WATCHDOG2_RESET:
				
/* USER CODE BEGIN (15) */
        SL_ESM_Init(ESM_ApplicationCallback);
        _enable_interrupt_();
    #if 1
        uint32 i;
        uint32 size=(uint32)&ulHighHandlerSize;
        for(i=0;i<size;i++)
        {
            ((char *)&ulHighHandlerStartAddr)[i] =((char *)&ulHighHandlerLoadStart)[i];
        }

        /* Enable DMA RAM ECC */
        BF_SET(sl_dmaREG->DMAPCR, DMA_PARCTRL_ECC_EN, DMA_PARCTRL_ECC_EN_START, DMA_PARCTRL_ECC_EN_LENGTH);
        /* Auto Initialization of DMA RAM */
        memoryInit(RAMTYPE_DMA_RAM);
        /* Enable CAN RAM SECDED */
        BF_SET(sl_canREG1->CTL, CAN_CTRL_SECDED_EN, CAN_CTRL_SECDED_START, CAN_CTRL_SECDED_LENGTH);
        /* Auto Initialization of DCAN1 RAM */
        memoryInit(RAMTYPE_DCAN1_RAM);
        /* Enable MibSPI1 RAM SECDED */
        BF_SET(sl_mibspiREG1->PAR_ECC_CTRL, SPI_PAR_CTRL_ECC_EN, SPI_PAR_CTRL_ECC_START, SPI_PAR_CTRL_ECC_LENGTH);
        /* Auto Initialization of MibSPI1 RAM */
        memoryInit(RAMTYPE_MIBSPI_RAM);
        /* enable MibSPI */
        BIT_SET(sl_mibspiREG1->GCR0, SPI_GCR0_RESET);

    #endif
    /* USER CODE END */
        break;
    
        case CPU0_RESET:
/* USER CODE BEGIN (16) */
    /* USER CODE END */

/* USER CODE BEGIN (17) */
    /* USER CODE END */
		
/* USER CODE BEGIN (18) */
    #endif
                else if((RESET_TYPE_OSC_FAILURE == resetReason) || (RESET_TYPE_WATCHDOG == resetReason))
                {

                }
    #if 0
    /* USER CODE END */

        /* Enable CPU Event Export */
        /* This allows the CPU to signal any single-bit or double-bit errors detected
         * by its ECC logic for accesses to program flash or data RAM.
         */
        _coreEnableEventBusExport_();
		
/* USER CODE BEGIN (19) */
    #endif
            else if((RESET_TYPE_CPU0 == resetReason) || (RESET_TYPE_CPU1 == resetReason))
            {
                    /* Reset caused due to CPU reset.
                    CPU reset can be caused by CPU self-test completion, or
                    by toggling the "CPU RESET" bit of the CPU Reset Control Register. */

                    /* reset could be caused by stcSelfCheck run or by an actual CPU self-test run */

                    /* check if this was an stcSelfCheck run */
    #if defined(_TMS570LS31x_) || defined(_TMS570LS12x_) || defined(_RM48x_) || defined(_RM46x_) || defined(_RM42x_) || defined(_TMS570LS04x_)
                    if ((stcREG->STCSCSCR & 0xFU) == 0xAU)
                    {
                        /* check if the self-test fail bit is set */
                        if ((stcREG->STCGSTAT & 0x3U) != 0x3U)
    #endif
    #if defined(_TMS570LC43x_) || defined(_RM57Lx_)
                    if ((stcREG1->STCSCSCR & 0xFU) == 0xAU)
                    {
                        /* check if the self-test fail bit is set */
                        if ((stcREG1->STCGSTAT & 0x3U) != 0x3U)
    #endif
                        {
                            for(;;)
                            {

                            }
                        }
                        /* STC self-check has passed */
                        else
                        {
                            /* clear self-check mode */
    #if defined(_TMS570LS31x_) || defined(_TMS570LS12x_) || defined(_RM48x_) || defined(_RM46x_) || defined(_RM42x_) || defined(_TMS570LS04x_)
                            stcREG->STCSCSCR = 0x05U;

                            /* clear STC global status flags */
                            stcREG->STCGSTAT = 0x3U;
    #endif
    #if defined(_TMS570LC43x_) || defined(_RM57Lx_)
                            stcREG1->STCSCSCR = 0x05U;

                            /* clear STC global status flags */
                            stcREG1->STCGSTAT = 0x3U;
    #endif

                            /* clear ESM group1 channel 27 status flag */
                            esmREG->SR1[0U] = 0x08000000U;

                            /* Start CPU Self-Test */
                            /*there is no alternate usercode place holder to place the safety library api so this block of code can *
                            get overwritten on helcogen code regeneration*/
                            /*********************************************************************************************************/
                            /*cpuSelfTest(STC_INTERVAL, STC_MAX_TIMEOUT, TRUE);*/
                            stcSelfTestConfig.stcClockDiv        = 0;             /* STC Clock divider = 1 */
                            stcSelfTestConfig.intervalCount      = 1;             /* One interval only */
                            stcSelfTestConfig.restartInterval0   = TRUE;         /* Start from interval 0 */
                            stcSelfTestConfig.timeoutCounter     = 0xFFFFFFFF;     /* Timeout counter*/
                            _SL_HoldNClear_nError();
    #if defined(_TMS570LS31x_) || defined(_TMS570LS12x_) || defined(_RM48x_) || defined(_RM46x_) || defined(_RM42x_) || defined(_TMS570LS04x_)
                            SL_SelfTest_STC(STC_RUN, TRUE, &stcSelfTestConfig);
    #endif
    #if defined(_TMS570LC43x_) || defined(_RM57Lx_)
                            SL_SelfTest_STC(STC1_RUN, TRUE, &stcSelfTestConfig);
    #endif
                            /*********************************************************************************************************/
                        }
                    }
                    /* CPU reset caused by CPU self-test completion */
    #if defined(_TMS570LS31x_) || defined(_TMS570LS12x_) || defined(_RM48x_) || defined(_RM46x_) || defined(_RM42x_) || defined(_TMS570LS04x_)
                    else if ((stcREG->STCGSTAT & 0x1U) == 0x1U)
                    {
                        /* Self-Test Fail flag is set */
                        if ((stcREG->STCGSTAT & 0x2U) == 0x2U)
                        {
    #endif
    #if defined(_TMS570LC43x_) || defined(_RM57Lx_)
                    else if ((stcREG1->STCGSTAT & 0x1U) == 0x1U)
                    {
                        /* Self-Test Fail flag is set */
                        if ((stcREG1->STCGSTAT & 0x2U) == 0x2U)
                        {
    #endif
                            for(;;)
                            {

                            }
                        }
                        /* CPU self-test completed successfully */
                        else
                        {
                            /* Continue start-up sequence after CPU STC completed */
                            afterSTC();
                        }
                    }
                    /* CPU reset caused by software writing to CPU RESET bit */
                    else
                    {
                        /* Add custom routine here to handle the case where software causes CPU reset */
                    }
                }
    #if 0
    /* USER CODE END */
        break;
    
        case SW_RESET:
		
/* USER CODE BEGIN (20) */
    /* USER CODE END */
        break;
    
        default:
/* USER CODE BEGIN (21) */
    /* USER CODE END */
        break;
    }

/* USER CODE BEGIN (22) */
    /* USER CODE END */

    _mpuInit_();
	
/* USER CODE BEGIN (23) */
    #endif
            else if(RESET_TYPE_SWRST == resetReason)
            {

            }
    #if 0
    /* USER CODE END */

    _cacheEnable_();

/* USER CODE BEGIN (24) */
    /* USER CODE END */


/* USER CODE BEGIN (25) */
    #endif
        else
        {

        }
        /* Check if there were ESM group3 errors during power-up.
         * These could occur during eFuse auto-load or during reads from flash OTP
         * during power-up. Device operation is not reliable and not recommended
         * in this case. */
        if ((esmREG->SR1[2]) != 0U)
        {
           esmGroup3Notification(esmREG,esmREG->SR1[2]);
        }

        if(RESET_TYPE_DEBUG != resetReason)
        {
        /* Make sure that the CPU self-test controller can actually detect a fault inside CPU */
        stcSelfTestConfig.stcClockDiv        = 0;             /* STC Clock divider = 1 */
        stcSelfTestConfig.intervalCount     = 1;             /* One interval only */
        stcSelfTestConfig.restartInterval0     = TRUE;         /* Start from interval 0 */
        stcSelfTestConfig.timeoutCounter     = 0xFFFFFFFF;     /* Timeout counter*/
        _SL_HoldNClear_nError();
    #if defined(_TMS570LS31x_) || defined(_TMS570LS12x_) || defined(_RM48x_) || defined(_RM46x_) || defined(_RM42x_) || defined(_TMS570LS04x_)
        SL_SelfTest_STC(STC_COMPARE_SELFCHECK, TRUE, &stcSelfTestConfig);
    #endif
    #if defined(_TMS570LC43x_) || defined(_RM57Lx_)
        SL_SelfTest_STC(STC1_COMPARE_SELFCHECK, TRUE, &stcSelfTestConfig);
    #endif
        }else
        {
            afterSTC();
        }
    }
    #if 0
    /* USER CODE END */

        /* initialize global variable and constructors */
    __TI_auto_init();
/* USER CODE BEGIN (26) */
    #endif
    void afterSTC(void)
    {
        /* Initialize L2RAM to avoid ECC errors right after power on
         * This function uses the system module's hardware for auto-initialization of memories and their
         * associated protection schemes. The CPU RAM is initialized by setting bit 0 of the MSIENA register.
         * Hence the value 0x1 passed to the function.
         * This function will initialize the entire CPU RAM and the corresponding ECC locations.
         */
        SL_Init_Memory(RAMTYPE_RAM);

        /* Enable IRQ offset via Vic controller */
        _coreEnableIrqVicOffset_();

        /* Initialize System - Clock, Flash settings with Efuse self check */
        systemInit();

        /* Initialize VIM table */
        vimInit();

        /* Configure system response to error conditions signaled to the ESM group1 */
        /* This function can be configured from the ESM tab of HALCoGen */
        esmInit();

        /* Initialize EPC */
        epcCAMInit();

        _mpuInit_();

        /* initialize global variable and constructors */
        __TI_auto_init();

        SL_ESM_Init(ESM_ApplicationCallback);
        _enable_interrupt_();

        uint32 i;
        uint32 size=(uint32)&ulHighHandlerSize;
        for(i=0;i<size;i++)
        {
            ((char *)&ulHighHandlerStartAddr)[i] =((char *)&ulHighHandlerLoadStart)[i];
        }

        /* call the application */
    /*SAFETYMCUSW 296 S MR:8.6 <APPROVED> "Startup code(library functions at block scope)" */
    /*SAFETYMCUSW 326 S MR:8.2 <APPROVED> "Startup code(Declaration for main in library)" */
    /*SAFETYMCUSW 60 D MR:8.8 <APPROVED> "Startup code(Declaration for main in library;Only doing an extern for the same)" */
        main();

        /*SAFETYMCUSW 122 S MR:20.11 <APPROVED> "Startup code(exit and abort need to be present)" */
            exit(0);
    }
    #if 0
    /* USER CODE END */
    
        /* call the application */
/*SAFETYMCUSW 296 S MR:8.6 <APPROVED> "Startup code(library functions at block scope)" */
/*SAFETYMCUSW 326 S MR:8.2 <APPROVED> "Startup code(Declaration for main in library)" */
/*SAFETYMCUSW 60 D MR:8.8 <APPROVED> "Startup code(Declaration for main in library;Only doing an extern for the same)" */
    main();
/* USER CODE BEGIN (27) */
    /* USER CODE END */
/*SAFETYMCUSW 122 S MR:20.11 <APPROVED> "Startup code(exit and abort need to be present)" */
    exit(0);


/* USER CODE BEGIN (28) */
    /* USER CODE END */

}

/* USER CODE BEGIN (29) */
    #endif
/* USER CODE END */

/** @fn void handlePLLLockFail(void)
*   @brief This function handles PLL lock fail.
*/
/* USER CODE BEGIN (30) */
/* USER CODE END */
void handlePLLLockFail(void)
{
/* USER CODE BEGIN (31) */
/* USER CODE END */
	while(1)
	{
		
	}
/* USER CODE BEGIN (32) */
/* USER CODE END */
}
/* USER CODE BEGIN (33) */
/* USER CODE END */
