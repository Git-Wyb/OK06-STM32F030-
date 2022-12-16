#include "Timer.h"
#include "variables.h"
#include "constants.h"
#include "functions.h"
//#include "serial_transmission.h"
#include "anjou_test.h"
#include "flash_data_read.h"
#include "tst_break.h"

//u2 u2g_d_pwm = 0;
//u2 u2g_t_break_duty = 0;
u1 time_cnt = 0;
u4 u4l_High_Length = 0;
u4 u4l_Low_Length = 0;
u4 u4g_Plus_Length = 0;

volatile u4 g_tau0_ch2_width = 0UL;

static u1 u1l_count_100ms = 0;

void Init_Timer6(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* TIM6 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

    /* Enable the TIM6 gloabal Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM6_DAC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 4;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = 1000 - 1;   //ARR自动重载值
    TIM_TimeBaseStructure.TIM_Prescaler = 15;//f = fCK_PSC / (PSC[15:0] + 1) = 16MHz / 16 = 1MHz.
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);

    TIM_SetCounter(TIM6,0);
    TIM_ARRPreloadConfig(TIM6,ENABLE);  //开启自动加载值
    /* TIM Interrupts enable */
    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);//

    /* TIM6 enable counter */
    TIM_Cmd(TIM6, ENABLE);
}
//TIM_ClearFlag
void TIM6_DAC_IRQHandler(void)
{
    if((TIM6->SR & TIM_FLAG_Update) == SET)    
    {
        TIM6->SR &= ~TIM_FLAG_Update;   //Clear flag
        int_system_timer();
        time_cnt++; 
        if(time_cnt >= 200) 
        {
            time_cnt = 0;
        }
    }
}
//TIM_PrescalerConfig

//计时结束产生中断，马达T = 2.732ms(366Hz)，刹车T = 9ms(111Hz)
//马达f = 4MHz,MAX = 10928//0x2AB0,99.6% * MAX = 10884//0x2A84
//PA6 -> TIM16_CH1
void Init_Timer16(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    /* GPIOA Clocks enable */
    RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_5);
    
    /* TIM16 clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM16, ENABLE);
    
    /* Enable the TIM16 gloabal Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM16_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = D_PWM_MAX_T - 1; //T = 2.732ms, 10928//0x2AB0
    TIM_TimeBaseStructure.TIM_Prescaler = 3;   //16MHz/(3+1) = 4MHz.
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM16, &TIM_TimeBaseStructure);
    TIM_ARRPreloadConfig(TIM16,ENABLE);  //开启自动加载值
    
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   //CNT < TIM_Pulse为有效电平
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_Pulse = 0;//5464;//8742;//3278;//5464;  //占空比

    TIM_OC1Init(TIM16, &TIM_OCInitStructure);
    //TIM_OC1PreloadConfig(TIM16, TIM_OCPreload_Disable);
    
    TIM_ITConfig(TIM16,TIM_IT_Update,ENABLE);
    TIM_ClearFlag(TIM16, TIM_FLAG_Update);
    /* TIM1 counter enable */
    //TIM_Cmd(TIM16, ENABLE);
    /* TIM1 Main Output Enable */
    //TIM_CtrlPWMOutputs(TIM16, ENABLE);
}
//2160=4479;720=1550;545=980;654=1320;630=1250/1178;580=1080;600=1128;610=1146;624=1180/1144;620=1160;622=1168
void TIM16_IRQHandler(void)
{
    if((TIM16->SR & TIM_FLAG_Update) == SET)
    {
        TIM16->SR &= ~TIM_FLAG_Update;

        TIM16->CCR1 = (u2)u2g_d_pwm;//1090;//763;//(u2)u2g_d_pwm;//624;//5464;//(u2)u2g_d_pwm;
    }
}

void R_TAU0_Channel4_Start(void)
{
    if(flag_tim16_en == 0)
    {
        flag_tim16_en = 1;
        Init_Timer16();
        TIM_Cmd(TIM16, ENABLE);
        TIM_CtrlPWMOutputs(TIM16, ENABLE);
    }
}
void R_TAU0_Channel4_Stop(void)
{
    GPIO_InitTypeDef    GPIO_InitStructure;
    if(flag_tim16_en == 1)
    {
        flag_tim16_en = 0;
        TIM16->CNT = 0;
        TIM16->CCR1 = 0;
        TIM_CtrlPWMOutputs(TIM16, DISABLE);
        TIM_Cmd(TIM16, DISABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        P_PWM_OUT_0;
    }
}

//刹车:Fclk = 4MHz,TIM_Period = 36000 D_BREAK_MAX_LEVEL=0x8CA0,T = 9ms(111.1Hz)
//PA7 -> TIM17_CH1
void Init_Timer17(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    /* GPIOA Clocks enable */
    RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//GPIO_PuPd_UP ;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_5);
    
    /* TIM17 clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM17, ENABLE);
    
    /* Enable the TIM17 gloabal Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM17_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = D_BREAK_MAX_LEVEL - 1;  //36000
    TIM_TimeBaseStructure.TIM_Prescaler = 3;   //16MHz/(3+1) = 4MHz.
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM17, &TIM_TimeBaseStructure);
    TIM_ARRPreloadConfig(TIM17,ENABLE);  //开启自动加载值
    
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   //CNT < TIM_Pulse为有效电平
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_Pulse = 0;//18000;  //占空比

    TIM_OC1Init(TIM17, &TIM_OCInitStructure);
    //TIM_OC1PreloadConfig(TIM17, TIM_OCPreload_Disable);
    
    TIM_ITConfig(TIM17,TIM_IT_Update,ENABLE);
    TIM_ClearFlag(TIM17, TIM_FLAG_Update);
    /* TIM1 counter enable */
    //TIM_Cmd(TIM17, ENABLE);
    /* TIM1 Main Output Enable */
    //TIM_CtrlPWMOutputs(TIM17, ENABLE);
}

void TIM17_IRQHandler(void)
{
    if((TIM17->SR & TIM_FLAG_Update) == SET)
    {
        TIM17->SR &= ~TIM_FLAG_Update;    //TIM_ClearITPendingBit
        
        TIM17->CCR1 = (u2)u2g_t_break_duty;
    }
}

void R_TAU0_Channel6_Start(void)
{
    if(flag_tim17_en == 0)
    {
        flag_tim17_en = 1;
        Init_Timer17();
        TIM_Cmd(TIM17, ENABLE);
        TIM_CtrlPWMOutputs(TIM17, ENABLE);
    }
}
void R_TAU0_Channel6_Stop(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    if(flag_tim17_en == 1)
    {
        flag_tim17_en = 0;
        TIM17->CNT = 0;
        TIM17->CCR1 = 0;
        TIM_CtrlPWMOutputs(TIM17, DISABLE);
        TIM_Cmd(TIM17, DISABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//GPIO_PuPd_UP ;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        P_T_BREAK_0;
    }
}



//编码器输入PA3 -> Timer15_CH2
void Init_Timer15(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_ICInitTypeDef  TIM_ICInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_0);
    /* GPIOA Clocks enable */
    RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* TIM15 clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM15, ENABLE);
    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = 65535;//1440;  //2.777KHz
    TIM_TimeBaseStructure.TIM_Prescaler = 31;//16MHz/(31+1) = 0.5MHz.
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //0
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM15, &TIM_TimeBaseStructure);
    
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICFilter = 0x03;    //0011: fSAMPLING = fCK_INT, N = 8
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;   
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;   //IC2 is mapped on TI2
    TIM_ICInit(TIM15,&TIM_ICInitStructure);
        
    NVIC_InitStructure.NVIC_IRQChannel = TIM15_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;        //使能
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_Init(&NVIC_InitStructure);
    
    TIM_ClearITPendingBit(TIM15,TIM_IT_Update | TIM_IT_CC2);    //清理中断标志
    //TIM_ITConfig(TIM15,TIM_IT_Update,ENABLE);   //更新中断
    TIM_ITConfig(TIM15,TIM_IT_CC2,ENABLE);  //捕获中断
    
    TIM_Cmd(TIM15,ENABLE);
}

//RL78/G13
//TImn引脚输入的有效边缘被用作启动触发器和捕获触发器
//两条边(当测量低电平宽度时),启动触发:下降边缘，捕获触发:上升边缘
//计时器中断在计数开始时不产生,(计时器输出也没有改变)
u1 overflow_cnt = 0;
void TIM15_IRQHandler(void)
{    
    if((TIM15->SR & TIM_FLAG_CC2) == TIM_SR_CC2IF)   //捕获标志
    {
        TIM15->SR &= ~TIM_FLAG_CC2;    //TIM_ClearITPendingBit
        if(flag_CaptureStart == 1)
        {   
            g_tau0_ch2_width = TIM15->CCR2 + 65535*overflow_cnt;
            overflow_cnt = 0;
            TIM15->CNT = 0;
            TIM15->CCR2 = 0;
            u4g_plus_length_buffer = g_tau0_ch2_width;
            int_input_encoder();
            //int_input_encoder_test();
            TIM15->SR &= ~TIM_FLAG_Update;   //Clear Flag
        }

        if(flag_CaptureStart == 0 && P_ENCODER_A == 1)
        {
            flag_CaptureStart = 1;
            TIM15->CNT = 0;
            TIM15->CCR2 = 0;
            overflow_cnt = 0;
            TIM15->SR &= ~TIM_FLAG_CC2; 
            TIM15->SR &= ~TIM_FLAG_Update;   //Clear Flag
            TIM_ITConfig(TIM15,TIM_IT_Update,ENABLE);   //更新中断
        }
    }
    else if((TIM15->SR & TIM_FLAG_Update) == TIM_SR_UIF && flag_CaptureStart == 1) //更新中断
    {
        overflow_cnt++;
//        u1a_fg_current_pulse_over_flow = 1;
        if(overflow_cnt >= 5)
        {
            overflow_cnt = 0;
            u1a_fg_current_pulse_over_flow = 0;
            flag_CaptureStart = 0;
            TIM15->SR &= ~TIM_FLAG_CC2;    //TIM_ClearITPendingBit
            TIM15->SR &= ~TIM_FLAG_Update;   //Clear Flag
            TIM_ITConfig(TIM15,TIM_IT_Update,DISABLE);   //关闭更新中断
        }
    }
    TIM15->SR &= ~TIM_FLAG_Update;   //Clear Flag
}
f4 Pwm_val = 0;
f4 T = 0;
u4 rpm_val = 0;
void int_input_encoder_test(void)
{
    if(g_tau0_ch2_width <= 20 && overflow_cnt == 0){}
    else
    {
        if(P_ENCODER_A == 1)    //上升沿捕获的，计数值为低电平时间。
        {
            u4l_Low_Length = g_tau0_ch2_width;
            rpm_val = 7500000 / u4g_Plus_Length;
        }
        else
        {
            u4l_High_Length = g_tau0_ch2_width;
        }
        u4g_Plus_Length = u4l_High_Length + u4l_Low_Length;
        T = ((f4)1/(f4)1000000 * (f4)u4g_Plus_Length * (f4)1000);
        Pwm_val = ((f4)u4l_High_Length / (f4)u4g_Plus_Length);
    }
}
//TIM_IT_Trigger


void int_system_timer(void)
{
/*------------------------ 1msec --------------------------*/
	if( u1g_fg_charge_pump_enable == 1 ){
		P_RELAY_1_1;
	}
	else{
		P_RELAY_1_0;
	}

	//sw_input_check();
	u2g_c_interval_plus++;
		
	if( u1g_pwm_break_timer_counter < 255 ){
		u1g_pwm_break_timer_counter ++;
	}
		if(u2g_systimer_1ms_wait_motion < (u2)U2L_1000_TIME ){
			u2g_systimer_1ms_wait_motion++;
		}
		else{
			u2g_systimer_1ms_wait_motion = U1L_ZERO;
			u2g_systimer_1sec_wait_motion++;
		}		
		if(u2g_systimer_1ms_for_signal < (u2)U2L_1000_TIME ){
			u2g_systimer_1ms_for_signal++;
		}
		else{
			u2g_systimer_1ms_for_signal = U1L_ZERO;
			if(u2g_systimer_1sec_for_signal < (u2)U2L_MAX ){
				u2g_systimer_1sec_for_signal++;
			}
			else{}
		}
			
		if(u2g_systimer_1ms_timer_for_anjou < (u2)U2L_1000_TIME ){
			u2g_systimer_1ms_timer_for_anjou++;
		}
		else{
			u2g_systimer_1ms_timer_for_anjou = U1L_ZERO;
			if(u2g_systimer_1sec_timer_for_anjou < (u2)U2L_MAX ){
				u2g_systimer_1sec_timer_for_anjou++;
			}
			else{}
		}
			
		if((u2g_systimer_1sec_for_signal == U2L_TIME_KAHUKA_LOOSE_SEC)
		   && (u2g_systimer_1ms_for_signal == U2L_TIME_KAHUKA_LOOSE_MS)){
			u1g_timer_kahuka_loose_input = 1;
		}
		else if((u2g_systimer_1sec_for_signal == TIME_2sec)
			&& (u2g_systimer_1ms_for_signal == U1L_ZERO)){
			u1g_timer_2sec_input = 1;
		} 
		else if((u2g_systimer_1sec_for_signal == TIME_5sec)
			&& (u2g_systimer_1ms_for_signal == U1L_ZERO)){
		}
		
		else if((u2g_systimer_1sec_for_signal == TIME_90sec)
			&& (u2g_systimer_1ms_for_signal == U1L_ZERO)){
			u1g_total_timer_input = 1;
			u1g_huka_ad_value = (u1)u2g_ad_now[(CURR - CURR)]/4;
		}
		else{}
	
		u1g_c_no_plus++;
		if( u1g_c_no_plus >= 0xfe )
			{
				u1g_c_no_plus = 0xfd;
			}
		else{}

		u1g_count_timer_1ms++;
		if( u1g_count_timer_1ms >= U1L_100_TIME)
			{
				u1g_count_timer_1ms = U1L_ZERO;
				u1l_count_100ms++;
				Fg_timer_100ms_f = U1L_MAX;
				
				if( u1g_t_break_max_timer_counter < 255 ){
					u1g_t_break_max_timer_counter ++;
				}				
				if(u1l_count_100ms >= U1L_10_TIME)
					{
						u1l_count_100ms = U1L_ZERO;
					}
				else{}
			}
		else{}
			
}

void reset_system_timer(void)
{
		u1g_count_timer_1ms = U1L_ZERO;
		Fg_timer_100ms_f = U1L_ZERO;
}
