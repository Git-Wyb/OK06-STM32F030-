#include "M24C16.h"


//初始化IIC接口
void Init_M24C16(void)
{
    Init_IIC_Gpio();
}


//在指定地址读出一个数据
//ReadAddr:开始读数的地址  
//返回值  :读到的数据
u1 M24C16_ReadOneByte(u2 ReadAddr)
{				  
	u1 temp=0;		  	    																 
    IIC_Start();  
	IIC_Send_Byte(0xA0 + ((ReadAddr/256) << 1));   //发送器件地址0XA0,写数据 	 
	IIC_Wait_Ack(); 
    IIC_Send_Byte(ReadAddr % 256);   //发送低地址
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_Send_Byte(0XA1);           //进入接收模式			   
	IIC_Wait_Ack();	 
    temp=IIC_Read_Byte(0);		   
    IIC_Stop();//产生一个停止条件	    
	return temp;
}


//在指定地址写入一个数据
//WriteAddr  :写入数据的目的地址    
//DataToWrite:要写入的数据
void M24C16_WriteOneByte(u2 WriteAddr,u1 DataToWrite)
{				   	  	    																 
    IIC_Start();  
	IIC_Send_Byte(0XA0 + ((WriteAddr/256) << 1));   //发送器件地址0XA0,写数据 
	IIC_Wait_Ack();	   
    IIC_Send_Byte(WriteAddr % 256);   //发送低地址
	IIC_Wait_Ack(); 	 										  		   
	IIC_Send_Byte(DataToWrite);     //发送字节							   
	IIC_Wait_Ack();  		    	   
    IIC_Stop();//产生一个停止条件 
	delay_ms(10);	 
}


//指定地址开始写入长度为Len的数据
//该函数用于写入16bit或者32bit的数据.
//WriteAddr  :开始写入的地址  
//DataToWrite:数据数组首地址
//Len        :要写入数据的长度2,4
void AT24CXX_WriteLenByte(u2 WriteAddr,u4 DataToWrite,u1 Len)
{  	
	u1 t;
	for(t=0;t<Len;t++)
	{
		M24C16_WriteOneByte(WriteAddr+t,(DataToWrite >> (8*t)) & 0xff);
	}												    
}

//指定地址开始读出长度为Len的数据
//该函数用于读出16bit或者32bit的数据.
//ReadAddr   :开始读出的地址 
//返回值     :数据
//Len        :要读出数据的长度2,4
u4 M24C16_ReadLenByte(u2 ReadAddr,u1 Len)
{  	
	u1 t;
	u4 temp = 0;
	for(t=0;t<Len;t++)
	{
		temp <<= 8;
		temp += M24C16_ReadOneByte(ReadAddr + Len - t - 1); 	 				   
	}
	return temp;												    
}


//指定地址开始读出指定个数的数据
//ReadAddr :开始读出的地址
//pBuffer  :数据数组首地址
//NumToRead:要读出数据的个数
void M24C16_Read(u2 ReadAddr,u1 *pBuffer,u2 NumToRead) //read 1byte 0.8ms,80byte 64ms;
{
	while(NumToRead)
	{
		*pBuffer++ = M24C16_ReadOneByte(ReadAddr++);	
		NumToRead--;
        R_WDT_Restart();
	}
}


//指定地址开始写入指定个数的数据
//WriteAddr :开始写入的地址
//pBuffer   :数据数组首地址
//NumToWrite:要写入数据的个数
void M24C16_Write(u2 WriteAddr,u1 *pBuffer,u2 NumToWrite) //write 1byte 10.4ms,80byte 852ms;
{
	while(NumToWrite--)
	{
		M24C16_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
        R_WDT_Restart();
	}
}


