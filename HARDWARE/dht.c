#include "dht.h"
//#include "systick.h"
//#include "usart1.h"

extern void delay_ms(u32);
extern void delay_us(u32);

GPIO_InitTypeDef GPIO_InitStruct1;

//��ʼ��DHT11
void DHT11_Init()
{
	
	//����GPIOGʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	
	//����GPIOG
	GPIO_InitStruct1.GPIO_Mode		= GPIO_Mode_OUT;
	GPIO_InitStruct1.GPIO_OType	= GPIO_OType_PP;
	GPIO_InitStruct1.GPIO_Pin		= GPIO_Pin_9;
	GPIO_InitStruct1.GPIO_PuPd		= GPIO_PuPd_UP;
	GPIO_InitStruct1.GPIO_Speed	= GPIO_Speed_25MHz;
	GPIO_Init(GPIOG, &GPIO_InitStruct1);
}

//����DHT11ģ��
int Read_DHT11(char *c)
{
	int i = 0;
	//����DHT11
	DHT11_OUT();
	
	SetGPIO(0);
	delay_ms(20);
	SetGPIO(1);
	delay_us(30);
	
	//����DHT��Ӧ
	DHT11_IN();
	while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_9) == 1);		//�͵�ƽΪ��Ӧ�źſ�ʼ
	while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_9) == 0){		//�жϵ͵�ƽ�Ƿ����80us
		i++;
		if(i > 17)return -1;
		delay_us(5);
	}
	i = 0;
	
	
	if(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_9) == 1){			//�ߵ�ƽΪ��Ӧ�źŵĽ���
		while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_9) == 1){	//�жϸߵ�ƽ�Ƿ����80us + 20~40����ʱ�ȴ�
			i++;
			if(i > 110)return -1;
			delay_us(1);
		}
	}else{
		return -1;
	}
	
	//��������
	if(Read_Data(c) != 0){
		return -2;
	}
	
	//��������
	if(c[4] == (c[0] + c[1] +c[2] +c[3])){
		return 0;
	}else{
		return -3;
	}
}

//����DHT11���͵�40bit����
int Read_Data(char *ch)
{
	int i = 0;
	int j = 0;
	int count = 0;
	
	if(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_9) == 0){
		for(j = 0; j < 5; j++){
			ch[j] = 0;
			for(i = 0; i < 8; i++){
				while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_9) == 0){
					count++;
					if(count > 50)return -1;
					delay_us(1);
				}
				count = 0;
				delay_us(30);
				if(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_9) == 1){
					ch[j] |= (0x1 << (7 - i));
				}
				while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_9) == 1){
					count++;
					if(count > 70)return -2;
					delay_us(1);
				}
				count = 0;
			}
		}
		return 0;
	}else{
		return -3;
	}
}
