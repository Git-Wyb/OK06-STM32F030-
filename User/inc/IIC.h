#ifndef __IIC_H__
#define __IIC_H__

#include "stm32f0xx.h"
#include "Sys.h"
#include "Gpio.h"

//PB8 -> IIC1_SCL; PB9 -> IIC1_SDA
#define SDA_IN()  {GPIOB->MODER &= 0xFFF3FFFF;}
#define SDA_OUT() {GPIOB->MODER &= 0xFFF3FFFF; GPIOB->MODER |= (u4)1 << 18;}

//IO��������	 
//#define IIC_SCL    PBout(6) //SCL
//#define IIC_SDA    PBout(7) //SDA	 
//#define READ_SDA   PBin(7)  //����SDA
#define IIC_SCL_0 GPIOx_OUT(GPIOB,GPIO_Pin_8,0) //{GPIOB->BRR = GPIO_Pin_8;}    //GPIO_ResetBits
#define IIC_SCL_1 GPIOx_OUT(GPIOB,GPIO_Pin_8,1) //{GPIOB->BSRR = GPIO_Pin_8;}   //GPIO_SetBits
#define IIC_SDA_0 GPIOx_OUT(GPIOB,GPIO_Pin_9,0) //GPIO_ResetBits
#define IIC_SDA_1 GPIOx_OUT(GPIOB,GPIO_Pin_9,1) //GPIO_SetBits
#define READ_SDA  GPIOx_IN(GPIOB,GPIO_Pin_9);

//IIC���в�������
void Init_IIC_Gpio(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u1 txd);			//IIC����һ���ֽ�
u1 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u1 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�



#endif


