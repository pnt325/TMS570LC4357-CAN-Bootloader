/** @file HL_sys_main.c 
*   @brief Application main file
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   This file contains an empty main function,
*   which can be used for the application.
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

/* USER CODE BEGIN (1) */
#include "HL_sys_core.h"
#include "HL_system.h"
#include "HL_esm.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PMU_CYCLE

#ifdef PMU_CYCLE
#include "HL_sys_pmu.h"
#endif
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
#define ROW    100
#define COLUMN 100

uint32_t testMatrix1[ROW][COLUMN];
uint32_t testMatrix2[ROW][COLUMN];
uint32_t testMatrix3[ROW][COLUMN];

uint32_t number_of_elements = ROW*COLUMN;

uint32_t measure_cycles_per_Inst(void);
uint32_t measure_DCache_miss(void);
uint32_t measure_ICache_miss(void);
float measure_code_execution_time(void);
void _pmuEnableUserMode_(void);

uint32_t fill_matrix(uint32_t array);
uint32_t add_matrix();

/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    uint32_t retVal;
    float code_execution_useconds;

#ifdef PMU_CYCLE
    _pmuInit_();

    /* Enables User mode access to the PMU */
    _pmuEnableUserMode_();

#endif //PMU_Cycle

    /*********************************************************
     * Test 1
     * Count the cycles token by a function or a piece of code
     *
     */
    code_execution_useconds = measure_code_execution_time();

     /*********************************************************
      * Test 2
      * Measure the average cycles per instruction
      *
      */
     retVal = measure_cycles_per_Inst();

     /*********************************************************
      * Test 3
      * Measure the Data Cache Miss rate for read/write
      *
      */
     retVal = measure_DCache_miss();

     /*********************************************************
      * Test 4
      * Measure the Instruction Cache Miss rate for read/write
      *
      */
     retVal = measure_ICache_miss();

/* USER CODE END */

     return 0;
}


/* USER CODE BEGIN (4) */
float measure_code_execution_time(void)
{
    float cycles, uSeconds;
    uint32_t pll_NR, pll_NF, pll_OD, pll_R, pll1;

    /*Reset Cycle Counter */
    _pmuResetCounters_();

    /*Start Cycle Counter */
    _pmuStartCounters_(pmuCYCLE_COUNTER);

    add_matrix();

    /*Stop Cycle Counter */
    _pmuStopCounters_(pmuCYCLE_COUNTER);

    /* read the CNNT cycle */
    cycles= _pmuGetCycleCount_();

    /**/
    pll_R  = ((systemREG1->PLLCTL1 >> 24) & 0x1F) + 1;
    pll_NR = ((systemREG1->PLLCTL1 >> 16) & 0x3F) + 1;
    pll_NF = ((systemREG1->PLLCTL1 >> 8)  & 0xFF) + 1;
    pll_OD = ((systemREG1->PLLCTL2 >> 9)  & 0x07) + 1;
    pll1 = OSC_FREQ * pll_NF / (pll_NR * pll_OD * pll_R);

    /* calculate micro-seconds*/
    uSeconds = cycles / pll1;

    printf("\nPerformance monitor results\n\n");
    printf("Cycle Count (CCNT) = %u\n",  (uint32_t)cycles );
    printf("Code Execution time (uSeconds = %f\n", uSeconds);

    return uSeconds;
}


uint32_t measure_cycles_per_Inst(void)
{
    float cycl_inst;
    uint32_t cycles, event0_cycles, event1_cycles, event2_cycles;

    fill_matrix(1); //Fill matrix 1 with random numbers
    fill_matrix(2); //Fill matrix 2 with random numbers

    _pmuSetCountEvent_(pmuCOUNTER0, PMU_INST_ARCH_EXECUTED);
    _pmuSetCountEvent_(pmuCOUNTER1, PMU_DATA_READ_ARCH_EXECUTED);
    _pmuSetCountEvent_(pmuCOUNTER2, PMU_DATA_WRITE_ARCH_EXECUTED);

     /*Reset Cycle Counter, Event Counter[2:0]*/
    _pmuResetCounters_();

     /*Start Cycle Counter, or Event Counter[2:0]*/
    _pmuStartCounters_(pmuCYCLE_COUNTER | pmuCOUNTER0 | pmuCOUNTER1 |pmuCOUNTER2);


    add_matrix();

    _pmuStopCounters_(pmuCYCLE_COUNTER | pmuCOUNTER0 | pmuCOUNTER1 |pmuCOUNTER2);
    cycles         = _pmuGetCycleCount_();
    event0_cycles = _pmuGetEventCount_(pmuCOUNTER0);
    event1_cycles = _pmuGetEventCount_(pmuCOUNTER1);
    event2_cycles = _pmuGetEventCount_(pmuCOUNTER2);

    asm(" NOP");  //for breakpoint when debugging

    printf("\nPerformance monitor results\n\n");
    printf("Instructions Executed = %u\n", event0_cycles );
    printf("Cycle Count (CCNT) = %u\n",    cycles );
    printf("Data Reads = %u\n",            event1_cycles );
    printf("Data Writes = %u\n",           event2_cycles );
    cycl_inst = (float)cycles / (float)event0_cycles;
    printf("Average cycles per instruction = %f\n", cycl_inst);

    return 0;
}

uint32_t measure_DCache_miss(void)
{
    float cache_miss_rate;
    uint32_t cycles, event0_cycles, event1_cycles, event2_cycles;

    fill_matrix(1); //Fill matrix 1 with random numbers
    fill_matrix(2); //Fill matrix 2 with random numbers


    _pmuSetCountEvent_(pmuCOUNTER0, PMU_DATA_CACHE_ACCESS );
    _pmuSetCountEvent_(pmuCOUNTER1, PMU_DATA_CACHE_MISS );
    _pmuSetCountEvent_(pmuCOUNTER2, PMU_DATA_CACHE_WRITE_BACK );

     /*Reset Cycle Counter, Event Counter[2:0]*/
    _pmuResetCounters_();

     /*Start Cycle Counter, or Event Counter[2:0]*/
    _pmuStartCounters_(pmuCYCLE_COUNTER | pmuCOUNTER0 | pmuCOUNTER1 |pmuCOUNTER2);


    add_matrix();

    _pmuStopCounters_(pmuCYCLE_COUNTER | pmuCOUNTER0 | pmuCOUNTER1 |pmuCOUNTER2);
    cycles         = _pmuGetCycleCount_();
    event0_cycles = _pmuGetEventCount_(pmuCOUNTER0);
    event1_cycles = _pmuGetEventCount_(pmuCOUNTER1);
    event2_cycles = _pmuGetEventCount_(pmuCOUNTER2);

    asm(" NOP");  //for breakpoint when debugging

    printf("\nPerformance monitor results\n\n");
    printf("Data Cache Access = %u\n", event0_cycles );
    printf("Cycle Count (CCNT) = %u\n",    cycles );
    printf("Data Cache Misses = %u\n",            event1_cycles );
    printf("Data Cache Write=back = %u\n",           event2_cycles );
    cache_miss_rate = (float)event1_cycles / (float)event0_cycles;
    printf("DCache miss rate = %f\n", cache_miss_rate);

    return 0;
}

uint32_t measure_ICache_miss(void)
{
    float cache_miss_rate;
    uint32_t cycles, event0_cycles, event1_cycles, event2_cycles;

    fill_matrix(1); //Fill matrix 1 with random numbers
    fill_matrix(2); //Fill matrix 2 with random numbers


    _pmuSetCountEvent_(pmuCOUNTER0, PMU_INST_CACHE_ACCESS );
    _pmuSetCountEvent_(pmuCOUNTER1, PMU_INST_CACHE_MISS );            //data cache misses
    _pmuSetCountEvent_(pmuCOUNTER2, PMU_INST_ARCH_EXECUTED );

     /*Reset Cycle Counter, Event Counter[2:0]*/
    _pmuResetCounters_();

     /*Start Cycle Counter, or Event Counter[2:0]*/
    _pmuStartCounters_(pmuCYCLE_COUNTER | pmuCOUNTER0 | pmuCOUNTER1 |pmuCOUNTER2);


    add_matrix();

    _pmuStopCounters_(pmuCYCLE_COUNTER | pmuCOUNTER0 | pmuCOUNTER1 |pmuCOUNTER2);
    cycles         = _pmuGetCycleCount_();
    event0_cycles = _pmuGetEventCount_(pmuCOUNTER0);
    event1_cycles = _pmuGetEventCount_(pmuCOUNTER1);
    event2_cycles = _pmuGetEventCount_(pmuCOUNTER2);

    asm(" NOP");

    printf("\nPerformance monitor results\n\n");
    printf("Instruction Cache Access = %u\n", event0_cycles );
    printf("Cycle Count (CCNT) = %u\n",    cycles );
    printf("Instruction Cache Misses = %u\n",            event1_cycles );
    printf("Instruction executed = %u\n",           event2_cycles );
    cache_miss_rate = (float)event1_cycles / (float)event0_cycles;
    printf("ICache miss rate = %f\n", cache_miss_rate);

    return 0;
}


uint32_t fill_matrix(uint32_t array)
{
    uint32_t i,j;
    if(array == 1)
    {
        for(i = 0;i < ROW;i++)
        {
            for(j = 0;j < COLUMN;j++)
            {
                testMatrix1[i][j]=rand() % 100;
            }
        }
    }
    if(array == 2)
    {
        for(i = 0;i < ROW;i++)
        {
            for(j = 0;j < COLUMN;j++)
            {
                testMatrix2[i][j]=rand() % 100;
            }
        }
    }
    return 0;
}

uint32_t add_matrix()
{
    uint32_t i,j;
    for(i = 0; i < ROW; i++)
    {
        for(j = 0; j < COLUMN; j++)
        {
            testMatrix3[i][j] = testMatrix1[i][j] + testMatrix2[i][j]; // Adds Matrix 1 and 2 one element at a time
        }
    }
    return 0;
}

/* Enables User mode access to the PMU (must be called in a privileged mode)
 ***/
void _pmuEnableUserMode_(void)
{
    asm(" MRC     p15, #0, r0, c9, c14, #0"); //Read PMUSERENR Register
    asm(" ORR     r0, r0, #0x01");            //Set EN bit (bit 0)
    asm(" MCR     p15, #0, r0, c9, c14, #0"); //Write PMUSERENR Register
    asm(" ISB");                              //Synchronize context
}
/* USER CODE END */
