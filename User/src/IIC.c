#include "IIC.h"


//PB8 -> IIC1_SCL; PB9 -> IIC1_SDA
void Init_IIC_Gpio(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    //RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE );
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
//    IIC_SCL_0;
//    IIC_SDA_0;
}



//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT();    //sda�����
	IIC_SDA_1;	  	  
	IIC_SCL_1;
	delay_us(4);
 	IIC_SDA_0;  //START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL_0;  //ǯסI2C���ߣ�׼�����ͻ�������� 
}

//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL_0;
	IIC_SDA_0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL_1;
    delay_us(4);    
	IIC_SDA_1;//����I2C���߽����ź�							   	
}

//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u1 IIC_Wait_Ack(void)
{
	u1 ucErrTime = 0,x_sda = 0;
	SDA_IN();      //SDA����Ϊ����  
	IIC_SDA_1; delay_us(1);	   
	IIC_SCL_1; delay_us(1);
    x_sda = READ_SDA;   
	while(x_sda)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
        x_sda = READ_SDA;
	}
	IIC_SCL_0;//ʱ�����0 	   
	return 0;  
} 

//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL_0;
	SDA_OUT();
	IIC_SDA_0;
	delay_us(2);
	IIC_SCL_1;
	delay_us(2);
	IIC_SCL_0;
}
//������ACKӦ��		    
void IIC_NAck(void)
{
	IIC_SCL_0;
	SDA_OUT();
	IIC_SDA_1;
	delay_us(2);
	IIC_SCL_1;
	delay_us(2);
	IIC_SCL_0;
}

//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u1 txd)
{                        
    u1 t;   
	SDA_OUT(); 	    
    IIC_SCL_0;//����ʱ�ӿ�ʼ���ݴ���
    for(t = 0; t < 8; t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd & 0x80) >> 7)
        {
			IIC_SDA_1;
        }
		else
        {
			IIC_SDA_0;
        }
		txd <<= 1; 	  
		delay_us(2);  
		IIC_SCL_1;
		delay_us(2); 
		IIC_SCL_0;	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u1 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0,x_sda = 0;
	SDA_IN();//SDA����Ϊ����
    for(i = 0; i < 8; i++ )
	{
        IIC_SCL_0; 
        delay_us(2);
		IIC_SCL_1;
        receive <<= 1;
        x_sda = READ_SDA;
        if(x_sda) receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}
