#include "HL_adc.h"
#include "HL_sci.h"

/** @fn void adcGetSingleData(adcBASE_t *adc, unsigned group, adcData_t *data)
*   @brief Get single converted ADC value
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*              - adcREG2: ADC2 module pointer
*              - adcREG3: ADC3 module pointer
*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*   @param[out] data Pointer to store ADC converted data
*
*/
void adcGetSingleData(adcBASE_t *adc, unsigned group, adcData_t *data)
{
    unsigned  buf;
    adcData_t *ptr = data; 

    /** -  Get conversion data and channel/pin id */
    buf        = adc->GxBUF[group].BUF0;
    ptr->value = (unsigned short)(buf & 0xFFFU);
    ptr->id    = (unsigned short)((buf >> 16U) & 0x1FU); // int to unsigned short

    adc->GxINTFLG[group] = 9U;

    /**   @note The function canInit has to be called before this function can be used.\n
    *           The user is responsible to initialize the message box.
    */
}

/** @fn void adcStartConversion_selChn(adcBASE_t *adc, unsigned channel, unsigned fifo_size, unsigned group)
*   @brief Starts an ADC conversion
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*              - adcREG2: ADC2 module pointer
*   @param[in] channel ADC channel to be selected for conversion
*   @param[in] fifo_size ADC fifo size to be configured.
*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*
*   This function Starts the convesion of the ADC selected group for the selected channel
*
*/
void adcStartConversion_selChn(adcBASE_t *adc, unsigned channel, unsigned fifo_size, unsigned group)
{
    /** - Setup FiFo size */
    adc->GxINTCR[group] = fifo_size;

    /** - Start Conversion */
    adc->GxSEL[group] = 1 << channel;
}

void sciDisplayText(sciBASE_t *sci, uint8 *text, uint32 length) {
	while (length--) {
		while ((sci->FLR & 0x4) == 4)
			; /* wait until busy */
		sciSendByte(sci, *text++); /* send out text   */
	};
}

void sciDisplayData(sciBASE_t *sci, uint8 *text,uint32 length)
{
    uint8 txt = 0;
    uint8 txt1 = 0;

#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
text = text + (length -1);
#endif

    while(length--)
    {
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
        txt = *text--;
#else
        txt = *text++;
#endif

        txt1 = txt;

        txt  &= ~(0xF0);
        txt1 &= ~(0x0F);
        txt1  =txt1>>4;

        if(txt<=0x9)
        {
            txt +=0x30;
        }
        else if(txt > 0x9 && txt < 0xF)
        {
            txt +=0x37;
        }
        else
        {
            txt = 0x30;
        }

        if(txt1 <= 0x9)
        {
            txt1 +=0x30;
        }
        else if((txt1 > 0x9) && (txt1 <= 0xF))
        {
            txt1 +=0x37;
        }
        else
        {
            txt1 = 0x30;
        }

        while ((sciREG1->FLR & 0x4) == 4); /* wait until busy */
        sciSendByte(sciREG1,txt1);      /* send out text   */
        while ((sciREG1->FLR & 0x4) == 4); /* wait until busy */
        sciSendByte(sciREG1,txt);      /* send out text   */
    };
}
