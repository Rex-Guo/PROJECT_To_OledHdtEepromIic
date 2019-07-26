#include "At24c02_Read.h"

/*
 * ��  �ܣ�AT24C02ʵ�ֶ�
 * ��  ����
 *		addr	--->�� AT24C02 �� addr �����ַ�н����ݶ���
 * 		pBuf	--->������������ݵĵ�ַ
 * 		length	--->��Ҫ�������ֽ���
 * ����ֵ��
 *		ʧ��	--->-1
 * 		�ɹ�	--->�ɹ��������ֽ���
 */
int AT24C02_PageReadData(uint8_t addr ,uint8_t pBuf[] ,uint8_t length)
{
	uint8_t count = 0; //ͳ��д����ֽ���
	
	int i = 0;
	
	//1��STM32������ʼ�ź�
	IIC24_Start();
	
	//2��STM32����������ַѡ����Ӧ�豸����˵�������Ҫִ��д����
	IIC24_WriteByte(0xA0);
	if( IIC24_WaitAck() )  
	{
		IIC24_Stop();
		printf("����������ַʧ��...\r\n");
		return -1;
	}
	
	//3��STM32������ֵ�ַ��ʼ������
	IIC24_WriteByte(addr);
	IIC24_Ack(0);
	
	
	//4��STM32����������ַѡ����Ӧ�豸����˵�������Ҫִ�ж�����
	IIC24_Start();
	IIC24_WriteByte(0xA1);
	IIC24_Ack(0);
	
	//5ѭ����lebght������
	for(;i < length; i++){
		pBuf[i] = IIC24_ReadByte();
		IIC24_Ack(0);
	}
	
	//6������
	//pBuf[i] = '\r';
	//pBuf[i+1] = '\n';
	IIC24_Ack(1);
	IIC24_Stop();
	
	
	return count;
}































