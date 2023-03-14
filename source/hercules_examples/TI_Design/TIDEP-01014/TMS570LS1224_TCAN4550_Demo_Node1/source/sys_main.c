/** @file sys_main.c 
*   @brief Application main file
*   @date 07-July-2017
*   @version 04.07.00
*
*   Created on Dec 08, 2018 for TMS570 MCU; QJ Wang (qjwang@ti.com)
*/

/* 
* Copyright (C) 2009-2016 Texas Instruments Incorporated - www.ti.com 
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

#include "sys_common.h"

/* USER CODE BEGIN (1) */
#include "gio.h"
#include "sci.h"
#include "spi.h"
#include "het.h"
#include "rti.h"
#include "adc.h"
#include "etpwm.h"

#include "tms570_debug.h"
#include "hw_config.h"
#include "TCAN45x_Diag.h"
#include <TCAN45x.h>
#include <TMS570_TCAN45x.h>

/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
//void tcan45xInit(void);
volatile uint8_t TCAN_Int_Cnt = 0;    // A variable used to keep track of interrupts on GIOA0 (MCAN Interrupt pin)
uint8_t receivedData[64];

uint16_t g_usADC1Data[32];
uint8_t  g_ucADC1Data[2][64];
uint8_t  g_ucAdcDataIndex = 0;
uint8_t  g_ucCurrentAdcDataIndex = 0;
uint8_t  g_ucNextAdcDataIndex = 0;
uint8_t  g_ucADC1SampleNum = 0;
uint8_t  g_ucUserButtonPressed = 0;
uint8_t  g_ucTCAN_nInt_Cnt = 0;
uint8_t  g_ucTCAN_busFault_Cnt = 0;
uint8_t  g_ucTCAN_nWKRQ_Cnt = 0;
uint8_t  g_ucTCAN_Int1_Cnt = 0;
uint8_t  g_ucADCData64BytesFlg = 0;


void gioNotification(gioPORT_t *port, uint32 bit);
void TCAN45x_devConfig();
void TCAN45x_Reset();

void smallDelay(void) {
      static volatile unsigned int delayval;
      //delayval = 100000;   //8.8ms
      delayval = 5000;   //0.5ms
      while(delayval--);
}
/* USER CODE END */
/* For demo, #1 board TX MSG is 0x128, RX MSG is 0x158 */
/* For demo, #2 board TX MSG is 0x158, RX MSG is 0x128 */

void main(void)
{
/* USER CODE BEGIN (3) */
    uint32_t i, receivedAdcData, cmpB;

    /* Init NHET port, NHET1[9] is used to measure the receiving time*/
    hetInit();

    /* Initialize RTI driver */
    rtiInit();

    /* Enable RTI Compare 0 interrupt notification */
    rtiEnableNotification(rtiNOTIFICATION_COMPARE0);

    /** - Setup compare 0 value. This value is compared with selected free running counter. */
    rtiREG1->CMP[0U].COMPx = 10000U * 100; //100ms

    /** - Setup update compare 0 value. This value is added to the compare 0 value on each compare match. */
    rtiREG1->CMP[0U].UDCPx = 10000U * 100; //100ms


    /*linsci is used to print the debug message WAG_DEBUGF*/
    sciInit();

    /* initialize ADC  */
    /* Group1 -> Channel 6, light sensor on Launchpad    */
    /* HW trigger trigger source as ePWMB         */
    adcInit();
    adcEnableNotification(adcREG1, adcGROUP1);

    /* Initialise EPWM */
    etpwmInit();

    /** - Sets up the ADC SOC period */
    /*Generate the EPWMxSOCA pulse on the third event:*/
    //etpwmREG1->ETPS |= ((uint16)((uint16)3U << 8U)
    //                  | (uint16)((uint16)3U << 12U));

    /*GIOA0/1 as input, pull-up, interrupt is falling edge*/
    gioInit();

    /*SPI3 of LS12x is used to communicate with TCAN4550*/
    spiInit();      /*SPI3 and nCS2 are used*/

    //reset TCAN4550 device. GIOB[3] is connected to nRST of TCAN4550 device
    TCAN45x_Reset();

    /* Configure TMS570LSx GIO0/1/2/7 as Interrupt inputs from TCAN45x*/
    TCAN45x_devConfig();

    /* Enable IRQ - Clear I flag in CPS register */
    _enable_IRQ();

    /* Initialize the MCAN timing parameters, enable interrupts, and MRAM for RX/TX*/
    tcan45xInit();

    TCAN45x0_eccSelfTest();

#if 0   //doing internal and external loopback test
    uint32_t retVal;
    TCAN45x0_EnableLoopBack(Internal_Lbk);
    retVal=TCAN45x0_loopBackTest();
    if (retVal == 0)
        TMS570_DEBUGF(("LoopBack Test Failed!!! \n"));

    TCAN45x0_DisableLoopBack();
#endif

    /* Start RTI Counter Block 0, then check SPI read every 100ms */
//    rtiStartCounter(rtiCOUNTER_BLOCK0);

    /* start adc conversion */
    //adcREG1->G1SRC = (uint32)0x00000000U
    //               | (uint32)ADC1_HET2_13; /* Alternate Trigger Source */
    adcREG1->G1SRC = (uint32)0x00000000U
                   | (uint32)ADC1_EPWM_A2; /* Alternate Trigger Source */
    adcStartConversion(adcREG1, adcGROUP1);

    /* Start counter in CountUp mode */
    etpwmSetCount(etpwmREG1, 0);
    etpwmSetCounterMode(etpwmREG1, CounterMode_UpDown);
    etpwmStartTBCLK();

    TCAN45x0_TX_HEADER header = {0};                // Remember to initialize to 0, or you'll get random garbage!
    header.DLC = MCAN_DLC_64B;                      // Set the DLC to be equal to or less than the data payload (it is ok to pass a 64 byte data array into the WriteTXFIFO function if your DLC is 8 bytes, only the first 8 bytes will be read)
    header.ID = 0x128;                              // Set the ID. #1 board use 0x128, #2 board use 0x158
    header.FDF = 1;                                 // CAN FD frame enabled
    header.BRS = 1;                                 // Bit rate switch enabled
    header.EFC = 0;
    header.MM  = 0;
    header.RTR = 0;
    header.XTD = 0;                                 // We are not using an extended ID in this example
    header.ESI = 0;                                 // Error state indicator

    /* Waiting for the interrupt of GIOB2 (user button)*/
    /* First button press, sending CAN data */
    /* 2nd button press, stop sending */
//    uint8_t td[64];
//    for (i=0; i<64; i++){
//        td[i]=0x5A;
//    }

    while(1)
    {
        if (( 1 == g_ucUserButtonPressed % 2) && (g_ucADCData64BytesFlg == 1))
        {
            MCAN_WriteTXFIFO(0, &header, &g_ucADC1Data[g_ucCurrentAdcDataIndex][0]);    // This function actually writes the header and data payload to the specified TX Fifo number. It returns the bit necessary to write to TXBAR,
            //retVal = MCAN_WriteTXFIFO(0, &header, &td[0]);    // This function actually writes the header and data payload to the specified TX Fifo number. It returns the bit necessary to write to TXBAR,

            // This line writes the data and header to TX FIFO 1 and it will write the return value (corresponding to the
            // FIFO bit number in TX BAR
            AHB_WRITE_B_FL_32(M_CAN_TXBAR, 0x00000001);     // Now we can send the TX FIFO element 1 data that we had queued up earlier but didn't send.

#ifdef FUNCTION_SAFETY
            unit32_t j;
            MCAN_ReadTXFIFO(0, &readData[0]);
            for (j=0; j<16; j++){
                if(readData[j] != g_ucADC1Data[g_ucCurrentAdcDataIndex][j])
                   error++;
            }
            if (error > 0 ){
                error = 0;
                //TMS570_DEBUGF(("Data is not written to TCAN MRA Successfully!!! \n"));
            }
#endif

        }  //end of if{} loop

        if (g_ucTCAN_Int1_Cnt > 0 )
        {
            //Toggle NHET pin to check how long tit takes to receive the CAN-FD data
            gioSetBit(hetPORT1, 9, 0);
            g_ucTCAN_Int1_Cnt--;
            TCAN45x0_CAN_Interrupt_Register MCAN_IR = {0};  // Setup a new MCAN IR object for easy interrupt checking
            MCAN_ReadInterruptRegister(&MCAN_IR);           // Read the interrupt register

            if (MCAN_IR.RF0N) {                     // If a new message in RX FIFO 0
                TCAN45x0_RX_HEADER MsgHeader = {0}; // Initialize to 0 or you'll get garbage
                uint8_t numBytes = 0;
                uint8_t dataPayload[64] = {0};

                AHB_WRITE_B_FL_32(M_CAN_IR, MCAN_IR_RF0N);  // Clear the interrupt bit to release the INT pin.
                numBytes = MCAN_ReadNextFIFO( RXFIFO0, &MsgHeader, dataPayload);    // This will read the next element in the RX FIFO 0

                //Toggle NHET pin to check how long tit takes to receive the CAN-FD data
                gioSetBit(hetPORT1, 9, 1);

                for(i=0; i<numBytes/2; i++){
                   receivedAdcData = dataPayload[i] << 8 | dataPayload[i+1];
                }
                cmpB = (etpwmREG6->TBPRD * receivedAdcData*2/numBytes)/0xFFF;
                etpwmSetCmpB(etpwmREG6, cmpB);
                if (MsgHeader.ID == 0x158) {     // #1 board use 0x158, #2 board use 0x128
                   // Do something
                   TMS570_DEBUGF(("Received CAN-FD Data: 0x%x bytes\n", numBytes));
                   for(i=0; i<numBytes; i++){
                       TMS570_DEBUGF(("  0x%X     ", dataPayload[i]));
                   }
                   TMS570_DEBUGF(("  \n\n "));
                }
            }
        }//end of RX INT if()
    }

/* USER CODE END */

//    return 0;
}


/* USER COD BEGIN (4) */


void gioNotification(gioPORT_t *port, uint32 bit)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
    if (port == gioPORTA){
        switch (bit)
        {
            case 0:     /*gioA0*/
                g_ucTCAN_nInt_Cnt++;   //CAN_nINT
                break;
            case 1:     /*gioA1*/
                g_ucTCAN_busFault_Cnt++;   //CAN bus fault event interrupt, CAN_GPIO2_INT
                break;
            case 2:   /*gioA2*/
                g_ucTCAN_nWKRQ_Cnt++;   //CAN Wake Request. WUP, LWU,
                break;
            case 7:   /*gioA7*/
                g_ucTCAN_Int1_Cnt++;   /* CAN_GPIO1_INT, MCAN_INT1*/
                break;
        }
    }
    if (port == gioPORTB){
        switch (bit)
        {
            case 2:  /* User Button on Launchpad*/
                g_ucUserButtonPressed++;
                break;    /*gioB[2]*/
        }
    }

}

/* Note-You need to remove rtiNotification from notification.c to avoid redefinition */
void rtiNotification(uint32 notification)
{
    uint8_t status=0;
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
    //gioSetPort(hetPORT1, gioGetPort(hetPORT1) ^ (0x1 << 13)); //Use HET1_13 to trigger ADC sampling
    status = TCAN45x0_Check_spiRead();
    if (status == SPI_READ_FAIL)
        TMS570_DEBUGF(("SPI Read Failed!!! \n"));
}

void adcNotification(adcBASE_t *adc, uint32 group)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (11) */
    uint32  buf;
    uint16  cmpA;

    /* ADC sampling is trigger by ADC SOC generated by PWM CMPB*/
    buf = adc->GxBUF[adcGROUP1].BUF0;
    g_usADC1Data[g_ucADC1SampleNum] = (uint16)(buf & 0xFFFU);
    g_ucADC1Data[g_ucAdcDataIndex][g_ucADC1SampleNum*2+1]   = (uint8)(buf & 0xFFU);
    g_ucADC1Data[g_ucAdcDataIndex][g_ucADC1SampleNum*2] = (uint8)((buf & 0xF00U) >> 8);

    //change the duty cycle of epwm6_A
    cmpA = (etpwmREG6->TBPRD * g_usADC1Data[g_ucADC1SampleNum])/0xFFF;
    etpwmSetCmpA(etpwmREG6, cmpA);
    g_ucADC1SampleNum++;
    if (g_ucADC1SampleNum > 32){   //ADC data is 12bits, not 8 bits
        g_ucADC1SampleNum = 0;
        g_ucADCData64BytesFlg = 1;
        g_ucCurrentAdcDataIndex = g_ucAdcDataIndex;
        g_ucNextAdcDataIndex = g_ucAdcDataIndex ^ 0x1;
        g_ucAdcDataIndex = g_ucNextAdcDataIndex;
    }
}

void TCAN45x_devConfig()
{
    gioPORTA->DIR     = (uint32)((uint32)0U << 0U);     /* Bit 0/1/2/7 */
    gioPORTB->DIR     = (uint32)((uint32)0xFB);         /* Bit 2 as input */
    gioREG->POL       = (uint32)((uint32)0x0U << 0U);   /* Bit 0/1, falling edge */
    gioREG->LVLSET    = (uint32)((uint32)(0x13U | 0x400));   /* GIOA Bit 0/1/2/7, GIOB Bit 2, high priority interrupt */
    gioPORTA->PULDIS  = 0x87; /* Bit 0/1/2/7, disable the pull */
    gioPORTB->PULDIS  = 0x04; /* Bit 2, disable the pull */
    gioEnableNotification(gioPORTA, 0x87); //enable the INT on GIOA0,GIOA1,GIOA2,GIOA7
    gioEnableNotification(gioPORTB, 0x04); //enable the INT on GIOB2, user button input
}

void TCAN45x_Reset()
{
    static volatile unsigned int delayval;
    delayval = 10000;   //1ms

    //reset TCAN4550 device. GIOB[3] is connected to nRST of TCAN4550 device
    gioPORTB->PULDIS |= (0x1<<3);
    gioSetDirection(gioPORTB, 0x1 << 3);
    gioSetBit(gioPORTB, 3, 1);
    while(delayval--);
    //release the TCAN4550 nRST
    gioSetBit(gioPORTB, 3, 0);

    delayval = 10000;
    while(delayval--);          //is requires. otherwise it doesn't work. QJ 2019
}



/* USER CODE END */
