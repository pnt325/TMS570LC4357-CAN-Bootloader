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
 * @file    DLOG.h
 * @author  Texas Instruments (C) Copyright 2012 (Assisted by D3 Engineering Tech Team)
 * @date    5-7-2012
 * @version 1.0
 * @brief   This is the header file for the DLogger
 */

#ifndef GRAPH_DATA_H_
#define GRAPH_DATA_H_

// Includes

// Defines
#define WAIT_TRIGGER_LOW	0
#define WAIT_TRIGGER_HIGH	1
#define FILL_BUFFERS		2
#define HOLDOFF				3
#define DLOG_ARRAY_SIZE		256

// Typedefs
typedef struct {
    float32_t *ch1Ptr;
    float32_t *ch2Ptr;
    float32_t *ch3Ptr;
    float32_t *ch4Ptr;
    float32_t *writePtr1;
    float32_t *writePtr2;
    float32_t *writePtr3;
    float32_t *writePtr4;
    float32_t trigValue;
    uint16_t holdoff;
    uint16_t cntr;
    uint16_t size;
    uint16_t prescalar;
    uint16_t skipCntr;
    uint16_t task;
} GRAPH_DATA;

typedef GRAPH_DATA *GRAPH_Handle;

// Globals
extern float32_t gDLog4CHBuff1[DLOG_ARRAY_SIZE];
extern float32_t gDLog4CHBuff2[DLOG_ARRAY_SIZE];
extern float32_t gDLog4CHBuff3[DLOG_ARRAY_SIZE];
extern float32_t gDLog4CHBuff4[DLOG_ARRAY_SIZE];

// Function Prototypes
/*!
 * @ingroup         Graph_Data_Init
 * @fn              void Graph_Data_Init(GRAPH_Handle g)
 * @brief           Initializes the Graph handler/DLogger
 * @param [in/out]  g	Handler for the Grapher
 */
inline void Graph_Data_Init(GRAPH_Handle g)
{
    g->task = WAIT_TRIGGER_LOW;
    g->writePtr1 = &gDLog4CHBuff1[0];
    g->writePtr2 = &gDLog4CHBuff2[0];
    g->writePtr3 = &gDLog4CHBuff3[0];
    g->writePtr4 = &gDLog4CHBuff4[0];
}

/*!
 * @ingroup         Graph_Data_Update
 * @fn              void Graph_Data_Update(GRAPH_Handle g)
 * @brief           Function to update the graph data
 * @param [in/out]  g	Handler for the Grapher
 */
inline void Graph_Data_Update(GRAPH_Handle g)
{
    switch(g->task)
    {
        //wait for channel 1 to fall below the trigger level
    case WAIT_TRIGGER_LOW:
        if((*g->ch1Ptr < g->trigValue)||(g->trigValue == 0))
        {
            g->task++;
        }
        break;
        //wait for the rising edge
    case WAIT_TRIGGER_HIGH:
        if((*g->ch1Ptr > g->trigValue)||(g->trigValue == 0))
        {
            g->task++;
            g->cntr = 0;
            g->skipCntr = 0;
        }
        break;
    case FILL_BUFFERS:
        g->skipCntr++;
        if(g->skipCntr == g->prescalar)
        {
            g->skipCntr = 0;
            g->writePtr1[g->cntr] = *g->ch1Ptr;
            g->writePtr2[g->cntr] = *g->ch2Ptr;
            g->writePtr3[g->cntr] = *g->ch3Ptr;
            g->writePtr4[g->cntr] = *g->ch4Ptr;
            if(g->cntr == g->size)
            {
                g->task++;
                g->cntr = 0;
                g->skipCntr = 0;
            }
            else
            	g->cntr++;
        }
        break;
    case HOLDOFF:
        g->cntr++;
        if(g->cntr == g->holdoff)
        {
            g->task = WAIT_TRIGGER_LOW;
            g->cntr = 0;
            g->skipCntr = 0;
        }
        break;
    }
}

//! \brief     	Sets the graphing module prescalar
//! \param[in] 	handle		The graph handle
//! \param[in] 	prescalar	Value of prescalar
inline void Graph_set_prescalar(GRAPH_Handle graphHandle, uint16_t prescalar)
{
	GRAPH_DATA *obj = (GRAPH_DATA *) graphHandle;

	obj->prescalar = prescalar;
}


//! \brief     	Gets the graphing module prescalar
//! \param[in] 	handle		The graph handle
//! \return		prescalar	Current value of prescalar
inline uint16_t Graph_get_prescalar(GRAPH_Handle graphHandle)
{
	GRAPH_DATA *obj = (GRAPH_DATA *) graphHandle;

	return(obj->prescalar);
}


#endif /*GRAPH_DATA_H_*/
