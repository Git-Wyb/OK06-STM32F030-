#include "Adc.h"
#include "variables.h"
#include "Gpio.h"


void Init_Adc_Gpio(void)
{
    GPIO_InitTypeDef    GPIO_InitStruct;
    
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_5;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}

#ifndef ADC1_DMA_EN
void Init_Adc(void)
{
    ADC_InitTypeDef     ADC_InitStructure;
//    NVIC_InitTypeDef    NVIC_InitStruct;
    Init_Adc_Gpio();

    ADC_DeInit(ADC1);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    //ADC_JitterCmd(ADC1,ADC_CFGR2_JITOFFDIV2,ENABLE);   // PCLK/2,
    /* Initialize ADC structure */
    ADC_StructInit(&ADC_InitStructure);

    /* Configure the ADC1 in continous mode withe a resolutuion equal to 12 bits  */
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_10b;  //�ֱ���
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;  //����ת��
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; //����Ӳ�����������������ת��
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;  //ADC�����Ҷ���
    ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward; //ͨ��ɨ���ch0-ch18
    ADC_Init(ADC1, &ADC_InitStructure); 
    
    ADC1->IER = ADC_IER_EOCIE;    //����ת�������ж�
    NVIC_EnableIRQ(ADC1_COMP_IRQn);
    NVIC_SetPriority(ADC1_COMP_IRQn,5);
    
    /* ADC Calibration */
    ADC_GetCalibrationFactor(ADC1);
    
    /* Enable ADC1 */
    ADC_Cmd(ADC1, ENABLE);
    
    /* Wait the ADRDY falg */
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY));

    /* Convert the ADC1 ADC_Channel_1 with 55.5 Cycles as sampling time */ 
    //ADC_ChannelConfig(ADC1, ADC_Channel_2,ADC_SampleTime_55_5Cycles);//�¶� //ѡ��ת��ͨ��
    //ADC_ChannelConfig(ADC1,ADC_Channel_1,ADC_SampleTime_55_5Cycles);    //��ѹ
    //ADC_ChannelConfig(ADC1,ADC_Channel_5,ADC_SampleTime_55_5Cycles);    //������
}

void R_ADC_Start(void)
{
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY));
    ADC_StartOfConversion(ADC1);
}

void R_ADC_Stop(void)
{
    ADC_StopOfConversion(ADC1);
}

void ADC1_COMP_IRQHandler(void)
{
    //if(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == SET)
    if(ADC1->ISR & ADC_ISR_EOC == ADC_FLAG_EOC)
    {
        //ADC_ClearFlag(ADC1,ADC_FLAG_EOC);
        if( u1g_limit_ad < 7)
        {
            u2g_raw_data[u1g_limit_ad] = (ADC1->DR);
        }
        u1g_limit_ad ++; 
        if(u1g_limit_ad >= 7)
        {
            R_ADC_Stop();
        }
        ADC1->ISR = (uint32_t)ADC_FLAG_EOC; //Clear
    }
}

void select_ad_class(u1 u1l_ad_class)
{
	if((ADC1->CR & 0x00000005) == 0x00000001) //ADC enable but no ADC conversion is ongoing.
    {	
        switch( u1l_ad_class )
        {
            case CURR :  //������
                //ADC_ChannelConfig(ADC1,ADC_Channel_5,ADC_SampleTime_55_5Cycles);
                ADC_ChannelSet(ADC_Channel_5,ADC_SampleTime_55_5Cycles);
                break;

            case VER :  //��ѹ 
                ADC_ChannelSet(ADC_Channel_1,ADC_SampleTime_55_5Cycles);
                break;

            case TEMP : //�¶�
                ADC_ChannelSet(ADC_Channel_2,ADC_SampleTime_55_5Cycles);
                break;

            default:
                break;
        } 
    }
	else{}	
}
u1 curr_buff[10] = {0};
u1 ad_num_test = 9;
void adc_test(void)
{
    u1 i = 0;
    if(u1g_limit_ad >= 7)
    {
        u1g_limit_ad = 0;
        //R_ADC_Stop();
        select_ad_class(ad_num_test);
        if(ad_num_test == VER)  
        {
            P_VER_POWER_1;
        }
        else    
        {
            P_VER_POWER_0;
        }
        if(ad_num_test == 10)
        {
            for(i=0; i<7; i++)
            {
                curr_buff[i] = u2g_raw_data[i];
            }
        }
        R_ADC_Start();
        ad_num_test++;
        if(ad_num_test == 12) ad_num_test = 9;
    }
}

void ADC_ChannelSet(uint32_t ADC_Channel,uint32_t ADC_SampleTime)
{
    ADC1->CHSELR = ADC_Channel;
    ADC1->SMPR = ADC_SampleTime;
}

#else
void Init_Adc_DMA(void)
{
    ADC_InitTypeDef     ADC_InitStructure;
    DMA_InitTypeDef     DMA_InitStructure;
    NVIC_InitTypeDef    NVIC_InitStruct;
    
    Init_Adc_Gpio();
    
    /* ADC1 DeInit */  
    ADC_DeInit(ADC1);

    /* ADC1 Periph clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    //RCC_ADCCLKConfig(RCC_ADCCLK_PCLK_Div2);
    
    /* DMA1 clock enable */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 , ENABLE);

    /* DMA1 Channel1 Config */
    DMA_DeInit(DMA1_Channel1);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_DR_Address;   //ADC1���ݼĴ�����ַ
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)u2g_raw_data;  //�洢����ַ
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //�������ȡ����(���赽�ڴ�)
    DMA_InitStructure.DMA_BufferSize = NUM_CAPTURE_DATA;//���ݳ���
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�����ַ������
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;     //�洢����ַ����
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //��������Ϊ16bit
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //�洢������Ϊ16bit
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMA_Mode_Normal; //������ģʽ
    DMA_InitStructure.DMA_Priority = DMA_Priority_High; //ͨ�����ȼ���
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;    //��ֹ�ڴ浽�ڴ�ģʽ
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);
    
    NVIC_InitStruct.NVIC_IRQChannel = DMA1_Channel1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

    /* Initialize ADC structure */
    ADC_StructInit(&ADC_InitStructure);

    /* Configure the ADC1 in continous mode withe a resolutuion equal to 12 bits  */
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_10b;  //�ֱ���
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; //����ת��ģʽ
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; //����Ӳ������
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //�����Ҷ���
    ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward; //ͨ��ɨ���ch0-ch18
    ADC_Init(ADC1, &ADC_InitStructure); 

    /* Convert the ADC1 temperature sensor  with 55.5 Cycles as sampling time */ 
    //ADC_ChannelConfig(ADC1, ADC_Channel_TempSensor , ADC_SampleTime_55_5Cycles);  
    //ADC_TempSensorCmd(ENABLE);

    /* Convert the ADC1 Vref  with 55.5 Cycles as sampling time */ 
    //ADC_ChannelConfig(ADC1, ADC_Channel_Vrefint , ADC_SampleTime_55_5Cycles); 
    //ADC_VrefintCmd(ENABLE);

    /* ADC Calibration */
    ADC_GetCalibrationFactor(ADC1);
    
    /* Enable ADC_DMA */
    //ADC_DMACmd(ADC1, ENABLE);

    /* Enable ADC1 */
    ADC_Cmd(ADC1, ENABLE);  
    
    /* ADC DMA request in circular mode */
    ADC_DMARequestModeConfig(ADC1, ADC_DMAMode_OneShot);    //DMA One Shot Mode
    
    /* Wait the ADRDY falg */
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY)); 

    /* DMA1 Channel1 enable */
    //DMA_Cmd(DMA1_Channel1, ENABLE);
    
    DMA_ITConfig(DMA1_Channel1,DMA_IT_TC,ENABLE);
    DMA_ClearFlag(DMA1_FLAG_TC1); 
  
    /* ADC1 regular Software Start Conv */ 
    //ADC_StartOfConversion(ADC1);
}

void DMA1_Channel1_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_IT_TC1))
    {
        ADC_StopOfConversion(ADC1);
        ADC_DMACmd(ADC1,DISABLE);
        DMA_Cmd(DMA1_Channel1,DISABLE);       
        u1g_limit_ad = 7;               
        DMA_ClearFlag(DMA1_FLAG_TC1);
    }
}

void R_ADC_Start(void)
{
    DMA1_Channel1->CNDTR = NUM_CAPTURE_DATA;
    ADC_DMACmd(ADC1,ENABLE);
    DMA_Cmd(DMA1_Channel1, ENABLE);
    ADC_StartOfConversion(ADC1);
}

void R_ADC_Stop(void)
{
    ADC_DMACmd(ADC1,DISABLE);
    DMA_Cmd(DMA1_Channel1,DISABLE);
    ADC_StopOfConversion(ADC1);
}
#endif



