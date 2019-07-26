#ifndef _IIC_H
#define _IIC_H 			    

//ͷ�ļ�
#include "stm32f4xx.h"
#include "uart.h"
#include "systick.h"

#define IIC_SDA_OUT(a);		if(a) \
								GPIO_SetBits(GPIOE,GPIO_Pin_15); \
							else \
								GPIO_ResetBits(GPIOE,GPIO_Pin_15);

#define IIC_SCL_OUT(a);		if(a) \
								GPIO_SetBits(GPIOD,GPIO_Pin_9); \
							else \
								GPIO_ResetBits(GPIOD,GPIO_Pin_9);
							
#define IIC_SDA_IN()		GPIO_ReadInputDataBit(GPIOE ,GPIO_Pin_15)		
							
							
//��������
/*
 * ��  �ܣ�IIC��ʼ��  
 * ��  ������
 * ����ֵ����
 */
void IIC_Init(void);
							
/*
 * ��  �ܣ�IIC��ʼ�źź���  ---���� SCL Ϊ�ߵ�ƽʱ��SDA �ɸ߱��
 * ��  ������
 * ����ֵ����
 */
void IIC_Start(void);
							
/*
 * ��  �ܣ�IICֹͣ�źź���   ---���� SCL Ϊ�ߵ�ƽʱ��SDA �ɵͱ��
 * ��  ������
 * ����ֵ����
 */
void IIC_Stop(void);

/*
 * ��  �ܣ�IICдһ���ֽں���  --->STM32 д�� 24C02
 * ��  ����
 * 		data	---����Ҫд���һ���ֽ�����
 * ����ֵ����
 */
void IIC_WriteByte(uint8_t data);

/*
 * ��  �ܣ�IIC��һ���ֽں���  --->24C02 д�� STM32 
 * ��  ������
 * ����ֵ���ɹ���ȡ��һ���ֽ�����
 */
uint8_t IIC_ReadByte(void);

/*
 * ��  �ܣ�IICӦ����  --->24C02 д�� STM32 ���ݣ�STM32 �� 24c02 һ���ظ�
 * ��  ������
 * ����ֵ���ɹ���ȡ��һ���ֽ�����
 */
void IIC_Ack(uint8_t ack);

/*
 * ��  �ܣ�IIC�ȴ�Ӧ����  ---> STM32 д�� 24C02 ���ݣ�24C02��STM32һ���ظ�
 * ��  ������
 * ����ֵ���ɹ��õ��Ļظ� 
 * 		1	--->��Ӧ��
 * 		0	--->Ӧ��
 */
uint8_t IIC_WaitAck(void);





#endif
