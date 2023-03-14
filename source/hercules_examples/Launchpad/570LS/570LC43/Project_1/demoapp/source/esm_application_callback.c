/*
 * esm_application_callback.c
 *
 *  Created on: Jun 21, 2013
 *      Author: a0131910
 */

#include <sl_api.h>
#include <HL_sci.h>

#define ESM_GRP1_MASK (1U<<16U)
#define ESM_GRP2_MASK (2U<<16U)
#define BIT(n)                  ((uint32)((uint32)1u <<(n)))
#define GET_ESM_BIT_NUM(x)		((x)<(uint32)32U? (BIT((x))): (BIT(((x)-(uint32)32U))))


extern void _SL_HoldNClear_nError();
extern void sciDisplayText(sciBASE_t *sci, uint8 *text, uint32 length);

void ESM_ApplicationCallback(uint32 grp_channel, uint32 param1, uint32 param2, uint32 param3)
{
    uint32 channel;
    channel = grp_channel & 0xffffu;
    if ((grp_channel & ESM_GRP1_MASK) == ESM_GRP1_MASK)
    {
        if (ESM_G1ERR_CCMR5_SELFTEST == channel)
        {
            sl_esmREG->SR1[0] = GET_ESM_BIT_NUM(channel);
            /* no need to set the flag cccmr5f_errorforcing_app_callback, as the
             * flag is already set by the G2 error */
        }
        /*whenever the there is LPOCLK detect then the channel 11 and 10 esm GROUP1 errors are set*/
        if (10 == channel)
        {
            sl_esmREG->SR1[0] = GET_ESM_BIT_NUM(10)|GET_ESM_BIT_NUM(11);
            /* no need to set the flag cccmr5f_errorforcing_app_callback, as the
             * flag is already set by the G2 error */
            sciDisplayText(sciREG1,(uint8*)"CLOCKMONITOR ESM on LPOCCLOCK detect\r\n",38);
        }
        /*whenever the there is LPOCLK detect then the channel 11 and 10 esm GROUP1 errors are set*/
        if (11 == channel)
        {
            sl_esmREG->SR1[0] = GET_ESM_BIT_NUM(10)|GET_ESM_BIT_NUM(11);
            /* no need to set the flag cccmr5f_errorforcing_app_callback, as the
             * flag is already set by the G2 error */
            sciDisplayText(sciREG1,(uint8*)"CLOCKMONITOR ESM on LPOCCLOCK detect\r\n",38);
        }
    }
    if ((grp_channel & ESM_GRP2_MASK) == ESM_GRP2_MASK)
    {
    	/* process group 2 call-backs */
    	if ((ESM_G2ERR_CCMR5_CPUCOMP_ERR == channel))

    	{
    		sciDisplayText(sciREG1,(uint8*)"CCM-R5F - CPU compare error detected\r\n",38);
    		__asm(" B #-8 ");
    	}
    }

}
