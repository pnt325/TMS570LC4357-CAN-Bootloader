
#include "Application_Types.h"
#include "math.h"
#include "sys_selftest.h"

#if defined (_TMS570LS12x_) || defined(_RM46x_) || defined(_RM42x_) || defined(_TMS570LS04x_)
#include "sci.h"
#include "gio.h"
#include "rti.h"
#include "adc.h"
#include "het.h"
#include "mibspi.h"
#endif

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
extern uint32 Get_Light_Sensor_data(void);
void sciDisplayData(sciBASE_t *sci, uint8 *text,uint32 length);
void SelfTest_Flash_1bitECC_Error(void);
void SelfTest_Flash_2bitECC_Error(void);


void main()
{
	volatile boolean retVal; /* For function return values */
	periodicSTPassCount = 0;
	periodicSTFailCount = 0;

 	/* USER Button S3: MIBSPI3NCS_0/AD2EVT/GIOB_2/EQEP1*/
    /* USER Button S4: N2HET1_15/MIBSPI1NCS_4/ECAP1*/
    /* USER LED2: GIOB_1 */
    /* USER LED3: GIOB_2 */
    gioInit();
    hetInit();
	adcInit();
	adcCalibration(adcREG1);
    rtiInit();
    sciInit();
    mibspiInit();

    hetREG1->DIR &= (1<<15);  //User Button S4
    hetREG1->PSL &= (1<<15);  //User Button S4

    mibspiREG3->PC0 &= 0xFFE; //CS0 is GIO
    mibspiREG3->PC1 &= 0x6FE; //CS0 is input
    mibspiREG3->PC8 |= 0x1;   //pull-up CS0


    sciDisplayText(scilinREG,(uint8*)"------------------------------------------------------------------------------------------------------ \r\n",105);
	sciDisplayText(scilinREG,(uint8*)"                                 Welcome to the Hercules Launchpad demo                                \r\n",105);
	sciDisplayText(scilinREG,(uint8*)"------------------------------------------------------------------------------------------------------ \r\n",105);
	sciDisplayText(scilinREG,(uint8*)"1> Light Sensor Demo: USER LED B (LED3) blinking frequency is controlled by the ambient light sensor.  \r\n",105);
	sciDisplayText(scilinREG,(uint8*)"   Vary the intensity of the light on the sensor (Q1) to observe the response.                         \r\n",105);
	sciDisplayText(scilinREG,(uint8*)"2> Force 1 bit Flash ECC error: Each press of USER SWITCH A button inserts 1-bit ECC error in flash.   \r\n",105);
    sciDisplayText(scilinREG,(uint8*)"   Each button press doubles the blink rate of USER LED A (LED2).                                      \r\n",105);
	sciDisplayText(scilinREG,(uint8*)"3> Force 2 bit Flash ECC error: Each press of USER SWITCH B button inserts 2-bit ECC error in flash.   \r\n",105);
    sciDisplayText(scilinREG,(uint8*)"   nERROR lights up when fault is detected. Press USER SWITCH A button to clear nERROR LED.            \r\n",105);
	sciDisplayText(scilinREG,(uint8*)"4> OSCILLATOR FAILURE: oscillator can be killed placing jumper JP1 in OSC KILL position to             \r\n",105);
    sciDisplayText(scilinREG,(uint8*)"   create an oscillator fault which in turn creates error in system. ERR LED is ON as a result.        \r\n",105);
    sciDisplayText(scilinREG,(uint8*)"   Press nPORRT button (S1) to restore.                                                                \r\n",105);
	sciDisplayText(scilinREG,(uint8*)"------------------------------------------------------------------------------------------------------ \r\n",105);


	//SL_ESM_Init(ESM_ApplicationCallback);
    /* Enable RTI Compare 0,1,2 interrupt notification */
	/*rtiCOMPARE0 used for detecting push button press*/
    rtiEnableNotification(rtiNOTIFICATION_COMPARE0);
	/*rtiCOMPARE1 used for blinking LED2*/
    rtiEnableNotification(rtiNOTIFICATION_COMPARE1);
	/*rtiCOMPARE1 used for blinking LED3*/
    rtiEnableNotification(rtiNOTIFICATION_COMPARE2);
	/*rtiCOMPARE1 used for updating current temperature*/
    rtiEnableNotification(rtiNOTIFICATION_COMPARE3);
    /* Enable IRQ - Clear I flag in CPS register */
    /* Note: This is usually done by the OS or in an svc dispatcher */
    _enable_IRQ();
    /* the current periods fo the COMPARE1 and COMPARE2*/
    rtiCOMPARE2_PER = rtiGetPeriod(rtiCOMPARE2);
    rtiCOMPARE1_PER_NEW = rtiGetPeriod(rtiCOMPARE1);
    /* Start RTI Counter Block 0 */
    rtiStartCounter(rtiCOUNTER_BLOCK0);

	while (1) {
		maintaskcount++;
		/*change the period of the ambient light balancing led LED3 based on the ambient light sensor input */
		/*as the light sensor input increases the speed of the blinking increases*/
		g_PotReading = Get_Light_Sensor_data();
    	rtiSetPeriod(rtiCOMPARE2,1000*g_PotReading+468750);

		/*check whether switch USER1 has been pressed and do a flash ecc 1 bit selftest*/
		if (SHORT_PRESS == USER1)
		{
            sciDisplayText(scilinREG,(uint8*)"Injecting a single bit FLASH ECC Error                                                                 \r\n",105);
            SelfTest_Flash_1bitECC_Error();

            /* The nERROR pin will become inactive once the LTC counter expires */
            /* This error is caused by pressing Button B*/
            if ((esmREG->EPSR & 0x01) == 0x0 ){
                sciDisplayText(scilinREG,(uint8*)"2-bit ECC error is cleared                                                                             \r\n",105);
                esmREG->EKR = 0x5U;
                esmREG->EKR = 0x0U;
            }

		    rtiCOMPARE1_PER_NEW = rtiGetPeriod(rtiCOMPARE1) / 2;
			rtiSetPeriod(rtiCOMPARE1,rtiCOMPARE1_PER_NEW);
			USER1 = NONE;
		}
		if(SHORT_PRESS == USER2)
		{
            sciDisplayText(scilinREG,(uint8*)"Injecting a double bit FLASH ECC Error                                                                 \r\n",105);
            SelfTest_Flash_2bitECC_Error();

            sciDisplayText(scilinREG,(uint8*)"The nERROR LED is turned on, Press Button A to clear nERROR                                            \r\n",105);

			USER2 = NONE;
		}
	}
}

void SelfTest_Flash_1bitECC_Error(void)
{
    /* Routine to check operation of ECC logic inside CPU for accesses to program flash */
    volatile uint32 flashread = 0U;

/* USER CODE BEGIN (40) */
/* USER CODE END */

    /* Flash Module ECC Response enabled */
    flashWREG->FEDACCTRL1 = 0x000A060AU;

    /* Enable diagnostic mode and select diag mode 7 */
    flashWREG->FDIAGCTRL = 0x00050007U;

    /* Select ECC diagnostic mode, single-bit to be corrupted */
    flashWREG->FPAROVR = 0x00005A01U;

    /* Set the trigger for the diagnostic mode */
    flashWREG->FDIAGCTRL |= 0x01000000U;

    /* read a flash location from the mirrored memory map */
    flashread = flashBadECC1;

    /* disable diagnostic mode */
    flashWREG->FDIAGCTRL = 0x000A0007U;

    /* this will have caused a single-bit error to be generated and corrected by CPU */
    /* single-bit error not captured in flash module */
    /*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Hardware status bit read check" */
    if ((flashWREG->FEDACSTATUS & 0x2U) == 0U)
    {
        selftestFailNotification(CHECKFLASHECC_FAIL1);
    }
    else
    {
        /* clear single-bit error flag */
        flashWREG->FEDACSTATUS = 0x2U;

        /* clear ESM flag */
        esmREG->SR1[0U] = 0x40U;
    }
}

void SelfTest_Flash_2bitECC_Error(void)
{
    /* Routine to check operation of ECC logic inside CPU for accesses to program flash */
    volatile uint32 flashread = 0U;

    /* Enable diagnostic mode and select diag mode 7 */
    flashWREG->FDIAGCTRL = 0x00050007U;

    /* Select ECC diagnostic mode, two bits of ECC to be corrupted */
    flashWREG->FPAROVR = 0x00005A03U;

    /* Set the trigger for the diagnostic mode */
    flashWREG->FDIAGCTRL |= 0x01000000U;

    /* read from flash location from mirrored memory map this will cause a data abort */
    flashread = flashBadECC2;

    /* Read FUNCERRADD register */
    flashread = flashWREG->FUNCERRADD;

    /* disable diagnostic mode */
    flashWREG->FDIAGCTRL = 0x000A0007U;
}
