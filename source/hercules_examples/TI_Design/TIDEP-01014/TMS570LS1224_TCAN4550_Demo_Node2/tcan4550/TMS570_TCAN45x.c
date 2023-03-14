/*
 *  TCAN4550.c  : Functions to burst read and write from/to TCAN4550
 *  Author      : QJ Wang. qjwang@ti.com
 *  Date        : 2-19-2018
 *
 **/
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
#include <spi.h>
#include <TMS570_TCAN45x.h>
#include "hw_config.h"
#include "sys_common.h"

/* Burst Write 4-bytes word (32-bit), fixed length
 * <WRITE_B_FL OPCODE> <2 address bytes> <1 length bytes> <length words of write data>
 * WRITE_B_FL OPCODE is: 0x61
 * */
uint32_t AHB_WRITE_B_FL_32(uint16_t address, uint32_t data)
{
    spiDAT1_t dataconfig1_t;
    uint8_t txData[8], DataLength, blockSize;
    uint32_t spiErrorFlag;

    DataLength = 1;   //number of 32-bit words
    blockSize = DataLength * 4 + 4; /* # of bytes*/

    dataconfig1_t.CS_HOLD = TRUE;
    dataconfig1_t.WDEL    = TRUE;
    dataconfig1_t.DFSEL   = SPI_FMT_0;
    dataconfig1_t.CSNR    = (0xFF ^ (0x1 << SPI_CS));            /*0xFB, CS2*/

    txData[0] = AHB_WRITE_B_FL_OPCODE;
    txData[1] = (address & 0xFF00) >> 0x8;
    txData[2] = (address & 0x00FF) >> 0x0;
    txData[3] = DataLength;
    txData[4] = (data >> 24) & 0xFF;
    txData[5] = (data >> 16) & 0xFF;
    txData[6] = (data >> 8 ) & 0xFF;
    txData[7] = (data >> 0 ) & 0xFF;

    spiErrorFlag = spiTransmitData(SPI_PORT, &dataconfig1_t, blockSize, &txData[0]);
    return spiErrorFlag;
}

/* Burst read 4-bytes word (32-bit), fixed length
 * <READ_B_FL OPCODE> <2 address bytes> <1 length bytes><length words of read data>
 * READ_B_FL OPCODE is: 0x41
 * */
uint32_t AHB_READ_B_FL_32(uint16_t address)
{
    spiDAT1_t dataconfig1_t;
    uint8_t txData[8], rxData[8], DataLength, blockSize;
    uint32_t returnData;
//    uint32_t spiErrorFlag;

    DataLength = 1;   //number of 32-bit words
    blockSize = DataLength * 4 + 4;  /* bytes */

    dataconfig1_t.CS_HOLD = TRUE;
    dataconfig1_t.WDEL    = TRUE;
    dataconfig1_t.DFSEL   = SPI_FMT_0;
    dataconfig1_t.CSNR    = (0xFF ^ (0x1 << SPI_CS));     /*SPI3_CS2*/

    txData[0] = AHB_READ_B_FL_OPCODE;
    txData[1] = (address & 0xFF00) >> 0x8;
    txData[2] = (address & 0x00FF) >> 0x0;
    txData[3] = DataLength;
    txData[4] = 0x00;
    txData[5] = 0x00;
    txData[6] = 0x00;
    txData[7] = 0x00;

    spiTransmitAndReceiveData(SPI_PORT, &dataconfig1_t, blockSize, &txData[0], &rxData[0]);
    returnData = (rxData[4] << 24) | (rxData[5] << 16) | (rxData[6] << 8) | (rxData[7] << 0);

    return returnData;
}

/* Burst read 4-bytes word (32-bit) with a dummy read byte, fixed length
 * <READ_B_FL_W_WAIT OPCODE> <2 address bytes> <1 length bytes> <1 dummy read byte> <length words of read data>
 * READ_B_FL_W_WAIT OPCODE is 0x85
 * READ_B_FL_W_WAIT must be used when crystal clock is 20 MHz and the spi clock frequency is greater than 12.4 MHz
 * */
uint32_t AHB_READ_B_FL_32_WAIT(uint16_t address)
{
    spiDAT1_t dataconfig1_t;
    uint8_t txData[8], rxData[8], DataLength, blockSize;
    uint32_t returnData;
//    uint32_t spiErrorFlag;

    DataLength = 1;   //number of 32-bit words
    blockSize = DataLength * 4 + 4 + 1;  /* bytes. +1 means 1 dummy read byte */

    dataconfig1_t.CS_HOLD = TRUE;
    dataconfig1_t.WDEL    = TRUE;
    dataconfig1_t.DFSEL   = SPI_FMT_0;
    dataconfig1_t.CSNR    = (0xFF ^ (0x1 << SPI_CS));               /*SPI3_CS1*/

    txData[0] = AHB_READ_B_FL_WAIT_OPCODE;
    txData[1] = (address & 0xFF00) >> 0x8;
    txData[2] = (address & 0x00FF) >> 0x0;
    txData[3] = DataLength;
    txData[4] = 0x00;  /* for 1 dummy read byte*/
    txData[5] = 0x00;
    txData[6] = 0x00;
    txData[7] = 0x00;

    spiTransmitAndReceiveData(SPI_PORT, &dataconfig1_t, blockSize, &txData[0], &rxData[0]);
    returnData = (rxData[4] << 24) | (rxData[5] << 16) | (rxData[6] << 8) | (rxData[7] << 0);

    return returnData;
}

/* Write data with varied length. The CSHOLD is set until all the data is read out
 * len: number of 32-bit words
 */
uint32_t AHB_Write_Burst(uint16_t address, uint8_t* dataBuff, uint32_t len)
{
    uint32_t spiErrorFlag;
    spiDAT1_t dataconfig1_t;
    uint32_t DataLength, blockSize, i;

    uint8_t tx_Data[72]={0};

    DataLength = len;   //number of 32-bit words, data length
    blockSize = DataLength * 4 + 4; /* # of bytes; data length (bytes) + 1 byte cmd 2 bytes address + 1 byte length */

    dataconfig1_t.CS_HOLD = TRUE;
    dataconfig1_t.WDEL    = TRUE;
    dataconfig1_t.DFSEL   = SPI_FMT_0;
    dataconfig1_t.CSNR    = (0xFF ^ (0x1 << SPI_CS));                /*SPI3_CS1*/

    tx_Data[0] = AHB_WRITE_B_FL_OPCODE;
    tx_Data[1] = (address & 0xFF00) >> 0x8;
    tx_Data[2] = (address & 0x00FF) >> 0x0;
    tx_Data[3] = DataLength;

    for(i=0; i<DataLength*4; i++){
        tx_Data[i+4] = *dataBuff++;
    }

    /* Transmits Data on SPI2 using polling method
     * There is errors if the return value is not zero
     * 0-> no error detected
     * */
    spiErrorFlag = spiTransmitData(SPI_PORT, &dataconfig1_t, blockSize, &tx_Data[0]);

    return spiErrorFlag;
}

/* DataLength: number of 32-bit words*/
uint32_t AHB_Read_Burst(uint16_t address, uint8_t DataLength, uint8_t * destbuff)
{
    uint32_t spiErrorFlag;

    spiDAT1_t dataconfig1_t;
    uint8_t blockSize;
    uint8_t txData[72]={0};

    blockSize = DataLength * 4 + 4;  /* bytes, DataLength is # of 32-bit words */

    dataconfig1_t.CS_HOLD = TRUE;
    dataconfig1_t.WDEL    = TRUE;
    dataconfig1_t.DFSEL   = SPI_FMT_0;
    dataconfig1_t.CSNR    = (0xFF ^ (0x1 << SPI_CS));          /*SPI3_CS1*/

    txData[0] = AHB_READ_B_FL_OPCODE;
    txData[1] = (address & 0xFF00) >> 0x8;
    txData[2] = (address & 0x00FF) >> 0x0;
    txData[3] = DataLength;

    /* Initiate SPI2 Transmit and Receive through Polling Mode
     * There is errors if the return value is not zero
     * 0-> no error detected
     * */
    spiErrorFlag = spiTransmitAndReceiveData(SPI_PORT, &dataconfig1_t, blockSize, &txData[0], destbuff);

    return spiErrorFlag;
}

/* Burst read with a 1 dummy read byte
 * This function must be used when crystal clock is 20 MHz and the spi clock frequency is greater than 12.4 MHz
 * The user needs to discard the first byte of read data: destbuff
 * Return Value: SPI error flag. 0-> no error detected
 * */
uint32_t AHB_Read_Burst_Wait(uint16_t address, uint8_t DataLength, uint8_t * destbuff)
{
    uint32_t spiErrorFlag;
    spiDAT1_t dataconfig1_t;
    uint8_t blockSize;
    blockSize = DataLength * 4 + 4 + 1;  /* bytes, DataLength is # of 32-bit words; +1 means 1 dummy read byte */

    uint8_t txData[blockSize];

    dataconfig1_t.CS_HOLD = TRUE;
    dataconfig1_t.WDEL    = TRUE;
    dataconfig1_t.DFSEL   = SPI_FMT_0;
    dataconfig1_t.CSNR    = (0xFF ^ (0x1 << SPI_CS));            /*SPI3_CS1*/

    txData[0] = AHB_READ_B_FL_OPCODE;
    txData[1] = (address & 0xFF00) >> 0x8;
    txData[2] = (address & 0x00FF) >> 0x0;
    txData[3] = DataLength;

    /* Initiate SPI2 Transmit and Receive through Polling Mode
     * There is errors if the return value is not zero
     * 0-> no error detected
     * */
    spiErrorFlag = spiTransmitAndReceiveData(SPI_PORT, &dataconfig1_t, blockSize, &txData[0], destbuff);

    return spiErrorFlag;
}
