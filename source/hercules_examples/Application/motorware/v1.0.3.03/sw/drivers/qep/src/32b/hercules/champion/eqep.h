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
#ifndef _QEP_H_
#define _QEP_H_

//! \file   ~/sw/drivers/qep/src/32b/hercules/champion/qep.h
//! \brief  Contains public interface to various functions related
//!         to the quadrature pulse encoder (QEP) object
//!
//! (C) Copyright 2011, Texas Instruments, Inc.


// **************************************************************************
// the includes

// drivers


// modules
#include "modules/types/src/32b/types.h"


//!
//! \defgroup QEP

//!
//! \ingroup QEP
//@{


#ifdef __cplusplus
extern "C" {
#endif


// **************************************************************************
// the defines

#define QEP_BASE_ADDR1              (0xFCF79900) //!<base address of QEP1
#define QEP_BASE_ADDR2              (0xFCF79A00) //!<base address of QEP2

// QDECCTL Register
#define QEP_QDECCTL_QSRC					 (3  << 14)		//!<position counter source selection
#define QEP_QDECCTL_SOEN					 (1  << 13)		//!<sync output enable
#define QEP_QDECCTL_SPSEL					 (1  << 12)		//!<sync output pin selection
#define QEP_QDECCTL_XCR						 (1  << 11)		//!<external clock rate
#define QEP_QDECCTL_SWAP					 (1  << 10)		//!<swap quadrature clock inputs
#define QEP_QDECCTL_IGATE					 (1  <<  9)		//!<index pulse gating option
#define QEP_QDECCTL_QAP						 (1  <<  8)		//!<QEPA input polarity
#define QEP_QDECCTL_QBP						 (1  <<  7)		//!<QEPB input polarity
#define QEP_QDECCTL_QIP						 (1  <<  6)		//!<QEPI input polarity
#define QEP_QDECCTL_QSP						 (1  <<  5)		//!<QEPS input polarity

// QEPCTL Register
#define QEP_QEPCTL_FREESOFT					 ( 3 << 14)		//!<emulation control bit
#define QEP_QEPCTL_PCRM						 ( 3 << 12)		//!<emulation control bit
#define QEP_QEPCTL_SEI						 ( 3 << 10)		//!<strobe event initialization of position counter
#define QEP_QEPCTL_IEI						 ( 3 <<  8)		//!<index event initialization of position counter
#define QEP_QEPCTL_SWI						 ( 1 <<  7)		//!<software initialization of position counter
#define QEP_QEPCTL_SEL						 ( 1 <<  6)		//!<strobe event latch of position counter
#define QEP_QEPCTL_IEL						 ( 3 <<  4)		//!<index event latch of position counter (software index marker)
#define QEP_QEPCTL_QPEN						 ( 1 <<  3)		//!<quad position counter enable/software reset
#define QEP_QEPCTL_QCLM						 ( 1 <<  2)		//!<QEP capture latch mode
#define QEP_QEPCTL_UTE						 ( 1 <<  1)		//!<QEP unit timer enable
#define QEP_QEPCTL_WDE						 ( 1 <<  0)		//!<watchdog timer enable

// QPOSCTL Register
#define QEP_QPOSCTL_PCSHDW					 (   1 << 15)	//!<position compare shadow enable
#define QEP_QPOSCTL_PCLOAD					 (   1 << 14)	//!<position compare shadow load mode
#define QEP_QPOSCTL_PCPOL					 (   1 << 13)	//!<load when QPOSCNT = QPOSCMP
#define QEP_QPOSCTL_PCE						 (   1 << 12)	//!<position compare enable/disable
#define QEP_QPOSCTL_PCSPW					 (4095 <<  0)	//!<selection position compare sync output pulse width

// QCAPCTL Register
#define QEP_QCAPCTL_CEN						 (   1 << 15)	//!<enable QEP capture
#define QEP_QCAPCTL_CCPS					 (   7 <<  4)	//!<qep capture timer clock prescaler
#define QEP_QCAPCTL_UPPS					 (  15 <<  0)	//!<unit position event prescaler

// QEINT Register
#define QEP_QEINT_UTO						 (   1 << 11)	//!<unit timeout interrupt enable
#define QEP_QEINT_IEL						 (   1 << 10)	//!<index event latch interrupt enable
#define QEP_QEINT_SEL						 (   1 <<  9)	//!<strobe event latch	interrupt enable
#define QEP_QEINT_PCM						 (   1 <<  8)	//!<position compare match interrupt enable	
#define QEP_QEINT_PCR						 (   1 <<  7)	//!<position compare ready interrupt enable 
#define QEP_QEINT_PCO						 (   1 <<  6)	//!<position counter overflow interrupt enable
#define QEP_QEINT_PCU						 (   1 <<  5)	//!<position counter underflow interrupt enable
#define QEP_QEINT_WTO						 (   1 <<  4)	//!<watchdog time out interrupt enable
#define QEP_QEINT_QDC						 (   1 <<  3)	//!<quadrature direction change interrupt enable
#define QEP_QEINT_QPE						 (   1 <<  2)	//!<quadrature phase error interrupt enable
#define QEP_QEINT_PCE						 (   1 <<  1)	//!<position counter error interrupt enable
																
// QFLG Register
#define QEP_QFLG_UTO						 (   1 << 11)	//!<unit timeout interrupt flag
#define QEP_QFLG_IEL						 (   1 << 10)	//!<index event latch interrupt flag
#define QEP_QFLG_SEL						 (   1 <<  9)	//!<strobe event latch	interrupt flag
#define QEP_QFLG_PCM						 (   1 <<  8)	//!<position compare match interrupt flag
#define QEP_QFLG_PCR						 (   1 <<  7)	//!<position compare ready interrupt flag
#define QEP_QFLG_PCO						 (   1 <<  6)	//!<position counter overflow interrupt flag
#define QEP_QFLG_PCU						 (   1 <<  5)	//!<position counter underflow interrupt flag
#define QEP_QFLG_WTO						 (   1 <<  4)	//!<watchdog time out interrupt flag
#define QEP_QFLG_QDC						 (   1 <<  3)	//!<quadrature direction change interrupt flag
#define QEP_QFLG_QPE						 (   1 <<  2)	//!<quadrature phase error interrupt flag
#define QEP_QFLG_PCE						 (   1 <<  1)	//!<position counter error interrupt flag

// QCLR Register
#define QEP_QCLR_UTO						 (   1 << 11)	//!<clear unit timeout interrupt flag
#define QEP_QCLR_IEL						 (   1 << 10)	//!<clear index event latch interrupt flag
#define QEP_QCLR_SEL						 (   1 <<  9)	//!<clear strobe event latch interrupt flag
#define QEP_QCLR_PCM						 (   1 <<  8)	//!<clear position compare match interrupt flag
#define QEP_QCLR_PCR						 (   1 <<  7)	//!<clear position compare ready interrupt flag
#define QEP_QCLR_PCO						 (   1 <<  6)	//!<clear position counter overflow interrupt flag
#define QEP_QCLR_PCU						 (   1 <<  5)	//!<clear position counter underflow interrupt flag
#define QEP_QCLR_WTO						 (   1 <<  4)	//!<clear watchdog time out interrupt flag
#define QEP_QCLR_QDC						 (   1 <<  3)	//!<clear quadrature direction change interrupt flag
#define QEP_QCLR_QPE						 (   1 <<  2)	//!<clear quadrature phase error interrupt flag
#define QEP_QCLR_PCE						 (   1 <<  1)	//!<clear position counter error interrupt flag

// QFRC Register
#define QEP_QFRC_UTO						 (   1 << 11)	//!<force unit timeout interrupt 
#define QEP_QFRC_IEL						 (   1 << 10)	//!<force index event latch interrupt 
#define QEP_QFRC_SEL						 (   1 <<  9)	//!<force strobe event latch interrupt 
#define QEP_QFRC_PCM						 (   1 <<  8)	//!<force position compare match interrupt 
#define QEP_QFRC_PCR						 (   1 <<  7)	//!<force position compare ready interrupt 
#define QEP_QFRC_PCO						 (   1 <<  6)	//!<force position counter overflow interrupt 
#define QEP_QFRC_PCU						 (   1 <<  5)	//!<force position counter underflow interrupt 
#define QEP_QFRC_WTO						 (   1 <<  4)	//!<force watchdog time out interrupt 
#define QEP_QFRC_QDC						 (   1 <<  3)	//!<force quadrature direction change interrupt 
#define QEP_QFRC_QPE						 (   1 <<  2)	//!<force quadrature phase error interrupt 
#define QEP_QFRC_PCE						 (   1 <<  1)	//!<force position counter error interrupt 

// QEPSTS Register
#define QEP_QEPSTS_UPEVNT					(   1 << 7)		//!<unit position event flag
#define QEP_QEPSTS_FDF						(   1 << 6)		//!<direction on the first index marker
#define QEP_QEPSTS_QDF						(   1 << 5)		//!<quadrature direction flag
#define QEP_QEPSTS_QDLF						(   1 << 4)		//!<direction latch flag
#define QEP_QEPSTS_COEF						(   1 << 3)		//!<capture overflow error flag
#define QEP_QEPSTS_CDEF						(   1 << 2)		//!<capture direction error flag
#define QEP_QEPSTS_FIMF						(   1 << 1)		//!<first index marker flag
#define QEP_QEPSTS_PCEF						(   1 << 0)		//!<position counter error flag

// **************************************************************************
// the typedefs

//! \brief QEP counting mode
//!
typedef enum
{
	QEP_Qsrc_Quad_Count_Mode=(0 << 14),						//!<quadrature count mode
	QEP_Qsrc_Dir_Count_Mode=(1 << 14),						//!<direction count mode
	QEP_Qsrc_Up_Count_Mode=(2 << 14),						//!<up count mode for frequency measurement (QCLK=XCLK, QDIR=1)
	QEP_Qsrc_Down_Count_Mode=(3 << 14)						//!<down count mode for frequency measurement (QCLK=XCLK, QDIR=0)
} QEP_Qsrc_e;

//! \brief Sync output pin selection
//!
typedef enum
{	
	QEP_Spsel_Index_Pin_Sync_Output=(0 << 12),				//!<index pin for sync output
	QEP_Spsel_Strobe_Pin_Sync_Output=(1 << 12)				//!<strobe pin for sync output
} QEP_Spsel_e;

//! \brief External clock rate
//!
typedef enum
{
	QEP_Xcr_2x_Res=(0 << 11),								//!<2x resolution: count the rising/falling edge
	QEP_Xcr_1x_Res=(1 << 11)								//!<1x resolution: count the rising edge only
} QEP_Xcr_e;

//! \brief Swap A/B channels
//!
typedef enum
{
	QEP_Swap_Not_Swapped=(0 << 10),							//!<quad inputs not swapped
	QEP_Swap_Swapped=(1 << 10)								//!<quad inputs swapped
} QEP_Swap_e;

//! \brief Index gating
//!
typedef enum
{
	QEP_Igate_Disable=(0 << 9),								//!<disable gating of index pulse
	QEP_Igate_Enable=(1 << 9)								//!<enable gating of index pulse
} QEP_Igate_e;

//! \brief Channel A polarity
//!
typedef enum
{
	QEP_Qap_No_Effect=(0 << 8),								//!<no effect
	QEP_Qap_Inverted=(1 << 8)								//!<negates QEPA input
} QEP_Qap_e;

//! \brief Channel B polarity
//!
typedef enum
{
	QEP_Qbp_No_Effect=(0 << 7),								//!<no effect
	QEP_Qbp_Inverted=(1 << 7)								//!<negates QEPB input
} QEP_Qbp_e;

//! \brief Index polarity
//
typedef enum
{
	QEP_Qip_No_Effect=(0 << 6),								//!<no effect
	QEP_Qip_Inverted=(1 << 6)								//!<negates QEPI input
} QEP_Qip_e;

//! \brief Channel S polarity
//!
typedef enum
{
	QEP_Qsp_No_Effect=(0 << 5),								//!<no effect
	QEP_Qsp_Inverted=(1 << 5)								//!<negates QEPS input
} QEP_Qsp_e;

//! \brief Emulation control bits
//!
typedef enum
{
	QEPCTL_Freesoft_Immediate_Halt=(0 << 14),				//!<position, watchdog, unit timer, capture timer stops immediately
	QEPCTL_Freesoft_Rollover_Halt=(1 << 14),				//!<position, watchdog, unit timer continues until rollover, capture counts until next unit period event
	QEPCTL_Freesoft_Unaffected_Halt=(2 << 14)				//!<position, watchdog, unit timer, capture timer unaffected by emu suspend
} QEPCTL_Freesoft_e;

//! \brief Position counter reset mode
//!
typedef enum
{
	QEPCTL_Pcrm_Index_Reset=(0 << 12),						//!<position counter reset on index event
	QEPCTL_Pcrm_Max_Reset=(1 << 12),						//!<position counter reset on max position
	QEPCTL_Pcrm_First_Index_Reset=(2 << 12),				//!<position counter reset on first index event
	QEPCTL_Pcrm_Unit_Time_Reset=(3 << 12)					//!<position counter reset on unit time event
} QEPCTL_Pcrm_e;

//! \brief Strobe event initialization of position counter
//!
typedef enum
{
	QEPCTL_Sei_Nothing=(0 << 10),							//!<does nothing
	QEPCTL_Sei_Rising_Edge_Init=(2 << 10),					//!<initializes on rising edge of QEPS signal
	QEPCTL_Sei_Rising_Falling_Edge_Init=(3 << 10)			//!<initializes on rising/falling edge of QEPS signal
} QEPCTL_Sei_e;

//! \brief Index event initialization of position counter
//!
typedef enum
{
	QEPCTL_Iei_Nothing=(0 << 8),							//!<does nothing
	QEPCTL_Iei_Rising_Edge_Init=(2 << 8),					//!<initializes on rising edge of QEPI signal
	QEPCTL_Iei_Rising_Falling_Edge_Init=(3 << 8)			//!<initializes on falling edge of QEPI signal
} QEPCTL_Iei_e;

//! \brief Software initialization of position counter
//!
typedef enum
{
	QEPCTL_Swi_Nothing=(0 << 7),							//!<does nothing
	QEPCTL_Swi_Auto_Init_Counter=(1 << 7)					//!<init position counter (QPOSCNT=QPOSINIT)
} QEPCTL_Swi_e;

//! \brief Strobe event latch of position counter
//!
typedef enum
{
	QEPCTL_Sel_Rising_Edge=(0 << 6),						//!<Position counter latched on rising edge of QEPS strobe (QPOSSLAT = POSCCNT)
	QEPCTL_Sel_Rising_Falling_Edge=(1 << 6)					//!<Clockwise: position counter latched on rising edge, counter clockwise: latched on falling edge
} QEPCTL_Sel_e;
	
//! \brief Index event latch of position counter (software index marker)
//!
typedef enum
{
	QEPCTL_Iel_Rising_Edge=(1 << 4),						//!<latches position counter on rising edge of index signal
	QEPCTL_Iel_Falling_Edge=(2 << 4),						//!<ditto on falling edge of index signal
	QEPCTL_Iel_Software_Index_Marker=(3 << 4)				//!<software index marker.  See data sheet.
} QEPCTL_Iel_e;

//! \brief QEP capture latch mode
//!
typedef enum
{
	QEPCTL_Qclm_Latch_on_CPU_Read=(0 << 2),					//!<latch on position counter read by cpu
	QEPCTL_Qclm_Latch_on_Unit_Timeout=(1 << 2)				//!<latch on unit time out
} QEPCTL_Qclm_e;

//! \brief Position compare shadow enable
//!
typedef enum
{
	QPOSCTL_Pcshdw_Load_Immediate=(0 << 15),				//!<shadow disabled, load immediate
	QPOSCTL_Pcshdw_Shadow_Enabled=(1 << 15)					//!<shadow enabled
} QPOSCTL_Pcshdw_e;

//! \brief Position compare shadow load mode
//!
typedef enum
{
	QPOSCTL_Pcload_Load_Posn_Count_Zero=(0 << 14),			//!<load on qposcnt = 0
	QPOSCTL_Pcload_Load_Posn_Count_Equal_Compare=(1 << 14)	//!<load when qposcnt = qposcmp
} QPOSCTL_Pcload_e;

//! \brief Polarity of sync output
//!
typedef enum
{
	QPOSCTL_Pcpol_Active_High=(0 << 13),					//!<active high pulse output
	QPOSCTL_Pcpol_Active_Low=(1 << 13)						//!<active low pulse output
} QPOSCTL_Pcpol_e;

//! \brief QEP capture timer clock prescaler
//!
typedef enum
{
	QCAPCTL_Ccps_Capture_Div_1=(0 << 4),					//!<capclk = sysclkout/1
	QCAPCTL_Ccps_Capture_Div_2=(1 << 4),					//!<capclk = sysclkout/2
	QCAPCTL_Ccps_Capture_Div_4=(2 << 4),					//!<capclk = sysclkout/4
	QCAPCTL_Ccps_Capture_Div_8=(3 << 4),					//!<capclk = sysclkout/8
	QCAPCTL_Ccps_Capture_Div_16=(4 << 4),					//!<capclk = sysclkout/16
	QCAPCTL_Ccps_Capture_Div_32=(5 << 4),					//!<capclk = sysclkout/32
	QCAPCTL_Ccps_Capture_Div_64=(6 << 4),					//!<capclk = sysclkout/64
	QCAPCTL_Ccps_Capture_Div_128=(7 << 4)					//!<capclk = sysclkout/128
} QCAPCTL_Ccps_e;

//! \brief Unit position event prescaler
//!
typedef enum
{
	QCAPCTL_Upps_Div_1_Prescale=(0 << 0),					//!<upevnt = qclk/1
	QCAPCTL_Upps_Div_2_Prescale=(1 << 0),					//!<upevnt = qclk/2
	QCAPCTL_Upps_Div_4_Prescale=(2 << 0),					//!<upevnt = qclk/4
	QCAPCTL_Upps_Div_8_Prescale=(3 << 0),					//!<upevnt = qclk/8
	QCAPCTL_Upps_Div_16_Prescale=(4 << 0),					//!<upevnt = qclk/16
	QCAPCTL_Upps_Div_32_Prescale=(5 << 0),					//!<upevnt = qclk/32
	QCAPCTL_Upps_Div_64_Prescale=(6 << 0),					//!<upevnt = qclk/64
	QCAPCTL_Upps_Div_128_Prescale=(7 << 0),					//!<upevnt = qclk/128
	QCAPCTL_Upps_Div_256_Prescale=(8 << 0),					//!<upevnt = qclk/256
	QCAPCTL_Upps_Div_512_Prescale=(9 << 0),					//!<upevnt = qclk/512
	QCAPCTL_Upps_Div_1024_Prescale=(10 << 0),				//!<upevnt = qclk/1024
	QCAPCTL_Upps_Div_2048_Prescale=(11 << 0)				//!<upevnt = qclk/2048
} QCAPCTL_Upps_e;

//! \brief QEP interrupt enable flags
typedef enum
{
	QEINT_Uto=(1 << 11),									//!<unit time out interrupt enable
	QEINT_Iel=(1 << 10),									//!<index event latch interrupt enable
	QEINT_Sel=(1 << 9),										//!<strobe event latch interrupt enable
	QEINT_Pcm=(1 << 8),										//!<position compare match interrupt enable
	QEINT_Pcr=(1 << 7),										//!<position compare ready interrupt enable 
	QEINT_Pco=(1 << 6),										//!<position compare overflow interrupt enable
	QEINT_Pcu=(1 << 5),										//!<position compare underflow interrupt enable
	QEINT_Wto=(1 << 4),										//!<position compare watchdog time out interrupt enable
	QEINT_Qdc=(1 << 3),										//!<quadrature direction change interrupt enable
	QEINT_Qpe=(1 << 2),										//!<quadrature phase error interrupt enable
	QEINT_Pce=(1 << 1)										//!<position counter interrupt enable
} QEINT_e;

#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
//! \brief Defines the QEP object
//!
typedef struct _QEP_Obj_
{
  uint32_t      QPOSCNT;       //!< QEP Position Counter
  uint32_t      QPOSINIT;      //!< QEP Initialization Position Count
  uint32_t      QPOSMAX;       //!< QEP Maximum Position Count
  uint32_t      QPOSCMP;       //!< QEP Position Compare
  uint32_t      QPOSILAT;      //!< QEP Index Position Latch
  uint32_t      QPOSSLAT;      //!< QEP Strobe Position Latch
  uint32_t      QPOSLAT;       //!< QEP Position Latch
  uint32_t      QUTMR;         //!< QEP Unit Timer
  uint32_t      QUPRD;         //!< QEP Unit Period
  uint16_t		QWDTMR;		   //!< QEP Watchdog Timer
  uint16_t		QWDPRD;		   //!< QEP Watchdog Period
  uint16_t		QDECCTL;	   //!< QEP Decoder Control
  uint16_t		QEPCTL;		   //!< QEP Control
  uint16_t		QCAPCTL;	   //!< QEP Capture Control
  uint16_t		QPOSCTL;	   //!< QEP Position Compare Control
  uint16_t		QEINT;		   //!< QEP Interrupt Enable Register
  uint16_t		QFLG;		   //!< QEP Interrupt Flag Register
  uint16_t		QCLR;		   //!< QEP Interrupt Clear Register
  uint16_t		QFRC;		   //!< QEP Interrupt Force Register
  uint16_t		QEPSTS;		   //!< QEP Status Register
  uint16_t		QCTMR;		   //!< QEP Capture Timer
  uint16_t		QCPRD;		   //!< QEP Capture Period
  uint16_t		QCTMRLAT;	   //!< QEP Capture Timer Latch
  uint16_t		QCPRDLAT;	   //!< QEP Capture Period Latch
  uint16_t		rsvd_1;	   //!< QEP Capture Period Latch
} QEP_Obj;

//----------------------------------------------------
#else
//! \brief Defines the QEP object
//!
typedef struct _QEP_Obj_
{
  uint32_t      QPOSCNT;       //!< QEP Position Counter
  uint32_t      QPOSINIT;      //!< QEP Initialization Position Count
  uint32_t      QPOSMAX;       //!< QEP Maximum Position Count
  uint32_t      QPOSCMP;       //!< QEP Position Compare
  uint32_t      QPOSILAT;      //!< QEP Index Position Latch
  uint32_t      QPOSSLAT;      //!< QEP Strobe Position Latch
  uint32_t      QPOSLAT;       //!< QEP Position Latch
  uint32_t      QUTMR;         //!< QEP Unit Timer
  uint32_t      QUPRD;         //!< QEP Unit Period
  uint16_t		QWDPRD;		   //!< QEP Watchdog Period
  uint16_t		QWDTMR;		   //!< QEP Watchdog Timer
  uint16_t		QEPCTL;		   //!< QEP Control
  uint16_t		QDECCTL;	   //!< QEP Decoder Control
  uint16_t		QPOSCTL;	   //!< QEP Position Compare Control
  uint16_t		QCAPCTL;	   //!< QEP Capture Control
  uint16_t		QFLG;		   //!< QEP Interrupt Flag Register
  uint16_t		QEINT;		   //!< QEP Interrupt Enable Register
  uint16_t		QFRC;		   //!< QEP Interrupt Force Register
  uint16_t		QCLR;		   //!< QEP Interrupt Clear Register
  uint16_t		QCTMR;		   //!< QEP Capture Timer
  uint16_t		QEPSTS;		   //!< QEP Status Register
  uint16_t		QCTMRLAT;	   //!< QEP Capture Timer Latch
  uint16_t		QCPRD;		   //!< QEP Capture Period
  uint16_t		rsvd_1;	   //!< QEP Capture Period Latch
  uint16_t		QCPRDLAT;	   //!< QEP Capture Period Latch
} QEP_Obj;



#endif

//! \brief Defines the QEP handle
//!
typedef struct QEP_Obj  *QEP_Handle;


// **************************************************************************
// the globals


// **************************************************************************
// the function prototypes

//! \brief Clears all QEP interrupt flags
//! \param[in] qepHandle		Handle to QEP object
void QEP_clear_all_interrupt_flags (QEP_Handle qepHandle);

//! \brief Clears a single interrupt flag
//! \param[in] qepHandle		Handle to QEP object
//! \param[in] QEINT			Interrupt flag
void QEP_clear_interrupt_flag (QEP_Handle qepHandle, const QEINT_e QEINT);

//! \brief Clears the position counter
//! \param[in] qepHandle		Handle to QEP object
void QEP_clear_posn_counter (QEP_Handle qepHandle);

//! \brief Clears the decoder control register
//! \param[in] qepHandle		Handle to QEP object
void QEP_clear_decode_control (QEP_Handle qepHandle);

//! \brief Clears the qep control register
//! \param[in] qepHandle		Handle to QEP object
void QEP_clear_qep_control (QEP_Handle qepHandle);

//! \brief Clears the cap control register
//! \param[in] qepHandle		Handle to QEP object
void QEP_clear_cap_control (QEP_Handle qepHandle);

//! \brief Disables all interrupts
//! \param[in] qepHandle		Handle to QEP object
void QEP_disable_all_interrupts (QEP_Handle qepHandle);

//! \brief Disable capture
//! \param[in] qepHandle		Handle to QEP object
void QEP_disable_capture (QEP_Handle qepHandle);

//! \brief Disable gating of index pulse
//! \param[in] qepHandle		Handle to QEP object
void QEP_disable_gate_index (QEP_Handle qepHandle);

//! \brief Disable individual interrupt
//! \param[in] qepHandle		Handle to QEP object
//! \param[in] QEINT			Individual interrupts
void QEP_disable_interrupt (QEP_Handle qepHandle, const QEINT_e QEINT);

//! \brief Disable position compare
//! \param[in] qepHandle		Handle to QEP object
void QEP_disable_posn_compare (QEP_Handle qepHandle);

//! \brief Disable position compare shadowing
//! \param[in] qepHandle		Handle to QEP object
void QEP_disable_posn_compare_shadow (QEP_Handle qepHandle);

//! \brief Disable output sync pulse
//! \param[in] qepHandle		Handle to QEP object
void QEP_disable_sync_out (QEP_Handle qepHandle);

//! \brief Disable unit timer
//! \param[in] qepHandle		Handle to QEP object
void QEP_disable_unit_timer (QEP_Handle qepHandle);

//! \brief Disable watchdog timer
//! \param[in] qepHandle		Handle to QEP object
void QEP_disable_watchdog (QEP_Handle qepHandle);

//! \brief Enable capture
//! \param[in] qepHandle		Handle to QEP object
void QEP_enable_capture (QEP_Handle qepHandle);

//! \brief Enable counter
//! \param[in] qepHandle		Handle to QEP object
void QEP_enable_counter (QEP_Handle qepHandle);

//! \brief Enable gating of index pulse
//! \param[in] qepHandle		Handle to QEP object
void QEP_enable_gate_index (QEP_Handle qepHandle);

//! \brief Enable individual interrupt
//! \param[in] qepHandle		Handle to QEP object
//! \param[in] QEINT			Individual interrupts
void QEP_enable_interrupt (QEP_Handle qepHandle, const QEINT_e QEINT);

//! \brief Enable position compare
//! \param[in] qepHandle		Handle to QEP object
void QEP_enable_posn_compare (QEP_Handle qepHandle);

//! \brief Enable position compare shadowing
//! \param[in] qepHandle		Handle to QEP object
void QEP_enable_posn_compare_shadow (QEP_Handle qepHandle);

//! \brief Enable output sync pulse
//! \param[in] qepHandle		Handle to QEP object
void QEP_enable_sync_out (QEP_Handle qepHandle);

//! \brief Enable unit timer
//! \param[in] qepHandle		Handle to QEP object
void QEP_enable_unit_timer (QEP_Handle qepHandle);

//! \brief Enable watchdog timer
//! \param[in] qepHandle		Handle to QEP object
void QEP_enable_watchdog (QEP_Handle qepHandle);

//! \brief Manually force QEP interrupt
//! \param[in] qepHandle		Handle to QEP object
//! \param[in] QEINT			Individual interrupt
void QEP_force_interrupt (QEP_Handle qepHandle, const QEINT_e QEINT);

//! \brief Initializes the QEP object
//! \param[in] pMemory			Memory pointer for new object
//! \param[in] numBytes			Object size
//! \return						QEP Handle
QEP_Handle QEP_init(void *pMemory,const size_t numBytes);

//! \brief Reads capture period latch
//! \param[in] qepHandle		Handle to QEP object
//! \return						Counter value
uint16_t QEP_read_capture_period_latch (QEP_Handle qepHandle);

//! \brief Reads timer latch
//! \param[in] qepHandle		Handle to QEP object
//! \return						Timer value
uint16_t QEP_read_capture_timer_latch (QEP_Handle qepHandle);

//! \brief Reads interrupt flag value
//! \param[in] qepHandle		Handle to QEP object
//! \param[in] QEINT			Which interrupt to interrogate
//! \return						Interrupt flag value
uint16_t QEP_read_interrupt_flag (QEP_Handle qepHandle, const QEINT_e QEINT);

//! \brief Reads position compare register
//! \param[in] qepHandle		Handle to QEP object
//! \return						Counter value
uint32_t QEP_read_posn_compare (QEP_Handle qepHandle);

//! \brief Reads position counter
//! \param[in] qepHandle		Handle to QEP object
//! \return						Counter value
uint32_t QEP_read_posn_count (QEP_Handle qepHandle);

//! \brief Reads position counter value index pulse latch register
//! \param[in] qepHandle		Handle to QEP object
//! \return						Counter value
uint32_t QEP_read_posn_index_latch (QEP_Handle qepHandle);

//! \brief Reads position counter value
//! \param[in] qepHandle		Handle to QEP object
//! \return						Counter value
uint32_t QEP_read_posn_latch (QEP_Handle qepHandle);

//! \brief Reads position strobe latch
//! \param[in] qepHandle		Handle to QEP object
//! \return						Counter value
uint32_t QEP_read_posn_strobe_latch (QEP_Handle qepHandle);

//! \brief Reads status register
//! \param[in] qepHandle		Handle to QEP object
//! \return						Status register value
uint16_t QEP_read_status (QEP_Handle qepHandle);

//! \brief Resets counter
//! \param[in] qepHandle		Handle to QEP object
void QEP_reset_counter (QEP_Handle qepHandle);

//! \brief Sets capture latch mode
//! \param[in] qepHandle		Handle to QEP object
//! \param[in] QEPCTL_Qclm		capture latch mode
void QEP_set_capture_latch_mode (QEP_Handle qepHandle, const QEPCTL_Qclm_e QEPCTL_Qclm);

//! \brief Sets capture period
//! \param[in] qepHandle		Handle to QEP object
//! \param[in] period			Capture period
void QEP_set_capture_period (QEP_Handle qepHandle, const uint16_t period);

//! \brief Sets capture pre-scaler
//! \param[in] qepHandle		Handle to QEP object
//! \param[in] QCAPCTL_Ccps		Capture pre-scaler 
void QEP_set_capture_prescale (QEP_Handle qepHandle, const QCAPCTL_Ccps_e QCAPCTL_Ccps);

//! \brief Sets emulation control
//! \param[in] qepHandle		Handle to QEP object
//! \param[in] QEPCTL_Freesoft	Emulation control bits
void QEP_set_emu_control (QEP_Handle qepHandle, const QEPCTL_Freesoft_e QEPCTL_Freesoft);

//! \brief Sets external clock rate
//! \param[in] qepHandle		Handle to QEP object
//! \param[in] QEP_Xcr			External clock rate
void QEP_set_ext_clock_rate (QEP_Handle qepHandle, const QEP_Xcr_e QEP_Xcr);

//! \brief Sets the event which initializes the counter register
//! \param[in] qepHandle		Handle to QEP object
//! \param[in] QEPCTL_Iei		Index event
void QEP_set_index_event_init (QEP_Handle qepHandle, const QEPCTL_Iei_e QEPCTL_Iei);

//! \brief Sets the index event which latches the position counter 
//! \param[in] qepHandle		Handle to QEP object
//! \param[in] QEPCTL_Iel		Latch event
void QEP_set_index_event_latch (QEP_Handle qepHandle, const QEPCTL_Iel_e QEPCTL_Iel);

//! \brief Sets index polarity
//! \param[in] qepHandle		Handle to QEP object
//! \param[in] QEP_Qip			Index polarity
void QEP_set_index_polarity (QEP_Handle qepHandle, const QEP_Qip_e QEP_Qip);

//! \brief Sets max position count
//! \param[in] qepHandle		Handle to QEP object
//! \param[in] max_count		Maximum counter value
void QEP_set_max_posn_count (QEP_Handle qepHandle, const uint32_t max_count);

//! \brief Sets output pulse width when a match occur
//! \param[in] qepHandle		Handle to QEP object
//! \param[in] pulse_width		Pulse width value
void QEP_set_posn_compare_pulse_width (QEP_Handle qepHandle, const uint16_t pulse_width);

//! \brief Sets position compare shadow load mode
//! \param[in] qepHandle		Handle to QEP object
//! \param[in] QPOSCTL_Pcload	PC load event	
void QEP_set_posn_compare_shadow_load (QEP_Handle qepHandle, const QPOSCTL_Pcload_e QPOSCTL_Pcload);

//! \brief Sets position counter reset mode
//! \param[in] qepHandle		Handle to QEP object
//! \param[in] QEPCTL_Pcrm		Position counter reset mode
void QEP_set_posn_count_reset_mode (QEP_Handle qepHandle, const QEPCTL_Pcrm_e QEPCTL_Pcrm);

//! \brief Sets initial position counter value
//! \param[in] qepHandle		Handle to QEP object
//! \param[in] init_count		initial counter value
void QEP_set_posn_init_count (QEP_Handle qepHandle, const uint32_t init_count);

//! \brief Selects whether index or strobe pin is used for sync output
//! \param[in] qepHandle		Handle to QEP object
//! \param[in] QEP_SPsel		Selected pin
void QEP_set_select_sync_pin (QEP_Handle qepHandle, const QEP_Spsel_e QEP_SPsel);

//! \brief Determines if software initialization of position counter enabled 
//! \param[in] qepHandle		Handle to QEP object
//! \param[in] QEPCTL_Swi		Enable/disable position counter initialization
void QEP_set_soft_init (QEP_Handle qepHandle, const QEPCTL_Swi_e QEPCTL_Swi);

//! \brief Determines strobe initialization of position counter 
//! \param[in] qepHandle		Handle to QEP object
//! \param[in] QEPCTL_Sei		Strobe initialization of position counter (disabled, rising edge of QEPI) or rising/falling depending on direction
void QEP_set_strobe_event_init (QEP_Handle qepHandle, const QEPCTL_Sei_e QEPCTL_Sei);

//! \brief Sets up strobe latch of position counter 
//! \param[in] qepHandle		Handle to QEP object
//! \param[in] QEPCTL_Sel		Sets strobe latch of position counter
void QEP_set_strobe_event_latch (QEP_Handle qepHandle, const QEPCTL_Sel_e QEPCTL_Sel);

//! \brief Sets up strobe polarity 
//! \param[in] qepHandle		Handle to QEP object
//! \param[in] QEP_Qsp			Strobe polarity
void QEP_set_strobe_polarity (QEP_Handle qepHandle, const QEP_Qsp_e QEP_Qsp);

//! \brief Sets up swapping of A/B channels
//! \param[in] qepHandle		Handle to QEP object
//! \param[in] QEP_Swap			Swap/don't swap A/B channels
void QEP_set_swap_quad_inputs (QEP_Handle qepHandle, QEP_Swap_e QEP_Swap);

//! \brief Sets synch output compare polarity
//! \param[in] qepHandle		Handle to QEP object
//! \param[in] QPOSCTL_Pcpol	Polarity of sync output
void QEP_set_synch_output_compare_polarity (QEP_Handle qepHandle, const QPOSCTL_Pcpol_e QPOSCTL_Pcpol);

//! \brief Sets unit timer period
//! \param[in] qepHandle		Handle to QEP object
//! \param[in] unit_period		Unit period
void QEP_set_unit_period (QEP_Handle qepHandle, const uint32_t unit_period);

//! \brief Sets unit timer prescaling
//! \param[in] qepHandle		Handle to QEP object
//! \param[in] QCAPCTL_Upps		Unit timer prescaling
void QEP_set_unit_posn_prescale (QEP_Handle qepHandle, const QCAPCTL_Upps_e QCAPCTL_Upps);

//! \brief Sets watchdog period
//! \param[in] qepHandle		Handle to QEP object
//! \param[in] watchdog_period	Watchdog period
void QEP_set_watchdog_period (QEP_Handle qepHandle, const uint16_t watchdog_period);

//! \brief Sets A polarity
//! \param[in] qepHandle		Handle to QEP object
//! \param[in] QEP_Qap			Channel A polarity
void QEP_set_A_polarity (QEP_Handle qepHandle, const QEP_Qap_e QEP_Qap);

//! \brief Sets B polarity
//! \param[in] qepHandle		Handle to QEP object
//! \param[in] QEP_Qbp			Channel B polarity
void QEP_set_B_polarity (QEP_Handle qepHandle, const QEP_Qbp_e QEP_Qbp);

//! \brief QEP counting mode
//! \param[in] qepHandle		Handle to QEP object
//! \param[in] QEP_Qsrc			Sets QEP counting mode	
void QEP_set_QEP_source (QEP_Handle qepHandle, const QEP_Qsrc_e QEP_Qsrc);

//! \brief Writes a value to the position compare register
//! \param[in] qepHandle		Handle to QEP object
//! \param[in] posn				Position compare register value
void QEP_write_posn_compare (QEP_Handle qepHandle, const uint32_t posn);

#ifdef __cplusplus
}
#endif // "C"

//@}  // ingroup

#endif // end of _QEP_H_ definition

