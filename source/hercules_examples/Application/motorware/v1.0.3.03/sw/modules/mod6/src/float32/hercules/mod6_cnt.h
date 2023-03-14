/* --COPYRIGHT--,BSD
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
/*!
 * @file    mod6_cnt.h
 * @author  Texas Instruments (C) Copyright 2012 (Assisted by D3 Engineering Tech Team)
 * @date    5-7-2012
 * @version 1.0
 * @brief   This is the header file for the Mod 6 Counter Module
 */
#ifndef __MOD6_CNT_H__
#define __MOD6_CNT_H__

// Includes
#include "modules/types/src/32b/types.h"

// Defines
//Default initalizer for the MOD6CNT object.
#define MOD6CNT_TRIGIN_DEFAULT	0
#define MOD6CNT_CNTDIR_DEFAULT	0.0
#define	MOD6CNT_COUNT_DEFAULT	0

// Typedefs
typedef struct {
    int  trigInput;   	// Input: Modulo 6 counter trigger input
    float32_t	 cntDirection;	// Count UP >= 0 or DOWN < 0
    int  counter;	    // Output: Modulo 6 counter output - Q0 (0,1,2,3,4,5)
} MOD6CNT;

typedef MOD6CNT *H_MOD6CNT;

// Globals

// Function Prototypes
//Prototypes for the functions in MOD6_CNT.C
/*!
 * @ingroup         MOD6CNT_Setup
 * @fn              void MOD6CNT_Setup(H_MOD6CNT mod6Handle)
 * @brief           Function to setup the Modular 6 Counter
 * @param [in/out]  mod6Handle		The Handle for the Modular 6 Counter
 */
void MOD6CNT_Setup(H_MOD6CNT mod6Handle);

/*!
 * @ingroup         MOD6CNT_Set_TrigIn
 * @fn              void MOD6CNT_Set_TrigIn(H_MOD6CNT mod6Handle, int trigInput)
 * @brief           Function to Set the TrigIn of the Modular 6 Counter
 * @param [in/out]  mod6Handle		The Handle for the Modular 6 Counter
 * @param [in]		trigInput		The new trigInput value for the Modular 6 Counter
 */
void MOD6CNT_Set_TrigIn(H_MOD6CNT mod6Handle, int trigInput);

/*!
 * @ingroup         MOD6CNT_Get_TrigIn
 * @fn              int MOD6CNT_Get_TrigIn(H_MOD6CNT mod6Handle)
 * @brief           Function to Get TrigIn for the Modular 6 Counter
 * @param [in]      mod6Handle		The Handle for the Modular 6 Counter
 * @return			int				The trigInput value for the Modular 6 Counter
 */
int MOD6CNT_Get_TrigIn(H_MOD6CNT mod6Handle);

/*!
 * @ingroup         MOD6CNT_Set_CntDir
 * @fn              void MOD6CNT_Set_CntDir(H_MOD6CNT mod6Handle, float32_t CntDirection)
 * @brief           Function to Set the cntDirection of the Modular 6 Counter
 * @param [in/out]  mod6Handle		The Handle for the Modular 6 Counter
 * @param [in]		cntDirection	The new cntDirection value for the Modular 6 Counter
 */
void MOD6CNT_Set_CntDir(H_MOD6CNT mod6Handle, float32_t cntDirection);

/*!
 * @ingroup         MOD6CNT_Get_CntDir
 * @fn              float32_t MOD6CNT_Get_CntDir(H_MOD6CNT mod6Handle)
 * @brief           Function to Get cntDirection for the Modular 6 Counter
 * @param [in]      mod6Handle		The Handle for the Modular 6 Counter
 * @return			float32_t				The cntDirection value for the Modular 6 Counter
 */
float32_t MOD6CNT_Get_CntDir(H_MOD6CNT mod6Handle);

/*!
 * @ingroup         MOD6CNT_Set_Counter
 * @fn              void MOD6CNT_Set_Counter(H_MOD6CNT mod6Handle, int Counter)
 * @brief           Function to Set the counter of the Modular 6 Counter
 * @param [in/out]  mod6Handle		The Handle for the Modular 6 Counter
 * @param [in]		counter			The new counter value for the Modular 6 Counter
 */
void MOD6CNT_Set_Counter(H_MOD6CNT mod6Handle, int counter);

/*!
 * @ingroup         MOD6CNT_Get_Counter
 * @fn              int MOD6CNT_Get_Counter(H_MOD6CNT mod6Handle)
 * @brief           Function to Get the Counter for the Modular 6 Counter
 * @param [in]      mod6Handle		The Handle for the Modular 6 Counter
 * @return			int				The Counter value for the Modular 6 Counter
 */
int MOD6CNT_Get_Counter(H_MOD6CNT mod6Handle);

/*!
 * @ingroup         MOD6CNT_Calc
 * @fn              void MOD6CNT_Calc(H_MOD6CNT v)
 * @brief           Function to run the Mod6 Calculation
 * @param [in/out]  v		The Handler for the Mod6 Module
 */
inline void MOD6CNT_Calc(H_MOD6CNT v)
{
    if (v->trigInput > 0)
    {
        if (v->cntDirection >= 0)
        {
            if(v->counter == 5)
            {
                v->counter = 0;
            }
            else
            {
                v->counter++;
            }
        }
        else
        {
            if(v->counter == 0)
            {
                v->counter = 5;
            }
            else
            {
                v->counter--;
            }
        }
    }
}

#endif // __MOD_6CNT_H__ 
