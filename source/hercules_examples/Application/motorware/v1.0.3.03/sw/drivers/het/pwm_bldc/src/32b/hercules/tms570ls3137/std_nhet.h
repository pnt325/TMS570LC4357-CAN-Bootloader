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
/** @file std_nhet.h
*   @brief - NHET Instruction Definition File
*   @date 04.March.2010
*   @version 1.00.000
*   
*   (c) Texas Instruments 2009, All rights reserved.
*/

#ifndef __STD_NHET_H__
#define __STD_NHET_H__

#if defined(_TMS470_BIG) || defined(__big_endian__)

#ifndef HET_v2
#   define HET_v2 0
#endif

#ifndef HETBYTE
#   define HETBYTE unsigned char
#endif

typedef struct memory_format
{
  unsigned int program_word  ;
  unsigned int control_word  ;
  unsigned int data_word     ;
  unsigned int reserved_word ;
} HET_MEMORY  ;
 

/*---------------------------------------------*/
/* ACMP INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct acmp_format
{
  unsigned int                      : 6 ;
  unsigned int reqnum               : 3 ;
  unsigned int brk                  : 1 ;
  unsigned int next_program_address : 9 ;
  unsigned int op_code              : 4 ;
  unsigned int                      : 9 ;

  unsigned int                      : 3 ;
  unsigned int request              : 2 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int coutprv              : 1 ;
  unsigned int                      : 2 ;
  unsigned int en_pin_action        : 1 ;
  unsigned int cond_addr            : 9 ;
  unsigned int pin_select           : 5 ;
  unsigned int ext_reg              : 1 ;
  unsigned int                      : 2 ; 
  unsigned int pin_action           : 1 ;
  unsigned int                      : 1 ;
  unsigned int t_register_select    : 1 ;
  unsigned int ab_register_select   : 1 ;
  unsigned int interrupt_enable     : 1 ;
 
  unsigned int data                 : 25 ;
  unsigned int                      : 7  ;
 
} ACMP_FIELDS;
 
typedef union
{
  ACMP_FIELDS  acmp   ;
  HET_MEMORY   memory ;
} ACMP_INSTRUCTION;


/*---------------------------------------------*/
/* ECMP INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct ecmp_format   
{
  unsigned int                      : 6 ;
  unsigned int reqnum               : 3 ;
  unsigned int brk                  : 1 ;          
  unsigned int next_program_address : 9 ;          
  unsigned int op_code              : 4 ;
  unsigned int hr_lr                : 1 ;
  unsigned int angle_compare        : 1 ;
  unsigned int                      : 7 ;

  unsigned int                      : 3 ;
  unsigned int request              : 2 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int                      : 3 ;
  unsigned int en_pin_action        : 1 ;
  unsigned int cond_addr            : 9 ;
  unsigned int pin_select           : 5 ;
  unsigned int                      : 1 ;
  unsigned int sub_opcode           : 2 ;
  unsigned int pin_action           : 1 ;
  unsigned int opposite_action      : 1 ;
  unsigned int t_register_select    : 1 ;
  unsigned int ab_register_select   : 1 ;
  unsigned int interrupt_enable     : 1 ;

  
  unsigned int data                 : 25 ;
  unsigned int hr_data              : 7 ;

} ECMP_FIELDS;

typedef union 
{
  ECMP_FIELDS  ecmp   ;
  HET_MEMORY   memory ;
} ECMP_INSTRUCTION;


/*---------------------------------------------*/
/* SCMP INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct scmp_format     
{
  unsigned int                      : 6 ;
  unsigned int reqnum               : 3 ;
  unsigned int brk                  : 1 ;          
  unsigned int next_program_address : 9 ;          
  unsigned int op_code              : 4 ;
  unsigned int                      : 2 ;
  unsigned int                      : 2 ;
  unsigned int                      : 5 ;

  unsigned int                      : 3 ;
  unsigned int request              : 2 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int coutprv              : 1 ;
  unsigned int                      : 2 ;
  unsigned int en_pin_action        : 1 ;
  unsigned int cond_addr            : 9 ;
  unsigned int pin_select           : 5 ;
  unsigned int                      : 1 ;
  unsigned int compare_mode         : 2 ;
  unsigned int pin_action           : 1 ;
  unsigned int                      : 2 ;
  unsigned int restart_en           : 1 ;
  unsigned int interrupt_enable     : 1 ;

  
  unsigned int data                 : 25 ;
  unsigned int                      : 7 ;

} SCMP_FIELDS ;

typedef union 
{
  SCMP_FIELDS  scmp   ;
  HET_MEMORY   memory ;
} SCMP_INSTRUCTION;


/*---------------------------------------------*/
/* MCMP INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct mcmp_format                     
{
  unsigned int                      : 6 ;
  unsigned int reqnum               : 3 ;
  unsigned int brk                  : 1 ;
  unsigned int next_program_address : 9 ;
  unsigned int op_code              : 4 ;
  unsigned int hr_lr                : 1 ;
  unsigned int angle_compare        : 1 ;
  unsigned int                      : 1 ;
  unsigned int save_subtract        : 1 ;
  unsigned int                      : 5 ;
 
  unsigned int                      : 3 ;
  unsigned int request              : 2 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int                      : 3 ;
  unsigned int en_pin_action        : 1 ;
  unsigned int cond_addr            : 9 ;
  unsigned int pin_select           : 5 ;
  unsigned int                      : 1 ;
  unsigned int sub_opcode           : 1 ; 
  unsigned int order                : 1 ; 
  unsigned int pin_action           : 1 ;
  unsigned int opposite_action      : 1 ;
  unsigned int t_register_select    : 1 ;
  unsigned int ab_register_select   : 1 ;
  unsigned int interrupt_enable     : 1 ;
 
  
  unsigned int data                 : 25 ;
  unsigned int hr_data              : 7 ;
 
} MCMP_FIELDS ; 

typedef union 
{
  MCMP_FIELDS  mcmp   ;
  HET_MEMORY   memory ;
} MCMP_INSTRUCTION;


/*---------------------------------------------*/
/* MOV64 INSTRUCTION                           */
/*---------------------------------------------*/
typedef struct mov64_format                     
{
  unsigned int                      : 9 ;
  unsigned int brk                  : 1 ;
  unsigned int next_program_address : 9 ;          
  unsigned int op_code              : 4 ;
  unsigned int remote_address       : 9 ;

  unsigned int                      : 3 ;
  unsigned int request              : 2 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int                      : 3 ;
  unsigned int en_pin_action        : 1 ;
  unsigned int cond_addr            : 9 ;
  unsigned int pin_select           : 5 ;
  unsigned int                      : 1 ;
  unsigned int compare_mode         : 2 ;
  unsigned int pin_action           : 1 ;
  unsigned int opposite_action      : 1 ;
  unsigned int t_register_select    : 1 ;
  unsigned int ab_register_select   : 1 ;
  unsigned int interrupt_enable     : 1 ;
 
  
  unsigned int data                 : 25 ;
  unsigned int hr_data              : 7 ;

} MOV64_FIELDS ; 

typedef union 
{
  MOV64_FIELDS  mov64  ;
  HET_MEMORY    memory ;
} MOV64_INSTRUCTION;


/*---------------------------------------------*/
/* DADM64 INSTRUCTION                          */
/*---------------------------------------------*/
typedef struct dadm64_format                     
{
  unsigned int                      : 9 ;
  unsigned int brk                  : 1 ;
  unsigned int next_program_address : 9 ;
  unsigned int op_code              : 4 ;
  unsigned int remote_address       : 9 ;
 
  unsigned int                      : 3 ;
  unsigned int request              : 2 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int                      : 3 ;
  unsigned int en_pin_action        : 1 ;
  unsigned int cond_addr            : 9 ;
  unsigned int pin_select           : 5 ;
  unsigned int                      : 1 ;
  unsigned int compare_mode         : 2 ;
  unsigned int pin_action           : 1 ;
  unsigned int opposite_action      : 1 ;
  unsigned int t_register_select    : 1 ;
  unsigned int ab_register_select   : 1 ;
  unsigned int interrupt_enable     : 1 ;
 
  
  unsigned int data                 : 25 ;
  unsigned int hr_data              : 7 ;
 
} DADM64_FIELDS ; 

typedef union 
{
  DADM64_FIELDS  dadm64 ;
  HET_MEMORY     memory ;
} DADM64_INSTRUCTION;


/*---------------------------------------------*/
/* RADM64 INSTRUCTION                          */
/*---------------------------------------------*/
typedef struct RADM64_format                     
{
  unsigned int                      : 9 ;
  unsigned int brk                  : 1 ;
  unsigned int next_program_address : 9 ;
  unsigned int op_code              : 4 ;
  unsigned int remote_address       : 9 ;
 
  unsigned int                      : 3 ;
  unsigned int request              : 2 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int                      : 3 ;
  unsigned int en_pin_action        : 1 ;
  unsigned int cond_addr            : 9 ;
  unsigned int pin_select           : 5 ;
  unsigned int                      : 1 ;
  unsigned int compare_mode         : 2 ;
  unsigned int pin_action           : 1 ;
  unsigned int opposite_action      : 1 ;
  unsigned int t_register_select    : 1 ;
  unsigned int ab_register_select   : 1 ;
  unsigned int interrupt_enable     : 1 ;
 
  
  unsigned int data                 : 25 ;
  unsigned int hr_data              : 7 ;
 
} RADM64_FIELDS ; 


typedef union 
{
  RADM64_FIELDS  radm64 ;
  HET_MEMORY     memory ;
} RADM64_INSTRUCTION;


/*---------------------------------------------*/
/* MOV32 INSTRUCTION                           */
/*---------------------------------------------*/
typedef struct MOV32_format                     
{
  unsigned int                      : 9 ;
  unsigned int brk                  : 1 ;
  unsigned int next_program_address : 9 ;
  unsigned int op_code              : 4 ;
  unsigned int remote_address       : 9 ;
 
  unsigned int                      : 5 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int                      : 3 ;
  unsigned int z_flag               : 1 ;
  unsigned int                      : 15 ;
  unsigned int init_flag            : 1 ;
  unsigned int sub_opcode           : 1 ;   
  unsigned int move_type            : 2 ;     
  unsigned int t_register_select    : 1 ;
  unsigned int ab_register_select   : 1 ;
  unsigned int                      : 1 ;
 
  
  unsigned int data                 : 25 ;
  unsigned int hr_data              : 7 ;
 
} MOV32_FIELDS ; 


typedef union 
{
  MOV32_FIELDS  mov32  ;
  HET_MEMORY    memory ;
} MOV32_INSTRUCTION;


/*---------------------------------------------*/
/* ADM32 INSTRUCTION                           */
/*---------------------------------------------*/
typedef struct ADM32_format                     
{
  unsigned int                      : 9 ;
  unsigned int brk                  : 1 ;
  unsigned int next_program_address : 9 ;
  unsigned int op_code              : 4 ;
  unsigned int remote_address       : 9 ;
 
  unsigned int                      : 5 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int                      : 19 ;
  unsigned int init_flag            : 1 ;
  unsigned int sub_opcode           : 1 ;
  unsigned int move_type            : 2 ;
  unsigned int t_register_select    : 1 ;
  unsigned int ab_register_select   : 1 ;
  unsigned int                      : 1 ;
 
  
  unsigned int data                 : 25 ;
  unsigned int hr_data              : 7 ;
 
} ADM32_FIELDS ; 


typedef union 
{
  ADM32_FIELDS  adm32  ;
  HET_MEMORY    memory ;
} ADM32_INSTRUCTION;


/*---------------------------------------------*/
/* ADCNST INSTRUCTION                          */
/*---------------------------------------------*/
typedef struct ADCNST_format                     
{
  unsigned int                      : 9 ;
  unsigned int brk                  : 1 ;
  unsigned int next_program_address : 9 ;
  unsigned int op_code              : 4 ;
  unsigned int remote_address       : 9 ;
 
  unsigned int                      : 5 ;
  unsigned int control              : 1 ;  /* pk */
  unsigned int                      : 1 ;
  unsigned int constant             : 25 ;
 
  
  unsigned int data                 : 25 ;
  unsigned int hr_data              : 7 ;
 
} ADCNST_FIELDS ;


typedef union 
{
  ADCNST_FIELDS  adcnst ;
  HET_MEMORY     memory ;
} ADCNST_INSTRUCTION;


/*----------------------------------------------*/
/* ADD INSTRUCTION				  	*/
/*----------------------------------------------*/

typedef struct ADD_format                     
{
  unsigned int                      : 9 ;
  unsigned int brk                  : 1 ;
  unsigned int next_program_address : 9 ;
  unsigned int op_code              : 4 ;
  unsigned int remote_address       : 9 ;
 
  unsigned int                      : 5 ;
  unsigned int control              : 1;
  unsigned int sub_opcode3          : 3 ;
  unsigned int src_1                : 4 ;
  unsigned int src_2                : 3 ;
  unsigned int shft_mode            : 3 ;
  unsigned int shft_cnt             : 5 ;
  unsigned int reg_ext              : 1 ;
  unsigned int init_flag            : 1 ;
  unsigned int sub_opcode1          : 1 ;
  unsigned int rem_dest             : 2 ;
  unsigned int reg	                : 2 ;
  unsigned int                      : 1 ;
 
  
  unsigned int data                 : 25 ;
  unsigned int hr_data              : 7 ;
 
} ADD_FIELDS ;


typedef union 
{
  ADD_FIELDS  add ;
  HET_MEMORY  memory ;
} ADD_INSTRUCTION;



/*----------------------------------------------*/
/* ADC INSTRUCTION					*/
/*----------------------------------------------*/

typedef struct ADC_format                     
{
  unsigned int                      : 9 ;
  unsigned int brk                  : 1 ;
  unsigned int next_program_address : 9 ;
  unsigned int op_code              : 4 ;
  unsigned int remote_address       : 9 ;
 
  unsigned int                      : 5 ;
  unsigned int control              : 1;
  unsigned int sub_opcode3          : 3 ;
  unsigned int src_1                : 4 ;
  unsigned int src_2                : 3 ;
  unsigned int shft_mode            : 3 ;
  unsigned int shft_cnt             : 5 ;
  unsigned int reg_ext              : 1 ;
  unsigned int init_flag            : 1 ;
  unsigned int sub_opcode1          : 1 ;
  unsigned int rem_dest             : 2 ;
  unsigned int reg	                : 2 ;
  unsigned int                      : 1 ;
 
  
  unsigned int data                 : 25 ;
  unsigned int hr_data              : 7 ;
 
} ADC_FIELDS ;


typedef union 
{
  ADC_FIELDS  adc ;
  HET_MEMORY  memory ;
} ADC_INSTRUCTION;



/*----------------------------------------------*/
/* SUB INSTRUCTION					*/
/*----------------------------------------------*/

typedef struct SUB_format                     
{
  unsigned int                      : 9 ;
  unsigned int brk                  : 1 ;
  unsigned int next_program_address : 9 ;
  unsigned int op_code              : 4 ;
  unsigned int remote_address       : 9 ;
 
  unsigned int                      : 5 ;
  unsigned int control              : 1;
  unsigned int sub_opcode3          : 3 ;
  unsigned int src_1                : 4 ;
  unsigned int src_2                : 3 ;
  unsigned int shft_mode            : 3 ;
  unsigned int shft_cnt             : 5 ;
  unsigned int reg_ext              : 1 ;
  unsigned int init_flag            : 1 ;
  unsigned int sub_opcode1          : 1 ;
  unsigned int rem_dest             : 2 ;
  unsigned int reg	                : 2 ;
  unsigned int                      : 1 ;
 
  
  unsigned int data                 : 25 ;
  unsigned int hr_data              : 7 ;
 
} SUB_FIELDS ;


typedef union 
{
  SUB_FIELDS  sub ;
  HET_MEMORY  memory ;
} SUB_INSTRUCTION;



/*----------------------------------------------*/
/* SBB INSTRUCTION					*/
/*----------------------------------------------*/

typedef struct SBB_format                     
{
  unsigned int                      : 9 ;
  unsigned int brk                  : 1 ;
  unsigned int next_program_address : 9 ;
  unsigned int op_code              : 4 ;
  unsigned int remote_address       : 9 ;
 
  unsigned int                      : 5 ;
  unsigned int control              : 1;
  unsigned int sub_opcode3          : 3 ;
  unsigned int src_1                : 4 ;
  unsigned int src_2                : 3 ;
  unsigned int shft_mode            : 3 ;
  unsigned int shft_cnt             : 5 ;
  unsigned int reg_ext              : 1 ;
  unsigned int init_flag            : 1 ;
  unsigned int sub_opcode1          : 1 ;
  unsigned int rem_dest             : 2 ;
  unsigned int reg	                : 2 ;
  unsigned int                      : 1 ;
 
  
  unsigned int data                 : 25 ;
  unsigned int hr_data              : 7 ;
 
} SBB_FIELDS ;


typedef union 
{
  SBB_FIELDS  sbb ;
  HET_MEMORY  memory ;
} SBB_INSTRUCTION;



/*----------------------------------------------*/
/* AND INSTRUCTION				      */
/*----------------------------------------------*/

typedef struct AND_format
{
  unsigned int                      : 9 ;
  unsigned int brk                  : 1 ;
  unsigned int next_program_address : 9 ;
  unsigned int op_code              : 4 ;
  unsigned int remote_address       : 9 ;
 
  unsigned int                      : 5 ;
  unsigned int control              : 1;
  unsigned int sub_opcode3          : 3 ;
  unsigned int src_1                : 4 ;
  unsigned int src_2                : 3 ;
  unsigned int shft_mode            : 3 ;
  unsigned int shft_cnt             : 5 ;
  unsigned int reg_ext              : 1 ;
  unsigned int init_flag            : 1 ;
  unsigned int sub_opcode1          : 1 ;
  unsigned int rem_dest             : 2 ;
  unsigned int reg	                : 2 ;
  unsigned int                      : 1 ;
 
  
  unsigned int data                 : 25 ;
  unsigned int hr_data              : 7 ;
 
} AND_FIELDS ;


typedef union 
{
  AND_FIELDS  and ;
  HET_MEMORY  memory ;
} AND_INSTRUCTION;



/*----------------------------------------------*/
/* OR INSTRUCTION					      */
/*----------------------------------------------*/


typedef struct OR_format
{
  unsigned int                      : 9 ;
  unsigned int brk                  : 1 ;
  unsigned int next_program_address : 9 ;
  unsigned int op_code              : 4 ;
  unsigned int remote_address       : 9 ;
 
  unsigned int                      : 5 ;
  unsigned int control              : 1;
  unsigned int sub_opcode3          : 3 ;
  unsigned int src_1                : 4 ;
  unsigned int src_2                : 3 ;
  unsigned int shft_mode            : 3 ;
  unsigned int shft_cnt             : 5 ;
  unsigned int reg_ext              : 1 ;
  unsigned int init_flag            : 1 ;
  unsigned int sub_opcode1          : 1 ;
  unsigned int rem_dest             : 2 ;
  unsigned int reg	                : 2 ;
  unsigned int                      : 1 ;
 
  
  unsigned int data                 : 25 ;
  unsigned int hr_data              : 7 ;
 
} OR_FIELDS ;


typedef union 
{
  OR_FIELDS  or ;
  HET_MEMORY  memory ;
} OR_INSTRUCTION;



/*----------------------------------------------*/
/* XOR INSTRUCTION					*/
/*----------------------------------------------*/

typedef struct XOR_format                     
{
  unsigned int                      : 9 ;
  unsigned int brk                  : 1 ;
  unsigned int next_program_address : 9 ;
  unsigned int op_code              : 4 ;
  unsigned int remote_address       : 9 ;
 
  unsigned int                      : 5 ;
  unsigned int control              : 1;
  unsigned int sub_opcode3          : 3 ;
  unsigned int src_1                : 4 ;
  unsigned int src_2                : 3 ;
  unsigned int shft_mode            : 3 ;
  unsigned int shft_cnt             : 5 ;
  unsigned int reg_ext              : 1 ;
  unsigned int init_flag            : 1 ;
  unsigned int sub_opcode1          : 1 ;
  unsigned int rem_dest             : 2 ;
  unsigned int reg	                : 2 ;
  unsigned int                      : 1 ;
 
  
  unsigned int data                 : 25 ;
  unsigned int hr_data              : 7 ;
 
} XOR_FIELDS ;


typedef union 
{
  XOR_FIELDS  xor ;
  HET_MEMORY  memory ;
} XOR_INSTRUCTION;



/*---------------------------------------------*/
/* CNT INSTRUCTION                             */
/*---------------------------------------------*/
typedef struct CNT_format                     
{
  unsigned int                      : 9 ;        
  unsigned int brk                  : 1 ;          
  unsigned int next_program_address : 9 ;          
  unsigned int op_code              : 4 ;
  unsigned int angle_cnt            : 1 ;
  unsigned int t_register_select    : 1 ;
  unsigned int ab_register_select   : 1 ;
  unsigned int                      : 4 ;
  unsigned int interrupt_enable     : 1 ;
 

  unsigned int                      : 3 ;
  unsigned int request              : 2 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int                      : 1 ;
  unsigned int max                  : 25 ;

  
  unsigned int data                 : 25 ;
  unsigned int                      : 7 ;

} CNT_FIELDS ; 

typedef union 
{
  CNT_FIELDS   cnt    ; 
  HET_MEMORY   memory ;
} CNT_INSTRUCTION;


/*---------------------------------------------*/
/* APCNT INSTRUCTION                           */
/*---------------------------------------------*/
typedef struct apcnt_format
{
  unsigned int                      : 6 ;
  unsigned int reqnum               : 3 ;
  unsigned int brk                  : 1 ;
  unsigned int next_program_address : 9 ;
  unsigned int op_code              : 4 ;
  unsigned int interrupt_enable     : 1 ;
  unsigned int edge_select          : 2 ;
  unsigned int                      : 6 ;

  unsigned int                      : 3 ;
  unsigned int request              : 2 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int previous_bit         : 1 ;
  unsigned int count                : 25 ;
 
  
  unsigned int data                 : 25 ;
  unsigned int                      : 7 ;
 
} APCNT_FIELDS ;
 
typedef union
{
  APCNT_FIELDS  apcnt   ;
  HET_MEMORY   memory ;
} APCNT_INSTRUCTION;
 
 

/*---------------------------------------------*/
/* PCNT INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct pcnt_format                     
{
  unsigned int                      : 6 ;
  unsigned int reqnum               : 3 ;
  unsigned int brk                  : 1 ;          
  unsigned int next_program_address : 9 ;          
  unsigned int op_code              : 4 ;
  unsigned int interrupt_enable     : 1 ;
  unsigned int period_pulse_select  : 2 ;
  unsigned int                      : 1 ;
  unsigned int pin_select           : 5 ;

  unsigned int                      : 3 ;
  unsigned int request              : 2 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int previous_bit         : 1 ;
  unsigned int count                : 25 ;

  
  unsigned int data                 : 25 ;
  unsigned int hr_data              : 7 ;

} PCNT_FIELDS ;      

typedef union 
{
  PCNT_FIELDS  pcnt   ; 
  HET_MEMORY   memory ;
} PCNT_INSTRUCTION;


/*---------------------------------------------*/
/* SCNT INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct scnt_format                     
{
  unsigned int                      : 9 ;
  unsigned int brk                  : 1 ;
  unsigned int next_program_address : 9 ;
  unsigned int op_code              : 4 ;
  unsigned int                      : 1 ;
  unsigned int count_mode           : 2 ;
  unsigned int step_width           : 2 ;
  unsigned int                      : 4 ;

  unsigned int                      : 5 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int                      : 1 ;
  unsigned int gap_start            : 25 ;

  
  unsigned int data                 : 25 ;
  unsigned int                      : 7 ;

} SCNT_FIELDS ;      

typedef union 
{
  SCNT_FIELDS  scnt   ; 
  HET_MEMORY   memory ;
} SCNT_INSTRUCTION;



/*---------------------------------------------*/
/* ACNT INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct acnt_format                     
{
  unsigned int                      : 6 ;
  unsigned int reqnum               : 3 ;
  unsigned int brk                  : 1 ;
  unsigned int next_program_address : 9 ;          
  unsigned int op_code              : 4 ;
  unsigned int edge_select          : 1 ;
  unsigned int                      : 7 ;
  unsigned int interrupt_enable     : 1 ; 

  unsigned int                      : 3 ;
  unsigned int request              : 2 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int previous_bit         : 1 ;
  unsigned int gap_end              : 25 ;
 
  
  unsigned int data                 : 25 ;
  unsigned int                      : 7 ;

} ACNT_FIELDS ;      

typedef union 
{
  ACNT_FIELDS  acnt   ; 
  HET_MEMORY   memory ;
} ACNT_INSTRUCTION;


/*---------------------------------------------*/
/* ECNT INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct ecnt_format
{
  unsigned int                      : 6 ;
  unsigned int reqnum               : 3 ;
  unsigned int brk                  : 1 ;
  unsigned int next_program_address : 9 ;
  unsigned int op_code              : 4 ;
  unsigned int                      : 1 ;
  unsigned int count_mode           : 2 ;
  unsigned int                      : 6 ;
 
  unsigned int                      : 3 ;
  unsigned int request              : 2 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int previous_bit         : 1 ;
  unsigned int                      : 3 ;
  unsigned int cond_addr            : 9 ;
  unsigned int pin_select           : 5 ;
  unsigned int                      : 1 ;
  unsigned int count_cond           : 3 ;
  unsigned int                      : 1 ;
  unsigned int t_register_select    : 1 ;
  unsigned int ab_register_select   : 1 ;
  unsigned int interrupt_enable     : 1 ;

  
  unsigned int data                 : 25 ;
  unsigned int                      : 7 ;
 
} ECNT_FIELDS ;
 
typedef union
{
  ECNT_FIELDS  ecnt   ;
  HET_MEMORY   memory ;
} ECNT_INSTRUCTION;



/*---------------------------------------------*/
/* RCNT INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct rcnt_format
{
  unsigned int                      : 6 ;
  unsigned int reqnum               : 3 ;
  unsigned int brk                  : 1 ;
  unsigned int next_program_address : 9 ;
  unsigned int op_code              : 4 ;
  unsigned int                      : 1 ;
  unsigned int count_mode           : 2 ;
  unsigned int                      : 5 ;
  unsigned int count_mode1          : 1 ;
 
  unsigned int                      : 3 ;
  unsigned int                      : 2 ;
  unsigned int control              : 1 ;
  unsigned int                      : 1 ;
  unsigned int divisor              : 25 ;

  
  unsigned int data                 : 25 ;
  unsigned int                      : 7 ;
 
} RCNT_FIELDS ;
 
typedef union
{
  RCNT_FIELDS  rcnt   ;
  HET_MEMORY   memory ;
} RCNT_INSTRUCTION;


/*---------------------------------------------*/
/* DJNZ INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct djnz_format                     
{
  unsigned int                      : 6 ;
  unsigned int reqnum               : 3 ;
  unsigned int brk                  : 1 ;
  unsigned int next_program_address : 9 ;          
  unsigned int op_code              : 4 ;
  unsigned int                      : 1 ;
  unsigned int sub_opcode           : 2 ;
  unsigned int                      : 6 ;

  unsigned int                      : 3 ;
  unsigned int request              : 2 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int                      : 4 ;
  unsigned int cond_addr            : 9 ;
  unsigned int                      : 10 ;
  unsigned int t_register_select    : 1 ;
  unsigned int ab_register_select   : 1 ;
  unsigned int interrupt_enable     : 1 ;

  
  unsigned int data                 : 25 ;
  unsigned int                      : 7 ;

} DJNZ_FIELDS ;      

typedef union 
{
  DJNZ_FIELDS  djnz   ; 
  HET_MEMORY   memory ;
} DJNZ_INSTRUCTION;


/*---------------------------------------------*/
/* DJZ INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct djz_format                     
{
  unsigned int                      : 6 ;
  unsigned int reqnum               : 3 ;
  unsigned int brk                  : 1 ;
  unsigned int next_program_address : 9 ;          
  unsigned int op_code              : 4 ;
  unsigned int                      : 1 ;
  unsigned int sub_opcode           : 2 ;
  unsigned int                      : 6 ;

  unsigned int                      : 3 ;
  unsigned int request              : 2 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int                      : 4 ;
  unsigned int cond_addr            : 9 ;
  unsigned int                      : 10 ;
  unsigned int t_register_select    : 1 ;
  unsigned int ab_register_select   : 1 ;
  unsigned int interrupt_enable     : 1 ;

  
  unsigned int data                 : 25 ;
  unsigned int                      : 7 ;

} DJZ_FIELDS ;      

typedef union 
{
  DJZ_FIELDS  djz   ; 
  HET_MEMORY   memory ;
} DJZ_INSTRUCTION;

/*---------------------------------------------*/
/* PWCNT INSTRUCTION                           */
/*---------------------------------------------*/
typedef struct pwcnt_format                     
{
  unsigned int                      : 6 ;
  unsigned int reqnum               : 3 ;
  unsigned int brk                  : 1 ;
  unsigned int next_program_address : 9 ;
  unsigned int op_code              : 4 ;
  unsigned int hr_lr                : 1 ;
  unsigned int count_mode           : 2 ;
  unsigned int                      : 6 ;

  unsigned int                      : 3 ;
  unsigned int request              : 2 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int                      : 3 ;
  unsigned int en_pin_action        : 1 ;
  unsigned int cond_addr            : 9 ;
  unsigned int pin_select           : 5 ;
  unsigned int                      : 3 ;
  unsigned int pin_action           : 1 ;
  unsigned int opposite_action      : 1 ;
  unsigned int t_register_select    : 1 ;
  unsigned int ab_register_select   : 1 ;
  unsigned int interrupt_enable     : 1 ;

  
  unsigned int data                 : 25 ;
  unsigned int hr_data              : 7 ;
 
} PWCNT_FIELDS ;      

typedef union 
{
  PWCNT_FIELDS  pwcnt ;
  HET_MEMORY   memory ;
} PWCNT_INSTRUCTION;


/*---------------------------------------------*/
/* WCAP INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct wcap_format                     
{
  unsigned int                      : 6 ;
  unsigned int reqnum               : 3 ;
  unsigned int brk                  : 1 ;
  unsigned int next_program_address : 9 ;
  unsigned int op_code              : 4 ;
  unsigned int hr_lr                : 1 ;
  unsigned int                      : 8 ;
  
  unsigned int                      : 3 ;
  unsigned int request              : 2 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int previous_bit         : 1 ;
  unsigned int                      : 3 ;
  unsigned int cond_addr            : 9 ;
  unsigned int pin_select           : 5 ;
  unsigned int                      : 1 ;
  unsigned int capture_condition    : 2 ;
  unsigned int                      : 2 ;
  unsigned int t_register_select    : 1 ;
  unsigned int ab_register_select   : 1 ;
  unsigned int interrupt_enable     : 1 ;

  
  unsigned int data                 : 25 ;
  unsigned int hr_data              : 7 ;

} WCAP_FIELDS ;      

typedef union 
{
  WCAP_FIELDS  wcap   ; 
  HET_MEMORY   memory ;
} WCAP_INSTRUCTION;
 
/*----------------------------------------------*/
/* WCAPE INSTRUCTION                            */
/*----------------------------------------------*/
typedef struct wcape_format                     
{
  unsigned int                      : 6 ;
  unsigned int reqnum               : 3 ;
  unsigned int brk                  : 1 ;
  unsigned int next_program_address : 9 ;
  unsigned int op_code              : 4 ;
  unsigned int                      : 9 ;
  
  unsigned int                      : 3 ;
  unsigned int request              : 2 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int previous_bit         : 1 ;
  unsigned int                      : 3 ;
  unsigned int cond_addr            : 9 ;
  unsigned int pin_select           : 5 ;
  unsigned int                      : 1 ;
  unsigned int capture_condition    : 2 ;
  unsigned int                      : 2 ;
  unsigned int t_register_select    : 1 ;
  unsigned int ab_register_select   : 1 ;
  unsigned int interrupt_enable     : 1 ;

  
  unsigned int ts_data              : 25 ;
  unsigned int ec_data              : 7 ;

} WCAPE_FIELDS ;      

typedef union 
{
  WCAPE_FIELDS  wcape   ; 
  HET_MEMORY   memory ;
} WCAPE_INSTRUCTION;
 

/*---------------------------------------------*/
/* BR   INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct br_format                     
{
  unsigned int                      : 6 ;
  unsigned int reqnum               : 3 ;
  unsigned int brk                  : 1 ;
  unsigned int next_program_address : 9 ;
  unsigned int op_code              : 4 ;
  unsigned int                      : 9 ;

  unsigned int                      : 3 ;
  unsigned int request              : 2 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int previous_bit         : 1 ;
  unsigned int                      : 3 ;
  unsigned int cond_addr            : 9 ;
  unsigned int pin_select           : 5 ;

#if HET_v2
  unsigned int branch_condition     : 5 ;
#else 
  unsigned int branch_condition     : 3 ;
  unsigned int                      : 1 ;
  unsigned int                      : 1 ;
#endif 

  unsigned int                      : 2 ;
  unsigned int interrupt_enable     : 1 ;
 
  
  unsigned int data                 : 25 ;
  unsigned int hr_data              : 7 ;
 
} BR_FIELDS ;      

typedef union 
{
  BR_FIELDS  br     ; 
  HET_MEMORY memory ;
} BR_INSTRUCTION;

 
/*---------------------------------------------*/
/* SHFT INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct shft_format                     
{
  unsigned int                      : 6 ;
  unsigned int reqnum               : 3 ;
  unsigned int brk                  : 1 ;
  unsigned int next_program_address : 9 ;
  unsigned int op_code              : 4 ;
  unsigned int                      : 5 ;
  unsigned int shift_mode           : 4 ;
 
  unsigned int                      : 3 ;
  unsigned int request              : 2 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int previous_bit         : 1 ;
  unsigned int                      : 3 ;
  unsigned int cond_addr            : 9 ;
  unsigned int pin_select           : 5 ;
  unsigned int                      : 1 ;
  unsigned int shift_condition      : 2 ;
  unsigned int                      : 2 ;
  unsigned int t_register_select    : 1 ;
  unsigned int ab_register_select   : 1 ;
  unsigned int interrupt_enable     : 1 ;

  
  unsigned int data                 : 25 ;
  unsigned int                      : 7 ;

} SHFT_FIELDS ;      

typedef union 
{
  SHFT_FIELDS  shft   ; 
  HET_MEMORY   memory ;
} SHFT_INSTRUCTION;

/* ---------------------------------------------------------------------------------------------------- */

#elif defined(_TMS470_LITTLE) || defined(__little_endian__)

#ifndef HETBYTE
#   define HETBYTE unsigned char
#endif

typedef struct memory_format
{
  unsigned int program_word  ;
  unsigned int control_word  ;
  unsigned int data_word     ;
  unsigned int reserved_word ;
} HET_MEMORY  ;
 
/*---------------------------------------------*/
/* ACMP INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct acmp_format
{
  unsigned int                      : 9 ;
  unsigned int op_code              : 4 ;
  unsigned int next_program_address : 9 ;
  unsigned int brk                  : 1 ;
  unsigned int reqnum               : 3 ;
  unsigned int                      : 6 ;

  unsigned int interrupt_enable     : 1 ;
  unsigned int ab_register_select   : 1 ;
  unsigned int t_register_select    : 1 ;
  unsigned int                      : 1 ;
  unsigned int pin_action           : 1 ;
  unsigned int                      : 3 ;
  unsigned int pin_select           : 5 ;
  unsigned int cond_addr            : 9 ; 
  unsigned int en_pin_action        : 1 ;
  unsigned int                      : 2 ;
  unsigned int coutprv              : 1 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int request              : 2 ;
  unsigned int                      : 3 ; 

  unsigned int                      : 7  ;
  unsigned int data                 : 25 ;
 
} ACMP_FIELDS;
 
typedef union
{
  ACMP_FIELDS  acmp   ;
  HET_MEMORY   memory ;
} ACMP_INSTRUCTION;


/*---------------------------------------------*/
/* ECMP INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct ecmp_format   
{
  unsigned int                      : 7 ;
  unsigned int angle_compare        : 1 ;
  unsigned int hr_lr                : 1 ;         
  unsigned int op_code              : 4 ;
  unsigned int next_program_address : 9 ;
  unsigned int brk                  : 1 ; 
  unsigned int reqnum               : 3 ;
  unsigned int                      : 6 ;

  unsigned int interrupt_enable     : 1 ;
  unsigned int ab_register_select   : 1 ;
  unsigned int t_register_select    : 1 ;
  unsigned int opposite_action      : 1 ;
  unsigned int pin_action           : 1 ;
  unsigned int sub_opcode           : 2 ;
  unsigned int                      : 1 ;
  unsigned int pin_select           : 5 ;
  unsigned int cond_addr            : 9 ;
  unsigned int en_pin_action        : 1 ;
  unsigned int                      : 3 ;
  unsigned int auto_read_clear      : 1 ; 
  unsigned int request              : 2 ;
  unsigned int                      : 3 ;
  
  unsigned int hr_data              : 7 ;
  unsigned int data                 : 25 ;

} ECMP_FIELDS;

typedef union 
{
  ECMP_FIELDS  ecmp   ;
  HET_MEMORY   memory ;
} ECMP_INSTRUCTION;


/*---------------------------------------------*/
/* SCMP INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct scmp_format     
{
  unsigned int                      : 5 ;
  unsigned int                      : 2 ;
  unsigned int                      : 2 ;         
  unsigned int op_code              : 4 ;
  unsigned int next_program_address : 9 ;
  unsigned int brk                  : 1 ; 
  unsigned int reqnum               : 3 ;
  unsigned int                      : 6 ;

  unsigned int interrupt_enable     : 1 ;
  unsigned int restart_en           : 1 ;
  unsigned int                      : 2 ;
  unsigned int pin_action           : 1 ;
  unsigned int compare_mode         : 2 ;
  unsigned int                      : 1 ;
  unsigned int pin_select           : 5 ;
  unsigned int cond_addr            : 9 ;
  unsigned int en_pin_action        : 1 ;
  unsigned int                      : 2 ;
  unsigned int coutprv              : 1 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int request              : 2 ;
  unsigned int                      : 3 ;
  
  unsigned int                      : 7 ;
  unsigned int data                 : 25 ;

} SCMP_FIELDS ;

typedef union 
{
  SCMP_FIELDS  scmp   ;
  HET_MEMORY   memory ;
} SCMP_INSTRUCTION;


/*---------------------------------------------*/
/* MCMP INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct mcmp_format                     
{
  unsigned int                      : 5 ;
  unsigned int save_subtract        : 1 ;
  unsigned int                      : 1 ;
  unsigned int angle_compare        : 1 ;
  unsigned int hr_lr                : 1 ;
  unsigned int op_code              : 4 ;
  unsigned int next_program_address : 9 ;
  unsigned int brk                  : 1 ;
  unsigned int reqnum               : 3 ;
  unsigned int                      : 6 ;
 
  unsigned int interrupt_enable     : 1 ;
  unsigned int ab_register_select   : 1 ;
  unsigned int t_register_select    : 1 ;
  unsigned int opposite_action      : 1 ;
  unsigned int pin_action           : 1 ;
  unsigned int order                : 1 ; 
  unsigned int sub_opcode           : 1 ;  
  unsigned int                      : 1 ;
  unsigned int pin_select           : 5 ;
  unsigned int cond_addr            : 9 ;
  unsigned int en_pin_action        : 1 ;
  unsigned int                      : 3 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int request              : 2 ;
  unsigned int                      : 3 ;
 
  
  unsigned int hr_data              : 7 ;
  unsigned int data                 : 25 ; 

} MCMP_FIELDS ; 

typedef union 
{
  MCMP_FIELDS  mcmp   ;
  HET_MEMORY   memory ;
} MCMP_INSTRUCTION;

/*---------------------------------------------*/
/* MOV64 INSTRUCTION                           */
/*---------------------------------------------*/
typedef struct mov64_format                     
{
  unsigned int remote_address       : 9 ;
  unsigned int op_code              : 4 ;
  unsigned int next_program_address : 9 ;          
  unsigned int brk                  : 1 ;
  unsigned int                      : 9 ;

  unsigned int interrupt_enable     : 1 ;
  unsigned int ab_register_select   : 1 ;
  unsigned int t_register_select    : 1 ;
  unsigned int opposite_action      : 1 ;
  unsigned int pin_action           : 1 ;
  unsigned int compare_mode         : 2 ;
  unsigned int                      : 1 ;
  unsigned int pin_select           : 5 ;
  unsigned int cond_addr            : 9 ;
  unsigned int en_pin_action        : 1 ;
  unsigned int                      : 3 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int request              : 2 ;
  unsigned int                      : 3 ; 
  
  unsigned int hr_data              : 7 ;
  unsigned int data                 : 25 ;

} MOV64_FIELDS ; 

typedef union 
{
  MOV64_FIELDS  mov64  ;
  HET_MEMORY    memory ;
} MOV64_INSTRUCTION;


/*---------------------------------------------*/
/* DADM64 INSTRUCTION                          */
/*---------------------------------------------*/
typedef struct dadm64_format                     
{
  unsigned int remote_address       : 9 ;
  unsigned int op_code              : 4 ;
  unsigned int next_program_address : 9 ;
  unsigned int brk                  : 1 ;
  unsigned int                      : 9 ; 

  unsigned int interrupt_enable     : 1 ;
  unsigned int ab_register_select   : 1 ;
  unsigned int t_register_select    : 1 ;
  unsigned int opposite_action      : 1 ;
  unsigned int pin_action           : 1 ;
  unsigned int compare_mode         : 2 ;
  unsigned int                      : 1 ;
  unsigned int pin_select           : 5 ;
  unsigned int cond_addr            : 9 ;
  unsigned int en_pin_action        : 1 ;
  unsigned int                      : 3 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int request              : 2 ;
  unsigned int                      : 3 ; 
  
  unsigned int hr_data              : 7 ;
  unsigned int data                 : 25 ;
 
} DADM64_FIELDS ; 

typedef union 
{
  DADM64_FIELDS  dadm64 ;
  HET_MEMORY     memory ;
} DADM64_INSTRUCTION;


/*---------------------------------------------*/
/* RADM64 INSTRUCTION                          */
/*---------------------------------------------*/
typedef struct RADM64_format                     
{
  unsigned int remote_address       : 9 ;
  unsigned int op_code              : 4 ;
  unsigned int next_program_address : 9 ;
  unsigned int brk                  : 1 ;
  unsigned int                      : 9 ; 

  unsigned int interrupt_enable     : 1 ;
  unsigned int ab_register_select   : 1 ;
  unsigned int t_register_select    : 1 ;
  unsigned int opposite_action      : 1 ;
  unsigned int pin_action           : 1 ;
  unsigned int compare_mode         : 2 ;
  unsigned int                      : 1 ;
  unsigned int pin_select           : 5 ;
  unsigned int cond_addr            : 9 ;
  unsigned int en_pin_action        : 1 ;
  unsigned int                      : 3 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int request              : 2 ;
  unsigned int                      : 3 ; 
  
  unsigned int hr_data              : 7 ;
  unsigned int data                 : 25 ; 

} RADM64_FIELDS ; 


typedef union 
{
  RADM64_FIELDS  radm64 ;
  HET_MEMORY     memory ;
} RADM64_INSTRUCTION;


/*---------------------------------------------*/
/* MOV32 INSTRUCTION                           */
/*---------------------------------------------*/
typedef struct MOV32_format                     
{
  unsigned int remote_address       : 9 ;
  unsigned int op_code              : 4 ;
  unsigned int next_program_address : 9 ;
  unsigned int brk                  : 1 ;
  unsigned int                      : 9 ;
 
  unsigned int                      : 1 ;
  unsigned int ab_register_select   : 1 ;
  unsigned int t_register_select    : 1 ;
  unsigned int move_type            : 2 ;
  unsigned int sub_opcode           : 1 ;
  unsigned int init_flag            : 1 ;
  unsigned int                      : 15 ;
  unsigned int z_flag               : 1 ;
  unsigned int                      : 3 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int                      : 5 ; 
  
  unsigned int hr_data              : 7 ;
  unsigned int data                 : 25 ;
 
} MOV32_FIELDS ; 


typedef union 
{
  MOV32_FIELDS  mov32  ;
  HET_MEMORY    memory ;
} MOV32_INSTRUCTION;


/*---------------------------------------------*/
/* ADM32 INSTRUCTION                           */
/*---------------------------------------------*/
typedef struct ADM32_format                     
{
  unsigned int remote_address       : 9 ;
  unsigned int op_code              : 4 ;
  unsigned int next_program_address : 9 ;
  unsigned int brk                  : 1 ;
  unsigned int                      : 9 ; 

  unsigned int                      : 1 ;
  unsigned int ab_register_select   : 1 ;
  unsigned int t_register_select    : 1 ;
  unsigned int move_type            : 2 ;
  unsigned int sub_opcode           : 1 ;
  unsigned int init_flag            : 1 ;
  unsigned int                      : 19 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int                      : 5 ; 
  
  unsigned int hr_data              : 7 ;
  unsigned int data                 : 25 ;
   
} ADM32_FIELDS ; 


typedef union 
{
  ADM32_FIELDS  adm32  ;
  HET_MEMORY    memory ;
} ADM32_INSTRUCTION;


/*---------------------------------------------*/
/* ADCNST INSTRUCTION                          */
/*---------------------------------------------*/
typedef struct ADCNST_format                     
{
  unsigned int remote_address       : 9 ;
  unsigned int op_code              : 4 ;
  unsigned int next_program_address : 9 ;
  unsigned int brk                  : 1 ;
  unsigned int                      : 9 ;
 
  unsigned int constant             : 25 ;
  unsigned int                      : 1 ;
  unsigned int                      : 5 ; 
  
  unsigned int hr_data              : 7 ;
  unsigned int data                 : 25 ; 

} ADCNST_FIELDS ;


typedef union 
{
  ADCNST_FIELDS  adcnst ;
  HET_MEMORY     memory ;
} ADCNST_INSTRUCTION;



/*----------------------------------------------*/
/* ADD INSTRUCTION					*/
/*----------------------------------------------*/
typedef struct ADD_format                     
{

  unsigned int remote_address       : 9 ;	
  unsigned int op_code              : 4 ;
  unsigned int next_program_address : 9 ;
  unsigned int brk                  : 1 ;	
  unsigned int                      : 9 ;

  unsigned int                      : 1 ;  
  unsigned int reg	                : 2 ;
  unsigned int rem_dest             : 2 ;
  unsigned int sub_opcode1          : 1 ;
  unsigned int init_flag            : 1 ;
  unsigned int reg_ext              : 1 ;
  unsigned int shft_cnt             : 5 ;
  unsigned int shft_mode            : 3 ;
  unsigned int src_2                : 3 ;
  unsigned int src_1                : 4 ;
  unsigned int sub_opcode3          : 3 ;
  unsigned int control              : 1 ;
  unsigned int                      : 5 ;

  unsigned int hr_data              : 7 ; 
  unsigned int data                 : 25 ;
 
 
} ADD_FIELDS ;


typedef union 
{
  ADD_FIELDS  add ;
  HET_MEMORY  memory ;
} ADD_INSTRUCTION;




/*----------------------------------------------*/
/* ADC INSTRUCTION					*/
/*----------------------------------------------*/


typedef struct ADC_format                     
{

  unsigned int remote_address       : 9 ;	
  unsigned int op_code              : 4 ;
  unsigned int next_program_address : 9 ;
  unsigned int brk                  : 1 ;	
  unsigned int                      : 9 ;

  unsigned int                      : 1 ;  
  unsigned int reg	                : 2 ;
  unsigned int rem_dest             : 2 ;
  unsigned int sub_opcode1          : 1 ;
  unsigned int init_flag            : 1 ;
  unsigned int reg_ext              : 1 ;
  unsigned int shft_cnt             : 5 ;
  unsigned int shft_mode            : 3 ;
  unsigned int src_2                : 3 ;
  unsigned int src_1                : 4 ;
  unsigned int sub_opcode3          : 3 ;
  unsigned int control              : 1 ;
  unsigned int                      : 5 ;

  unsigned int hr_data              : 7 ; 
  unsigned int data                 : 25 ;
 
 
} ADC_FIELDS ;


typedef union 
{
  ADC_FIELDS  adc ;
  HET_MEMORY  memory ;
} ADC_INSTRUCTION;




/*----------------------------------------------*/
/* SUB INSTRUCTION					*/
/*----------------------------------------------*/

typedef struct SUB_format                     
{

  unsigned int remote_address       : 9 ;	
  unsigned int op_code              : 4 ;
  unsigned int next_program_address : 9 ;
  unsigned int brk                  : 1 ;	
  unsigned int                      : 9 ;

  unsigned int                      : 1 ;  
  unsigned int reg	                : 2 ;
  unsigned int rem_dest             : 2 ;
  unsigned int sub_opcode1          : 1 ;
  unsigned int init_flag            : 1 ;
  unsigned int reg_ext              : 1 ;
  unsigned int shft_cnt             : 5 ;
  unsigned int shft_mode            : 3 ;
  unsigned int src_2                : 3 ;
  unsigned int src_1                : 4 ;
  unsigned int sub_opcode3          : 3 ;
  unsigned int control              : 1 ;
  unsigned int                      : 5 ;

  unsigned int hr_data              : 7 ; 
  unsigned int data                 : 25 ;
 
 
} SUB_FIELDS ;


typedef union 
{
  SUB_FIELDS  sub ;
  HET_MEMORY  memory ;
} SUB_INSTRUCTION;





/*----------------------------------------------*/
/* SBB INSTRUCTION					*/
/*----------------------------------------------*/

typedef struct SBB_format
{

  unsigned int remote_address       : 9 ;	
  unsigned int op_code              : 4 ;
  unsigned int next_program_address : 9 ;
  unsigned int brk                  : 1 ;	
  unsigned int                      : 9 ;

  unsigned int                      : 1 ;  
  unsigned int reg	                : 2 ;
  unsigned int rem_dest             : 2 ;
  unsigned int sub_opcode1          : 1 ;
  unsigned int init_flag            : 1 ;
  unsigned int reg_ext              : 1 ;
  unsigned int shft_cnt             : 5 ;
  unsigned int shft_mode            : 3 ;
  unsigned int src_2                : 3 ;
  unsigned int src_1                : 4 ;
  unsigned int sub_opcode3          : 3 ;
  unsigned int control              : 1 ;
  unsigned int                      : 5 ;

  unsigned int hr_data              : 7 ; 
  unsigned int data                 : 25 ;
 
 
} SBB_FIELDS ;


typedef union 
{
  SBB_FIELDS  sbb ;
  HET_MEMORY  memory ;
} SBB_INSTRUCTION;




/*----------------------------------------------*/
/* AND INSTRUCTION					*/
/*----------------------------------------------*/

typedef struct AND_format
{

  unsigned int remote_address       : 9 ;	
  unsigned int op_code              : 4 ;
  unsigned int next_program_address : 9 ;
  unsigned int brk                  : 1 ;	
  unsigned int                      : 9 ;

  unsigned int                      : 1 ;  
  unsigned int reg	                : 2 ;
  unsigned int rem_dest             : 2 ;
  unsigned int sub_opcode1          : 1 ;
  unsigned int init_flag            : 1 ;
  unsigned int reg_ext              : 1 ;
  unsigned int shft_cnt             : 5 ;
  unsigned int shft_mode            : 3 ;
  unsigned int src_2                : 3 ;
  unsigned int src_1                : 4 ;
  unsigned int sub_opcode3          : 3 ;
  unsigned int control              : 1 ;
  unsigned int                      : 5 ;

  unsigned int hr_data              : 7 ; 
  unsigned int data                 : 25 ;
 
 
} AND_FIELDS ;


typedef union 
{
  AND_FIELDS  and ;
  HET_MEMORY  memory ;
} AND_INSTRUCTION;



/*----------------------------------------------*/
/* OR INSTRUCTION						*/
/*----------------------------------------------*/

typedef struct OR_format
{

  unsigned int remote_address       : 9 ;	
  unsigned int op_code              : 4 ;
  unsigned int next_program_address : 9 ;
  unsigned int brk                  : 1 ;	
  unsigned int                      : 9 ;

  unsigned int                      : 1 ;  
  unsigned int reg	                : 2 ;
  unsigned int rem_dest             : 2 ;
  unsigned int sub_opcode1          : 1 ;
  unsigned int init_flag            : 1 ;
  unsigned int reg_ext              : 1 ;
  unsigned int shft_cnt             : 5 ;
  unsigned int shft_mode            : 3 ;
  unsigned int src_2                : 3 ;
  unsigned int src_1                : 4 ;
  unsigned int sub_opcode3          : 3 ;
  unsigned int control              : 1 ;
  unsigned int                      : 5 ;

  unsigned int hr_data              : 7 ; 
  unsigned int data                 : 25 ;
 
 
} OR_FIELDS ;


typedef union 
{
  OR_FIELDS  or ;
  HET_MEMORY  memory ;
} OR_INSTRUCTION;



/*----------------------------------------------*/
/* XOR INSTRUCTION					*/
/*----------------------------------------------*/

typedef struct XOR_format
{

  unsigned int remote_address       : 9 ;	
  unsigned int op_code              : 4 ;
  unsigned int next_program_address : 9 ;
  unsigned int brk                  : 1 ;	
  unsigned int                      : 9 ;

  unsigned int                      : 1 ;  
  unsigned int reg	                : 2 ;
  unsigned int rem_dest             : 2 ;
  unsigned int sub_opcode1          : 1 ;
  unsigned int init_flag            : 1 ;
  unsigned int reg_ext              : 1 ;
  unsigned int shft_cnt             : 5 ;
  unsigned int shft_mode            : 3 ;
  unsigned int src_2                : 3 ;
  unsigned int src_1                : 4 ;
  unsigned int sub_opcode3          : 3 ;
  unsigned int control              : 1 ;
  unsigned int                      : 5 ;

  unsigned int hr_data              : 7 ; 
  unsigned int data                 : 25 ;
 
 
} XOR_FIELDS ;


typedef union 
{
  XOR_FIELDS  xor ;
  HET_MEMORY  memory ;
} XOR_INSTRUCTION;




/*---------------------------------------------*/
/* CNT INSTRUCTION                             */
/*---------------------------------------------*/
typedef struct CNT_format                     
{
  unsigned int interrupt_enable     : 1 ;         
  unsigned int                      : 4 ;        
  unsigned int ab_register_select   : 1 ;          
  unsigned int t_register_select    : 1 ;
  unsigned int angle_cnt            : 1 ;
  unsigned int op_code              : 4 ;
  unsigned int next_program_address : 9 ;
  unsigned int brk                  : 1 ;  
  unsigned int                      : 9 ;  

  unsigned int max                  : 25 ;
  unsigned int                      : 1 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int request              : 2 ;
  unsigned int                      : 3 ;
  
  unsigned int                      : 7 ;
  unsigned int data                 : 25 ;

} CNT_FIELDS ; 

typedef union 
{
  CNT_FIELDS   cnt    ; 
  HET_MEMORY   memory ;
} CNT_INSTRUCTION;


/*---------------------------------------------*/
/* APCNT INSTRUCTION                           */
/*---------------------------------------------*/
typedef struct apcnt_format
{
  unsigned int                      : 6 ;
  unsigned int edge_select          : 2 ;
  unsigned int interrupt_enable     : 1 ;
  unsigned int op_code              : 4 ;
  unsigned int next_program_address : 9 ;
  unsigned int brk                  : 1 ;
  unsigned int reqnum               : 3 ;
  unsigned int                      : 6 ;

  unsigned int count                : 25 ;
  unsigned int previous_bit         : 1 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int request              : 2 ;
  unsigned int                      : 3 ; 
  
  unsigned int                      : 7 ;
  unsigned int data                 : 25 ; 

} APCNT_FIELDS ;
 
typedef union
{
  APCNT_FIELDS  apcnt   ;
  HET_MEMORY   memory ;
} APCNT_INSTRUCTION;
 
 

/*---------------------------------------------*/
/* PCNT INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct pcnt_format                     
{
  unsigned int pin_select           : 5 ;
  unsigned int                      : 1 ;
  unsigned int period_pulse_select  : 2 ;          
  unsigned int interrupt_enable     : 1 ;          
  unsigned int op_code              : 4 ;
  unsigned int next_program_address : 9 ;
  unsigned int brk                  : 1 ;
  unsigned int reqnum               : 3 ;
  unsigned int                      : 6 ;

  unsigned int count                : 25 ;
  unsigned int previous_bit         : 1 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int request              : 2 ;
  unsigned int                      : 3 ;
  
  unsigned int hr_data              : 7 ;
  unsigned int data                 : 25 ;

} PCNT_FIELDS ;      

typedef union 
{
  PCNT_FIELDS  pcnt   ; 
  HET_MEMORY   memory ;
} PCNT_INSTRUCTION;


/*---------------------------------------------*/
/* SCNT INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct scnt_format                     
{
  unsigned int                      : 4 ;
  unsigned int step_width           : 2 ;
  unsigned int count_mode           : 2 ;
  unsigned int                      : 1 ;
  unsigned int op_code              : 4 ;
  unsigned int next_program_address : 9 ;
  unsigned int brk                  : 1 ;
  unsigned int                      : 9 ;

  unsigned int gap_start            : 25 ;
  unsigned int                      : 1 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int                      : 5 ;
  
  unsigned int                      : 7 ;
  unsigned int data                 : 25 ;

} SCNT_FIELDS ;      

typedef union 
{
  SCNT_FIELDS  scnt   ; 
  HET_MEMORY   memory ;
} SCNT_INSTRUCTION;

/*---------------------------------------------*/
/* ACNT INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct acnt_format                     
{
  unsigned int interrupt_enable     : 1 ; 
  unsigned int                      : 7 ;
  unsigned int edge_select          : 1 ;
  unsigned int op_code              : 4 ;
  unsigned int next_program_address : 9 ;
  unsigned int brk                  : 1 ;
  unsigned int reqnum               : 3 ;
  unsigned int                      : 6 ;

  unsigned int gap_end              : 25 ;
  unsigned int previous_bit         : 1 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int request              : 2 ;
  unsigned int                      : 3 ; 
  
  unsigned int                      : 7 ;
  unsigned int data                 : 25 ;

} ACNT_FIELDS ;      

typedef union 
{
  ACNT_FIELDS  acnt   ; 
  HET_MEMORY   memory ;
} ACNT_INSTRUCTION;


/*---------------------------------------------*/
/* ECNT INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct ecnt_format
{
  unsigned int                      : 6 ;
  unsigned int count_mode           : 2 ;
  unsigned int                      : 1 ;
  unsigned int op_code              : 4 ;
  unsigned int next_program_address : 9 ;
  unsigned int brk                  : 1 ;
  unsigned int reqnum               : 3 ;
  unsigned int                      : 6 ;
 
  unsigned int interrupt_enable     : 1 ;
  unsigned int ab_register_select   : 1 ;
  unsigned int t_register_select    : 1 ;
  unsigned int                      : 1 ;
  unsigned int count_cond           : 3 ;
  unsigned int                      : 1 ;
  unsigned int pin_select           : 5 ;
  unsigned int cond_addr            : 9 ;
  unsigned int                      : 3 ;
  unsigned int previous_bit         : 1 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int request              : 2 ;
  unsigned int                      : 3 ;
  
  unsigned int                      : 7 ;
  unsigned int data                 : 25 ; 
 

} ECNT_FIELDS ;
 
typedef union
{
  ECNT_FIELDS  ecnt   ;
  HET_MEMORY   memory ;
} ECNT_INSTRUCTION;

/*---------------------------------------------*/
/* RCNT INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct rcnt_format
{

  unsigned int count_mode1          : 1 ;
  unsigned int                      : 5 ;
  unsigned int count_mode           : 2 ;
  unsigned int                      : 1 ;
  unsigned int op_code              : 4 ;
  unsigned int next_program_address : 9 ;
  unsigned int brk                  : 1 ;
  unsigned int reqnum               : 3 ;
  unsigned int                      : 6 ;


  unsigned int divisor              : 25 ;  
  unsigned int                      : 1 ;
  unsigned int control              : 1 ;
  unsigned int                      : 2 ;
  unsigned int                      : 3 ;

  unsigned int                      : 7 ;  
  unsigned int data                 : 25 ;

 
} RCNT_FIELDS ;
 
typedef union
{
  RCNT_FIELDS  rcnt   ;
  HET_MEMORY   memory ;
} RCNT_INSTRUCTION;


/*---------------------------------------------*/
/* DJNZ INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct djnz_format                     
{
  unsigned int                      : 6 ;
  unsigned int sub_opcode           : 2 ;
  unsigned int                      : 1 ;
  unsigned int op_code              : 4 ;
  unsigned int next_program_address : 9 ; 
  unsigned int brk                  : 1 ;
  unsigned int reqnum               : 3 ;
  unsigned int                      : 6 ;

  unsigned int interrupt_enable     : 1 ;
  unsigned int ab_register_select   : 1 ;
  unsigned int t_register_select    : 1 ;
  unsigned int                      : 10 ;
  unsigned int cond_addr            : 9 ;
  unsigned int                      : 4 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int request              : 2 ;
  unsigned int                      : 3 ;
  
  unsigned int                      : 7 ;
  unsigned int data                 : 25 ;

} DJNZ_FIELDS ;      

typedef union 
{
  DJNZ_FIELDS  djnz   ; 
  HET_MEMORY   memory ;
} DJNZ_INSTRUCTION;


/*---------------------------------------------*/
/* DJZ INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct djz_format                     
{
  unsigned int                      : 6 ;
  unsigned int sub_opcode           : 2 ;
  unsigned int                      : 1 ;
  unsigned int op_code              : 4 ;
  unsigned int next_program_address : 9 ; 
  unsigned int brk                  : 1 ;
  unsigned int reqnum               : 3 ;
  unsigned int                      : 6 ;

  unsigned int interrupt_enable     : 1 ;
  unsigned int ab_register_select   : 1 ;
  unsigned int t_register_select    : 1 ;
  unsigned int                      : 10 ;
  unsigned int cond_addr            : 9 ;
  unsigned int                      : 4 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int request              : 2 ;
  unsigned int                      : 3 ;
  
  unsigned int                      : 7 ;
  unsigned int data                 : 25 ;

} DJZ_FIELDS ;      

typedef union 
{
  DJZ_FIELDS  djz   ; 
  HET_MEMORY   memory ;
} DJZ_INSTRUCTION;

/*---------------------------------------------*/
/* PWCNT INSTRUCTION                           */
/*---------------------------------------------*/
typedef struct pwcnt_format                     
{
  unsigned int                      : 6 ;
  unsigned int count_mode           : 2 ;
  unsigned int hr_lr                : 1 ;
  unsigned int op_code              : 4 ;
  unsigned int next_program_address : 9 ;
  unsigned int brk                  : 1 ;
  unsigned int reqnum               : 3 ;
  unsigned int                      : 6 ;

  unsigned int interrupt_enable     : 1 ;
  unsigned int ab_register_select   : 1 ;
  unsigned int t_register_select    : 1 ;
  unsigned int opposite_action      : 1 ;
  unsigned int pin_action           : 1 ;
  unsigned int                      : 3 ;
  unsigned int pin_select           : 5 ;
  unsigned int cond_addr            : 9 ;
  unsigned int en_pin_action        : 1 ;
  unsigned int                      : 3 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int request              : 2 ;
  unsigned int                      : 3 ;
  

  unsigned int hr_data              : 7 ;
  unsigned int data                 : 25 ;  
 
} PWCNT_FIELDS ;      

typedef union 
{
  PWCNT_FIELDS  pwcnt ;
  HET_MEMORY   memory ;
} PWCNT_INSTRUCTION;


/*---------------------------------------------*/
/* WCAP INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct wcap_format                     
{
  unsigned int                      : 8 ;
  unsigned int hr_lr                : 1 ;
  unsigned int op_code              : 4 ;
  unsigned int next_program_address : 9 ;
  unsigned int brk                  : 1 ;
  unsigned int reqnum               : 3 ;
  unsigned int                      : 6 ; 
  
  unsigned int interrupt_enable     : 1 ;
  unsigned int ab_register_select   : 1 ;
  unsigned int t_register_select    : 1 ;
  unsigned int                      : 2 ;
  unsigned int capture_condition    : 2 ;
  unsigned int                      : 1 ;
  unsigned int pin_select           : 5 ;
  unsigned int cond_addr            : 9 ;
  unsigned int                      : 3 ;
  unsigned int previous_bit         : 1 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int request              : 2 ;
  unsigned int                      : 3 ;
  
  unsigned int hr_data              : 7 ;
  unsigned int data                 : 25 ;

} WCAP_FIELDS ;      

typedef union 
{
  WCAP_FIELDS  wcap   ; 
  HET_MEMORY   memory ;
} WCAP_INSTRUCTION;
 
/*----------------------------------------------*/
/* WCAPE INSTRUCTION                            */
/*----------------------------------------------*/
typedef struct wcape_format                     
{
  unsigned int                      : 9 ;
  unsigned int op_code              : 4 ;
  unsigned int next_program_address : 9 ;
  unsigned int brk                  : 1 ;
  unsigned int reqnum               : 3 ;
  unsigned int                      : 6 ;  

  unsigned int interrupt_enable     : 1 ;
  unsigned int ab_register_select   : 1 ;
  unsigned int t_register_select    : 1 ;
  unsigned int                      : 2 ;
  unsigned int capture_condition    : 2 ;
  unsigned int                      : 1 ;
  unsigned int pin_select           : 5 ;
  unsigned int cond_addr            : 9 ;
  unsigned int previous_bit         : 1 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int request              : 2 ;
  unsigned int                      : 3 ;
  
  unsigned int ec_data              : 7 ;
  unsigned int ts_data              : 25 ;

} WCAPE_FIELDS ;      

typedef union 
{
  WCAPE_FIELDS  wcape   ; 
  HET_MEMORY   memory ;
} WCAPE_INSTRUCTION;
 

/*---------------------------------------------*/
/* BR   INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct br_format                     
{
  unsigned int                      : 9 ;
  unsigned int op_code              : 4 ;
  unsigned int next_program_address : 9 ;
  unsigned int brk                  : 1 ;
  unsigned int reqnum               : 3 ;
  unsigned int                      : 6 ;

  unsigned int interrupt_enable     : 1 ;
  unsigned int                      : 2 ;
  unsigned int                      : 1 ;
  unsigned int                      : 1 ;
  unsigned int branch_condition     : 3 ;
  unsigned int pin_select           : 5 ;
  unsigned int cond_addr            : 9 ;
  unsigned int                      : 3 ;
  unsigned int previous_bit         : 1 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int request              : 2 ;
  unsigned int                      : 3 ; 
  
  unsigned int hr_data              : 7 ;
  unsigned int data                 : 25 ;

} BR_FIELDS ;      

typedef union 
{
  BR_FIELDS  br     ; 
  HET_MEMORY memory ;
} BR_INSTRUCTION;

 
/*---------------------------------------------*/
/* SHFT INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct shft_format                     
{
  unsigned int shift_mode           : 4 ;
  unsigned int                      : 5 ;
  unsigned int op_code              : 4 ;
  unsigned int next_program_address : 9 ;
  unsigned int brk                  : 1 ;
  unsigned int reqnum               : 3 ;
  unsigned int                      : 6 ; 

  unsigned int interrupt_enable     : 1 ;
  unsigned int ab_register_select   : 1 ;
  unsigned int t_register_select    : 1 ;
  unsigned int                      : 2 ;
  unsigned int shift_condition      : 2 ;
  unsigned int                      : 1 ;
  unsigned int pin_select           : 5 ;
  unsigned int cond_addr            : 9 ;
  unsigned int                      : 3 ;
  unsigned int previous_bit         : 1 ;
  unsigned int auto_read_clear      : 1 ;
  unsigned int request              : 2 ;
  unsigned int                      : 3 ;
  
  unsigned int                      : 7 ;
  unsigned int data                 : 25 ;

} SHFT_FIELDS ;      

typedef union 
{
  SHFT_FIELDS  shft   ; 
  HET_MEMORY   memory ;
} SHFT_INSTRUCTION;

#endif

#endif
/*--------------------------- End Of File ----------------------------------*/
