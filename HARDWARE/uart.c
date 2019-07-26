#include "uart.h"



/******************************** ʵ��printf��� ********************************/
#pragma import(__use_no_semihosting) 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout; 

void _sys_exit(int x) 
{ 
	x = x; 
} 

int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);    //0100 0000
	USART1->DR = (u8) ch;      
	return ch;
}
/*******************************************************************************/



/*
 * UART1_TX		--->PA9
 * UART1_RX		--->PA10
 */

/*
 * ��  �ܣ�UART1 �ĳ�ʼ��
 * ��  ����
 * 		BaudRate	--->�����ʣ����ǳ�������Щ 115200 9600 38400 ...
 * ����ֵ����
 * ˵  �����շ�˫���Ĳ����ʱ���һ��
 */
void UART1_Init(uint32_t BaudRate)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef  USART_InitStruct;
	NVIC_InitTypeDef  NVIC_InitStruct;
	
	//1������ UART1 ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	//2��ʹ�� UART1 �� GPIO ��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
	//3���� PA9 PA10 ����Ϊ UART1 �����⹦������
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9  , GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10  ,GPIO_AF_USART1);
	
	//4������ PA9 PA10 Ϊ����ģʽ
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;    //����ģʽ
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	//5������ UART1 ����Ϣ
	USART_InitStruct.USART_BaudRate = BaudRate;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //�ر�Ӳ������
	USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;   //�����ܷ�
	USART_InitStruct.USART_Parity = USART_Parity_No;  //��У��
	USART_InitStruct.USART_StopBits   = USART_StopBits_1; //һλֹͣλ
	USART_InitStruct.USART_WordLength = USART_WordLength_8b; //8λ����λ
	USART_Init(USART1, &USART_InitStruct);
	
	//6������ UART1 �Ľ����ж�   USART_IT_RXNE  --->�������ݼĴ�����Ϊ��
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	//7����ʼ�� NVIC
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	
	//8��ʹ�� UART1
	USART_Cmd(USART1, ENABLE);
}

uint8_t tempData[20] = {0};     //������յ�����
uint8_t RecvData[20] = {0};     //������յ�����
uint8_t count = 0;
uint8_t RecvFlag = 0;


//�����ݵ����ʹ�������ж�  			--->�Զ���Э�飬ʹ�� \r\n ��Ϊ������־
void USART1_IRQHandler(void)
{
	//��һ���ж� UART1 �Ľ����ж��Ƿ����
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		//�жϵ�ִ������
		tempData[count++] = USART_ReceiveData(USART1);
		if( (tempData[count-2]=='\r') && (tempData[count-1]=='\n'))
		{
			strcpy((char *)RecvData,(char *)tempData);
			
			//��ս����ڴ�
			memset(tempData,0,sizeof(tempData));
			count = 0;
			
			RecvFlag = 1;  //���ճɹ���־
		}
		//����жϱ�־λ
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}













