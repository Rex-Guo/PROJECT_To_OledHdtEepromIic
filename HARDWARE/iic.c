#include "iic.h"

/*
	��˵��д����
	PD9		--->IIC_SCL
	PE15	--->IIC_SDA
*/

GPIO_InitTypeDef GPIO_InitStruct;

/*
 * ��  �ܣ�IIC��ʼ��  
 * ��  ������
 * ����ֵ����
 */
void IIC_Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode		=	GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType	=	GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Pin		=	GPIO_Pin_9;
	GPIO_InitStruct.GPIO_PuPd		= GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed	=	GPIO_Speed_25MHz;
	GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin		=	GPIO_Pin_15;
	GPIO_Init(GPIOE, &GPIO_InitStruct);
	
	//��ʼ�ߵ�ƽ
	GPIO_SetBits(GPIOD,GPIO_Pin_9);	
	GPIO_SetBits(GPIOE,GPIO_Pin_15);
}

/*
 * ��  �ܣ�IIC_SDA���ģʽ  
 * ��  ������
 * ����ֵ����
 */
void IIC_SDAModeOut(void)
{
	GPIO_InitStruct.GPIO_Mode		=	GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin		=	GPIO_Pin_15;
	GPIO_Init(GPIOE, &GPIO_InitStruct);
}

/*
 * ��  �ܣ�IIC_SDA����ģʽ  
 * ��  ������
 * ����ֵ����
 */
void IIC_SDAModeIn(void)
{
	GPIO_InitStruct.GPIO_Mode		=	GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Pin		=	GPIO_Pin_15;
	GPIO_Init(GPIOE, &GPIO_InitStruct);
}

/*
 * ��  �ܣ�IIC��ʼ�źź���  ---���� SCL Ϊ�ߵ�ƽʱ��SDA �ɸ߱��
 * ��  ������
 * ����ֵ����
 */
void IIC_Start(void)
{
	IIC_SDAModeOut();
	
	IIC_SDA_OUT(1);
	IIC_SCL_OUT(1);
	delay_us(5);
	
	IIC_SDA_OUT(0);
	delay_us(5);
	IIC_SCL_OUT(0);
}

/*
 * ��  �ܣ�IICֹͣ�źź���   ---���� SCL Ϊ�ߵ�ƽʱ��SDA �ɵͱ��
 * ��  ������
 * ����ֵ����
 */
void IIC_Stop(void)	
{
	IIC_SDAModeOut();
	
	IIC_SDA_OUT(0);
	IIC_SCL_OUT(0);
	delay_us(5);
	
	IIC_SCL_OUT(1);
	delay_us(5);
	
	IIC_SDA_OUT(1);
}

/*
 * ��  �ܣ�IICдһ���ֽں���  --->STM32 д�� 24C02
 * ��  ����
 * 		data	---����Ҫд���һ���ֽ�����
 * ����ֵ����
 */
void IIC_WriteByte(uint8_t data)	 //01101011
{
	int i = 0;
	
	IIC_SDAModeOut();
	IIC_SCL_OUT(0);
	delay_us(5);
	
	for(; i < 8; i++){
		
		if(data & (0x1 << (7-i))){
			IIC_SDA_OUT(1);
		}else{
			IIC_SDA_OUT(0);
		}
		
		IIC_SCL_OUT(1);
		delay_us(5);
		
		IIC_SCL_OUT(0);
		delay_us(5);
		
	}
}

/*
 * ��  �ܣ�IIC��һ���ֽں���  --->24C02 д�� STM32 
 * ��  ������
 * ����ֵ���ɹ���ȡ��һ���ֽ�����
 */
uint8_t IIC_ReadByte(void)	 //01101011
{
	uint8_t data;
	int i = 0;
	IIC_SDAModeIn();
	
	IIC_SCL_OUT(0);
	delay_us(5);
	
	for(; i < 8; i++){
		IIC_SCL_OUT(1);
		delay_us(5);
		
		if(IIC_SDA_IN()){
			data |= (0x1 << (7-i));
		}else{
			data &= ~(0x1 << (7-i));
		}
		IIC_SCL_OUT(0);
		delay_us(5);
	}
	
	return data;
}


/*
 * ��  �ܣ�IICӦ����  --->24C02 д�� STM32 ���ݣ�STM32 �� 24c02 һ���ظ�
 * ��  ������
 * ����ֵ���ɹ���ȡ��һ���ֽ�����
 */
void IIC_Ack(uint8_t ack)
{
	IIC_SDAModeOut();
	
	IIC_SCL_OUT(0);
	delay_us(5);
	
	if(ack){
		IIC_SDA_OUT(1);		
	}else{
		IIC_SDA_OUT(0);
	}
	
	IIC_SCL_OUT(1);
	delay_us(5);
	
	IIC_SCL_OUT(0);
}

/*
 * ��  �ܣ�IIC�ȴ�Ӧ����  ---> STM32 д�� 24C02 ���ݣ�24C02��STM32һ���ظ�
 * ��  ������
 * ����ֵ���ɹ��õ��Ļظ� 
 * 		1	--->��Ӧ��
 * 		0	--->Ӧ��
 */
uint8_t IIC_WaitAck(void)
{
	uint8_t i = 0;
	IIC_SDAModeIn();
	
	IIC_SCL_OUT(0);
	delay_us(5);
	
	IIC_SCL_OUT(1);
	delay_us(5);
	
	if(IIC_SDA_IN()){
		i = 1;
	}else{
		i = 0;
	}
	
	IIC_SCL_OUT(0);
	
	return i;
}
	























///*
// * ��  �ܣ�IIC��ʼ��  
// * ��  ������
// * ����ֵ����
// */
//void IIC_Init(void)
//{
//	//����ṹ�����
//	GPIO_InitTypeDef  GPIO_InitStruct;
//	
//	//1������ GPIOB ʱ��		
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

//	//2������ GPIO
//	GPIO_InitStruct.GPIO_Mode  =GPIO_Mode_OUT;    	//���ģʽ
//	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;   	//����
//	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;    	//����
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz; 	//����ٶ�
//	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_9|GPIO_Pin_8;      	//�� 9 8 ������
//	GPIO_Init(GPIOB, &GPIO_InitStruct);

//	//��ʼ�ߵ�ƽ
//	GPIO_SetBits(GPIOB,GPIO_Pin_9|GPIO_Pin_8);																	
//}

///*
// * ��  �ܣ�IIC_SDA���ģʽ  
// * ��  ������
// * ����ֵ����
// */
//void IIC_SDAModeOut(void)
//{
//	//����ṹ�����
//	GPIO_InitTypeDef  GPIO_InitStruct;
//	
//	//1������ GPIOB ʱ��		
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

//	//2������ GPIO
//	GPIO_InitStruct.GPIO_Mode  =GPIO_Mode_OUT;    	//���ģʽ
//	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;   	//����
//	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;    	//����
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz; 	//����ٶ�
//	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_9;      	//�� 9 ������
//	GPIO_Init(GPIOB, &GPIO_InitStruct);																
//}

///*
// * ��  �ܣ�IIC_SDA����ģʽ  
// * ��  ������
// * ����ֵ����
// */
//void IIC_SDAModeIn(void)
//{
//	//����ṹ�����
//	GPIO_InitTypeDef  GPIO_InitStruct;
//	
//	//1������ GPIOB ʱ��		
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

//	//2������ GPIO
//	GPIO_InitStruct.GPIO_Mode  =GPIO_Mode_IN;    	//����ģʽ
//	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;    	//����
//	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_9;      	//�� 9 ������
//	GPIO_Init(GPIOB, &GPIO_InitStruct);																
//}

///*
// * ��  �ܣ�IIC��ʼ�źź���  ---���� SCL Ϊ�ߵ�ƽʱ��SDA �ɸ߱��
// * ��  ������
// * ����ֵ����
// */
//void IIC_Start(void)
//{
//	//1������ SDA Ϊ���ģʽ
//	IIC_SDAModeOut();
//	
//	IIC_SDA_OUT(1);
//	IIC_SCL_OUT(1); 
//	delay_us(5);
//	
//	IIC_SDA_OUT(0);
//	delay_us(5);
//	
//	IIC_SCL_OUT(0); 
//}

///*
// * ��  �ܣ�IICֹͣ�źź���   ---���� SCL Ϊ�ߵ�ƽʱ��SDA �ɵͱ��
// * ��  ������
// * ����ֵ����
// */
//void IIC_Stop(void)	
//{
//	//1������ SDA Ϊ���ģʽ
//	IIC_SDAModeOut();
//	
//	IIC_SDA_OUT(0);
//	IIC_SCL_OUT(0); 
//	delay_us(5);
//	
//	IIC_SCL_OUT(1);  //ִ����һ�е�ʱ�� SDA �ǵ͵�ƽ
//	delay_us(5);
//	
//	IIC_SDA_OUT(1);
//}

///*
// * ��  �ܣ�IICдһ���ֽں���  --->STM32 д�� 24C02
// * ��  ����
// * 		data	---����Ҫд���һ���ֽ�����
// * ����ֵ����
// */
//void IIC_WriteByte(uint8_t data)	 //01101011
//{
//	uint8_t i;
//	
//	//1������ SDA Ϊ���ģʽ
//	IIC_SDAModeOut();
//	
//	IIC_SCL_OUT(0); 	//���߶Է���Ҫȥʶ�� SDA �ĵ�ƽ
//	delay_us(5);
//	
//	for(i=0;i<8;i++)	//ѭ�� 8�� ÿ�δ���һλ ,��λ�ȳ�
//	{
//		//׼������
//		if(data & (0x1<<(7-i)))	
//		{
//			IIC_SDA_OUT(1);
//		}else{
//			IIC_SDA_OUT(0);
//		}
//		
//		IIC_SCL_OUT(1); 	//���߶Է�Ҫȥʶ�� SDA �ĵ�ƽ
//		delay_us(5);
//		
//		IIC_SCL_OUT(0); 	//���߶Է���Ҫȥʶ�� SDA �ĵ�ƽ
//		
//	}
//}

///*
// * ��  �ܣ�IIC��һ���ֽں���  --->24C02 д�� STM32 
// * ��  ������
// * ����ֵ���ɹ���ȡ��һ���ֽ�����
// */
//uint8_t IIC_ReadByte(void)	 //01101011
//{
//	uint8_t i;
//	uint8_t data = 0;
//	
//	//1������ SDA Ϊ����ģʽ
//	IIC_SDAModeIn();
//	
//	IIC_SCL_OUT(0); 	//��ǰstm32��ʶ��SDA��ƽ ���Է����ڿ�ʼ׼������
//	delay_us(5);
//	
//	for(i=0;i<8;i++)	//ѭ�� 8�� ÿ�δ���һλ ,��λ�ȳ�
//	{
//		IIC_SCL_OUT(1); 	//��ǰstm32��ʼʶ��SDA��ƽ ���Է�������׼������
//		delay_us(5);
//		
//		if( IIC_SDA_IN() )
//		{
//			data |= (0x1<<(7-i));
//		}else{
//			data &= ~(0x1<<(7-i));
//		}
//		
//		IIC_SCL_OUT(0); 	//��ǰstm32��ʶ��SDA��ƽ ���Է����ڿ�ʼ׼������
//		delay_us(5);      
//	}	
//	
//	return data;
//}


///*
// * ��  �ܣ�IICӦ����  --->24C02 д�� STM32 ���ݣ�STM32 �� 24c02 һ���ظ�
// * ��  ������
// * ����ֵ���ɹ���ȡ��һ���ֽ�����
// */
//void IIC_Ack(uint8_t ack)
//{
//	//1������ SDA Ϊ���ģʽ
//	IIC_SDAModeOut();
//	
//	IIC_SCL_OUT(0); 	//���߶Է���Ҫȥʶ�� SDA �ĵ�ƽ
//	delay_us(5);
//	
//	if(ack)
//	{
//		IIC_SDA_OUT(1);
//	}else{
//		IIC_SDA_OUT(0);  
//	}
//	
//	IIC_SCL_OUT(1); 	//���߶Է�Ҫȥʶ�� SDA �ĵ�ƽ 
//	delay_us(5);
//	
//	IIC_SCL_OUT(0); 
//}

///*
// * ��  �ܣ�IIC�ȴ�Ӧ����  ---> STM32 д�� 24C02 ���ݣ�24C02��STM32һ���ظ�
// * ��  ������
// * ����ֵ���ɹ��õ��Ļظ� 
// * 		1	--->��Ӧ��
// * 		0	--->Ӧ��
// */
//uint8_t IIC_WaitAck(void)
//{
//	uint8_t ack;
//	
//	//1������ SDA Ϊ����ģʽ
//	IIC_SDAModeIn();
//	
//	IIC_SCL_OUT(0); 	//��ǰstm32��ʶ��SDA��ƽ ���Է����ڿ�ʼ׼���ظ��ź�
//	delay_us(5);
//	
//	IIC_SCL_OUT(1); 	//��ǰstm32��ʼʶ��SDA��ƽ
//	delay_us(5);
//	
//	if( IIC_SDA_IN() )
//	{
//		ack = 1;
//	}else{
//		ack = 0;
//	}
//	
//	IIC_SCL_OUT(0);
//	
//	return ack;
//}






