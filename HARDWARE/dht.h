#ifndef _DHT_H_
#define _DHT_H_

/************************* ͷ�ļ� **************************/
#include "stm32f4xx.h"

/************************ �������� *************************/

/************************* �궨�� **************************/
#define DHT11_OUT()	GPIO_InitStruct1.GPIO_Mode		= GPIO_Mode_OUT;\
										GPIO_Init(GPIOG, &GPIO_InitStruct1);

#define DHT11_IN()	GPIO_InitStruct1.GPIO_Mode		= GPIO_Mode_IN;\
										GPIO_Init(GPIOG, &GPIO_InitStruct1);
										
#define SetGPIO(a) a?GPIO_SetBits(GPIOG, GPIO_Pin_9):GPIO_ResetBits(GPIOG, GPIO_Pin_9)

/************************ �������� *************************/
 /*
  * ��  �ܣ�DHT��ʼ��
  * ��  ����void
  * ����ֵ��void
  *
 */
void DHT11_Init(void);

 /*
  * ��  �ܣ���DHT11������
  * ��  ����char *c
  * ����ֵ��int		 0	�ɹ�
	*								-1	ʧ��,��Ӧ��ʱ
	*								-2	ʧ��,�������ݳ���
	*								-3	ʧ��,�������
  *
 */
int Read_DHT11(char *c);

int Read_Data(char *c);

#endif
