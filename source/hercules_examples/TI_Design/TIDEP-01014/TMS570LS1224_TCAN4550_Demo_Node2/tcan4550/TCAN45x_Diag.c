/*
 *  TCAN45x_Diag.c
 *
 *  Created on: Dec 08, 2018 for TMS570 MCU; QJ Wang (qjwang@ti.com)
 *
 */
/*
* Copyright (C) 2009-2015 Texas Instruments Incorporated - www.ti.com
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
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/
#include "TCAN45x.h"
#include "TMS570_TCAN45x.h"
#include "hw_config.h"
#include "TCAN45x_Diag.h"

uint8_t TCAN45x0_loopBackTest()
{
//    uint8_t cccr;
    uint32_t i;
    uint8_t error;

    TCAN45x0_TX_HEADER header = {0};                // Remember to initialize to 0, or you'll get random garbage!

    uint8_t data[4] = {0x55, 0xAA, 0x55, 0xAA};
    header.DLC = MCAN_DLC_4B;           // Set the DLC to be equal to or less than the data payload (it is ok to pass a 64 byte data array into the WriteTXFIFO function if your DLC is 8 bytes, only the first 8 bytes will be read)
    header.ID = 0x88;                   // Set the ID
    header.FDF = 1;                     // CAN FD frame enabled
    header.BRS = 1;                     // Bit rate switch enabled
    header.EFC = 0;
    header.MM  = 0;
    header.RTR = 0;
    header.XTD = 0;                                 // We are not using an extended ID in this example
    header.ESI = 0;                                 // Error state indicator
    //retVal = MCAN_WriteTXFIFO(0, &header, data);    // This function actually writes the header and data payload to the specified TX Fifo number. It returns the bit necessary to write to TXBAR,
    MCAN_WriteTXFIFO(0, &header, data);    // This function actually writes the header and data payload to the specified TX Fifo number. It returns the bit necessary to write to TXBAR,
                                                        // but does not necessarily require you to use it. In this example, we won't, so that we can send the data queued up at a later point.
    // This line writes the data and header to TX FIFO 1 and it will write the return value (corresponding to the
    // FIFO bit number in TX BAR
    AHB_WRITE_B_FL_32(M_CAN_TXBAR, 0x00000001);     // Now we can send the TX FIFO element 0 data that we had queued up earlier but didn't send.

    TCAN45x0_CAN_Interrupt_Register MCAN_IR = {0};  // Setup a new MCAN IR object for easy interrupt checking
//    do{
        MCAN_ReadInterruptRegister(&MCAN_IR);           // Read the interrupt register
//    }while(MCAN_IR.RF0N == 0);

//    if (MCAN_IR.RF0N) {                     // If a new message in RX FIFO 0
       TCAN45x0_RX_HEADER MsgHeader = {0}; // Initialize to 0 or you'll get garbage
       uint8_t dataPayload[64] = {0};

       AHB_WRITE_B_FL_32(M_CAN_IR, MCAN_IR_RF0N);  // Clear the interrupt bit to release the INT pin.
       /*To get rid of the warning msg, don't use the return value from those functions*/
       //numBytes = MCAN_ReadNextFIFO( RXFIFO0, &MsgHeader, dataPayload);    // This will read the next element in the RX FIFO 0
       //retVal = AHB_READ_B_FL_32( M_CAN_RXF0A);

       MCAN_ReadNextFIFO( RXFIFO0, &MsgHeader, dataPayload);    // This will read the next element in the RX FIFO 0
       AHB_READ_B_FL_32( M_CAN_RXF0A);

       if (MsgHeader.ID == 0x88) {     // Example of how you can do an action based off a received address
          for(i=0; i < 4; i++){
             if (dataPayload[i] != data[i]);
                error++;
          }
       }
//    }

   if(error == 0){
      return 1;           //SUCCESS;
   }else{
      return 0;           //fail;
   }
}

uint8_t TCAN45x0_EnableLoopBack(tcanLoopBackType_t Loopbacktype)
{
    uint8_t cccr;
    uint32_t temp;

    // First we need to make sure we have protected register access since these are protected
    cccr = TCAN45x0_EnableProtectedRegisters();
    if (cccr == CONFIG_FAIL)
        return CONFIG_FAIL;

    TCAN45x0_SetDeviceMode(TCAN45x0_MODE_TEST);

    /* Set bit 4 of TEST register to enable the loop back mode*/
    temp = AHB_READ_B_FL_32(M_CAN_TEST);
    AHB_WRITE_B_FL_32((M_CAN_TEST), temp | 0x00000010);

    /* Set bit 5 of control register to enable the internal loop back mode*/
    temp = AHB_READ_B_FL_32(M_CAN_CCCR);
    if ( Loopbacktype == Internal_Lbk){
        AHB_WRITE_B_FL_32((M_CAN_CCCR), temp | 0x00000020);
    }else{
        AHB_WRITE_B_FL_32((M_CAN_CCCR), temp & 0xFFFFFFDF);
    }

    // Turn off the initialization/protected mode if we had to enable it ourselves (this is a register update rather than a fresh config)
    if (cccr != CONFIG_SUCCESS_FIRST) {
        if (TCAN45x0_DisableProtectedRegisters() == CONFIG_FAIL)
            return CONFIG_FAIL;
    }

    temp = AHB_READ_B_FL_32(M_CAN_TEST);
    if ((temp | 0x00000010) != 0x00000010 )
        return CONFIG_FAIL;
    temp = AHB_READ_B_FL_32(M_CAN_CCCR);
    if (Loopbacktype != (temp | 0x00000020) >> 5 )
        return CONFIG_FAIL;

    return CONFIG_SUCCESS;
}

uint8_t TCAN45x0_DisableLoopBack()
{
    uint8_t cccr;
    uint32_t temp;

    // First we need to make sure we have protected register access since these are protected
    cccr = TCAN45x0_EnableProtectedRegisters();
    if (cccr == CONFIG_FAIL)
        return CONFIG_FAIL;

    /* Set the device to Test mode */
    TCAN45x0_SetDeviceMode(TCAN45x0_MODE_TEST);

    /* Set bit 4 of TEST register to enable the loop back mode*/
    temp = AHB_READ_B_FL_32(M_CAN_TEST);
    AHB_WRITE_B_FL_32((M_CAN_TEST), temp & 0xFFFFFFEF);

    TCAN45x0_SetDeviceMode(TCAN45x0_MODE_NORMAL);

    // Turn off the initialization/protected mode if we had to enable it ourselves (this is a register update rather than a fresh config)
    if (cccr != CONFIG_SUCCESS_FIRST) {
        if (TCAN45x0_DisableProtectedRegisters() == CONFIG_FAIL)
            return CONFIG_FAIL;
    }
    return CONFIG_SUCCESS;
}

uint8_t TCAN45x0_TransceiverTest()
{
    uint8_t cccr;
    uint32_t temp;

    // First we need to make sure we have protected register access since these are protected
    cccr = TCAN45x0_EnableProtectedRegisters();
    if (cccr == CONFIG_FAIL)
        return CONFIG_FAIL;

    /* Set the device to Test mode */
    TCAN45x0_SetDeviceMode(TCAN45x0_MODE_TEST);

    /* TEST_MODE_CONFIG (0x800[0]): Phy Test with TXD/RXD_INT_PHY and EN_INT are mapped
to external pins */
    temp = AHB_READ_B_FL_32(DEV_MODE_PINS);
    AHB_WRITE_B_FL_32((DEV_MODE_PINS), temp & 0xFFFFFFFE); //0x0800[0]=0

    // Turn off the initialization/protected mode if we had to enable it ourselves (this is a register update rather than a fresh config)
    if (cccr != CONFIG_SUCCESS_FIRST) {
        if (TCAN45x0_DisableProtectedRegisters() == CONFIG_FAIL)
            return CONFIG_FAIL;
    }

    /*Toggle TCAN GPIO1, then check if GPIO2 is toggle  */
    /* user code*/

    return CONFIG_SUCCESS;
}

uint8_t TCAN45x0_MCANCoreTest()
{
    uint8_t cccr;
    uint32_t temp;

    // First we need to make sure we have protected register access since these are protected
    cccr = TCAN45x0_EnableProtectedRegisters();
    if (cccr == CONFIG_FAIL)
        return CONFIG_FAIL;

    /* Set the device to Test mode */
    TCAN45x0_SetDeviceMode(TCAN45x0_MODE_TEST);

    /* TEST_MODE_CONFIG (0x800[1]): 1 = CAN Controller test with TXD/RXD_INT_CAN mapped to
external pins */
    temp = AHB_READ_B_FL_32(DEV_MODE_PINS);
    AHB_WRITE_B_FL_32((DEV_MODE_PINS), temp | 0x00000001); //0x0800[0]=1

    // Turn off the initialization/protected mode if we had to enable it ourselves (this is a register update rather than a fresh config)
    if (cccr != CONFIG_SUCCESS_FIRST) {
        if (TCAN45x0_DisableProtectedRegisters() == CONFIG_FAIL)
            return CONFIG_FAIL;
    }

    /*Toggle TCAN GPIO1, then check if GPIO2 is toggle  */
    /* user code*/

    return CONFIG_SUCCESS;
}

uint8_t TCAN45x0_eccSelfTest()
{
    uint32_t temp,ecc_check;

    temp = AHB_READ_B_FL_32(0x080C);
    temp |= (1 << 12); //Force a single bit ECC error
    temp &= (0xFFC0FFFF); //clear bit [21:16]: ECC_ERR_FORCE_BIT_SEL
    temp |= (0x0 << 16);  //bit 0
    AHB_WRITE_B_FL_32((0x080C), temp); //0x0800[0]=1

    /*Read the RCC_ERR_Check bit */
    ecc_check = AHB_READ_B_FL_32(0x080C);
    ecc_check &= 0x00000800;
    if (ecc_check){
        return 1;  //success
    }else{
        return 0;   //fail
    }

}

