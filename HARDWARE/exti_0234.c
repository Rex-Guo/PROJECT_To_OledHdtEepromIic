#include "exti_0234.h"
#include "Key.h"

volatile int light = 0;
volatile int Count_Pro = 0;
extern volatile int Temperature_Standard;	//�¶ȱȽ�ֵ
extern volatile int Humidity_Standard; 		//ʪ�ȱȽ�ֵ
extern void delay_us(u32);
extern void delay_ms(u32);
extern int printf(const char*,...);

void Exti_Init()
{
	EXTI_InitTypeDef	EXTI_InitStruct;
	NVIC_InitTypeDef	NVIC_InitStruct;
	
	//��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	//��ʼ������
	Init_Key();
	
	//ѡ���ж϶˿�EXTI0,EXTI2,EXTI3,EXTI4
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);
	
	//EXTI0,EXTI2,EXTI3,EXTI4�ж�ģʽ�봥����ʽ
	EXTI_InitStruct.EXTI_Line			= EXTI_Line0;
	EXTI_InitStruct.EXTI_LineCmd	= ENABLE;
	EXTI_InitStruct.EXTI_Mode			= EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger	= EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct);
	
	EXTI_InitStruct.EXTI_Line			= EXTI_Line2;
	EXTI_Init(&EXTI_InitStruct);
	
	EXTI_InitStruct.EXTI_Line			= EXTI_Line3;
	EXTI_Init(&EXTI_InitStruct);
	
	EXTI_InitStruct.EXTI_Line			= EXTI_Line4;
	EXTI_Init(&EXTI_InitStruct);
	
	//EXTI0,EXTI2,EXTI3,EXTI4���ж����������ȼ�
	NVIC_InitStruct.NVIC_IRQChannel										= EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd								= ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority	= 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority				= 1;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority	= 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority				= 2;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority	= 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority				= 3;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority	= 3;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority				= 4;
	NVIC_Init(&NVIC_InitStruct);
	
}

 /*
  * ��  �ܣ�EXTI0�жϴ���
  * ��  ����void
  * ����ֵ��void
  *
 */
void EXTI0_IRQHandler(void)
{
	/***************** ���� ***********************/
	if(RESET != EXTI_GetITStatus(EXTI_Line0)){
	delay_ms(300);
	}else{
		return;
	}
	/**********************************************/
	
	if(RESET != EXTI_GetITStatus(EXTI_Line0)){
		
		if(light == 1){
			light = 0;
		}else{
			light = 1;
		}
		Count_Pro = 0;
		//printf("EXTI1");
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

 /*
  * ��  �ܣ�EXTI2�жϴ���
  * ��  ����void
  * ����ֵ��void
  *
 */
void EXTI2_IRQHandler(void)
{
	/***************** ���� ***********************/
	if(RESET != EXTI_GetITStatus(EXTI_Line2)){
	delay_ms(300);
	}else{
		return;
	}
	/**********************************************/
	
	if(RESET != EXTI_GetITStatus(EXTI_Line2)){
		
		if(light != 1){
			if(Count_Pro == 2){
				Count_Pro = 3;
			}else{
				Count_Pro = 2;
			}
		}
		//printf("EXTI2");
		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}

 /*
  * ��  �ܣ�EXTI3�жϴ���
  * ��  ����void
  * ����ֵ��void
  *
 */
void EXTI3_IRQHandler(void)
{
	/***************** ���� ***********************/
	if(RESET != EXTI_GetITStatus(EXTI_Line3)){
	delay_ms(300);
	}else{
		return;
	}
	/**********************************************/
	
	if(RESET != EXTI_GetITStatus(EXTI_Line3)){

		if(light != 1){
			if(Count_Pro == 2){
				Temperature_Standard++;
			}else if(Count_Pro == 3){
				Humidity_Standard++;
			}
		}
		//printf("EXTI3");
		EXTI_ClearITPendingBit(EXTI_Line3);
	}
}

 /*
  * ��  �ܣ�EXTI4�жϴ���
  * ��  ����void
  * ����ֵ��void
  *
 */
void EXTI4_IRQHandler(void)
{
	/***************** ���� ***********************/
	if(RESET != EXTI_GetITStatus(EXTI_Line4)){
	delay_ms(300);
	}else{
		return;
	}
	/**********************************************/
	
	if(RESET != EXTI_GetITStatus(EXTI_Line4)){
		
		if(light != 1){
			if(Count_Pro == 2){
				Temperature_Standard--;
			}else if(Count_Pro == 3){
				Humidity_Standard--;
			}
		}
		//printf("EXTI4");
		EXTI_ClearITPendingBit(EXTI_Line4);
	}
}
