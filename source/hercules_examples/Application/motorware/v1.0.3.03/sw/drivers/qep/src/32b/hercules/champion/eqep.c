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
//! \file   ~sw/drivers/qep/src/32b/hercules/champion/qep.c
//! \brief  Contains the various functions related to the 
//!         QEP (quadrature position decoder) object.
//!
//! (C) Copyright 2011, Texas Instruments, Inc.


// **************************************************************************
// the includes

#include "eqep.h"


// **************************************************************************
// the defines


// **************************************************************************
// the globals


// **************************************************************************
// the functions

void QEP_clear_all_interrupt_flags (QEP_Handle qepHandle)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QCLR = 0xfff;
  
  return;	
} // end of QEP_clear_all_interrupt_flags() function

void QEP_clear_interrupt_flag (QEP_Handle qepHandle, const QEINT_e QEINT)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QCLR |= QEINT;
  
  return;	
} // end of QEP_clear_interrupt_flag() function

void QEP_clear_posn_counter (QEP_Handle qepHandle)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QPOSCNT = 0;	
  
  return;
} // end of QEP_clear_posn_counter() function

void QEP_clear_decode_control (QEP_Handle qepHandle)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QDECCTL = 0;

  return;
} // end of QEP_clear_decode_control() function

void QEP_clear_qep_control (QEP_Handle qepHandle)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QEPCTL = 0;

  return;
} // end of QEP_clear_qep_control() function

void QEP_clear_cap_control (QEP_Handle qepHandle)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QCAPCTL = 0;

  return;
} // end of QEP_clear_qep_control() function

void QEP_disable_all_interrupts (QEP_Handle qepHandle)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QEINT = 0;
  
  return;
} // end of QEP_disable_all_interrupts () function

void QEP_disable_capture (QEP_Handle qepHandle)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QCAPCTL &= (~QEP_QCAPCTL_CEN);
  
  return;	
} // end of QEP_disable_capture () function

void QEP_disable_gate_index (QEP_Handle qepHandle)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QDECCTL &= (~QEP_QDECCTL_IGATE);	
  
  return;
} // end of QEP_disable_gate_index () function

void QEP_disable_interrupt (QEP_Handle qepHandle, const QEINT_e QEINT)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QEINT &= (~QEINT);
  
  return;
} // end of QEP_disable_interrupt

void QEP_disable_posn_compare (QEP_Handle qepHandle)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QPOSCTL &= (~QEP_QPOSCTL_PCE);
  
  return;	
} // end of QEP_disable_posn_compare () function

void QEP_disable_posn_compare_shadow (QEP_Handle qepHandle)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QPOSCTL &= (~QEP_QPOSCTL_PCSHDW);
  
  return;	
} // end of QEP_disable_posn_compare_shadow () function

void QEP_disable_sync_out (QEP_Handle qepHandle)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QDECCTL &= (~QEP_QDECCTL_SOEN);
  
  return;
} // end of QEP_disable_sync_out () function

void QEP_disable_unit_timer (QEP_Handle qepHandle)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QEPCTL &= (~QEP_QEPCTL_UTE);
  
  return; 	
} // end of QEP_disable_unit_timer () function

void QEP_disable_watchdog (QEP_Handle qepHandle)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QEPCTL &= (~QEP_QEPCTL_WDE); 	
  
  return;
} // end of QEP_disable_watchdog () function

void QEP_enable_capture (QEP_Handle qepHandle)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QCAPCTL |= (uint32_t)QEP_QCAPCTL_CEN;	
  
  return;
} // end of QEP_enable_capture () function

void QEP_enable_counter (QEP_Handle qepHandle)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QEPCTL |= QEP_QEPCTL_QPEN;	
  
  return;
} // end of QEP_enable_counter () function

void QEP_enable_gate_index (QEP_Handle qepHandle)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QDECCTL |= QEP_Igate_Enable;	
  
  return;
} // end of QEP_enable_gate_index () function

void QEP_enable_interrupt (QEP_Handle qepHandle, const QEINT_e QEINT)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QEINT |= QEINT;	
  
  return;
} // end of QEP_enable_interrupt () function

void QEP_enable_posn_compare (QEP_Handle qepHandle)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QPOSCTL |= QEP_QPOSCTL_PCE;	
  
  return;
} // end of QEP_enable_posn_compare () function

void QEP_enable_posn_compare_shadow (QEP_Handle qepHandle)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QPOSCTL |= (uint32_t)QEP_QPOSCTL_PCSHDW;	
  
  return;
} // end of QEP_enable_posn_compare_shadow () function

void QEP_enable_sync_out (QEP_Handle qepHandle)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QDECCTL |= QEP_QDECCTL_SOEN;
  
  return;
} // end of QEP_enable_sync_out () function

void QEP_enable_unit_timer (QEP_Handle qepHandle)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QEPCTL |= QEP_QEPCTL_UTE;
  
  return; 	
} // end of QEP_enable_unit_timer () function

void QEP_enable_watchdog (QEP_Handle qepHandle)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QEPCTL |= QEP_QEPCTL_WDE; 	
  
  return;
} // end of QEP_enable_watchdog () function

void QEP_force_interrupt (QEP_Handle qepHandle, const QEINT_e QEINT)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QFRC |= QEINT;
  
  return;	
} // end of QEP_force_interrupt () function

QEP_Handle QEP_init(void *pMemory,const size_t numBytes)
{
  QEP_Handle qepHandle;

  if(numBytes < sizeof(QEP_Obj))
    return((QEP_Handle)NULL);

  // assign the handle
  qepHandle = (QEP_Handle)pMemory;
  
  return(qepHandle);
} // end of QEP_init() function

uint16_t QEP_read_capture_period_latch (QEP_Handle qepHandle)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  return qep->QCPRDLAT;	
} // end of QEP_read_capture_period_latch () function

uint16_t QEP_read_capture_timer_latch (QEP_Handle qepHandle)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  return qep->QCTMRLAT;	
} // end of QEP_read_capture_timer_latch () function

uint16_t QEP_read_interrupt_flag (QEP_Handle qepHandle, const QEINT_e QEINT)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;
	
	return (uint16_t) (qep->QFLG & QEINT); 
} // end of QEP_read_interrupt_flag () function

uint32_t QEP_read_posn_compare (QEP_Handle qepHandle)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  return qep->QPOSCMP;	
} // end of QEP_read_posn_compare () function

uint32_t QEP_read_posn_count (QEP_Handle qepHandle)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  return qep->QPOSCNT;	
} // end of QEP_read_posn_count () function

uint32_t QEP_read_posn_index_latch (QEP_Handle qepHandle)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  return qep->QPOSILAT;	
} // end of QEP_read_posn_index_latch () function

uint32_t QEP_read_posn_latch (QEP_Handle qepHandle)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  return qep->QPOSLAT;	
} // end of QEP_read_posn_latch () function

uint32_t QEP_read_posn_strobe_latch (QEP_Handle qepHandle)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  return qep->QPOSSLAT;	
} // end of QEP_read_posn_strobe_latch () function

uint16_t QEP_read_status (QEP_Handle qepHandle)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  return qep->QEPSTS;	
} // end of QEP_read_status () function

void QEP_reset_counter (QEP_Handle qepHandle)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QEPCTL &= (~QEP_QEPCTL_QPEN);
  
  return;	
} // end of QEP_reset_counter () function

void QEP_set_capture_latch_mode (QEP_Handle qepHandle, const QEPCTL_Qclm_e QEPCTL_Qclm)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QEPCTL &= (~QEP_QEPCTL_QCLM);
  qep->QEPCTL |= QEPCTL_Qclm;
  
  return;
} // end of QEP_set_capture_latch_mode () function

void QEP_set_capture_period (QEP_Handle qepHandle, const uint16_t period)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QCPRD = period;	
  
  return;
} // end of QEP_set_capture_period () function

void QEP_set_capture_prescale (QEP_Handle qepHandle, const QCAPCTL_Ccps_e QCAPCTL_Ccps)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QCAPCTL &= (~QEP_QCAPCTL_CCPS);
  qep->QCAPCTL |= QCAPCTL_Ccps;
} // end of QEP_set_capture_prescale () function

void QEP_set_emu_control (QEP_Handle qepHandle, const QEPCTL_Freesoft_e QEPCTL_Freesoft)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QEPCTL &= (~QEP_QEPCTL_FREESOFT);
  qep->QEPCTL |= QEPCTL_Freesoft; 	
  
  return;
} // end of QEP_set_emu_control () function

void QEP_set_ext_clock_rate (QEP_Handle qepHandle, const QEP_Xcr_e QEP_Xcr)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QDECCTL &= (~QEP_QDECCTL_XCR);
  qep->QDECCTL |= QEP_Xcr;	
  
  return;
} // end of QEP_set_ext_clock_rate () function

void QEP_set_index_event_init (QEP_Handle qepHandle, const QEPCTL_Iei_e QEPCTL_Iei)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QEPCTL &= (~QEP_QEPCTL_IEI);
  qep->QEPCTL |= QEPCTL_Iei;
  
  return;	
} // end of QEP_set_index_event_init () function

void QEP_set_index_event_latch (QEP_Handle qepHandle, const QEPCTL_Iel_e QEPCTL_Iel)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QEPCTL &= (~QEP_QEPCTL_IEL);
  qep->QEPCTL |= QEPCTL_Iel;
  
  return;
} // end of QEP_set_index_event_latch

void QEP_set_index_polarity (QEP_Handle qepHandle, const QEP_Qip_e QEP_Qip)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QDECCTL &= (~QEP_QDECCTL_QIP);
  qep->QDECCTL |= QEP_Qip;
  
  return;
} // end of QEP_set_index_polarity () function

void QEP_set_max_posn_count (QEP_Handle qepHandle, const uint32_t max_count)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QPOSMAX = max_count;	
  
  return;
} // end of QEP_set_max_posn_count () function

void QEP_set_posn_compare_pulse_width (QEP_Handle qepHandle, const uint16_t pulse_width)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;
  uint16_t pulse_width_masked;

  pulse_width_masked = pulse_width & 4095;
  qep->QPOSCTL &= (~QEP_QPOSCTL_PCSPW);
  qep->QPOSCTL |= pulse_width_masked;
  
  return;
} // end of QEP_set_posn_compare_pulse_width () function

void QEP_set_posn_compare_shadow_load (QEP_Handle qepHandle, const QPOSCTL_Pcload_e QPOSCTL_Pcload)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QPOSCTL &= (~QEP_QPOSCTL_PCLOAD);
  qep->QPOSCTL |= QPOSCTL_Pcload;
  
  return;
} // end of QEP_set_posn_compare_shadow_load () function

void QEP_set_posn_count_reset_mode (QEP_Handle qepHandle, const QEPCTL_Pcrm_e QEPCTL_Pcrm)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QEPCTL &= (~QEP_QEPCTL_PCRM);
  qep->QEPCTL |= QEPCTL_Pcrm;
  
  return; 	
} // end of QEP_set_posn_count_reset_mode () function

void QEP_set_posn_init_count (QEP_Handle qepHandle, uint32_t init_count)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;
  
  qep->QPOSINIT = init_count;
  
  return;
} // end of QEP_set_posn_init_count () function

void QEP_set_select_sync_pin (QEP_Handle qepHandle, const QEP_Spsel_e QEP_SPsel)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;
  
  qep->QDECCTL &= (~QEP_QDECCTL_SPSEL);
  qep->QDECCTL |= QEP_SPsel;
  
  return;
} // end of QEP_set_select_sync_pin () function

void QEP_set_soft_init (QEP_Handle qepHandle, const QEPCTL_Swi_e QEPCTL_Swi)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QEPCTL &= (~QEP_QEPCTL_SWI);
  qep->QEPCTL |= QEPCTL_Swi;
  
  return;
} // end of QEP_set_soft_init () function

void QEP_set_strobe_event_init (QEP_Handle qepHandle, const QEPCTL_Sei_e QEPCTL_Sei)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QEPCTL &= (~QEP_QEPCTL_SEI);
  qep->QEPCTL |= QEPCTL_Sei;
  
  return;
} // end of QEP_set_strobe_event_init () function

void QEP_set_strobe_event_latch (QEP_Handle qepHandle, const QEPCTL_Sel_e QEPCTL_Sel)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QEPCTL &= (~QEP_QEPCTL_SEL);
  qep->QEPCTL |= QEPCTL_Sel;
  
  return;	
} // end of QEP_set_strobe_event_latch () function

void QEP_set_strobe_polarity (QEP_Handle qepHandle, const QEP_Qsp_e QEP_Qsp)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QDECCTL &= (~QEP_QDECCTL_QSP);
  qep->QDECCTL |= QEP_Qsp;
  
  return;
} // end of QEP_set_strobe_polarity () function

void QEP_set_swap_quad_inputs (QEP_Handle qepHandle, QEP_Swap_e QEP_Swap)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QDECCTL &= (~QEP_QDECCTL_SWAP);
  qep->QDECCTL |= QEP_Swap;
  
  return;
} // end of QEP_set_swap_quad_inputs () function

void QEP_set_synch_output_compare_polarity (QEP_Handle qepHandle, const QPOSCTL_Pcpol_e QPOSCTL_Pcpol)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QPOSCTL &= (~QEP_QPOSCTL_PCPOL);
  qep->QPOSCTL |= QPOSCTL_Pcpol;
  
  return;
} // end of QEP_set_synch_output_compare_polarity () function

void QEP_set_unit_period (QEP_Handle qepHandle, const uint32_t unit_period)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QUPRD = unit_period;
  
  return;	
} // end of QEP_set_unit_period () function

void QEP_set_unit_posn_prescale (QEP_Handle qepHandle, const QCAPCTL_Upps_e QCAPCTL_Upps)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QCAPCTL &= (~QEP_QCAPCTL_UPPS);
  qep->QCAPCTL |= QCAPCTL_Upps;
  
  return;
} // end of QEP_set_unit_posn_prescale () function

void QEP_set_watchdog_period (QEP_Handle qepHandle, const uint16_t watchdog_period)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QWDPRD = watchdog_period;
  
  return;	
} // end of QEP_set_watchdog_period () function

void QEP_setup_strobe_event_latch (QEP_Handle qepHandle, const QEPCTL_Sel_e QEPCTL_Sel)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QEPCTL &= (~QEP_QEPCTL_SEL);
  qep->QEPCTL |= QEPCTL_Sel;
  
  return;
} // end of QEP_setup_strobe_event_latch () function


void QEP_set_A_polarity (QEP_Handle qepHandle, const QEP_Qap_e QEP_Qap)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QDECCTL &= (~QEP_QDECCTL_QAP);
  qep->QDECCTL |= QEP_Qap;
  
  return;
} // end of QEP_set_A_polarity () function

void QEP_set_B_polarity (QEP_Handle qepHandle, const QEP_Qbp_e QEP_Qbp)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;

  qep->QDECCTL &= (~QEP_QDECCTL_QBP);
  qep->QDECCTL |= QEP_Qbp;
  
  return;
} // end of QEP_set_B_polarity () function

void QEP_set_QEP_source (QEP_Handle qepHandle, const QEP_Qsrc_e QEP_Qsrc)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;
	  
  // set the value
  qep->QDECCTL &= (~QEP_QDECCTL_QSRC);
  qep->QDECCTL |= QEP_Qsrc;
  
  return;
} // end of QEP_set_QEP_source () function

void QEP_write_posn_compare (QEP_Handle qepHandle, const uint32_t posn)
{
  QEP_Obj *qep = (QEP_Obj *)qepHandle;
  
  qep->QPOSCMP = posn;
  
  return;
} // end of QEP_write_posn_compare () function

// end of file
