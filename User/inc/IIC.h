#ifndef __IIC_H__
#define __IIC_H__

#include "stm32f0xx.h"
#include "Sys.h"
#include "Gpio.h"

//PB8 -> IIC1_SCL; PB9 -> IIC1_SDA
#define SDA_IN()  {GPIOB->MODER &= 0xFFF3FFFF;}
#define SDA_OUT() {GPIOB->MODER &= 0xFFF3FFFF; GPIOB->MODER |= (u4)1 << 18;}

//IO操作函数	 
//#define IIC_SCL    PBout(6) //SCL
//#define IIC_SDA    PBout(7) //SDA	 
//#define READ_SDA   PBin(7)  //输入SDA
#define IIC_SCL_0 GPIOx_OUT(GPIOB,GPIO_Pin_8,0) //{GPIOB->BRR = GPIO_Pin_8;}    //GPIO_ResetBits
#define IIC_SCL_1 GPIOx_OUT(GPIOB,GPIO_Pin_8,1) //{GPIOB->BSRR = GPIO_Pin_8;}   //GPIO_SetBits
#define IIC_SDA_0 GPIOx_OUT(GPIOB,GPIO_Pin_9,0) //GPIO_ResetBits
#define IIC_SDA_1 GPIOx_OUT(GPIOB,GPIO_Pin_9,1) //GPIO_SetBits
#define READ_SDA  GPIOx_IN(GPIOB,GPIO_Pin_9);

//IIC所有操作函数
void Init_IIC_Gpio(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u1 txd);			//IIC发送一个字节
u1 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u1 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号



#endif


