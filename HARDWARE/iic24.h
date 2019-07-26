#ifndef _IIC24_H
#define _IIC24_H 			    

//ͷ�ļ�
#include "stm32f4xx.h"
#include "uart.h"
#include "systick.h"

#define IIC24_SDA_OUT(a);		if(a) \
								GPIO_SetBits(GPIOB,GPIO_Pin_9); \
							else \
								GPIO_ResetBits(GPIOB,GPIO_Pin_9);

#define IIC24_SCL_OUT(a);		if(a) \
								GPIO_SetBits(GPIOB,GPIO_Pin_8); \
							else \
								GPIO_ResetBits(GPIOB,GPIO_Pin_8);
							
#define IIC24_SDA_IN()		GPIO_ReadInputDataBit(GPIOB ,GPIO_Pin_9)							
							
//��������
/*
 * ��  �ܣ�IIC��ʼ��  
 * ��  ������
 * ����ֵ����
 */
void IIC24_Init(void);
							
/*
 * ��  �ܣ�IIC��ʼ�źź���  ---���� SCL Ϊ�ߵ�ƽʱ��SDA �ɸ߱��
 * ��  ������
 * ����ֵ����
 */
void IIC24_Start(void);
							
/*
 * ��  �ܣ�IICֹͣ�źź���   ---���� SCL Ϊ�ߵ�ƽʱ��SDA �ɵͱ��
 * ��  ������
 * ����ֵ����
 */
void IIC24_Stop(void);

/*
 * ��  �ܣ�IICдһ���ֽں���  --->STM32 д�� 24C02
 * ��  ����
 * 		data	---����Ҫд���һ���ֽ�����
 * ����ֵ����
 */
void IIC24_WriteByte(uint8_t data);

/*
 * ��  �ܣ�IIC��һ���ֽں���  --->24C02 д�� STM32 
 * ��  ������
 * ����ֵ���ɹ���ȡ��һ���ֽ�����
 */
uint8_t IIC24_ReadByte(void);

/*
 * ��  �ܣ�IICӦ����  --->24C02 д�� STM32 ���ݣ�STM32 �� 24c02 һ���ظ�
 * ��  ������
 * ����ֵ���ɹ���ȡ��һ���ֽ�����
 */
void IIC24_Ack(uint8_t ack);

/*
 * ��  �ܣ�IIC�ȴ�Ӧ����  ---> STM32 д�� 24C02 ���ݣ�24C02��STM32һ���ظ�
 * ��  ������
 * ����ֵ���ɹ��õ��Ļظ� 
 * 		1	--->��Ӧ��
 * 		0	--->Ӧ��
 */
uint8_t IIC24_WaitAck(void);





#endif
