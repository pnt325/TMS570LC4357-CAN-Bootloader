#include "HL_adc.h"

#define Temperature_Sensor 	6U

/* External Functions */
extern void adcStartConversion_selChn(adcBASE_t *adc, unsigned channel, unsigned fifo_size, unsigned group);
extern void adcGetSingleData(adcBASE_t *adc, unsigned group, adcData_t *data);
/** @fn void Temp_Sensor_demo(void)
*   @brief Temprature sensor demo software
*/
uint32 Get_Temp_Sensor_data(void)
{
	adcData_t adc_data;
	adcData_t *adc_data_ptr = &adc_data;

 	/** - Start Group1 ADC Conversion 
 	*     Select Channel 8 - Temprature Sensor for Conversion 
 	*/
	adcStartConversion_selChn(adcREG1, Temperature_Sensor, 1, adcGROUP1);

 	/** - Wait for ADC Group1 conversion to complete */
 	while(!adcIsConversionComplete(adcREG1, adcGROUP1)); 

	/** - Read the conversion result
	*     The data contains the Temprature sensor data
    */
	adcGetSingleData(adcREG1, adcGROUP1, adc_data_ptr);
	
	/** - Transnmit the Conversion data to PC using SCI
    */
	return (adc_data_ptr->value);
}
