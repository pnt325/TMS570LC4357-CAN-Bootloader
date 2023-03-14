/** @file HL_sys_selftest.c 
*   @brief Selftest Source File
*   @date 04.Oct.2013
*   @version 03.07.00
*
*   This file contains:
*   - Selftest API's
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

/* USER CODE BEGIN (0) */
/* USER CODE END */

#include "HL_sys_selftest.h"
#include "HL_sys_core.h"


/** @fn void selftestFailNotification(uint32 flag)
*   @brief Self test fail service routine
*
*    This function is called if there is a self test fail with appropriate flag
*/
void selftestFailNotification(uint32 flag)
{

/* USER CODE BEGIN (1) */
/* USER CODE END */

}

/** @fn void ccmSelfCheck(void)
*   @brief CCM module self check Driver
*
*   This function self checks the CCM module.
*/
void ccmSelfCheck(void)
{
/* USER CODE BEGIN (2) */
/* USER CODE END */

    /* Run a diagnostic check on the CCM-R5F module */
    /* This step ensures that the CCM-R5F can actually indicate an error */

    /* Configure CCM in self-test mode */
    ccmr5REG->CCMKEYR1 = 0x6U;                                
    /* Wait for CCM self-test to complete */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while ((ccmr5REG->CCMSR1 & 0x100U) != 0x100U)
    { 
    }/* Wait */         

/* USER CODE BEGIN (3) */
/* USER CODE END */
    
    /* Check if there was an error during the self-test */
    if ((ccmr5REG->CCMSR1 & 0x1U) == 0x1U)
    {
        /* STE is set */
        selftestFailNotification(CCMSELFCHECK_FAIL1);                                
    }
    else
    {
        /* Check CCM-R4 self-test error flag by itself (without compare error) */
        if ((esmREG->SR1[0U] & 0x80000000U) == 0x80000000U)
        {
            /* ESM flag is not set */
            selftestFailNotification(CCMSELFCHECK_FAIL2);
        }
        else
        {            
            /* Configure CCM in error-forcing mode */
            ccmr5REG->CCMKEYR1 = 0x9U;
            
            /* Wait till error-forcing is completed. */
            /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
            while (ccmr5REG->CCMKEYR1 != 0U)
            {
            }/* Wait */ 
            
            /* check if compare error flag is set */
            if ((esmREG->SR1[1U] & 0x4U) != 0x4U)
            {
                /* ESM flag is not set */
                selftestFailNotification(CCMSELFCHECK_FAIL3);
            }
            else
            {
                /* Check FIQIVEC to ESM High Interrupt flag is set */ 
                if((vimREG->FIQINDEX & 0x000000FFU) != 1U)
                {
                   /* ESM High Interrupt flag is not set in VIM*/
                   selftestFailNotification(CCMSELFCHECK_FAIL4);
                }
                
                /* clear ESM group2 channel 2 flag */ 
                esmREG->SR1[1U] = 0x4U;
                
                /* ESM self-test error needs to also be cleared */
                esmREG->SR1[0U] = 0x80000000U;        
                
                /* The nERROR pin will become inactive once the LTC counter expires */
                esmREG->EKR = 0x5U;    

                /* Configure CCM in selftest error-forcing mode */
                ccmr5REG->CCMKEYR1 = 0xFU;

                /* Wait till selftest error-forcing is completed. */
                /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
                while (ccmr5REG->CCMKEYR1 != 0U)
                {
                }/* Wait */ 

                if((esmREG->SR1[0U] & 0x80000000U) != 0x80000000U)
                {
                    /* ESM flag not set */
                    selftestFailNotification(CCMSELFCHECK_FAIL2);
                }
                else
                {
                    /* clear ESM flag */
                    esmREG->SR1[0U] = 0x80000000U;
                }
            }
        }
    }
}

/** @fn void memoryInit(uint32 ram)
*   @brief Memory Initialization Driver
*
*   This function is called to perform Memory initialization of selected RAM's.
*/
void memoryInit(uint32 ram)
{
/* USER CODE BEGIN (4) */
/* USER CODE END */

    /* Enable Memory Hardware Initialization */
    systemREG1->MINITGCR = 0xAU;    
    
    /* Enable Memory Hardware Initialization for selected RAM's */
    systemREG1->MSINENA  = ram;
    
    /* Wait until Memory Hardware Initialization complete */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while((systemREG1->MSTCGSTAT & 0x00000100U) != 0x00000100U)
    { 
    }/* Wait */         
    
    /* Disable Memory Hardware Initialization */
    systemREG1->MINITGCR = 0x5U;    
    
/* USER CODE BEGIN (5) */
/* USER CODE END */
}

/** @fn void stcSelfCheck(void)
*   @brief STC module self check Driver
*
*   This function is called to perform STC module self check.
*/
void stcSelfCheck(void)
{
/* USER CODE BEGIN (6) */
/* USER CODE END */
    uint32 i = 0U;

    /* Run a diagnostic check on the CPU self-test controller */
    /* First set up the STC clock divider as STC is only supported up to 110MHz */
    
    /* STC clock is now normal mode CPU clock frequency/3 = 330MHz/3 */
    systemREG2->STCCLKDIV = 0x02020000U;    
    
    /* Select one test interval, restart self-test next time, 0x00010001 */
    stcREG1->STCGCR0 = 0x00010001U;                        
    
    /* Enable comparator self-check and stuck-at-0 fault insertion in CPU, 0x1A */
    stcREG1->STCSCSCR = 0x1AU;                            
    
    /* Maximum time-out period */
    stcREG1->STCTPR = 0xFFFFFFFFU;                        

    /* wait for 16 VBUS clock cycles at least, based on HCLK to VCLK ratio */
    for (i=0U; i<(16U + (16U * 1U)); i++){ /* Wait */ }                                

    /* Enable self-test */
    stcREG1->STCGCR1 = 0xAU;                                    
   
    /* Idle the CPU so that the self-test can start */
    _gotoCPUIdle_();

/* USER CODE BEGIN (7) */
/* USER CODE END */
}

/** @fn void cpuSelfTest(uint32 no_of_intervals, uint32 max_timeout, boolean restart_test)
*   @brief CPU self test Driver
*   @param[in] no_of_intervals - Number of Test Intervals to be 
*   @param[in] max_timeout     - Maximum Timeout to complete selected test Intervals
*   @param[in] restart_test    - Restart the test from Interval 0 or Continue from where it stopped.
*
*   This function is called to perform CPU self test using STC module.
*/
void cpuSelfTest(uint32 no_of_intervals, uint32 max_timeout, boolean restart_test)
{
    uint32 i = 0U;

/* USER CODE BEGIN (8) */
/* USER CODE END */

    /* STC clock is now normal mode CPU clock frequency/3 = 330MHz/3 */
    systemREG2->STCCLKDIV = 0x02020000U;    
	
    /* Run specified no of test intervals starting from interval 0 */
    /* Start test from interval 0 or continue the test. */ 
    stcREG1->STCGCR0 = (no_of_intervals << 16U)
                    | (uint32) restart_test;                        
    
    /* Configure Maximum time-out period */
    stcREG1->STCTPR = max_timeout;                        
    
    /* wait for 16 VBUS clock cycles at least, based on HCLK to VCLK ratio */
    for (i=0U; i<(16U + (16U * 1U)); i++){ /* Wait */ }                                

    /* Enable self-test */
    stcREG1->STCGCR1 = 0xAU;                                
  
    /* Idle the CPU so that the self-test can start */    
    _gotoCPUIdle_();
    
}

/** @fn void pbistSelfCheck(void)
*   @brief PBIST self test Driver
*
*   This function is called to perform PBIST self test.
*/
void pbistSelfCheck(void)
{
    uint32 i = 0U;
    uint32 PBIST_FSRF0, PBIST_FSRF1;
	
/* USER CODE BEGIN (9) */
/* USER CODE END */
    /* Run a diagnostic check on the memory self-test controller */
    /* First set up the PBIST ROM clock as this clock frequency is limited to 90MHz */
    
    /* PBIST ROM clock frequency = HCLK frequency /2 */
    /* Disable memory self controller */
    systemREG1->MSTGCR = 0x00000205U;                
    
    /* Disable Memory Initialization controller */
    systemREG1->MINITGCR = 0x5U;                            

    /* Enable PBIST controller */
    systemREG1->MSINENA = 0x1U;                            
    
    /* Enable memory self controller */
    systemREG1->MSTGCR = 0x0000010AU;                               
    
    /* wait for 64 VBUS clock cycles at least, based on HCLK to VCLK ratio */
    for (i=0U; i<(64U + (64U * 1U)); i++){ /* Wait */ }                                

/* USER CODE BEGIN (10) */
/* USER CODE END */
    
    /* Enable PBIST clocks and ROM clock */
    pbistREG->PACT = 0x3U;                                
    
    /* Select algo#3, march13n to be run */
    pbistREG->ALGO = 0x00000004U;                        
    
    /* Select RAM Group 1, which is actually the PBIST ROM */
    pbistREG->RINFOL = 0x1U;                                
    
    /* ROM contents will not override ALGO and RINFOx settings */
    pbistREG->OVER = 0x0U;                                
    
    /* Algorithm code is loaded from ROM */
    pbistREG->ROM = 0x3U;                                
    
    /* Start PBIST */
    pbistREG->DLR = 0x14U;                                
    
    /* wait until memory self-test done is indicated */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while ((systemREG1->MSTCGSTAT & 0x1U) != 0x1U)
    { 
    }/* Wait */                 
    
    /* Check for the failure */
    PBIST_FSRF0 = pbistREG->FSRF0;
    PBIST_FSRF1 = pbistREG->FSRF1;
    if (((PBIST_FSRF0 & 0x1U) != 0x1U) && ((PBIST_FSRF1 & 0x1U) != 0x1U))
    {
        /* no failure was indicated even if the march13n algorithm was run on a ROM */
        selftestFailNotification(PBISTSELFCHECK_FAIL1);
        
/* USER CODE BEGIN (11) */
/* USER CODE END */
    }
    else                                                
    {
        /* PBIST self-check has passed */
        
        /* Disable PBIST clocks and ROM clock */
        pbistREG->PACT = 0x0U;                            
        
        /* Disable PBIST */
        systemREG1->MSTGCR &= ~(0xFU);                    
        systemREG1->MSTGCR |= 0x5U;
        
/* USER CODE BEGIN (12) */
/* USER CODE END */
    }
}

/** @fn void pbistRun(uint64 raminfo, uint32 algomask)
*   @brief CPU self test Driver
*   @param[in] raminfo    - Select the list of RAM to be tested.
*   @param[in] algomask   - Select the list of Algorithm to be run.
*
*   This function performs Memory Built-in Self test using PBIST module.
*/
void pbistRun(uint64 raminfo, uint32 algomask)
{
    uint32 i = 0U;

/* USER CODE BEGIN (13) */
/* USER CODE END */

    /* PBIST ROM clock frequency = HCLK frequency /2 */
    /* Disable memory self controller */
    systemREG1->MSTGCR = 0x00000105U;                
    
    /* Disable Memory Initialization controller */
    systemREG1->MINITGCR = 0x5U;                            

    /* Enable PBIST controller */
    systemREG1->MSINENA = 0x1U;                            
    
    /* Enable memory self controller */
    systemREG1->MSTGCR = 0x0000010AU;
    
    /* wait for 64 VBUS clock cycles at least, based on HCLK to VCLK ratio */
    for (i=0U; i<(32U + (64U * 1U)); i++){ /* Wait */ }                             

/* USER CODE BEGIN (14) */
/* USER CODE END */
    
    /* Enable PBIST clocks and ROM clock */
    pbistREG->PACT = 0x3U;                                 
    
    /* Select all algorithms to be tested */
    pbistREG->ALGO = algomask;                             
    
    /* Select RAM groups */
    pbistREG->RINFOL = (uint32)raminfo;
    pbistREG->RINFOU = (uint32)(raminfo >> 32);                     
    
    /* ROM contents will not override RINFOx settings */
    pbistREG->OVER = 0x0U;                                 
    
    /* Algorithm code is loaded from ROM */
    pbistREG->ROM = 0x3U;                                 
    
    /* Start PBIST */
    pbistREG->DLR = 0x14U;                                 

/* USER CODE BEGIN (15) */
/* USER CODE END */
}

/** @fn void pbistStop(void)
*   @brief Routine to stop PBIST test enabled.
*
*   This function is called to stop PBIST after test is performed.
*/
void pbistStop(void)
{
/* USER CODE BEGIN (16) */
/* USER CODE END */
    /* disable pbist clocks and ROM clock */
    pbistREG->PACT = 0x0U;                            
    systemREG1->MSTGCR &= ~(0xFU);
    systemREG1->MSTGCR |= 0x5U;
/* USER CODE BEGIN (17) */
/* USER CODE END */
}

/** @fn boolean pbistIsTestCompleted(void)
*   @brief Checks to see if the PBIST test is completed.
*   @return 1 if PBIST test completed, otherwise 0.
*
*   Checks to see if the PBIST test is completed.
*/
boolean pbistIsTestCompleted(void)
{
/* USER CODE BEGIN (18) */
/* USER CODE END */

    return ((systemREG1->MSTCGSTAT & 0x1U) != 0U);
/* USER CODE BEGIN (19) */
/* USER CODE END */
}

/** @fn boolean pbistIsTestPassed(void)
*   @brief Checks to see if the PBIST test is completed successfully.
*   @return 1 if PBIST test passed, otherwise 0.
*
*   Checks to see if the PBIST test is completed successfully.
*/
boolean pbistIsTestPassed(void)
{
/* USER CODE BEGIN (20) */
/* USER CODE END */

    return (((pbistREG->FSRF0 ==0U) && (pbistREG->FSRF1 ==0U)) == TRUE);
/* USER CODE BEGIN (21) */
/* USER CODE END */
}

/** @fn boolean pbistPortTestStatus(uint32 port)
*   @brief Checks to see if the PBIST Port test is completed successfully.
*   @param[in] port   - Select the port to get the status.
*   @return 1 if PBIST Port test completed successfully, otherwise 0.
*
*   Checks to see if the selected PBIST Port test is completed successfully.
*/
boolean pbistPortTestStatus(uint32 port)
{
    boolean status;
/* USER CODE BEGIN (22) */
/* USER CODE END */

    if(port == PBIST_PORT0)
    {
      status =  ((boolean)pbistREG->FSRF0 == 0U);
    }
    else
    {
      status =  ((boolean)pbistREG->FSRF1 == 0U);    
    }
    
    return  status;
}

/** @fn void pbistFail(void)
*   @brief PBIST Module test fail handler
*
*   This function is for PBIST Module test fail handler.
*/
void pbistFail(void)
{
    uint32 PBIST_RAMT, PBIST_FSRA0, PBIST_FSRDL0, PBIST_FSRA1, PBIST_FSRDL1;
	/*SAFETYMCUSW 134 S MR:12.2 <APPROVED> "Hardware status bit read check" */
    PBIST_RAMT = pbistREG->RAMT;
    PBIST_FSRA0 = pbistREG->FSRA0;
    PBIST_FSRDL0 = pbistREG->FSRDL0;
    PBIST_FSRA1 = pbistREG->FSRA1;
    PBIST_FSRDL1 = pbistREG->FSRDL1;
    
    if(pbistPortTestStatus((uint32)PBIST_PORT0) != TRUE)
    {
        memoryPort0TestFailNotification((uint32)((PBIST_RAMT & 0xFF000000U) >> 24U), (uint32)((PBIST_RAMT & 0x00FF0000U) >> 16U),(uint32)PBIST_FSRA0, (uint32)PBIST_FSRDL0);
    }
    else if(pbistPortTestStatus((uint32)PBIST_PORT1) != TRUE)
    {
        memoryPort1TestFailNotification((uint32)((PBIST_RAMT & 0xFF000000U) >> 24U), (uint32)((PBIST_RAMT & 0x00FF0000U) >> 16U), (uint32)PBIST_FSRA1, (uint32)PBIST_FSRDL1);
    }
    else
    {
/* USER CODE BEGIN (23) */
/* USER CODE END */
/*SAFETYMCUSW 5 C MR:NA <APPROVED> "for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below" */
/*SAFETYMCUSW 26 S MR:NA <APPROVED> "for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below" */
/*SAFETYMCUSW 28 D MR:NA <APPROVED> "for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below" */
        for(;;)
        { 
        }/* Wait */                 

/* USER CODE BEGIN (24) */
/* USER CODE END */
    }
}

/** @fn void efcCheck(void)
*   @brief EFUSE module self check Driver
*
*   This function self checks the EFUSE module.
*/
void efcCheck(void)
{
    uint32 efcStatus = 0U;

/* USER CODE BEGIN (25) */
/* USER CODE END */
    
    /* read the EFC Error Status Register */
    efcStatus = efcREG->ERR_STAT;                        

/* USER CODE BEGIN (26) */
/* USER CODE END */
    
    if (efcStatus == 0x0U)
    {
        /* run stuck-at-zero test and check if it passed */
        if (efcStuckZeroTest()== TRUE)                        
        {
            /* start EFC ECC logic self-test */
            efcSelfTest();                            
        }
        else
        {
            /* EFC output is stuck-at-zero, device operation unreliable */
            selftestFailNotification(EFCCHECK_FAIL1);
        }
    }
    /* EFC Error Register is not zero */
    else                                            
    {
        /* one-bit error detected during autoload */
        if (efcStatus == 0x15U)                        
        {
            /* start EFC ECC logic self-test */
            efcSelfTest();                            
        }
        else
        {
            /* Some other EFC error was detected */
            selftestFailNotification(EFCCHECK_FAIL1);                
        }
    }
}

/** @fn boolean efcStuckZeroTest(void)
*   @brief Checks to see if the EFUSE Stuck at zero test is completed successfully.
*   @return 1 if EFUSE Stuck at zero test completed, otherwise 0.
*
*   Checks to see if the EFUSE Stuck at zero test is completed successfully.
*/
boolean efcStuckZeroTest(void)
{
/* USER CODE BEGIN (27) */
/* USER CODE END */

    uint32 ESM_SR4, ESM_SR1;
    
    boolean result = FALSE;
    uint32 error_checks = EFC_INSTRUCTION_INFO_EN  | 
                          EFC_INSTRUCTION_ERROR_EN | 
                          EFC_AUTOLOAD_ERROR_EN    | 
                          EFC_SELF_TEST_ERROR_EN;
    
    /* configure the output enable for auto load error , instruction info,
         instruction error, and self test error using BOUND register 
         and drive values one across all the errors */
      efcREG->BOUND = (OUTPUT_ENABLE | error_checks);
      
    /* Read from the pin register. This register holds the current values 
         of above errors. This value should be 0x5c00.If not at least one of
         the above errors is stuck at 0. */
    if ((efcREG->PINS & 0x5C00U) == 0x5C00U)
    {
        ESM_SR4 = esmREG->SR4[0U];
        ESM_SR1 = esmREG->SR1[2U];
        /* check if the ESM group1 channels 41 is set and group3 channel 2 is set */
        if (((ESM_SR4 & 0x200U) == 0x200U) & ((ESM_SR1 & 0x2U) == 0x2U))
        {
           /* stuck-at-zero test passed */
           result = TRUE;                                    
        }
    }
    
    /* put the pins back low */
    efcREG->BOUND = OUTPUT_ENABLE;
    
    /* clear group1 flags */
    esmREG->SR4[0U] = 0x300U;
    
    /* clear group3 flag */
    esmREG->SR1[2U] = 0x2U;                    
    
    /* The nERROR pin will become inactive once the LTC counter expires */
    esmREG->EKR = 0x5U;                            

    return result;
}

/** @fn void efcSelfTest(void)
*   @brief EFUSE module self check Driver
*
*   This function self checks the EFSUE module.
*/
void efcSelfTest(void)
{
/* USER CODE BEGIN (28) */
/* USER CODE END */
    /* configure self-test cycles */
    efcREG->ST_CY = 0x258U;
    
    /* configure self-test signature */
    efcREG->ST_SIG = 0x5362F97FU;
    
    /* configure BOUND register to start ECC self-test */
    efcREG->BOUND = 0x0000200FU;
}

/** @fn boolean checkefcSelfTest(void)
*   @brief EFUSE module self check Driver
*
*   This function self checks the EFSUE module.
*/
boolean checkefcSelfTest(void)
{
/* USER CODE BEGIN (29) */
/* USER CODE END */
    boolean result = FALSE;
    
    uint32 EFC_PINS, EFC_ERROR;
    
    /* wait until EFC self-test is done */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while((!(efcREG->PINS & EFC_SELF_TEST_DONE)) != 0U)
    { 
    }/* Wait */         
    
    /* check if EFC self-test error occurred */
    EFC_PINS = efcREG->PINS;
    EFC_ERROR = efcREG->ERR_STAT;
    if (((!(EFC_PINS & EFC_SELF_TEST_ERROR)) & (!(EFC_ERROR & SELF_TEST_ERROR))) !=0U)
    {
        /* check if EFC self-test error is set */
        if ((esmREG->SR4[0U] & 0x100U) != 0x100U)        
        {
            result = TRUE;
        }
    }
    return result;
}
/** @fn void custom_dabort(void)
*   @brief Custom Data abort routine for the application.
*
*   Custom Data abort routine for the application.
*/
void custom_dabort(void)
{
    /* Need custom data abort handler here.
     * This data abort is not caused due to diagnostic checks of flash and TCRAM ECC logic.
     */
/* USER CODE BEGIN (36) */
/* USER CODE END */
}


/** @fn void vimECCCheck(void)
*   @brief Routine to check VIM RAM ECC error detection and signaling mechanism
*
*   Routine to check VIM RAM ECC error detection and signaling mechanism
*/
void vimECCCheck(void)
{
	volatile uint32 vimramread = 0U;

/* USER CODE BEGIN (66) */
/* USER CODE END */
	
	/* Enable Error Signalling and ECC test mode. ECC already enabled. */
	VIM_ECCCTL = ((VIM_ECCCTL & 0xF0FFF0FF) | 0x0A000500);
	

	/* flip 1 bit in the VIM RAM ECC location */
	VIMRAMECCLOC ^= 0x1U;

	/* cause ECC single bit error */
	vimramread = VIMRAMLOC;					
   
    /* check if SBERR Flag in ECC Status Register was updated. */
	if ((VIM_ECCSTAT & 0x100U) == 0U)
	{
		/* VIM RAM ECC single bit error was not detected. */
		selftestFailNotification(VIMECCCHECK_SINGLEBIT_FAIL);
	}
	else
	{
	    /* clear VIM RAM ECC error flag in VIM */
		VIM_ECCSTAT = 0x101U;
		
		/* clear ESM group1 channel 15 flag */
		esmREG->SR7[0U] = 0x80000U;
		
		/* Revert back to correct data*/
		VIMRAMECCLOC ^= 0x1U;
	}
	
	/* flip 2 bit in the VIM RAM ECC location */
	VIMRAMECCLOC ^= 0x3U;

	/* cause ECC uncorrectable error */
	vimramread = VIMRAMLOC;					
   
    /* check if UERR flag in ECC Status Register was updated. */
	if ((VIM_ECCSTAT & 0x1U) == 0U)
	{
		/* VIM RAM ECC uncorrectable error was not detected. */
		selftestFailNotification(VIMECCCHECK_DOUBLEBIT_FAIL);
	}
	else
	{
	    /* clear VIM RAM ECC error flag in VIM */
		VIM_ECCSTAT = 0x101U;
		
		/* clear ESM group1 channel 15 flag */
		esmREG->SR1[0U] = 0x8000U;
	
		/* Revert back to correct data*/
		VIMRAMECCLOC ^= 0x3U;
	}
	/* Disable ECCENA, Error Signalling and ECC test mode */
	VIM_ECCCTL = ((VIM_ECCCTL & 0xF0FFF0F0) | 0x05000A05);

/* USER CODE BEGIN (67) */
/* USER CODE END */
}


/** @fn void l2ramwECCCHECK(void)
*   @brief Verified SECDED Block functioning inside L2RAMW. 
*
*   This test verfies the Write and RMW Path SECDED block inside L2RAMW. 
*/
void l2ramwECCCHECK()
{
/* USER CODE BEGIN (68) */
/* USER CODE END */
	/* Enabling ECC and ESM Error Signalling */
	l2ramwREG->RAMCTRL = ((l2ramwREG->RAMCTRL & 0XFF0F0FF0) | 0x0000100AU);

	l2ramwREG->DIAGDATAVECTOR_H = 0x00000000;
	l2ramwREG->DIAGDATAVECTOR_L = 0x0000000A;

	/* ECC Value of 0xA */
	l2ramwREG->DIAG_ECC = 0x12U;

	/* Single Bit Error */
	l2ramwREG->DIAG_ECC ^= 0x1U;

	/* Select Equality Mode*/
	l2ramwREG->RAMTEST = (l2ramwREG->RAMTEST & 0xFFFFFF0F) | 0x00000080;

	/* Enabling Test Mode with Trigger */
	l2ramwREG->RAMTEST = (l2ramwREG->RAMTEST & 0xFFFFFFF0) | 0x0000000A;
	l2ramwREG->RAMTEST |= 0x100;

	/* Wait till the Diagnostic Test is done. */
	while(!((l2ramwREG->RAMERRSTATUS & 0x80000) && (l2ramwREG->RAMERRSTATUS & 0x200000)));

	/* Check if ESM Group 2 Channel 5 is flagged. */
	if(!(esmREG->SR1[1] & 0x00000080))
	{
		selftestFailNotification(L2RAMECCCHECK_SINGLEBIT_FAIL);
	}
	else
	{
		/* Clear DWSE and DRSE Bits in the Error Status Register */
		l2ramwREG->RAMERRSTATUS = 0x280000;

		/* Clear ESM Bits. */
		esmREG->SR1[1] = 0x00000080;

		/*Disable Test Mode */
		l2ramwREG->RAMTEST = 0x00000005;

		/* Reverting back to the original Value */
		l2ramwREG->DIAG_ECC ^= 0x1U;

	}

	/*Double Bit */
	/*Double Bit Error in ECC */
	l2ramwREG->DIAG_ECC ^= 0x3U;

	/* Select Equality Mode*/
	l2ramwREG->RAMTEST = (l2ramwREG->RAMTEST & 0xFFFFFF0F) | 0x00000080;

	/* Enabling Test Mode with Trigger */
	l2ramwREG->RAMTEST = (l2ramwREG->RAMTEST & 0xFFFFFFF0) | 0x0000000A;
	l2ramwREG->RAMTEST |= 0x100;

	/* Wait till the Diagnostic Test is done. */
	while(!((l2ramwREG->RAMERRSTATUS & 0x100000) && (l2ramwREG->RAMERRSTATUS & 0x400000)));

	/* Check if ESM Group 2 Channel 5 is flagged. */
	if(!(esmREG->SR1[1] & 0x00000080))
	{
		selftestFailNotification(L2RAMECCCHECK_DOUBLEBIT_FAIL);
	}
	else
	{
		/* Clear DWDE and DRDE Bits in the Error Status Register */
		l2ramwREG->RAMERRSTATUS = 0x500000;

		/* Clear ESM Bits. */
		esmREG->SR1[1] = 0x00000080;

		/*Disable Test Mode */
		l2ramwREG->RAMTEST = 0x00000005;

		/* Reverting back to the original Value */
		l2ramwREG->DIAG_ECC ^= 0x2U;


	}

/* USER CODE BEGIN (69) */
/* USER CODE END */
}



/** @fn void checkClockMonitor(void)
*   @brief Check clock monitor failure detection logic.
*
*   This function checks clock monitor failure detection logic.
*/
void checkClockMonitor(void)
{
    uint32 ghvsrc_bk;
	
    /* Enable clock monitor range detection circuitry */
    systemREG1->CLKTEST |= 0x03000000U;

    /* Backup register GHVSRC */
	ghvsrc_bk = systemREG1->GHVSRC;
    
	/* Switch all clock domains to HF LPO */
    systemREG1->GHVSRC = 0x05050005U;

    /* Disable oscillator to cause a oscillator fail */
    systemREG1->CSDISSET = 0x1U;

    /* Wait till oscillator fail flag is set */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while((systemREG1->GBLSTAT & 0x1U) == 0U)
    {
    } /* Wait */

    if(esmREG->SR1[0U] != 0x800U)
    {
        selftestFailNotification(CHECKCLOCKMONITOR_FAIL1);
    }
    else
    {
        /* Clear ESM flag */
        esmREG->SR1[0U] = 0x800U;

        systemREG1->CLKTEST &= ~(0x03000000U);

        /* Enable oscillator */
        systemREG1->CSDISCLR = 0x1U;

        /* Wait until oscillator is enabled */
        /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
        while((systemREG1->CSVSTAT & 0x3U) == 0U)
        {
        } /* Wait */

        /* Clear oscillator fail flag and PLL slip flag if any*/
        systemREG1->GBLSTAT = 0x301U;

        /* Switch back all clock domains */
        systemREG1->GHVSRC = ghvsrc_bk;
    }
}

/** @fn void checkPLL1Slip(void)
*   @brief Check PLL1 Slip detection logic.
*
*   This function checks PLL1 Slip detection logic.
*/
void checkPLL1Slip(void)
{
    uint32 ghvsrc_bk, pllctl1_bk;

    /* Back up the the registers GHVSRC and PLLCTRL1 */
    ghvsrc_bk = systemREG1->GHVSRC;
    pllctl1_bk = systemREG1->PLLCTL1;

    /* Disable Reset on PLL Slip and enable Bypass on PLL slip */
    systemREG1->PLLCTL1 &= 0x1FFFFFFFU;

    /* Force a PLL Slip */
    systemREG1->PLLCTL1 ^= 0x8000U;

    /* Wait till PLL slip flag is set */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while((systemREG1->GBLSTAT & 0x300U) == 0U)
    {
    } /* Wait */

    if((esmREG->SR1[0U] & 0x400U) != 0x400U)
    {
        /* ESM flag not set */
        selftestFailNotification(CHECKPLL1SLIP_FAIL1);
    }
    else
    {
        /* Switch all clock domains to oscillator */
        systemREG1->GHVSRC = 0x00000000U;

        /* Disable PLL1 */
        systemREG1->CSDISSET = 0x2U;

        /* Wait till PLL1 is disabled */
        /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
        while((systemREG1->CSDIS & 0x2U) == 0U)
        {
        } /* Wait */

        /* Restore the PLL multiplier value */
		systemREG1->PLLCTL1 ^= 0x8000U;

        /* Enable PLL1 */
        systemREG1->CSDISCLR = 0x2U;

        /* Wait till PLL1 is disabled */
        /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
        while((systemREG1->CSDIS & 0x2U) != 0U)
        {
        } /* Wait */

        /* Switch back to the initial clock source */
        systemREG1->GHVSRC = ghvsrc_bk;

        /* Clear PLL slip flag */
        systemREG1->GBLSTAT = 0x300U;

        /* Clear ESM flag */
        esmREG->SR1[0U] = 0x400U;
		
		/* Restore the PLLCTL1 register */
        systemREG1->PLLCTL1 = pllctl1_bk;
    }
}

/** @fn void checkPLL2Slip(void)
*   @brief Check PLL2 Slip detection logic.
*
*   This function checks PLL2 Slip detection logic.
*/
void checkPLL2Slip(void)
{
    uint32 ghvsrc_bk;

    /* Back up the the register GHVSRC */
    ghvsrc_bk = systemREG1->GHVSRC;

    /* Force a PLL2 Slip */
    systemREG2->PLLCTL3 ^= 0x8000U;

    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while((esmREG->SR4[0U] & 0x400U) != 0x400U)
    {
        /* Wait till ESM flag is set */
    }

    /* Switch all clock domains to oscillator */
    systemREG1->GHVSRC = 0x00000000U;

    /* Disable PLL2 */
    systemREG1->CSDISSET = 0x40U;

    /* Wait till PLL2 is disabled */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while((systemREG1->CSDIS & 0x40U) == 0U)
    {
    } /* Wait */

    /* Restore the PLL 2 multiplier value */
    systemREG2->PLLCTL3 ^= 0x8000U;

    /* Enable PLL2 */
    systemREG1->CSDISCLR = 0x40U;

    /* Wait till PLL2 is disabled */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while((systemREG1->CSDIS & 0x40U) != 0U)
    {
    } /* Wait */

    /* Switch back to the initial clock source */
    systemREG1->GHVSRC = ghvsrc_bk;

    /* Clear PLL slip flag */
    systemREG1->GBLSTAT = 0x300U;

    /* Clear ESM flag */
    esmREG->SR4[0U] = 0x400U;
}
