/*--------------------------------------------------------*/
/* Fapi_UserDefinedFunctions.c                            */
/*                                                        */
/* Copyright (c) 2010-2011 Texas Instruments Incorporated */
/*                                                        */
/*--------------------------------------------------------*/

/*!
    \file Fapi_UserDefinedFunctions.c
    \brief Contains all user defined functions that the Fapi functions use.
*/

/* Uncomment the appropriate include file for your device */

//#include "bl_config.h"
#include "F021.h"

/*
#if defined(RM48) || defined(RM46) || defined(RM42)
#include "Registers_FMC_LE.h"
#else
#include "Registers_FMC_BE.h"
#endif
*/

Fapi_StatusType Fapi_serviceWatchdogTimer(void)
{
   /* User to add their own watchdog servicing code here */

   return(Fapi_Status_Success);
}

Fapi_StatusType Fapi_setupEepromSectorEnable(void)
{
	FLASH_CONTROL_REGISTER->Fbse.u32Register = 0xFFFF;   /* Value must be 0xFFFF to enable erase and programming of the EEPROM bank, 0 to disable */
	FLASH_CONTROL_REGISTER->FsmSector1.u32Register = 0;  /* Enables/disables sectors  0-31 for bank and sector erase */
	FLASH_CONTROL_REGISTER->FsmSector2.u32Register = 0;  /* Enables/disables sectors 32-63 for bank and sector erase */
   
   return(Fapi_Status_Success);
}

Fapi_StatusType Fapi_setupBankSectorEnable(void)
{
	FLASH_CONTROL_REGISTER->FsmSector.FSM_SECTOR_BITS.SECT_ERASED = 0;  /* Enables/disables sectors 0-15 for bank and sector erase */
	FLASH_CONTROL_REGISTER->Fbse.u32Register = 0xFFFF;                  /* Enable sectors 0-15 for erase and programming */

   return(Fapi_Status_Success);
}      

/* End of File */

