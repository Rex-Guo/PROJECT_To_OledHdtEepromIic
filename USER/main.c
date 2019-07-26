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

extern	volatile int light;
extern	volatile int Count_Pro;
extern volatile int Temperature_Standard;	//�¶ȱȽ�ֵ
extern volatile int Humidity_Standard;		//ʪ�ȱȽ�ֵ

int main(void)
{
	int ret = 1;
	uint8_t pBuf[10] = {0};
	uint8_t fBuf[20];
	
	/****************** Ӳ����ʼ�� ********************/
	Systick_Init();
	UART1_Init(115200); 
	Led_Init();
	OLED_Clear();
	Exti_Init();
	AT24C02_Init();
	printf("HardWare Init Success!\r\n");
	
/****************** ʵ�ֵĹ��� ********************/
	/*
	*	����˵����	1���������뻶ӭҳ����ʾ��������������˵��
	*						2���ȴ�2������¶ȣ�ʪ�ȼ��ҳ�棬ʵʱ���
	*						3���� s1 ���� ���ҳ-����ҳ �����л����лؼ��ҳ����Ƚ�ֵ
	*						4��������ҳ�°� s2 �������ƶ���ͷָ���޸���
	*						5��������ҳ�°� s3 ������ֵ�� s4 ������ֵ
	*	�д����ƣ�	1��������Ļ��˸
	*						2�������л��ȴ�ʱ�䳤�����Ų���������Ϊ����������������
	*/
	
	/*********************** ��AT24C02��ȡ�¶ȡ�ʪ�ȱȽ�ֵ ****************************/
	
	memset(fBuf,0,sizeof(fBuf));
	AT24C02_PageReadData(0 ,fBuf ,7);
	delay_ms(5);
	if(fBuf[0] == 'F'){
		memset(fBuf,0,sizeof(fBuf));
		AT24C02_PageReadData(0 ,fBuf ,7);
		Temperature_Standard = ((int)fBuf[1] - '0')*100 + ((int)fBuf[2] - '0')*10 + ((int)fBuf[3] - '0');
		Humidity_Standard = ((int)fBuf[4] - '0')*100 + ((int)fBuf[5] - '0')*10 + ((int)fBuf[6] - '0');
	}else{																		
		//�״����д����洢��Ĭ��30��31
		pBuf[0] = 'F';
		pBuf[1] = Temperature_Standard / 100 + '0';
		pBuf[2] = Temperature_Standard % 100 / 10 + '0';
		pBuf[3] = Temperature_Standard % 10 + '0';
		pBuf[4] = Humidity_Standard / 100 + '0';
		pBuf[5] = Humidity_Standard % 100 / 10 + '0';
		pBuf[6] = Humidity_Standard % 10 + '0';
		AT24C02_PageWriteData(0 ,pBuf,strlen((char *)pBuf));
	}
	delay_ms(5);
	/*******************************************************************************/
	
	Login(author, role);	//��ӭҳ��author��������role����˵��
	light = 1;
	
	delay_s(2);						//2,��ʱ2s
	
	while(1){
		
		/*********************** �������洢 ************************/
		if(ret != light){
			delay_ms(10);
			Count_Pro = 0;
			ret = light;
			
			//�޸�AT24C02�бȽ�ֵ
			pBuf[0] = 'F';
			pBuf[1] = Temperature_Standard / 100 + '0';
			pBuf[2] = Temperature_Standard % 100 / 10 + '0';
			pBuf[3] = Temperature_Standard % 10 + '0';
			pBuf[4] = Humidity_Standard / 100 + '0';
			pBuf[5] = Humidity_Standard % 100 / 10 + '0';
			pBuf[6] = Humidity_Standard % 10 + '0';
			AT24C02_PageWriteData(0 ,pBuf,strlen((char *)pBuf));
		}
		/********************************************************/
		
		if(light == 1){							//true������ҳ
			if(Count_Pro == 0){				//�ж��Ƿ�ȫ�����
				OLED_Clear();
			}
			
			Start_Proj1();
			
			Count_Pro = 2;						//��־�´β�ȫ�����
		}else{											//��������ҳ��
			
			if(Count_Pro == 0){
				OLED_Clear();
			}
			
			Set_Config();
		}
		
		delay_s(1);									//���¶�ģ��ɼ���ʱ��
	}

	
		
	
}
