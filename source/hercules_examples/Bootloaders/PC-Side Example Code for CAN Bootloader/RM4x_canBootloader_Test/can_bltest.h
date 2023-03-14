//*****************************************************************************
//
// can_bltest.h - Test for the can boot loader.
//
// Copyright (c) 2010 Texas Instruments Incorporated.  All rights reserved.
// TI Information - Selective Disclosure
//
//*****************************************************************************


#ifndef __can_bltest_h__
#define __can_bltest_h__

#define  GET_DATA_FROM_FILE
//#undefine  GET_DATA_FROM_FILE

int main(int argc, char *argv[]) ;

unsigned char Checksum(unsigned char *pucBuffer, unsigned short ulSize);

void AckPacket(int handle);
void NakPacket(int handle);

unsigned int ReadPacket(int handle, unsigned char *pucBuffer, unsigned short *pulSize);
unsigned int SendPacket(int handle, unsigned char *pucBuffer, unsigned short ulSize);
unsigned int DoDownload(int handle, unsigned char *pucBuffer, unsigned int ulAddress, unsigned int ulLength);

void Get_BinaryData( char *filename );

#endif  /* __can_bltest_h__ */
