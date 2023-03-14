/*=========================================================================
|--------------------------------------------------------------------------
| Project : Cann Bootloader Sample Test Code
| File    : can_bltest.c
|
| Edited by qjwang@ti.com for Hercules MCU CAN Bootloader Test
|
|--------------------------------------------------------------------------
| Redistribution and use of this file in source and binary forms, with
| or without modification, are permitted.
|
| THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
| "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
| LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
| FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
| COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
| INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
| BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
| LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
| CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
| LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
| ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
| POSSIBILITY OF SUCH DAMAGE.
 ========================================================================*/

//=========================================================================
// INCLUDES
//=========================================================================
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>    // Include file for Win32 time functions
#include <conio.h>      // Include file for _getch/kbhit 
#include <string.h> 

#include "Nican.h" 
#include "bl_commands.h"
#include "can_bltest.h"

#define INTERCOM                0x01

#define CAN_CMD_SUCCESS         0x00
#define CAN_CMD_FAIL            0x01

#define NC_DURATION_3SEC 3000

//*****************************************************************************
//
// A buffer used to construct commands to be sent to the target device.
//
//*****************************************************************************

//#define TMS470M
//#define TMS570LS04
//#define TMS570LS31
//#define TMS570LS12
#define TMS570LC43

#define BUFFER_SIZE  2048

static unsigned char g_pucBuffer[256];

unsigned char image[BUFFER_SIZE*100];
unsigned long image_size;

static unsigned char data_in[BUFFER_SIZE];
static unsigned char data_out[BUFFER_SIZE];

//=========================================================================
// CONSTANTS
//=========================================================================
// Handle for Network Interface Object (receiver)
NCTYPE_OBJH		RxHandle = 0;
// Handle for the CAN object (transmitter)
NCTYPE_OBJH		TxHandle = 0;

/* NI-CAN handle */
NCTYPE_OBJH	TxRx=0;     


/* This function converts the absolute time obtained from ncReadMult into a string. */
void AbsTimeToString(NCTYPE_ABS_TIME *time, char *TimeString)
{
   SYSTEMTIME	stime;
   FILETIME		localftime;

   FileTimeToLocalFileTime((FILETIME *)(time), &localftime);
   FileTimeToSystemTime(&localftime, &stime);
	  sprintf(TimeString, "%02d:%02d:%02d.%03d",
            stime.wHour, stime.wMinute, stime.wSecond, 
            stime.wMilliseconds);
}


/* This function is used to print a description of an NI-CAN error/warning. */
void PrintStat(NCTYPE_STATUS status, char *source)
{
	char statusString[1024];

	if (status != 0) 
	{
		ncStatusToString(status, sizeof(statusString), statusString);
		printf("\n%s\nSource = %s\n", statusString, source);
	
		if (status < 0)
		{
			// On error, close object handles, then exit.  
			ncCloseObject(TxHandle);
			ncCloseObject(RxHandle);
			exit(1);
		}      
	}
}

void delay(void) {
	static volatile unsigned int delayval;
	delayval = 10000000;   // 100000 are about 10ms
	while(delayval--);
}


void Get_BinaryData( char *filename )
{
    FILE *file;
    int trans_num = 0;
	unsigned char *pImage;

	image_size = 0;
	pImage = &image[0];

    // Open the file
    file = fopen(filename, "rb");
    if (!file) {
        printf("Unable to open file '%s'\n", filename);
        return;
    }

    while (!feof(file)) {
        int num_write, count;
        int i;

        // Read from the file
        num_write = fread((void *)pImage, 1, BUFFER_SIZE, file);
        if (!num_write)  break;

        printf("*** Transaction #%02d\n", trans_num);

        // Dump the data to the screen
        printf("Data written to device:");
        for (i = image_size; i < (image_size+num_write); ++i) {
            if ((i&0x0f) == 0)      printf("\n%04x:  ", i);
            printf("%02x ", image[i] & 0xff);
            if (((i+1)&0x07) == 0)  printf(" ");
        }
        printf("\n\n");

		image_size += num_write;
		pImage += num_write;
        ++trans_num;

    }

cleanup:
    fclose(file);
}

//=========================================================================
// MAIN PROGRAM
//=========================================================================
int main(int argc, char *argv[]) 
{
	NCTYPE_STATUS		Status;
	NCTYPE_STATE		CurrentState;
	NCTYPE_ATTRID		AttrIdList[8];
	NCTYPE_UINT32		AttrValueList[8];
	NCTYPE_CAN_FRAME	Transmit;
	NCTYPE_UINT32		Baudrate = 500000;//500000;//250000;//125000;
						/*
						Baud Rate is the baud rate to use for communication. Basic baud
						rates are supported, including 33333, 83333, 100000, 125000,
						250000, 500000, and 1000000.
						*/
	NCTYPE_CAN_STRUCT	ReceiveBuf[10]; 
	NCTYPE_CAN_STRUCT	WriteBuf[150]; 
	NCTYPE_UINT32		ActualDataSize=0; 
	u32					i;
	u16					j;
    u8                  k;
	char				Interface[6] = "CAN0";
	char				output[15];
	char				CharBuff[50];
/* Set XTD = 1 to send extended ID frames */
	int					XTD = 0;
	int					id = CAN_COMMAND_PING;
	char				data_length = 8;

	char *filename;
	int                 rcvID;
	int                 rcvData;	
	int                 rcvDataLen;
    unsigned char ulIdx;
	unsigned long ulOffset;
	unsigned long ulLength;
	unsigned long ulAddress;

#if defined (TMS570LS04)
	filename = "TMS570LS04x_rtiBlinky_BL_APP10020.bin";
#endif
#if defined (TMS570LS31)
	filename = "TMS570LSx_rtiBlinky_BL_APP10020.bin";  /* at 0x10020 in flash*/
#endif
#if defined (TMS570LS12)
	filename = "TMS570LSx_rtiBlinky_BL_APP10020.bin";  /* at 0x10020 in flash*/
#endif
#if defined (TMS470M)
	filename = "TMS470MBlinky.bin";
#endif

#if defined (TMS570LC43)
	filename = "TMS570LC43x_rtiBlinky_BL_APP10020.bin";  /* at 0x10020 in flash*/
#endif




/* Configure the CAN Network Interface Object */
	AttrIdList[0] =         NC_ATTR_BAUD_RATE;   
	AttrValueList[0] =      Baudrate;
	AttrIdList[1] =         NC_ATTR_START_ON_OPEN;
	AttrValueList[1] =      NC_TRUE;
	AttrIdList[2] =         NC_ATTR_READ_Q_LEN;
	AttrValueList[2] =      150;
	AttrIdList[3] =         NC_ATTR_WRITE_Q_LEN;
	AttrValueList[3] =      0;	
	AttrIdList[4] =         NC_ATTR_CAN_COMP_STD;
	AttrValueList[4] =      0;
	AttrIdList[5] =         NC_ATTR_CAN_MASK_STD;
	AttrValueList[5] =      NC_CAN_MASK_STD_DONTCARE;
	AttrIdList[6] =         NC_ATTR_CAN_COMP_XTD;
	AttrValueList[6] =      0;
	AttrIdList[7] =         NC_ATTR_CAN_MASK_XTD;
	AttrValueList[7] =      NC_CAN_MASK_XTD_DONTCARE;


	Status = ncConfig(Interface, 8, AttrIdList, AttrValueList);
	if (Status < 0) 
	{
	   PrintStat(Status, "ncConfig");
	}

	/* open the CAN Network Interface Object */
	Status = ncOpenObject(Interface, &TxHandle);
	if (Status < 0) 
	{
		PrintStat(Status, "ncOpenObject");
	}   
	/* open the CAN Network Interface Object */
	Status = ncOpenObject(Interface, &RxHandle);
	if (Status < 0) 
	{
		PrintStat(Status, "ncOpenObject");
	}   

/* print out the instructions to the I/O window */
	printf("\n\ninitialized successfuly on CAN0 ... \n\n");
	
#ifdef INTERCOM	
	printf("\nSending COMMAND_PING command ...\n");
#endif
/*==============================================================================
* COMMAND PING
*===============================================================================*/

	Transmit.DataLength = 0;
	Transmit.IsRemote = 0;
	Transmit.ArbitrationId = CAN_COMMAND_PING;	
						
	Status= ncWrite(TxHandle, sizeof(Transmit), &Transmit);			
	if (Status < 0) 
	{
		PrintStat(Status, "ncWrite");
	}
	
	// Wait for receiving ACK for TMS570, Timeout = 3s	
	Status = ncWaitForState(RxHandle,NC_ST_READ_AVAIL,NC_DURATION_3SEC,(NCTYPE_STATE_P)&CurrentState);
	if(Status != 0)
	{		
		printf(" - Timeout waiting for ACK!\n");
		printf(" - COMMAND_PING failed!\n");
		return 0;
	}	
	Status = ncRead(RxHandle, sizeof(ReceiveBuf), (void *)ReceiveBuf);
	if (Status < 0)
	{
			PrintStat(Status, "ncReadMult");
	}
	rcvID = ReceiveBuf[0].ArbitrationId;
	rcvData = ReceiveBuf[0].Data[0];
    rcvDataLen = ReceiveBuf[0].DataLength;
	if((rcvID != 0x05a6) && (rcvData != 0) || Status == CanWarnOldData)
	{
		printf(" - COMMAND_PING failed!\n");
		return 0;
	}
#ifdef INTERCOM
	else
	{
		char ch;
		printf(" - COMMAND_PING success!\n");		
		while(1)
		{
			printf("Enter \"Y\" to continue or \"N\" to stop:");
			scanf("%c",&ch);
			getchar();
			if(ch == 'n' || ch == 'N')
			{
				return 0;
			}
			else if(ch == 'y' || ch == 'Y')
			{
				break;
			}
			else
			{
				printf("Wrong Char!\n");
			}
		}
	}
	printf("\nSending COMMAND_DOWNLOAD command ...\n");
#endif

/*==============================================================================
* COMMAND Download Address and Size
*===============================================================================*/
    Get_BinaryData( filename );
#if defined (TMS470M)
	ulAddress = 0x00004000;
#else
	ulAddress = 0x00010020;   //changed on May 20, 2019
#endif

	Transmit.DataLength = 8;
	Transmit.IsRemote = 0;
	Transmit.ArbitrationId = CAN_COMMAND_DOWNLOAD;	

#if defined (TMS470M)
	Transmit.Data[0] = (ulAddress >>  0) & 0xff;
	Transmit.Data[1] = (ulAddress >>  8) & 0Xff;
	Transmit.Data[2] = (ulAddress >> 16) & 0xff;
	Transmit.Data[3] = (ulAddress >> 24) & 0xff;
	Transmit.Data[4] = (image_size >> 0) & 0xff;
	Transmit.Data[5] = (image_size >> 8) & 0xff;
	Transmit.Data[6] = (image_size >>16) & 0xff;
	Transmit.Data[7] = (image_size >>24) & 0xff;
#else
	Transmit.Data[0] = (ulAddress >> 24) & 0xff;
	Transmit.Data[1] = (ulAddress >> 16) & 0Xff;
	Transmit.Data[2] = (ulAddress >> 8) & 0xff;
	Transmit.Data[3] = ulAddress & 0xff;
	Transmit.Data[4] = (image_size >> 24) & 0xff;
	Transmit.Data[5] = (image_size >> 16) & 0xff;
	Transmit.Data[6] = (image_size >> 8) & 0xff;
	Transmit.Data[7] = image_size & 0xff;
#endif
	
	Status= ncWrite(TxHandle, sizeof(Transmit), &Transmit);			
	if (Status < 0) 
	{
		PrintStat(Status, "ncWrite");
	}

	// Wait for receiving ACK for TMS470, Timeout = 1s	
	Status = ncWaitForState(RxHandle,NC_ST_READ_AVAIL,NC_DURATION_3SEC,(NCTYPE_STATE_P)&CurrentState);
	if(Status != 0)
	{		
		printf(" - Timeout waiting for ACK!\n");
		printf(" - COMMAND_DOWNLOAD failed!\n");
		return 0;
	}	

	Status = ncRead(RxHandle, sizeof(ReceiveBuf), (void *)ReceiveBuf);
	if (Status < 0)
	{
			PrintStat(Status, "ncReadMult");
	}
	rcvID = ReceiveBuf[0].ArbitrationId;
	rcvData = ReceiveBuf[0].Data[0];
    rcvDataLen = ReceiveBuf[0].DataLength;
	if((rcvID != 0x05a6) && (rcvData != 0) || Status == CanWarnOldData)
	{
		printf(" - COMMAND_DOWNLOAD failed!\n");
		return 0;
	}
#ifdef INTERCOM
	else
	{
		char ch;
		printf(" - COMMAND_DOWNLOAD success!\n");		
		while(1)
		{
			printf("Enter \"Y\" to continue or \"N\" to stop:");
			scanf("%c",&ch);
			getchar();
			if(ch == 'n' || ch == 'N')
			{
				return 0;
			}
			else if(ch == 'y' || ch == 'Y')
			{
				break;
			}
			else
			{
				printf("Wrong Char!\n");
			}
		}
	}
	printf("\nSending COMMAND_SEND_DATA command ...\n");
#endif

/*==============================================================================
* COMMAND Sent Data
*===============================================================================*/
#ifndef INTERCOM
	Sleep(1000);
#endif

	Transmit.DataLength = 8;
	Transmit.IsRemote = 0;
	Transmit.ArbitrationId = CAN_COMMAND_SEND_DATA;	
	ulLength = image_size;

    //#3, Loop through the data in the code to be downloaded.
    for(ulOffset = 0; ulOffset < ulLength; ulOffset += 8)
    {
        // Build a send data command.
        for(ulIdx = 0; ulIdx < 8; ulIdx++)
        {
           	Transmit.Data[ulIdx] = image[ulOffset + ulIdx];
        }

        // See if the entire buffer contains valid data to be downloaded.
        if((ulOffset + ulIdx) > ulLength)
        {
			Transmit.DataLength = ulLength - ulOffset;
            // Send the send data command with the remainder of the data to be downloaded.
			Sleep(100);
			Status= ncWrite(TxHandle, sizeof(Transmit), &Transmit);			
			if (Status < 0) 
			{
				PrintStat(Status, "ncWrite");
			}

			// Wait for receiving ACK for TMS470, Timeout = 1s	
			Status = ncWaitForState(RxHandle,NC_ST_READ_AVAIL,NC_DURATION_1SEC,(NCTYPE_STATE_P)&CurrentState);
			if(Status != 0)
			{		
				printf(" - Timeout waiting for ACK!\n");
				printf(" - COMMAND_SEND_DATA failed!\n");
				return 0;
			}	

			//Get the ACK
			do{
				Status = ncRead(RxHandle, sizeof(ReceiveBuf), (void *)ReceiveBuf);
			} while (Status < 0);
				
			if (Status < 0)
			{
					PrintStat(Status, "ncReadMult");
			}
			rcvID = ReceiveBuf[0].ArbitrationId;
			rcvData = ReceiveBuf[0].Data[0];
			rcvDataLen = ReceiveBuf[0].DataLength;
			if((rcvID != 0x05a6) && (rcvData != 0) || Status == CanWarnOldData)
			{
				printf(" - COMMAND_SEND_DATA failed!\n");
				return 0;
			}
        }
        else
        {
			Transmit.DataLength = 8;
            // Send the send data command with the remainder of the data to be downloaded.
			Sleep(100);
			do{
				Status= ncWrite(TxHandle, sizeof(Transmit), &Transmit);			
			}while(Status < 0);
			if (Status < 0) 
			{
				PrintStat(Status, "ncWrite");
			}

			// Wait for receiving ACK for TMS470, Timeout = 1s	
			Status = ncWaitForState(RxHandle,NC_ST_READ_AVAIL,NC_DURATION_3SEC,(NCTYPE_STATE_P)&CurrentState);
			if(Status != 0)
			{		
				printf(" - Timeout waiting for ACK!\n");
				printf(" - COMMAND_SEND_DATA failed!\n");
				return 0;
			}	

			//Get the ACK
			do{
				Status = ncRead(RxHandle, sizeof(ReceiveBuf), (void *)ReceiveBuf);
			} while (Status < 0);
				
			if (Status < 0)
			{
					PrintStat(Status, "ncReadMult");
			}
			rcvID = ReceiveBuf[0].ArbitrationId;
			rcvData = ReceiveBuf[0].Data[0];
			rcvDataLen = ReceiveBuf[0].DataLength;
			if((rcvID != 0x05a6) && (rcvData != 0) || Status == CanWarnOldData)
			{
				printf(" - COMMAND_SEND_DATA failed!\n");
				return 0;
			}
        }
    }
#ifdef INTERCOM			
	if(1)
	{
		char ch;
		printf(" - COMMAND_SEND_DATA success!\n");		
		while(1)
		{
			printf("Enter \"Y\" to continue or \"N\" to stop:");
			scanf("%c",&ch);
			getchar();
			if(ch == 'n' || ch == 'N')
			{
				return 0;
			}
			else if(ch == 'y' || ch == 'Y')
			{
				break;
			}
			else
			{
				printf("Wrong Char!\n");
			}
		}
	}
	printf("\nSending COMMAND_RESET command ...\n");
#endif


/*==============================================================================
* COMMAND RUN
*===============================================================================*/
/*
	Transmit.DataLength = 4;
	Transmit.IsRemote = 0;
	Transmit.ArbitrationId = CAN_COMMAND_RUN;	

#if defined (TMS470M)
	ulAddress = 0x00004000;
	Transmit.Data[0] = (ulAddress >> 0) & 0xff;
	Transmit.Data[1] = (ulAddress >> 8) & 0Xff;
	Transmit.Data[2] = (ulAddress >> 16) & 0xff;
	Transmit.Data[3] = (ulAddress >> 24) & 0xff;
#else
	ulAddress = 0x00020000;
	Transmit.Data[0] = (ulAddress >> 24) & 0xff;
	Transmit.Data[1] = (ulAddress >> 16) & 0Xff;
	Transmit.Data[2] = (ulAddress >> 8) & 0xff;
	Transmit.Data[3] = ulAddress & 0xff;
#endif

	Status= ncWrite(TxHandle, sizeof(Transmit), &Transmit);			
	if (Status < 0) 
	{
		PrintStat(Status, "ncWrite");
	}

	Status = ncRead(RxHandle, sizeof(ReceiveBuf), (void *)ReceiveBuf);
	if (Status < 0)
	{
			PrintStat(Status, "ncReadMult");
	}
	rcvID = ReceiveBuf[0].ArbitrationId;
	rcvData = ReceiveBuf[0].Data[0];
    rcvDataLen = ReceiveBuf[0].DataLength;
	if((rcvID != 0x05a6) && (rcvData != 0))
	{
		printf(" - COMMAND_DOWNLOAD failed!\n");
		return 0;
	}

	Sleep(100);
*/
/*==============================================================================
* COMMAND RESET
*===============================================================================*/
	Transmit.DataLength = 0;
	Transmit.IsRemote = 0;
	Transmit.ArbitrationId = CAN_COMMAND_RESET;	


	Status= ncWrite(TxHandle, sizeof(Transmit), &Transmit);			
	if (Status < 0) 
	{
		PrintStat(Status, "ncWrite");
	}

	// Wait for receiving ACK for TMS470, Timeout = 1s	
	Status = ncWaitForState(RxHandle,NC_ST_READ_AVAIL,NC_DURATION_3SEC,(NCTYPE_STATE_P)&CurrentState);
	if(Status != 0)
	{		
		printf(" - Timeout waiting for ACK!\n");
		printf(" - COMMAND_RESET failed!\n");
		return 0;
	}	

	Status = ncRead(RxHandle, sizeof(ReceiveBuf), (void *)ReceiveBuf);
	if (Status < 0)
	{
			PrintStat(Status, "ncReadMult");
	}
	rcvID = ReceiveBuf[0].ArbitrationId;
	rcvData = ReceiveBuf[0].Data[0];
    rcvDataLen = ReceiveBuf[0].DataLength;
	if((rcvID != 0x05a6) && (rcvData != 0) || Status == CanWarnOldData)
	{
		printf(" - COMMAND_RESET failed!\n");
		return 0;
	}
#ifdef INTERCOM
	else
	{		
		printf(" - COMMAND_RESET success!\n\n");				
	}
#endif

	Sleep(100);

/* Close the Network Interface Object */
	Status = ncCloseObject(TxHandle);              
	if (Status < 0)
	{
		PrintStat(Status, "ncCloseObject");
	}
	Status = ncCloseObject(RxHandle);              
	if (Status < 0)
	{
		PrintStat(Status, "ncCloseObject");
	}

    printf("Application Code has been downloaded to flash correctly!!\n");
	
	return 0;    
}
