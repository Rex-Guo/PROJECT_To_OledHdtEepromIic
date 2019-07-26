#include "iic24.h"

/*
	PB8		--->IIC_SCL
	PB9		--->IIC_SDA
*/

/*
 * ��  �ܣ�IIC��ʼ��  
 * ��  ������
 * ����ֵ����
 */
void IIC24_Init(void)
{
	//����ṹ�����
	GPIO_InitTypeDef  GPIO_InitStruct24;
	
	//1������ GPIOB ʱ��		
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	//2������ GPIO
	GPIO_InitStruct24.GPIO_Mode  =GPIO_Mode_OUT;    	//���ģʽ
	GPIO_InitStruct24.GPIO_OType = GPIO_OType_PP;   	//����
	GPIO_InitStruct24.GPIO_PuPd  = GPIO_PuPd_UP;    	//����
	GPIO_InitStruct24.GPIO_Speed = GPIO_Speed_100MHz; 	//����ٶ�
	GPIO_InitStruct24.GPIO_Pin   = GPIO_Pin_9|GPIO_Pin_8;      	//�� 9 8 ������
	GPIO_Init(GPIOB, &GPIO_InitStruct24);

	//��ʼ�ߵ�ƽ
	GPIO_SetBits(GPIOB,GPIO_Pin_9|GPIO_Pin_8);																	
}

/*
 * ��  �ܣ�IIC_SDA���ģʽ  
 * ��  ������
 * ����ֵ����
 */
void IIC24_SDAModeOut(void)
{
	//����ṹ�����
	GPIO_InitTypeDef  GPIO_InitStruct24;
	
	//1������ GPIOB ʱ��		
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	//2������ GPIO
	GPIO_InitStruct24.GPIO_Mode  =GPIO_Mode_OUT;    	//���ģʽ
	GPIO_InitStruct24.GPIO_OType = GPIO_OType_PP;   	//����
	GPIO_InitStruct24.GPIO_PuPd  = GPIO_PuPd_UP;    	//����
	GPIO_InitStruct24.GPIO_Speed = GPIO_Speed_100MHz; 	//����ٶ�
	GPIO_InitStruct24.GPIO_Pin   = GPIO_Pin_9;      	//�� 9 ������
	GPIO_Init(GPIOB, &GPIO_InitStruct24);																
}

/*
 * ��  �ܣ�IIC_SDA����ģʽ  
 * ��  ������
 * ����ֵ����
 */
void IIC24_SDAModeIn(void)
{
	//����ṹ�����
	GPIO_InitTypeDef  GPIO_InitStruct24;
	
	//1������ GPIOB ʱ��		
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	//2������ GPIO
	GPIO_InitStruct24.GPIO_Mode  =GPIO_Mode_IN;    	//����ģʽ
	GPIO_InitStruct24.GPIO_PuPd  = GPIO_PuPd_UP;    	//����
	GPIO_InitStruct24.GPIO_Pin   = GPIO_Pin_9;      	//�� 9 ������
	GPIO_Init(GPIOB, &GPIO_InitStruct24);																
}

/*
 * ��  �ܣ�IIC��ʼ�źź���  ---���� SCL Ϊ�ߵ�ƽʱ��SDA �ɸ߱��
 * ��  ������
 * ����ֵ����
 */
void IIC24_Start(void)
{
	//1������ SDA Ϊ���ģʽ
	IIC24_SDAModeOut();
	
	IIC24_SDA_OUT(1);
	IIC24_SCL_OUT(1); 
	delay_us(5);
	
	IIC24_SDA_OUT(0);
	delay_us(5);
	
	IIC24_SCL_OUT(0); 
}

/*
 * ��  �ܣ�IICֹͣ�źź���   ---���� SCL Ϊ�ߵ�ƽʱ��SDA �ɵͱ��
 * ��  ������
 * ����ֵ����
 */
void IIC24_Stop(void)	
{
	//1������ SDA Ϊ���ģʽ
	IIC24_SDAModeOut();
	
	IIC24_SDA_OUT(0);
	IIC24_SCL_OUT(0); 
	delay_us(5);
	
	IIC24_SCL_OUT(1);  //ִ����һ�е�ʱ�� SDA �ǵ͵�ƽ
	delay_us(5);
	
	IIC24_SDA_OUT(1);
}

/*
 * ��  �ܣ�IICдһ���ֽں���  --->STM32 д�� 24C02
 * ��  ����
 * 		data	---����Ҫд���һ���ֽ�����
 * ����ֵ����
 */
void IIC24_WriteByte(uint8_t data)	 //01101011
{
	uint8_t i;
	
	//1������ SDA Ϊ���ģʽ
	IIC24_SDAModeOut();
	
	IIC24_SCL_OUT(0); 	//���߶Է���Ҫȥʶ�� SDA �ĵ�ƽ
	delay_us(5);
	
	for(i=0;i<8;i++)	//ѭ�� 8�� ÿ�δ���һλ ,��λ�ȳ�
	{
		//׼������
		if(data & (0x1<<(7-i)))	
		{
			IIC24_SDA_OUT(1);
		}else{
			IIC24_SDA_OUT(0);
		}
		
		IIC24_SCL_OUT(1); 	//���߶Է�Ҫȥʶ�� SDA �ĵ�ƽ
		delay_us(5);
		
		IIC24_SCL_OUT(0); 	//���߶Է���Ҫȥʶ�� SDA �ĵ�ƽ
		
	}
}

/*
 * ��  �ܣ�IIC��һ���ֽں���  --->24C02 д�� STM32 
 * ��  ������
 * ����ֵ���ɹ���ȡ��һ���ֽ�����
 */
uint8_t IIC24_ReadByte(void)	 //01101011
{
	uint8_t i;
	uint8_t data = 0;
	
	//1������ SDA Ϊ����ģʽ
	IIC24_SDAModeIn();
	
	IIC24_SCL_OUT(0); 	//��ǰstm32��ʶ��SDA��ƽ ���Է����ڿ�ʼ׼������
	delay_us(5);
	
	for(i=0;i<8;i++)	//ѭ�� 8�� ÿ�δ���һλ ,��λ�ȳ�
	{
		IIC24_SCL_OUT(1); 	//��ǰstm32��ʼʶ��SDA��ƽ ���Է�������׼������
		delay_us(5);
		
		if( IIC24_SDA_IN() )
		{
			data |= (0x1<<(7-i));
		}else{
			data &= ~(0x1<<(7-i));
		}
		
		IIC24_SCL_OUT(0); 	//��ǰstm32��ʶ��SDA��ƽ ���Է����ڿ�ʼ׼������
		delay_us(5);      
	}	
	
	return data;
}


/*
 * ��  �ܣ�IICӦ����  --->24C02 д�� STM32 ���ݣ�STM32 �� 24c02 һ���ظ�
 * ��  ������
 * ����ֵ���ɹ���ȡ��һ���ֽ�����
 */
void IIC24_Ack(uint8_t ack)
{
	//1������ SDA Ϊ���ģʽ
	IIC24_SDAModeOut();
	
	IIC24_SCL_OUT(0); 	//���߶Է���Ҫȥʶ�� SDA �ĵ�ƽ
	delay_us(5);
	
	if(ack)
	{
		IIC24_SDA_OUT(1);
	}else{
		IIC24_SDA_OUT(0);  
	}
	
	IIC24_SCL_OUT(1); 	//���߶Է�Ҫȥʶ�� SDA �ĵ�ƽ 
	delay_us(5);
	
	IIC24_SCL_OUT(0); 
}

/*
 * ��  �ܣ�IIC�ȴ�Ӧ����  ---> STM32 д�� 24C02 ���ݣ�24C02��STM32һ���ظ�
 * ��  ������
 * ����ֵ���ɹ��õ��Ļظ� 
 * 		1	--->��Ӧ��
 * 		0	--->Ӧ��
 */
uint8_t IIC24_WaitAck(void)
{
	uint8_t ack;
	
	//1������ SDA Ϊ����ģʽ
	IIC24_SDAModeIn();
	
	IIC24_SCL_OUT(0); 	//��ǰstm32��ʶ��SDA��ƽ ���Է����ڿ�ʼ׼���ظ��ź�
	delay_us(5);
	
	IIC24_SCL_OUT(1); 	//��ǰstm32��ʼʶ��SDA��ƽ
	delay_us(5);
	
	if( IIC24_SDA_IN() )
	{
		ack = 1;
	}else{
		ack = 0;
	}
	
	IIC24_SCL_OUT(0);
	
	return ack;
}






