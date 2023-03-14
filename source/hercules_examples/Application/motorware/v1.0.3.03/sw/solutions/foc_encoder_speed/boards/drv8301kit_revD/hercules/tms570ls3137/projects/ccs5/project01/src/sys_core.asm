; --COPYRIGHT--,BSD
;  Copyright (c) 2012, Texas Instruments Incorporated
;  All rights reserved.
; 
;  Redistribution and use in source and binary forms, with or without
;  modification, are permitted provided that the following conditions
;  are met:
; 
;  *  Redistributions of source code must retain the above copyright
;     notice, this list of conditions and the following disclaimer.
; 
;  *  Redistributions in binary form must reproduce the above copyright
;     notice, this list of conditions and the following disclaimer in the
;     documentation and/or other materials provided with the distribution.
; 
;  *  Neither the name of Texas Instruments Incorporated nor the names of
;     its contributors may be used to endorse or promote products derived
;     from this software without specific prior written permission.
; 
;  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
;  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
;  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
;  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
;  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
;  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
;  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
;  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
;  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
;  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
;  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
; --/COPYRIGHT--
;-------------------------------------------------------------------------------
; sys_core.asm
;
; (c) Texas Instruments 2009-2012, All rights reserved.
;

    .text
    .arm

;-------------------------------------------------------------------------------
; Initialize CPU Registers

	.def     _coreInitRegisters_
    .asmfunc
    

_coreInitRegisters_


	; After reset, the CPU is in the Supervisor mode (M = 10011)
;		cpsie if
	    mov r0, lr
	    mov r1, #0x0000
	    mov r2, #0x0000
	    mov r3, #0x0000
	    mov r4, #0x0000
	    mov r5, #0x0000
	    mov r6, #0x0000
	    mov r7, #0x0000
	    mov r8, #0x0000
	    mov r9, #0x0000
	    mov r10, #0x0000
	    mov r11, #0x0000
	    mov r12, #0x0000
	    mov r13, #0x0000
	    mrs r1, cpsr
	    msr spsr_cxsf, r1 
	    ; Switch to FIQ mode (M = 10001)
	    cps #17
	    mov lr, r0
	    mov r8, #0x0000
	    mov r9, #0x0000
	    mov r10, #0x0000
	    mov r11, #0x0000
	    mov r12, #0x0000
	    mrs r1, cpsr
	    msr spsr_cxsf, r1 
	    ; Switch to IRQ mode (M = 10010)
	    cps #18
	    mov lr, r0
	    mrs r1,cpsr
	    msr spsr_cxsf, r1 	    
	    ; Switch to Abort mode (M = 10111)
	    cps #23
	    mov lr, r0
	    mrs r1,cpsr
	    msr spsr_cxsf, r1 	    
	    ; Switch to Undefined Instruction Mode (M = 11011)
	    cps #27
	    mov lr, r0
	    mrs r1,cpsr
	    msr spsr_cxsf, r1 	    
	    ; Switch back to Supervisor Mode (M = 10011)
	    cps #19

		fmdrr d0,         r1,     r1
        fmdrr d1,         r1,     r1
        fmdrr d2,         r1,     r1
        fmdrr d3,         r1,     r1
        fmdrr d4,         r1,     r1
        fmdrr d5,         r1,     r1
        fmdrr d6,         r1,     r1
        fmdrr d7,         r1,     r1
        fmdrr d8,         r1,     r1
        fmdrr d9,         r1,     r1
        fmdrr d10,        r1,     r1
        fmdrr d11,        r1,     r1
        fmdrr d12,        r1,     r1
        fmdrr d13,        r1,     r1
        fmdrr d14,        r1,     r1
        fmdrr d15,        r1,     r1
        bl    next1
next1
        bl    next2
next2
        bl    next3
next3
        bl    next4
next4
        bx    r0

    .endasmfunc


;-------------------------------------------------------------------------------
; Initialize Stack Pointers

    .def     _coreInitStackPointer_
    .asmfunc

_coreInitStackPointer_

        cps   #17
        ldr   sp,       fiqSp
        cps   #18
        ldr   sp,       irqSp
        cps   #23
        ldr   sp,       abortSp
        cps   #27
        ldr   sp,       undefSp
        cps   #31
        ldr   sp,       userSp
        cps   #19
        ldr   sp,       svcSp
        bx    lr

userSp  .word 0x08000000+0x00001000
svcSp   .word 0x08000000+0x00001000+0x00000100
fiqSp   .word 0x08000000+0x00001000+0x00000100+0x00000100
irqSp   .word 0x08000000+0x00001000+0x00000100+0x00000100+0x00000100
abortSp .word 0x08000000+0x00001000+0x00000100+0x00000100+0x00000100+0x00000100
undefSp .word 0x08000000+0x00001000+0x00000100+0x00000100+0x00000100+0x00000100+0x00000100

    .endasmfunc


;-------------------------------------------------------------------------------
; Enable VFP Unit

    .def     _coreEnableVfp_
    .asmfunc

_coreEnableVfp_

        mrc   p15,     #0x00,      r0,       c1, c0, #0x02
        orr   r0,      r0,         #0xF00000
        mcr   p15,     #0x00,      r0,       c1, c0, #0x02
        mov   r0,      #0x40000000
        fmxr  fpexc,   r0
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Enable Event Bus Export

    .def     _coreEnableEventBusExport_
    .asmfunc

_coreEnableEventBusExport_

        mrc   p15, #0x00, r0,         c9, c12, #0x00
        orr   r0,  r0,    #0x10
        mcr   p15, #0x00, r0,         c9, c12, #0x00
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Disable Event Bus Export

    .def     _coreDisableEventBusExport_
    .asmfunc

_coreDisableEventBusExport_

        mrc   p15, #0x00, r0,         c9, c12, #0x00
        bic   r0,  r0,    #0x10
        mcr   p15, #0x00, r0,         c9, c12, #0x00
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Enable RAM ECC Support

    .def     _coreEnableRamEcc_
    .asmfunc

_coreEnableRamEcc_

        mrc   p15, #0x00, r0,         c1, c0,  #0x01
        orr   r0,  r0,    #0x0C000000
        mcr   p15, #0x00, r0,         c1, c0,  #0x01
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Disable RAM ECC Support

    .def     _coreDisableRamEcc_
    .asmfunc

_coreDisableRamEcc_

        mrc   p15, #0x00, r0,         c1, c0,  #0x01
        bic   r0,  r0,    #0x0C000000
        mcr   p15, #0x00, r0,         c1, c0,  #0x01
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Enable Flash ECC Support

    .def     _coreEnableFlashEcc_
    .asmfunc

_coreEnableFlashEcc_

        mrc   p15, #0x00, r0,         c1, c0,  #0x01
        orr   r0,  r0,    #0x02000000
        mcr   p15, #0x00, r0,         c1, c0,  #0x01
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Disable Flash ECC Support

    .def     _coreDisableFlashEcc_
    .asmfunc

_coreDisableFlashEcc_

        mrc   p15, #0x00, r0,         c1, c0,  #0x01
        bic   r0,  r0,    #0x02000000
        mcr   p15, #0x00, r0,         c1, c0,  #0x01
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Enable Offset via Vic controller

    .def     _coreEnableIrqVicOffset_
    .asmfunc

_coreEnableIrqVicOffset_

        mrc   p15, #0, r0,         c1, c0,  #0
        orr   r0,  r0,    #0x01000000
        mcr   p15, #0, r0,         c1, c0,  #0
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Get data fault status register

    .def     _coreGetDataFault_
    .asmfunc

_coreGetDataFault_

        mrc   p15, #0, r0, c5, c0,  #0
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Clear data fault status register

    .def     _coreClearDataFault_
    .asmfunc

_coreClearDataFault_

        mov   r0,  #0
        mcr   p15, #0, r0, c5, c0,  #0
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Get instruction fault status register

    .def     _coreGetInstructionFault_
    .asmfunc

_coreGetInstructionFault_

        mrc   p15, #0, r0, c5, c0, #1
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Clear instruction fault status register

    .def     _coreClearInstructionFault_
    .asmfunc

_coreClearInstructionFault_

        mov   r0,  #0
        mcr   p15, #0, r0, c5, c0, #1
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Get data fault address register

    .def     _coreGetDataFaultAddress_
    .asmfunc

_coreGetDataFaultAddress_

        mrc   p15, #0, r0, c6, c0,  #0
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Clear data fault address register

    .def     _coreClearDataFaultAddress_
    .asmfunc

_coreClearDataFaultAddress_

        mov   r0,  #0
        mcr   p15, #0, r0, c6, c0,  #0
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Get instruction fault address register

    .def     _coreGetInstructionFaultAddress_
    .asmfunc

_coreGetInstructionFaultAddress_

        mrc   p15, #0, r0, c6, c0, #2
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Clear instruction fault address register

    .def     _coreClearInstructionFaultAddress_
    .asmfunc

_coreClearInstructionFaultAddress_

        mov   r0,  #0
        mcr   p15, #0, r0, c6, c0, #2
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Get auxiliary data fault status register

    .def     _coreGetAuxiliaryDataFault_
    .asmfunc

_coreGetAuxiliaryDataFault_

        mrc   p15, #0, r0, c5, c1, #0
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Clear auxiliary data fault status register

    .def     _coreClearAuxiliaryDataFault_
    .asmfunc

_coreClearAuxiliaryDataFault_

        mov   r0,  #0
        mcr   p15, #0, r0, c5, c1, #0
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Get auxiliary instruction fault status register

    .def     _coreGetAuxiliaryInstructionFault_
    .asmfunc

_coreGetAuxiliaryInstructionFault_

        mrc   p15, #0, r0, c5, c1, #1
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Clear auxiliary instruction fault status register

    .def     _coreClearAuxiliaryInstructionFault_
    .asmfunc

_coreClearAuxiliaryInstructionFault_

        mov   r0,  #0
        mrc   p15, #0, r0, c5, c1, #1
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Disable interrupts

        .def _disable_interrupts
    
        .asmfunc
_disable_interrupts
            cpsid if
            bx    lr
        .endasmfunc


;-------------------------------------------------------------------------------
; Enable interrupts

       .def _enable_interrupts
    
        .asmfunc
_enable_interrupts
            cpsie if
            bx    lr
        .endasmfunc


;-------------------------------------------------------------------------------
; C++ construct table pointers

    .def    __TI_PINIT_Base, __TI_PINIT_Limit
    .weak   SHT$$INIT_ARRAY$$Base, SHT$$INIT_ARRAY$$Limit

__TI_PINIT_Base  .long SHT$$INIT_ARRAY$$Base
__TI_PINIT_Limit .long SHT$$INIT_ARRAY$$Limit

    

;-------------------------------------------------------------------------------

