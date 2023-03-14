//*****************************************************************************
//
// bl_can.c - Test for the can boot loader.
//
// Contact Info:  qjwang@ti.com
// Copyright (c) 2010 Texas Instruments Incorporated.  All rights reserved.
// TI Information - Selective Disclosure
//
//*****************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include "bl_commands.h"
#include "can_bltest.h"
#include "Nican.h"



//*****************************************************************************
//
// Sends an ACK packet to the target.
//
//*****************************************************************************
 void AckPacket(Aardvark handle)
{
    unsigned char pucBuffer[2] = { 0, COMMAND_ACK };
	unsigned int count;

	// Send the ACK packet.
	count = aa_spi_write(handle, 2, pucBuffer, 2, data_in);
}

//*****************************************************************************
//
// Sends a NAK packet to the target.
//
//*****************************************************************************
 void NakPacket(Aardvark handle)
{
    unsigned char pucBuffer[2] = { 0, COMMAND_NAK };
	unsigned int count;

    //
    // Send the NAK packet.
    //
	count = aa_spi_write(handle, 2, pucBuffer, 2, data_in);
    
}

//*****************************************************************************
//
// Reads a packet from the target.
//
//*****************************************************************************
 unsigned int ReadPacket(Aardvark handle, unsigned char *pucBuffer, unsigned short *pulSize)
{
    unsigned char ulChecksum;
	unsigned int ulTimeout, waitCount, count;
    unsigned char  zeroA[16]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0,0,0,0,0,0,0,0};
    
	//
    // Loop until a non-zero size byte is received.
    //
    *pulSize = 0;
    ulTimeout = 4;

    while(*pulSize == 0)
    {
        //
        // Try to receive a byte.
        //
		count = aa_spi_write(handle, 1, zeroA, 1, (unsigned char *)pulSize);

    }

    // Decrement the packet size by the two bytes for the size and checksum.
    *pulSize -= 2;

    // Read the checksum byte.
	count = aa_spi_write(handle, 1,  zeroA, 1, (unsigned char *)&ulChecksum);

    // Read the packet data.
	count = aa_spi_write(handle, *pulSize, zeroA, *pulSize, pucBuffer);

    // Compute the checksum of the packet data and compare it to the sent
    // checksum.
    if(Checksum(pucBuffer, *pulSize) != ulChecksum)
    {
        NakPacket(handle);
    }
    else
    {
        AckPacket(handle);
    }

    // Success.
    return(1);
}

//*****************************************************************************
//
// Sends a packet to the target.
//
//*****************************************************************************
 unsigned int SendPacket(Aardvark handle, unsigned char *pucBuffer, unsigned short ulSize)
{
    unsigned char  ucChecksum;
	unsigned short i, length;
	int count;
	unsigned char  zeroA[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

    // Compute the checksum of the packet data.
    ucChecksum = Checksum(pucBuffer, ulSize);

    // Increment the packet size by the two bytes for the packet size and checksum.
    ulSize += 2;

    // #1, Send the packet size. The 1st Byte
   count = aa_spi_write(handle, 1, (unsigned char *)&ulSize, 1, data_in);


    // #2, Send the packet checksum. The 2nd byte
   count = aa_spi_write(handle, 1, (unsigned char *)&ucChecksum, 1, data_in);
  

   // #3, Send the packet data.
   count = aa_spi_write(handle, ulSize-2, pucBuffer, ulSize-2, data_in);

   // Loop until a non-zero byte is received.
	length = 1;

    while(data_in[0] == 0)
    {
        // Try to receive a byte.
        count = aa_spi_write(handle, length, zeroA, length, data_in);

		if (count < 0) {
			printf("error: %s\n", aa_status_string(count));
		}
		else if (count != length) {
			printf("error: read %d bytes (expected %d)\n", count, length);
		}

		// Dump the data to the screen
#if 0
		printf("\nData read from device:");
		for (i=0; i < length; ++i) {
			printf("%02x ", data_in[i] & 0xff);
		}
		printf("\n");
#endif

    }

    // Make sure that the packet was ACKed.
	if(data_in[0] != COMMAND_ACK)
    {
        return(0);
    }

    // Success.
    return(1);
}

//*****************************************************************************
//
// Download a block of code to the target using the download and send data
// commands.
//
//*****************************************************************************
 unsigned int DoDownload(Aardvark handle, unsigned char *pucBuffer, unsigned int ulAddress,
           unsigned int ulLength)
{
    unsigned char ulIdx;
	unsigned short ulOffset;
 
    // Build a download command.
    g_pucBuffer[0] = COMMAND_DOWNLOAD;
    g_pucBuffer[1] = (ulAddress >> 24) & 0xff;
    g_pucBuffer[2] = (ulAddress >> 16) & 0Xff;
    g_pucBuffer[3] = (ulAddress >> 8) & 0xff;
    g_pucBuffer[4] = ulAddress & 0xff;
    g_pucBuffer[5] = (ulLength >> 24) & 0xff;
    g_pucBuffer[6] = (ulLength >> 16) & 0xff;
    g_pucBuffer[7] = (ulLength >> 8) & 0xff;
    g_pucBuffer[8] = ulLength & 0xff;

    //#1, Send the download command.
    if(!SendPacket(handle, g_pucBuffer, 9))
    {
        printf(" - COMMAND_DOWNLOAD failed!\n");
        return(0);
    }

    //#2, Check the status of the the download command.
    aa_sleep_ms(1000);
    g_pucBuffer[0] = COMMAND_GET_STATUS;
    if(!SendPacket(handle, g_pucBuffer, 1))
    {
        printf(" - COMMAND_GET_STATUS failed!\n");
        return(0);
    }

    if(!ReadPacket(handle, g_pucBuffer, &ulOffset))
    {
        printf(" - Did not receive status packet!\n");
        return(0);
    }

    if((ulOffset != 1) || (g_pucBuffer[0] != COMMAND_RET_SUCCESS))
    {
        printf(" - Status is not success!\n");
        return(0);
    }

    //#3, Loop through the data in the code to be downloaded.
    for(ulOffset = 0; ulOffset < ulLength; ulOffset += 240)
    {
        // Build a send data command.
        g_pucBuffer[0] = COMMAND_SEND_DATA;
        for(ulIdx = 0; ulIdx < 240; ulIdx++)
        {
            g_pucBuffer[ulIdx + 1] = pucBuffer[ulOffset + ulIdx];
        }

        // See if the entire buffer contains valid data to be downloaded.
        if((ulOffset + ulIdx) > ulLength)
        {
            // Send the send data command with the remainder of the data to be
            // downloaded.
            if(!SendPacket(handle, g_pucBuffer, ulLength - ulOffset + 1))
            {
                printf(" - COMMAND_SEND_DATA failed!\n");
                return(0);
            }
        }
        else
        {
            // Send the send data command with the entire 252 bytes of data.
            aa_sleep_ms(1000);
            if(!SendPacket(handle, g_pucBuffer, 241))
            {
                printf(" - COMMAND_SEND_DATA failed!\n");
                return(0);
            }
        }
    }

    // Success.
    return(1);
}

//*****************************************************************************
//
// Test downloading via the configured interface.
//
//*****************************************************************************
unsigned int TestDownload(Aardvark handle)
{
    unsigned int error;
	unsigned long ulAddress, ulLength;

	ulAddress = 0x00020000;

    // #1,  Build a ping command.
    g_pucBuffer[0] = COMMAND_PING;

    // Send the ping command.
    if(!SendPacket(handle, g_pucBuffer, 1))
    {
        printf(" - COMMAND_PING failed!\n");
        return(0);
    }

    // #2, Download the code to be used with the run command.
    aa_sleep_ms(1000);
    if(!DoDownload(handle, image, ulAddress, image_size))
    {
        printf(" - Download failed!\n");
        return(0);
    }
	
    // #3, Send the run command.
    g_pucBuffer[0] = COMMAND_RUN;
    g_pucBuffer[1] = 0x00;
    g_pucBuffer[2] = 0x02;
    g_pucBuffer[3] = 0x00;
    g_pucBuffer[4] = 0x00;
    aa_sleep_ms(1000);
    if(!SendPacket(handle, g_pucBuffer, 5))
    {
        printf(" - COMMAND_RUN failed!\n");
        return(0);
    }

    // #4, Send the reset command.
    g_pucBuffer[0] = COMMAND_RESET;
    aa_sleep_ms(1000);
    if(!SendPacket(handle, g_pucBuffer, 1))
    {
        printf(" - COMMAND_RESET failed!\n");
        return(0);
    }

    // Success.
    return(1);
}

