#include "board_adc.h"

static volatile adcData_t raw_adc_data[13U];
static volatile adc_scaled_voltages adc_vals;

static float toVolts(uint16_t raw)
{
	return ((float)raw*(BOARD_ADREF_HIGH - BOARD_ADREF_LOW)/(float)ADC_RES) + BOARD_ADREF_LOW;
}

void board_adc_init(void)
{
	adcInit();
	adcStartConversion(adcREG1, adcGROUP1);
}

float board_adc_volts(board_adc_channel ch)
{
	switch(ch)
	{
		case VBAT1:
			return adc_vals.vbat1*K_VBAT1 + OFFSET_VBAT1;
		case VBAT2:
			return adc_vals.vbat2*K_VBAT2 + OFFSET_VBAT2;
		case INA_SENSE:
			return adc_vals.ina_sense*K_INA_SENSE + OFFSET_INA_SENSE;
		case AD1:
			return adc_vals.ad1*K_AD1 + OFFSET_AD1;
		case AD2:
			return adc_vals.ad2*K_AD2 + OFFSET_AD2;
		case AD3:
			return adc_vals.ad3*K_AD3 + OFFSET_AD3;
		case AD4:
			return adc_vals.ad4*K_AD4 + OFFSET_AD4;
		case AD5:
			return adc_vals.ad5*K_AD5 + OFFSET_AD5;
		case AD6:
			return adc_vals.ad6*K_AD6 + OFFSET_AD6;
		case AD7:
			return adc_vals.ad7*K_AD7 + OFFSET_AD7;
		case AD8:
			return adc_vals.ad8*K_AD8 + OFFSET_AD8;
		case P_SENSOR_1:
			return adc_vals.p_sensor_1*K_P_SENSOR_1 + OFFSET_P_SENSOR_1;
		case P_SENSOR_2:
			return adc_vals.p_sensor_2*K_P_SENSOR_2 + OFFSET_P_SENSOR_2;
		default:
			return 0.0f;
	}
}

void board_adc_update_blocking(void)
{
	while(!adcIsConversionComplete(adcREG1, adcGROUP1));
	adcGetData(adcREG1, adcGROUP1, &raw_adc_data[0]);
	
	if(raw_adc_data[0].id == CHANNEL_ID_VBAT1)
	{
		adc_vals.vbat1 = toVolts(raw_adc_data[0].value);
	}
	if(raw_adc_data[1].id == CHANNEL_ID_AD7)
	{
		adc_vals.ad7 = toVolts(raw_adc_data[1].value);
	}
	if(raw_adc_data[2].id == CHANNEL_ID_P_SENSOR_1)
	{
		adc_vals.p_sensor_1 = toVolts(raw_adc_data[2].value);
	}
	if(raw_adc_data[3].id == CHANNEL_ID_P_SENSOR_2)
	{
		adc_vals.p_sensor_2 = toVolts(raw_adc_data[3].value);
	}
	if(raw_adc_data[4].id == CHANNEL_ID_AD1)
	{
		adc_vals.ad1 = toVolts(raw_adc_data[4].value);
	}
	if(raw_adc_data[5].id == CHANNEL_ID_AD6)
	{
		adc_vals.ad6 = toVolts(raw_adc_data[5].value);
	}
	if(raw_adc_data[6].id == CHANNEL_ID_AD8)
	{
		adc_vals.ad8 = toVolts(raw_adc_data[6].value);
	}
	if(raw_adc_data[7].id == CHANNEL_ID_INA_SENSE)
	{
		adc_vals.ina_sense = toVolts(raw_adc_data[7].value);
	}
	if(raw_adc_data[8].id == CHANNEL_ID_VBAT2)
	{
		adc_vals.vbat2 = toVolts(raw_adc_data[8].value);
	}
	if(raw_adc_data[9].id == CHANNEL_ID_AD2)
	{
		adc_vals.ad2 = toVolts(raw_adc_data[9].value);
	}
	if(raw_adc_data[10].id == CHANNEL_ID_AD3)
	{
		adc_vals.ad3 = toVolts(raw_adc_data[10].value);
	}
	if(raw_adc_data[11].id == CHANNEL_ID_AD4)
	{
		adc_vals.ad4 = toVolts(raw_adc_data[11].value);
	}
	if(raw_adc_data[12].id == CHANNEL_ID_AD5)
	{
		adc_vals.ad5 = toVolts(raw_adc_data[12].value);
	}
}