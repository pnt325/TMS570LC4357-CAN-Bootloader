#include "sl_types.h"
#include "sl_api.h"
#include "HL_sci.h"
#include "HL_gio.h"
#include "HL_rti.h"
#include "HL_adc.h"
#include "esm_application_callback.h"
#include "Application_Types.h"
#include "math.h"


uint32 periodicSTPassCount=0;
uint32 periodicSTFailCount=0;
uint32 maintaskcount = 0;
uint32 rtiCOMPARE2_PER,rtiCOMPARE1_PER_NEW,old_FCORERRCNT;
uint32  g_PotReading = 468750;
button USER1 = NONE, USER2 = NONE;

uint32 lowlighttimerperiod[6] = {
		10240000,  /*for adc value below 50*/
		9216000,   /*for adc value 50  - 100*/
		8192000,   /*for adc value 100 - 150*/
		7168000,   /*for adc value 150 - 200*/
		6144000,   /*for adc value 200 - 250*/
		5120000    /*for adc value 250 - 300*/
};
uint32 highlighttimerperiod[6] = {
		4096000,  /*for adc value 300 - 935*/
		3481600,  /*for adc value 935 -1570*/
		2867200,  /*for adc value 1570-2205*/
		2252800,  /*for adc value 2205-2840*/
		1638400,  /*for adc value 2840-3475*/
		1024000   /*for adc value 3475-4096*/
};

/* External Support Functions */
extern void sciDisplayText(sciBASE_t *sci, uint8 *text, uint32 length);
extern uint32 Get_Temp_Sensor_data(void);
void sciDisplayData(sciBASE_t *sci, uint8 *text,uint32 length);

void main()
{
	volatile boolean retVal; /* For function return values */
	periodicSTPassCount = 0;
	periodicSTFailCount = 0;
	SL_SelfTest_Result    failInfoFlash;      /* Flash Self test failure information */
	SL_CCMR5F_FailInfo	  failInfoCCMR5F;	/* CCMR5 Self Test fail info */

	gioInit();
	adcInit();
	adcCalibration(adcREG1);
    rtiInit();
    sciInit();

    sciDisplayText(sciREG1,(uint8*)"------------------------------------------------------------------------------------------------------ \r\n",105);
    sciDisplayText(sciREG1,(uint8*)"                                 Welcome to the Hercules Launchpad demo                                \r\n",105);
    sciDisplayText(sciREG1,(uint8*)"------------------------------------------------------------------------------------------------------ \r\n",105);
    sciDisplayText(sciREG1,(uint8*)"1> Potentiometer Demo: USER LED B (LED3) blinking frequency is controlled by the Potentiometer         \r\n",105);
    sciDisplayText(sciREG1,(uint8*)"   settings. Turning the potentiometer will increase/decrease the speed at which USER LED B blinks.    \r\n",105);
    sciDisplayText(sciREG1,(uint8*)"2> CCMR5F Error Forcing Fault: Press USER SWITCH B button to inject this fault. ERR LED will           \r\n",105);
    sciDisplayText(sciREG1,(uint8*)"   light up when fault is detected.                                                                    \r\n",105);
    sciDisplayText(sciREG1,(uint8*)"3> FLASH ECC ERROR PROFILING TEST: Each press of USER SWITCH A button inserts 1-bit ECC error in flash.\r\n",105);
    sciDisplayText(sciREG1,(uint8*)"   Each button press doubles the blink rate of USER LED A (LED2).                                      \r\n",105);
    sciDisplayText(sciREG1,(uint8*)"4> OSCILLATOR FAILURE: oscillator can be killed pressing OSC KILL button to                            \r\n",105);
    sciDisplayText(sciREG1,(uint8*)"   create an oscillator fault which in turn creates error in system. ERR LED is ON as a result.        \r\n",105);
    sciDisplayText(sciREG1,(uint8*)"------------------------------------------------------------------------------------------------------ \r\n",105);
    sciDisplayText(sciREG1,(uint8*)"                  PLEASE DO POWER ON RESET(PORRST) WHENEVER YOU SEE ERR LED ON                         \r\n",105);
    sciDisplayText(sciREG1,(uint8*)"------------------------------------------------------------------------------------------------------ \r\n",105);


	SL_ESM_Init(ESM_ApplicationCallback);
    /* Enable RTI Compare 0,1,2 interrupt notification */
	/*rtiCOMPARE0 used for detecting push button press*/
    rtiEnableNotification(rtiREG1,rtiNOTIFICATION_COMPARE0);
	/*rtiCOMPARE1 used for blinking LED2*/
    rtiEnableNotification(rtiREG1,rtiNOTIFICATION_COMPARE1);
	/*rtiCOMPARE1 used for blinking LED3*/
    rtiEnableNotification(rtiREG1,rtiNOTIFICATION_COMPARE2);
	/*rtiCOMPARE1 used for updating current temperature*/
    rtiEnableNotification(rtiREG1,rtiNOTIFICATION_COMPARE3);
    /* Enable IRQ - Clear I flag in CPS register */
    /* Note: This is usually done by the OS or in an svc dispatcher */
    _enable_IRQ();
    /* the current periods fo the COMPARE1 and COMPARE2*/
    rtiCOMPARE2_PER = rtiGetPeriod(rtiREG1,rtiCOMPARE2);
    rtiCOMPARE1_PER_NEW = rtiGetPeriod(rtiREG1,rtiCOMPARE1);
    /* Start RTI Counter Block 0 */
    rtiStartCounter(rtiREG1,rtiCOUNTER_BLOCK0);

	while (1) {
		maintaskcount++;
		/*change the period of the ambient light balancing led LED3 based on the ambient light sensor input */
		/*as the light sensor input increases the speed of the blinking increases*/
		g_PotReading = Get_Temp_Sensor_data();
    	rtiSetPeriod(rtiREG1,rtiCOMPARE2,1000*g_PotReading+468750);

		/*check whether switch USER1 has been pressed and do a flash ecc 1 bit selftest using diagnostic library*/
		if (SHORT_PRESS == USER1)
		{
			sciDisplayText(sciREG1,(uint8*)"Injecting a single bit FLASH ECC Error\r\n",40);
			SL_SelfTest_Flash(FLASH_ECC_TEST_MODE_1BIT, TRUE, &failInfoFlash);

			/*There is flash ecc 1 bit error introduced by the call to SL_SelfTest_Flash and the threshold value in the sl_flashWREG->FEDACCTRL2 decreases by 1*/
			/*change the period of the led LED2 based on if number of  FLASH ECC 1 bit errors  */
			/*as the number of errors increases the speed of the blinking increases*/
		    rtiCOMPARE1_PER_NEW = rtiGetPeriod(rtiREG1,rtiCOMPARE1) / 2;
			rtiSetPeriod(rtiREG1,rtiCOMPARE1,rtiCOMPARE1_PER_NEW);
			USER1 = NONE;
		}
		if(SHORT_PRESS == USER2)
		{
			sciDisplayText(sciREG1,(uint8*)"Injecting CCMR5F ERROR FORCING FAULT INJECT\r\n",45);
			SL_SelfTest_CCMR5F(CCMR5F_CPUCOMP_ERROR_FORCING_TEST_FAULT_INJECT, TRUE, &failInfoCCMR5F);
			USER2 = NONE;
		}
	}
}



