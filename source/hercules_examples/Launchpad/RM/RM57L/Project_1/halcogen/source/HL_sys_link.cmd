/*----------------------------------------------------------------------------*/
/* sys_link.cmd                                                               */
/*                                                                            */
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

/*                                                                            */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN (0) */
/* USER CODE END */


/*----------------------------------------------------------------------------*/
/* Linker Settings                                                            */

--retain="*(.intvecs)"

/* USER CODE BEGIN (1) */
/* USER CODE END */

/*----------------------------------------------------------------------------*/
/* Memory Map                                                                 */

MEMORY
{
/* USER CODE BEGIN (2) */
#if 0
/* USER CODE END */
    VECTORS (X)  : origin=0x00000000 length=0x00000020
    FLASH0  (RX) : origin=0x00000020 length=0x001FFFE0
    FLASH1  (RX) : origin=0x00200000 length=0x00200000
    STACKS  (RW) : origin=0x08000000 length=0x00001500
    RAM     (RW) : origin=0x08001500 length=0x0007EB00

/* USER CODE BEGIN (3) */
#endif
    VECTORS (X)  : origin=0x00000000 length=0x00000020 vfill = 0xffffffff
    FLASH0  (RX) : origin=0x00000020 length=0x001FFFE0 vfill = 0xffffffff
    FLASH1  (RX) : origin=0x00200000 length=0x00200000 vfill = 0xffffffff
    STACKS  (RW) : origin=0x08000000 length=0x00001800
    RAM     (RW) : origin=0x08001800 length=0x0007E800

    ECC_VEC (R)  : origin=0xf0400000 length=0x4 ECC={ input_range=VECTORS }
    ECC_FLA0 (R) : origin=0xf0400000 + 0x4 length=0x3FFFC ECC={ input_range=FLASH0 }
    ECC_FLA1 (R) : origin=0xf0440000 length=0x40000 ECC={ input_range=FLASH1 }
/* USER CODE END */
}

/* USER CODE BEGIN (4) */
ECC
{
   algo_name : address_mask = 0xfffffff8
   hamming_mask = R4
   parity_mask = 0x0c
   mirroring = F021
}
/* USER CODE END */


/*----------------------------------------------------------------------------*/
/* Section Configuration                                                      */

SECTIONS
{
/* USER CODE BEGIN (5) */
#if 0
/* USER CODE END */
    .intvecs : {} > VECTORS
    .text   align(32) : {} > FLASH0 | FLASH1
    .const  align(32) : {} > FLASH0 | FLASH1
    .cinit  align(32) : {} > FLASH0 | FLASH1
    .pinit  align(32) : {} > FLASH0 | FLASH1
    .bss     : {} > RAM
    .data    : {} > RAM
    .sysmem  : {} > RAM
	

/* USER CODE BEGIN (6) */
#endif

    .intvecs : {} > VECTORS
    .text   align(8) : {} > FLASH0 | FLASH1
    .const  align(8) : {} > FLASH0 | FLASH1
    .cinit  align(8) : {} > FLASH0 | FLASH1
    .pinit  align(8) : {} > FLASH0 | FLASH1
    .STACK_DATA_svc     : {. += 1024;} > STACKS, RUN_START(StackModeSVC)
    .STACK_DATA_fiq     : {. += 1024;} > STACKS, RUN_START(StackModeFIQ)
    .STACK_DATA_irq     : {. += 1024;} > STACKS, RUN_START(StackModeIRQ)
    .STACK_DATA_abt     : {. += 1024;} > STACKS, RUN_START(StackModeABT)
    .STACK_DATA_und     : {. += 1024;} > STACKS, RUN_START(StackModeUND)
    .STACK_DATA_sys     : {. += 1024;} > STACKS, RUN_START(StackModeSYS)
    .bss     : {} > RAM
    .data    : {} > RAM
    .sysmem  : {} > RAM

LOG_DATA : START( ulLOGStartAddr ), END( ulLOGEndAddr ) > RAM
.sl_stflash_SRAM : RUN = RAM, LOAD = FLASH0|FLASH1, LOAD_START(ulHighHandlerLoadStart), LOAD_END(ulHighHandlerLoadEnd), LOAD_SIZE(ulHighHandlerSize), RUN_START( ulHighHandlerStartAddr ), RUN_END( ulHighHandlerEndAddr )
PROFILE_DATA        : START( ulPROFILEStartAddr ), END( ulPROFILEEndAddr ) > RAM
/* USER CODE END */
}

/* USER CODE BEGIN (7) */
/* USER CODE END */


/*----------------------------------------------------------------------------*/
/* Misc                                                                       */

/* USER CODE BEGIN (8) */
/* USER CODE END */
/*----------------------------------------------------------------------------*/

