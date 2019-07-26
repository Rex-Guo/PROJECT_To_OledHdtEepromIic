#ifndef _AT24C02_READ_H_ 
#define _AT24C02_READ_H_

//ͷ�ļ�
#include "stm32f4xx.h"
#include "iic24.h"

//�궨��


//��������
/*
 * ��  �ܣ�AT24C02ʵ�ֶ�
 * ��  ����
 *		addr	--->�� AT24C02 �� addr �����ַ�н����ݶ���
 * 		pBuf	--->������������ݵ��׵�ַ
 * 		length	--->��Ҫ�������ֽ���
 * ����ֵ��
 *		ʧ��	--->-1
 * 		�ɹ�	--->�ɹ��������ֽ���
 */
int AT24C02_PageReadData(uint8_t addr ,uint8_t pBuf[] ,uint8_t length);

#endif
