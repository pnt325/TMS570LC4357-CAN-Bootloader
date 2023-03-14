//*****************************************************************************
//
// bl_commands.h - The list of commands and return messages supported by the
//                 boot loader.
//
// Copyright (c) 2006-2011 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 8049 of the Stellaris Firmware Development Package.
//
//*****************************************************************************

#ifndef __BL_COMMANDS_H__
#define __BL_COMMANDS_H__

//*****************************************************************************
// These defines are used to define the range of values that are used for
// CAN update protocol.
//*****************************************************************************

//*****************************************************************************
// These defines are used to define the range of values that are used for
// CAN update protocol.
//*****************************************************************************

#define CAN_MSGID_MFR           0x5A0
#define CAN_API_UPD              CAN_MSGID_MFR                  //0x7F0
#define CAN_COMMAND_PING         (CAN_API_UPD | 0) << 0         //0x7F0
#define CAN_COMMAND_DOWNLOAD     (CAN_API_UPD | 1) << 0         //0x7F1
#define CAN_COMMAND_RUN          (CAN_API_UPD | 2) << 0         //0x7F1
#define CAN_COMMAND_REQUEST      (CAN_API_UPD | 3) << 0         //0x7F5
#define CAN_COMMAND_SEND_DATA    (CAN_API_UPD | 4) << 0         //0x7F2
#define CAN_COMMAND_RESET        (CAN_API_UPD | 5) << 0         //0x7F3
#define CAN_COMMAND_ACK          (CAN_API_UPD | 6) << 0         //0x7F4


#endif // __BL_COMMANDS_H__
