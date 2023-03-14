/* Copyright (C) 2013-2019 Texas Instruments Incorporated - http://www.ti.com/
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
    VECTORS (X)  : origin=0x00000000 length=0x00000020   vfill = 0xffffffff
    FLASH0  (RX) : origin=0x00000020 length=0x0005FFE0   vfill = 0xffffffff
    STACKS  (RW) : origin=0x08000000 length=0x00001500
    SRAM    (RWX) : origin=0x08001500 length=0x00006B00

/* USER CODE BEGIN (2) */
#if 1
    ECC_VEC  (R) : origin=(0xf0400000 + (start(VECTORS) >> 3))
                   length=(size(VECTORS) >> 3)
                   ECC={algorithm=algoL2R4F021, input_range=VECTORS}

    ECC_FLA0 (R) : origin=(0xf0400000 + (start(FLASH0)  >> 3))
                   length=(size(FLASH0)  >> 3)
                   ECC={algorithm=algoL2R4F021, input_range=FLASH0 }
#endif
/* USER CODE END */
}

/* USER CODE BEGIN (3) */
ECC
{
    algoL2R4F021 : address_mask = 0xfffffff8 /* Address Bits 31:3 */
                   hamming_mask = R4         /* Use R4/R5 build in Mask */
                   parity_mask  = 0x0c       /* Set which ECC bits are Even and Odd parity */
                   mirroring    = F021       /* RM57Lx and TMS570LCx are build in F021 */
}
/* USER CODE END */


/*----------------------------------------------------------------------------*/
/* Section Configuration                                                      */

SECTIONS
{
/* USER CODE BEGIN (5) */
/* USER CODE END */
   .intvecs : {} > VECTORS
   flashAPI :
   {
     .\source\Fapi_UserDefinedFunctions.obj (.text)
     .\source\bl_flash.obj (.text)
//     .\source\bl_dcan.obj (.text)
     --library= "c:\ti\Hercules\F021 Flash API\02.01.01\F021_API_CortexR4_LE.lib" (.text)
   } palign=8 load = FLASH0, run = SRAM, LOAD_START(apiLoadStart), RUN_START(apiRunStart), SIZE(apiLoadSize)


   .text    : {} palign=8 > FLASH0
   .const   : {} palign=8 load=FLASH0, run = SRAM, LOAD_START(constLoadStart), RUN_START(constRunStart), SIZE(constLoadSize)   /*Initialized constant data (e.g. const flash_sectors[..] = )*/
   .cinit   : {} palign=8 > FLASH0
   .pinit   : {} palign=8 > FLASH0
   .data    : {} > SRAM
   .bss     : {} > SRAM
   .sysmem  : {} > SRAM
/* USER CODE BEGIN (6) */

/* USER CODE END */
}

/* USER CODE BEGIN (7) */
/* USER CODE END */


/*----------------------------------------------------------------------------*/
/* Misc                                                                       */

/* USER CODE BEGIN (8) */
/* USER CODE END */
/*----------------------------------------------------------------------------*/



