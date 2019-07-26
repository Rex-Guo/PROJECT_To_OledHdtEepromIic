#ifndef _AT24C02_H_ 
#define _AT24C02_H_

//ͷ�ļ�
#include "stm32f4xx.h"
#include "iic24.h"

//�궨��


//��������
void AT24C02_Init(void);
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
int AT24C02_PageWriteData(uint8_t addr ,uint8_t pBuf[] ,uint8_t length);

#endif
