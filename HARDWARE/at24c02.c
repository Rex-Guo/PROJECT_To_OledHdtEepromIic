#include "at24c02.h"


/*
 * ��  �ܣ�AT24C02��ʼ��  
 * ��  ������
 * ����ֵ����
 */
void AT24C02_Init(void)
{
	IIC24_Init();
}

/*
 * ��  �ܣ�AT24C02ʵ��ҳд 
 * ��  ����
 *		addr	--->������д�� AT24C02 �� addr �����ַ��
 * 		pBuf	--->����Ҫд������ݵ��׵�ַ
 * 		length	--->��Ҫд����ֽ���
 * ����ֵ��
 *		ʧ��	--->-1
 * 		�ɹ�	--->�ɹ�д����ֽ���
 */
int AT24C02_PageWriteData(uint8_t addr ,uint8_t pBuf[] ,uint8_t length)
{
	uint8_t count = 0; //ͳ��д����ֽ���
	uint8_t tempAddr = addr;  
	uint8_t i;
	
	for(i=0;i<length;i++)
	{
		//����һ�ν��� ���� ����ҳ�߽��ַ�����º���ʼ
		if( (i==0) || (tempAddr%8==0) )
		{
			//STM32����ֹͣ�ź� �ر���һ�ε���ʼ�ź�
			IIC24_Stop();
			delay_s(1);
			
			//1��STM32������ʼ�ź�
			IIC24_Start();
			
			//2��STM32����������ַѡ����Ӧ�豸����˵�������Ҫִ��д����
			IIC24_WriteByte(0xA0);
			if( IIC24_WaitAck() )  //���ʽ����˵�����յ���Ӧ���ź�
			{
				IIC24_Stop();
				printf("����������ַʧ��...\r\n");
				return -1;
			}
			//3��STM32�����ֵ�ַ˵�������Ҫ������д������ֵ�ַ
			IIC24_WriteByte(tempAddr);
			if( IIC24_WaitAck() )  //���ʽ����˵�����յ���Ӧ���ź�
			{
				IIC24_Stop();
				printf("�����ֵ�ַʧ��...\r\n");
				return -1;
			}
		}
		
		//4��STM32���� ���� �� AT24C02
		IIC24_WriteByte(pBuf[count]);
		if( IIC24_WaitAck() )  //���ʽ����˵�����յ���Ӧ���ź�
		{
			IIC24_Stop();
			printf("��������ʧ��...\r\n");
			return -1;
		}else{
			count++;		//ͳ��д����ֽ���
			tempAddr++;   	//����ַ����ƫ��
		}
	}
	
	//5��STM32����ֹͣ�ź�
	IIC24_Stop();
	
	return count;
}































