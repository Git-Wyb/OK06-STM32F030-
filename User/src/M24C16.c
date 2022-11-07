#include "M24C16.h"


//��ʼ��IIC�ӿ�
void Init_M24C16(void)
{
    Init_IIC_Gpio();
}


//��ָ����ַ����һ������
//ReadAddr:��ʼ�����ĵ�ַ  
//����ֵ  :����������
u1 M24C16_ReadOneByte(u2 ReadAddr)
{				  
	u1 temp=0;		  	    																 
    IIC_Start();  
	IIC_Send_Byte(0xA0 + ((ReadAddr/256) << 1));   //����������ַ0XA0,д���� 	 
	IIC_Wait_Ack(); 
    IIC_Send_Byte(ReadAddr % 256);   //���͵͵�ַ
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_Send_Byte(0XA1);           //�������ģʽ			   
	IIC_Wait_Ack();	 
    temp=IIC_Read_Byte(0);		   
    IIC_Stop();//����һ��ֹͣ����	    
	return temp;
}


//��ָ����ַд��һ������
//WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ    
//DataToWrite:Ҫд�������
void M24C16_WriteOneByte(u2 WriteAddr,u1 DataToWrite)
{				   	  	    																 
    IIC_Start();  
	IIC_Send_Byte(0XA0 + ((WriteAddr/256) << 1));   //����������ַ0XA0,д���� 
	IIC_Wait_Ack();	   
    IIC_Send_Byte(WriteAddr % 256);   //���͵͵�ַ
	IIC_Wait_Ack(); 	 										  		   
	IIC_Send_Byte(DataToWrite);     //�����ֽ�							   
	IIC_Wait_Ack();  		    	   
    IIC_Stop();//����һ��ֹͣ���� 
	delay_ms(10);	 
}


//ָ����ַ��ʼд�볤��ΪLen������
//�ú�������д��16bit����32bit������.
//WriteAddr  :��ʼд��ĵ�ַ  
//DataToWrite:���������׵�ַ
//Len        :Ҫд�����ݵĳ���2,4
void AT24CXX_WriteLenByte(u2 WriteAddr,u4 DataToWrite,u1 Len)
{  	
	u1 t;
	for(t=0;t<Len;t++)
	{
		M24C16_WriteOneByte(WriteAddr+t,(DataToWrite >> (8*t)) & 0xff);
	}												    
}

//ָ����ַ��ʼ��������ΪLen������
//�ú������ڶ���16bit����32bit������.
//ReadAddr   :��ʼ�����ĵ�ַ 
//����ֵ     :����
//Len        :Ҫ�������ݵĳ���2,4
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


//ָ����ַ��ʼ����ָ������������
//ReadAddr :��ʼ�����ĵ�ַ
//pBuffer  :���������׵�ַ
//NumToRead:Ҫ�������ݵĸ���
void M24C16_Read(u2 ReadAddr,u1 *pBuffer,u2 NumToRead) //read 1byte 0.8ms,80byte 64ms;
{
	while(NumToRead)
	{
		*pBuffer++ = M24C16_ReadOneByte(ReadAddr++);	
		NumToRead--;
        R_WDT_Restart();
	}
}


//ָ����ַ��ʼд��ָ������������
//WriteAddr :��ʼд��ĵ�ַ
//pBuffer   :���������׵�ַ
//NumToWrite:Ҫд�����ݵĸ���
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


