/** @file HL_sys_main.c 
*   @brief Application main file
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com  
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
*
*/


/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "HL_sys_common.h"

/* USER CODE BEGIN (1) */
#include "HL_sci.h"
#include "HL_gio.h"
#include "HL_rti.h"
#include "HL_adc.h"
#include "HL_het.h"
#include "selftest.h"


/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */

typedef enum _button_EVENT
{
    NONE,
    SHORT_PRESS
}button;
#define USER1_BUTTON_GPIOPORT     gioPORTB
#define USER1_BUTTON_GPIOPIN      4
#define USER2_BUTTON_GPIOPORT     gioPORTB
#define USER2_BUTTON_GPIOPIN      5
#define LED1_GPIOPORT             gioPORTB
#define LED1_GPIOPIN              6
#define LED2_GPIOPORT             gioPORTB
#define LED2_GPIOPIN              7

uint32 rtiCOMPARE2_PER,rtiCOMPARE1_PER_NEW,old_FCORERRCNT;
uint32  g_PotReading = 468750;
button USER1 = NONE, USER2 = NONE;


/* External Support Functions */
adcData_t adc_data[1];

extern void sciDisplayText(sciBASE_t *sci, uint8 *text, uint32 length);
void sciDisplayData(sciBASE_t *sci, uint8 *text,uint32 length);
void rtiNotification(rtiBASE_t *rtiREG, uint32 notification);
void gioNotification(gioPORT_t *port, uint32 bit);

/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    uint32_t error;

    gioInit();
    adcInit();
    adcCalibration(adcREG1);
    rtiInit();
    sciInit();

    gioPORTB->DIR  = 0x00C0;  //bit[7:6} output
    gioPORTB->DOUT = 0x0000;

    //hetPORT2->DIR = (1 << 4) | (1 << 5); //used for RJ45 LEDs
    //hetPORT2->DOUT = (1 << 4) | (1 << 5); //turn off RJ45 LEDs

    sciDisplayText(sciREG1,(uint8*)"------------------------------------------------------------------------------------------------------ \r\n",105);
    sciDisplayText(sciREG1,(uint8*)"                                 Welcome to the Hercules Launchpad demo                                \r\n",105);
    sciDisplayText(sciREG1,(uint8*)"------------------------------------------------------------------------------------------------------ \r\n",105);
    sciDisplayText(sciREG1,(uint8*)"1> Light Sensor Demo: USER LED B (LED3) blinking frequency is controlled by the ambient light sensor.  \r\n",105);
    sciDisplayText(sciREG1,(uint8*)"   Vary the intensity of the light on the sensor to observe the response.                              \r\n",105);
    sciDisplayText(sciREG1,(uint8*)"2> CCMR4F Error Forcing Fault: Press USER SWITCH B button to inject this fault.ERR LED will            \r\n",105);
    sciDisplayText(sciREG1,(uint8*)"   light up when fault is detected.                                                                    \r\n",105);
    sciDisplayText(sciREG1,(uint8*)"3> FLASH ECC ERROR PROFILING TEST: Each press of USER SWITCH A button inserts 1-bit ECC error in flash.\r\n",105);
    sciDisplayText(sciREG1,(uint8*)"   Each button press doubles the blink rate of USER LED A (LED2).                                      \r\n",105);
    sciDisplayText(sciREG1,(uint8*)"4> OSCILLATOR FAILURE: oscillator can be killed placing jumper JP1 in OSC KILL position to             \r\n",105);
    sciDisplayText(sciREG1,(uint8*)"   create an oscillator fault which in turn creates error in system.ERR LED is ON as a result.         \r\n",105);
    sciDisplayText(sciREG1,(uint8*)"------------------------------------------------------------------------------------------------------ \r\n",105);
    sciDisplayText(sciREG1,(uint8*)"                  PLEASE DO POWER ON RESET(PORRST) WHENEVER YOU SEE ERR LED ON                         \r\n",105);
    sciDisplayText(sciREG1,(uint8*)"------------------------------------------------------------------------------------------------------ \r\n",105);

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
    rtiCOMPARE2_PER     = rtiGetPeriod(rtiREG1,rtiCOMPARE2);
    rtiCOMPARE1_PER_NEW = rtiGetPeriod(rtiREG1,rtiCOMPARE1);
    /* Start RTI Counter Block 0 */
    rtiStartCounter(rtiREG1,rtiCOUNTER_BLOCK0);

    unsigned int val;
    while (1) {

        //Flash_SelfTest(&val);
        /*change the period of the ambient light balancing led LED3 based on the ambient light sensor input */
        /*as the light sensor input increases the speed of the blinking increases*/
        /* start adc conversion */
        adcStartConversion(adcREG1,adcGROUP1);
        /* ... wait and read the conversion count */
        while((adcIsConversionComplete(adcREG1,adcGROUP1))==0);
        adcGetData(adcREG1, adcGROUP1,&adc_data[0]);
        g_PotReading = adc_data[0].value;


        rtiSetPeriod(rtiREG1, rtiCOMPARE2, 1000*g_PotReading+468750);

        /*check whether switch USER1 has been pressed and do a flash ecc 1 bit selftest using diagnostic library*/
        if (SHORT_PRESS == USER1)
        {
            sciDisplayText(sciREG1,(uint8*)"Injecting a single bit FLASH ECC Error\r\n",40);
            //error = SelfTest_Flash();

            /*There is flash ecc 1 bit error introduced by the call to SL_SelfTest_Flash and the threshold value in the sl_flashWREG->FEDACCTRL2 decreases by 1*/
            /*change the period of the led LED2 based on if number of  FLASH ECC 1 bit errors  */
            /*as the number of errors increases the speed of the blinking increases*/
            if (error){
               rtiCOMPARE1_PER_NEW = rtiGetPeriod(rtiREG1,rtiCOMPARE1) / 2;
            }
            rtiSetPeriod(rtiREG1,rtiCOMPARE1,rtiCOMPARE1_PER_NEW);
            USER1 = NONE;
        }
        if(SHORT_PRESS == USER2)
        {
            sciDisplayText(sciREG1,(uint8*)"Injecting CCMR5F ERROR FORCING FAULT INJECT\r\n",45);
            //SelfTest_CCMR5F_FaultInjection();
            USER2 = NONE;
        }
    }


/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
/* Note-You need to remove rtiNotification from notification.c to avoid redefinition */
void rtiNotification(rtiBASE_t *rtiREG, uint32 notification)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
    if (notification == 0){   //read USER button 1 (GIOB[4]) and button 2 (GIOB[5])
       if (( gioGetPort(gioPORTB) & 0x10) == 0x00){ //user button 1
           USER1 = SHORT_PRESS;
       }
       if (( gioGetPort(gioPORTB) & 0x20) == 0x00){ //user button 2
           USER2 = SHORT_PRESS;
       }

    }
    if (notification == 1){   //toggle LED2, GIOB[6]
       gioSetPort(gioPORTB, gioGetPort(gioPORTB) ^ 0x0040);
    }
    else if (notification == 2){   //toggle LED3, GIOB[7]
       gioSetPort(gioPORTB, gioGetPort(gioPORTB) ^ 0x0080);
    }
}


void gioNotification(gioPORT_t *port, uint32 bit)
{
   if (bit == 4){
       USER1 = SHORT_PRESS;
   }
   if (bit == 5){
       USER2 = SHORT_PRESS;
   }
}


void sciDisplayText(sciBASE_t *sci, uint8 *text, uint32 length) {
    while (length--) {
        while ((sci->FLR & 0x4) == 4)
            ; /* wait until busy */
        sciSendByte(sci, *text++); /* send out text   */
    };
}


void sciDisplayData(sciBASE_t *sci, uint8 *text,uint32 length)
{
    uint8 txt = 0;
    uint8 txt1 = 0;

#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
text = text + (length -1);
#endif

    while(length--)
    {
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
        txt = *text--;
#else
        txt = *text++;
#endif

        txt1 = txt;

        txt  &= ~(0xF0);
        txt1 &= ~(0x0F);
        txt1  =txt1>>4;

        if(txt<=0x9)
        {
            txt +=0x30;
        }
        else if(txt > 0x9 && txt < 0xF)
        {
            txt +=0x37;
        }
        else
        {
            txt = 0x30;
        }

        if(txt1 <= 0x9)
        {
            txt1 +=0x30;
        }
        else if((txt1 > 0x9) && (txt1 <= 0xF))
        {
            txt1 +=0x37;
        }
        else
        {
            txt1 = 0x30;
        }

        while ((sciREG1->FLR & 0x4) == 4); /* wait until busy */
        sciSendByte(sciREG1,txt1);      /* send out text   */
        while ((sciREG1->FLR & 0x4) == 4); /* wait until busy */
        sciSendByte(sciREG1,txt);      /* send out text   */
    };
}



/* USER CODE END */
