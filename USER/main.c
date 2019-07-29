#include "stm32f4xx.h"
#include "systick.h"
#include "uart.h"
#include "chinese.h"
#include "oledfont.h"
#include "oled.h"
#include "project_oled.h"
#include "exti_0234.h"
#include "at24c02.h"
#include "At24c02_Read.h"
#include "rtc.h"

extern	volatile int light;
extern	volatile int Count_Pro;
extern	RTC_InitTypeDef RTC_InitStruct;
extern	RTC_DateTypeDef RTC_DataStructure;
extern	RTC_TimeTypeDef RTC_TimeStructure;

int main(void)
{
	int ret = 1;
	int colun = 0;
	char buf[30];
//	RCC_ClocksTypeDef Get_RCC_Clocks;
//	uint32_t RCC_BASE_sel = *(uint32_t *)(0x40002834);
	
	/****************** Ӳ����ʼ�� ********************/
	Systick_Init();
	UART1_Init(115200); 
	Rtc_Init();
	Led_Init();
	OLED_ClearLogin();
	Exti_Init();
	AT24C02_Init();
	printf("HardWare Init Success!\r\n");
//	printf("%d ", RTC_TR_HT_0);
//	printf("%d\r\n", RTC_TR_HT_1);
//	printf("%d\r\n", RTC_TR_PM);
//	printf("%d\r\n", RCC_BASE_sel);
	
//	while (1)
//{
// RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
//	RTC_GetDate(RTC_Format_BIN, &RTC_DataStructure);
//	sprintf(buf,"20%0.2d/%0.2d/%0.2d", 
//	 RTC_DataStructure.RTC_Year, 
//	 RTC_DataStructure.RTC_Month, 
//	 RTC_DataStructure.RTC_Date);
//	printf("%s",buf);//���ʱ�䵽����
//	printf("\r\n");//����

//	sprintf(buf,"%0.2d:%0.2d:%0.2d", 
//	 RTC_TimeStructure.RTC_Hours, 
//	 RTC_TimeStructure.RTC_Minutes,
//	 RTC_TimeStructure.RTC_Seconds);
//	printf("%s",buf);//������ڵ�����
//	printf("\r\n");//����

//	delay_ms(100);
//} 
	
/****************** ʵ�ֵĹ��� ********************/
	/*
	*	����˵����	1���������뻶ӭҳ����ʾ��������������˵��
	*						2���ȴ�2������¶ȣ�ʪ�ȼ��ҳ�棬ʵʱ���
	*						3���� s1 ���� ���ҳ-����ҳ �����л����лؼ��ҳ����Ƚ�ֵ
	*						4��������ҳ�°� s2 �������ƶ���ͷָ���޸���
	*						5��������ҳ�°� s3 ������ֵ�� s4 ������ֵ
	*	�д����ƣ�	
	*						1�������л��ȴ�ʱ�䳤�����Ų���������Ϊ����������������
	*/
	
	/*********************** ��AT24C02��ȡ�¶ȡ�ʪ�ȱȽ�ֵ ****************************/
	Modify_TH(1);
	
	/*******************************************************************************/
	
	Login(author, role);	//��ӭҳ��author��������role����˵��
	light = 1;
	delay_s(2);						//2,��ʱ2s
	OLED_ClearLogin();
	
	while(1){
		/*********************** �������洢 ************************/
		if(ret != light){
			delay_ms(5);
			Count_Pro = 0;
			ret = light;
			
			//�޸�AT24C02�бȽ�ֵ
			Modify_TH(0);
		}
		/********************************************************/
		
		if(light == 1){							//true������ҳ
			if(Count_Pro == 0){				//�ж��Ƿ�ȫ�����
				OLED_Clear();
			}
			
			//3,��ȡ�¶ȣ�ʪ��
			if(colun % 10 == 0){
				Get_Data();
				colun = 0;
			}
			
			colun++;
			Start_Proj1();
			Count_Pro = 2;						//��־�´β�ȫ�����
		}else{											//��������ҳ��
			if(Count_Pro == 0){
				OLED_Clear();
			}
			
			Set_Config();
		}
	}

}
