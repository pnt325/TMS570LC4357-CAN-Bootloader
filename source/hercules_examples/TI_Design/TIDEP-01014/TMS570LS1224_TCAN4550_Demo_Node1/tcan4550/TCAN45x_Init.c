/*
 *  TCAN45x_Init.c
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
#include "tms570_debug.h"

/*
 * Initialize TCAN45x device
 */
void tcan45xInit(void)
{
    uint32_t readData, readID0, readID1, revNum;

#if 1
    // Step one attempt to clear all interrupts
    readID0 = AHB_READ_B_FL_32(SPI_DEVICE_ID0);     //0x4E414354
    readID1 = AHB_READ_B_FL_32(SPI_DEVICE_ID1);     //0x30353534
    revNum  = AHB_READ_B_FL_32(SPI_REVISION);       //0x100; Device REV_ID Major is 1

    AHB_READ_B_FL_32(M_CAN_CCCR);

    TMS570_DEBUGF(("Device ID0: %x  ID1:  %x    Revision: %x \n", readID0, readID1, revNum));

#endif

    AHB_WRITE_B_FL_32(DEV_IE, 0x00);                            // disabling all non-MCAN related interrupts for simplicity

    /*PWRON Flag is cleared by either writing a 1 or by going to sleep mode
     * or normal mode from standby mode.*/
    readData = AHB_READ_B_FL_32(DEV_IR);                        // Read the device interrupt register
    if (readData & DEVICE_IR_PWRON)
          AHB_WRITE_B_FL_32(DEV_IR, DEVICE_IR_PWRON);             // If the power on reset is set, then clear it

    /* Configure the CAN bus speeds */
    TCAN45x0_Nominal_Timing TCANNomTiming = {0};        // 500k arbitration with a 40 MHz crystal (40E6 / (57 + 22 + 1 (Sync)) = 500E3)
    //The crystal on EVM is 40MHz. BRP+1 = 4+1; fCAN=40/5=8MHz
    TCANNomTiming.NominalBitRatePrescaler = TCAN_NominalBitRatePrescaler;  //5;      //1    //5,11,4,1
    TCANNomTiming.NominalTimeSeg1andProp  = TCAN_NominalTimeSeg1andProp;   //11;     //57;
    TCANNomTiming.NominalTimeSeg2         = TCAN_NominalTimeSeg2;          //4;      //22;
    TCANNomTiming.NominalSyncJumpWidth    = TCAN_NominalSyncJumpWidth;     //1;      //11;

    TCAN45x0_CANFD_Timing TCANDataTiming = {0};         // 2 Mbps CAN FD with a 40 MHz crystal (40E6 / (14 + 5 + 1 (Sync)) = 2E6)
    TCANDataTiming.DataBitRatePrescaler = TCAN_DataBitRatePrescaler;   //5;     //1;  //4,3,1,1
    TCANDataTiming.DataTimeSeg1andProp  = TCAN_DataTimeSeg1andProp;    //5;     //14;
    TCANDataTiming.DataTimeSeg2         = TCAN_DataTimeSeg2;           //2;     //5;
    TCANDataTiming.DataSyncJumpWidth    = TCAN_DataSyncJumpWidth;      //1;     //5;

    /* Configure the MCAN core settings */
    TCAN45x0_CCCR_Config cccrConfig = {0};                      // Remember to initialize to 0, or you'll get random garbage!
    cccrConfig.FDOE = TCAN_CANFD_ENABLE;                                        // CAN FD mode enable
    cccrConfig.BRSE = TCAN_CANFD_BRSE_ENABLE;                                        // CAN FD Bit rate switch enable
    cccrConfig.DAR  = TCAN_AUTO_RETX_DISABLE;                                        // Disable automatic transmission

    /* ************************************************************************
     * In the next configuration block, we will set the MCAN core up to have:
     *   - 1 SID filter element
     *   - 1 XID Filter element
     *   - 5 RX FIFO 0 elements
     *   - RX FIFO 0 supports data payloads up to 64 bytes
     *   - RX FIFO 1 and RX Buffer will not have any elements, but we still set their data payload sizes, even though it's not required
     *   - No TX Event FIFOs
     *   - 2 Transmit buffers supporting up to 64 bytes of data payload
     */
#if 1
    TCAN45x0_MRAM_Config MRAMConfiguration = {0};
    MRAMConfiguration.SIDNumElements   = MRAM_SIDNumElements;                       // Standard ID number of elements
    MRAMConfiguration.XIDNumElements   = MRAM_XIDNumElements;                       // Extended ID number of elements
    MRAMConfiguration.Rx0NumElements   = MRAM_Rx0NumElements;                       // RX0 Number of elements
    MRAMConfiguration.Rx0ElementSize   = MRAM_Rx0ElementSize;       // RX0 FIFO data payload size (Use the defines)
    MRAMConfiguration.Rx1NumElements   = MRAM_Rx1NumElements;                       // RX1 number of elements
    MRAMConfiguration.Rx1ElementSize   = MRAM_Rx1ElementSize;       // RX1 FIFO data payload size (use the defines)
    MRAMConfiguration.RxBufNumElements = MRAM_RxBufNumElements;                     // RX buffer number of elements
    MRAMConfiguration.RxBufElementSize = MRAM_RxBufElementSize;     // RX buffer data payload size (use the defines)
    MRAMConfiguration.TxEventFIFONumElements = MRAM_TxEventFIFONumElements;               // TX Event FIFO number of elements
    MRAMConfiguration.TxBufferNumElements    = MRAM_TxBufferNumElements ;                  // TX buffer number of elements
    MRAMConfiguration.TxBufferElementSize    = MRAM_TxBufferElementSize;  // TX buffer data payload size (use the defines)
#endif
#if 0  //QJ
    TCAN45x0_MRAM_Config MRAMConfiguration = {0};
    MRAMConfiguration.SIDNumElements = 2;                       // Standard ID number of elements
    MRAMConfiguration.XIDNumElements = 1;                       // Extended ID number of elements
    MRAMConfiguration.Rx0NumElements = 4;                       // RX0 Number of elements
    MRAMConfiguration.Rx0ElementSize = MRAM_48_Byte_Data;       // RX0 FIFO data payload size (Use the defines)
    MRAMConfiguration.Rx1NumElements = 5;                       // RX1 number of elements
    MRAMConfiguration.Rx1ElementSize = MRAM_64_Byte_Data;       // RX1 FIFO data payload size (use the defines)
    MRAMConfiguration.RxBufNumElements = 0;                     // RX buffer number of elements
    MRAMConfiguration.RxBufElementSize = 0;     // RX buffer data payload size (use the defines)
    MRAMConfiguration.TxEventFIFONumElements = 3;               // TX Event FIFO number of elements
    MRAMConfiguration.TxBufferNumElements = 10;                  // TX buffer number of elements
    MRAMConfiguration.TxBufferElementSize = MRAM_64_Byte_Data;  // TX buffer data payload size (use the defines)
#endif

    // Configure the MCAN core with the settings above, these changes in this block all are protected write registers, so we just knock them out at once

    TCAN45x0_SetDeviceMode(TCAN45x0_MODE_NORMAL);
    AHB_READ_B_FL_32(DEV_MODE_PINS);

    TCAN45x0_EnableProtectedRegisters();                        // Start by making protected registers accessible
    TCAN45x0_ConfigureCCCRRegister(&cccrConfig);                // Enable FD mode and Bit rate switching
    TCAN45x0_ConfigureMCANTiming(&TCANNomTiming);               // Setup nominal/arbitration bit timing
    TCAN45x0_ConfigureMCANTimingFD(&TCANDataTiming);            // Setup CAN FD timing
    TCAN45x0_ClearMRAM();                                       // Clear all of MRAM (Writes 0's to all of it)
    TCAN45x0_ConfigureMRAM(&MRAMConfiguration);                 // Set up the applicable registers related to MRAM configuration
    TCAN45x0_DisableProtectedRegisters();                       // Disable protected write and take device out of INIT mode

    AHB_READ_B_FL_32(M_CAN_CCCR);        //0x359; not correct: the INIT is 1. It is 0x19 after RESET.

    // Set the interrupts we want to enable for MCAN
    TCAN45x0_CAN_Interrupt_Enable_Register TCAN_CAN_IE = {0};   // Remember to initialize to 0, or you'll get random garbage!
    TCAN_CAN_IE.RF0NE = 1;                                      // RX FIFO 0 new message enable
    TCAN_CAN_IE.RF1NE = 1;                                      // RX FIFO 1 new message enable
    MCAN_SetInterruptEnableRegister(&TCAN_CAN_IE);              // Enable the appropriate registers

    TCAN45x0_CAN_Interrupt_Line_Select_Register TCAN_CAN_ILS = {0};  //Interrupt Line Select (address = 1058)
    TCAN_CAN_ILS.RF0NL = 1;                                          //Rx FIFO 0 New Message Interrupt uses EINT1
    TCAN_CAN_ILS.RF1NL = 1;                                          //Rx FIFO 1 New Message Interrupt uses EINT1
    MCAN_SetInterruptLineSelectRegister(&TCAN_CAN_ILS);

    TCAN45x0_CAN_Interrupt_Line_Enable_Register TCAN_CAN_ILE = {0};  //Interrupt Line Enable (address = 105C)
    TCAN_CAN_ILE.EINT0 = 0;                                          //Interrupt line m_can_int0 is disabled
    TCAN_CAN_ILE.EINT1 = 1;                                          //Interrupt line m_can_int1 is enabled
    MCAN_SetInterruptLineEnableRegister(&TCAN_CAN_ILE);

    //AHB_WRITE_B_FL_32(M_CAN_ILS, 0x0001);                       // We must select the interrupt line
    //AHB_WRITE_B_FL_32(M_CAN_ILE, 0x0002);                       // We must enable MCAN_INT1 in order for MCAN to be able to set interrupts

    TCAN45x0_Config_GPIOMode(TCAN45x0_GPIO1_MCAN_INT1, TCAN45x0_GPIO2_CANBUS_INT);
    AHB_READ_B_FL_32(DEV_MODE_PINS);

    TCAN45x0_DisableWDT();//QJ, retVal=1 success

    // Setup filters, this filter will mark any message with ID 0x158 as a priority message
    TCAN45x0_SID_FILTER SID_ID = {0};
    SID_ID.SFT = TCAN45x0_SID_SFT_CLASSIC;                      // SFT: Standard filter type. Configured as a classic filter
    SID_ID.SFEC = TCAN45x0_SID_SFEC_PRIORITYSTORERX0;           // Standard filter element configuration, store it in RX fifo 0 as a priority message
    SID_ID.SFID1 = 0x158;                                       // SFID1 (Classic mode Filter); #1 board use 0x158, #2 board use 0x128 (for demo only)
    SID_ID.SFID2 = 0x7FF;                                       // SFID2 (Classic mode Mask)
    MCAN_WriteSIDFilter(0, &SID_ID);                            // Write to the MRAM

     // Store ID 0x12345678 as a priority message
    TCAN45x0_XID_FILTER XID_ID = {0};
    XID_ID.EFT = TCAN45x0_XID_EFT_CLASSIC;                      // EFT
    XID_ID.EFEC = TCAN45x0_XID_EFEC_PRIORITYSTORERX0;           // EFEC
    XID_ID.EFID1 = 0x12345678;                                  // EFID1 (Classic mode filter)
    XID_ID.EFID2 = 0x1FFFFFFF;                                  // EFID2 (Classic mode mask)
    MCAN_WriteXIDFilter(0, &XID_ID);                            // Write to the MRAM

    //TCAN45x0_SetDeviceMode(TCAN45x0_MODE_NORMAL);               // Set to normal mode, since configuration is done. This line turns on the transceiver

    AHB_WRITE_B_FL_32(M_CAN_IR, 0xFFFFFFFF);                    // Resets all interrupts
}
