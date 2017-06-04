#ifndef BOARD_ADC_H
#define BOARD_ADC_H		1

#include "hal_common_includes.h"

#define BOARD_ADREF_HIGH 	3.3f
#define BOARD_ADREF_LOW 	0.0f
#define ADC_RES				4096U

#define CHANNEL_ID_VBAT1		0U
#define CHANNEL_ID_AD7			1U
#define CHANNEL_ID_P_SENSOR_1	2U
#define CHANNEL_ID_P_SENSOR_2	3U
#define CHANNEL_ID_AD1			7U
#define CHANNEL_ID_AD6			9U
#define CHANNEL_ID_AD8			10U
#define CHANNEL_ID_INA_SENSE	16U
#define CHANNEL_ID_VBAT2		17U
#define CHANNEL_ID_AD2			18U
#define CHANNEL_ID_AD3			19U
#define CHANNEL_ID_AD4			20U
#define CHANNEL_ID_AD5			21U

#define K_VBAT1				1.0f
#define K_VBAT2				1.0f
#define K_INA_SENSE			1.0f
#define K_AD1				1.0f
#define K_AD2				1.0f
#define K_AD3				1.0f
#define K_AD4				1.0f
#define K_AD5				1.0f
#define K_AD6				1.0f
#define K_AD7				1.0f
#define K_AD8				1.0f
#define K_P_SENSOR_1		1.0f
#define K_P_SENSOR_2		1.0f

#define OFFSET_VBAT1		0.0f
#define OFFSET_VBAT2		0.0f
#define OFFSET_INA_SENSE	0.0f
#define OFFSET_AD1			0.0f
#define OFFSET_AD2			0.0f
#define OFFSET_AD3			0.0f
#define OFFSET_AD4			0.0f
#define OFFSET_AD5			0.0f
#define OFFSET_AD6			0.0f
#define OFFSET_AD7			0.0f
#define OFFSET_AD8			0.0f
#define OFFSET_P_SENSOR_1	0.0f
#define OFFSET_P_SENSOR_2	0.0f

typedef struct {
	float vbat1;
	float vbat2;
	float ina_sense;
	float ad1;
	float ad2;
	float ad3;
	float ad4;
	float ad5;
	float ad6;
	float ad7;
	float ad8;
	float p_sensor_1;
	float p_sensor_2;
} adc_scaled_voltages;

typedef enum {
	VBAT1,
	VBAT2,
	INA_SENSE,
	AD1,
	AD2,
	AD3,
	AD4,
	AD5,
	AD6,
	AD7,
	AD8,
	P_SENSOR_1,
	P_SENSOR_2
} board_adc_channel;

void board_adc_init(void);
float board_adc_volts(board_adc_channel ch);
void board_adc_update_blocking(void);

#endif