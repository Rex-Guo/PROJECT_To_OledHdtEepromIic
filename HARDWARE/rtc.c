#include "rtc.h"

RTC_InitTypeDef RTC_InitStruct;
RTC_DateTypeDef RTC_DataStructure;
RTC_TimeTypeDef RTC_TimeStructure;
/*
 * ��  �ܣ�RTC��ʼ��  
 * ��  ������
 * ����ֵ����
 */
void Rtc_Init(void)
{
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	PWR_BackupAccessCmd(ENABLE);/*ʹ�ܺ󱸼Ĵ�������*/
	
	if(RTC_ReadBackupRegister(RTC_BKP_DR0) == 0xA0A0)
	{
		RCC_LSEConfig(RCC_LSE_ON);/*ʹ��LSE����*/
		while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)/*�ȴ�����*/
		{
		}
		RCC_RTCCLKConfig(RCC_RTCCLKSource_HSE_Div2);/*ѡ��RTCʱ��Դ*/
		RCC_RTCCLKCmd(ENABLE);/*ʹ��RTCʱ��*/
		RTC_WaitForSynchro();/*�ȴ�RTC APB�Ĵ���ͬ��*/
		/*����RTC���ݼĴ����ͷ�Ƶ��*/
		RTC_InitStruct.RTC_AsynchPrediv	= IS_RTC_ASYNCH_PREDIV(0x7f);
		RTC_InitStruct.RTC_HourFormat		= RTC_HourFormat_24;
		RTC_InitStruct.RTC_SynchPrediv	= IS_RTC_SYNCH_PREDIV(0x7fff);
		RTC_Init(&RTC_InitStruct);
		/*���������պ�����*/
		RTC_DataStructure.RTC_Year = 0x19;
		RTC_DataStructure.RTC_Month = 0x7;
		RTC_DataStructure.RTC_Date = 0x06;
		RTC_DataStructure.RTC_WeekDay = 0x07;
		RTC_SetDate(RTC_Format_BCD,&RTC_DataStructure);
		/*����ʱ���� ����ʾ��ʽ*/
		RTC_TimeStructure.RTC_H12 = RTC_H12_AM;
		RTC_TimeStructure.RTC_Hours = 0x21;
		RTC_TimeStructure.RTC_Minutes = 0x30;
		RTC_TimeStructure.RTC_Seconds = 0x00;
		RTC_SetTime(RTC_Format_BCD,&RTC_TimeStructure);
		/*���ñ��ݼĴ�������ʾ�Ѿ����ù�RTC*/
		RTC_WriteBackupRegister(RTC_BKP_DR0,0xA0A0);
	}
	


}







