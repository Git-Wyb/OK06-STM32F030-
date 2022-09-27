#ifndef __ADC_H__
#define __ADC_H__

#include "stm32f0xx.h"
#include "Sys.h"
#include "variables.h"

//#define ADC1_DMA_EN

#define ADC1_DR_Address 0x40012440
//#define NUM_CAPTURE_DATA	(u1)7
//#define LIMIT_TIME_8BYTE	(u1)7

//#define	CURR				9						/*�^ؓ���ж���A/D����ch*/
//#define	VER				10						/*늈R�a��A/D����ch*/
//#define	TEMP				11						/*�¶��a��A/D����ch*/


void Init_Adc(void);
void R_ADC_Start(void);
void R_ADC_Stop(void);
void Init_Adc_DMA(void);
void adc_test(void);
void ADC_ChannelSet(uint32_t ADC_Channel,uint32_t ADC_SampleTime);

#endif
