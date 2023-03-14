/*
 * esm_application_callback.h
 *
 *  Created on: Jun 21, 2013
 *      Author: a0131910
 */

#ifndef ESM_APPLICATION_CALLBACK_H_
#define ESM_APPLICATION_CALLBACK_H_

#define grp1
#if defined(_TMS570LS31x_) || defined(_TMS570LS12x_) || defined(_RM48x_) || defined(_RM46x_) || defined(_RM42x_) || defined(_TMS570LS04x_)
extern boolean pscon_errorforcing_app_callback;
extern boolean cccmr4f_errorforcing_app_callback;
extern boolean pscon_selftest_errorforcing_app_callback;
extern boolean sram_radecode_diagnostics_app_callback;
extern boolean fee_1bit_faultinject_app_callback;
extern boolean fee_2bit_faultinject_app_callback;
extern boolean sram_1bit_prof_faultinject_callback;
extern boolean sram_2bit_faultinject_callback;
extern boolean flash_2bit_faultinject_callback;
#endif
#if defined(_TMS570LC43x_) || defined(_RM57Lx_)
extern boolean dma_1bit_faultinject_callback;
extern boolean dma_2bit_faultinject_callback;
extern boolean can_1bit_faultinject_callback;
extern boolean can_2bit_faultinject_callback;
extern boolean mibspi_1bit_faultinject_callback;
extern boolean mibspi_2bit_faultinject_callback;
extern boolean cccmr5f_errorforcing_app_callback;
#endif
void ESM_ApplicationCallback(uint32 grp_channel, uint32 param1, uint32 param2, uint32 param3);
extern boolean unknowncallback;
#endif /* ESM_APPLICATION_CALLBACK_H_ */
