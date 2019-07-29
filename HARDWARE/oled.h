#ifndef _OLED_H_ 
#define _OLED_H_

//ͷ�ļ�
#include "stm32f4xx.h"
#include "iic.h"

//�궨��
#define MOC_Data		0x40 
#define MOC_Commend	0x00 

//��������
/*
 * ��  �ܣ�����һ���ֽڵ����ݵ�OLED
 * ��  ����
 *		MOC		--->����
 * 		data	--->����
 * ����ֵ����
 */
void Out_Oled(uint8_t data, uint8_t MOC );

/*
 * ��  �ܣ�OLED��ʾ
 * ��  ����
 *		x		--->��ʾ�������Ͻ�x������
 *		y		--->��ʾ�������Ͻ�y������
 * 		ch	--->����
 * 		num	--->��ʾ���ָ���
 * ����ֵ����
 */
void Show_Zh(uint8_t x ,uint8_t y ,char ch[] ,uint8_t num);

/*
 * ��  �ܣ�OLED��ʾ8*16λ
 * ��  ����
 *		x		--->��ʾ�������Ͻ�x������
 *		y		--->��ʾ�������Ͻ�y������
 * 		ch	--->����
 * 		num	--->��ʾ���ָ���
 * ����ֵ����
 */
void Show_Num(uint8_t x ,uint8_t y ,char ch[] ,uint8_t num);

/*
 * ��  �ܣ�OLED��ʾ32λ
 * ��  ����
 *		x		--->��ʾ�������Ͻ�x������
 *		y		--->��ʾ�������Ͻ�y������
 * 		ch	--->����
 * 		num	--->��ʾ���ָ���
 * ����ֵ����
 */
void Show_Zh32(uint8_t x ,uint8_t y ,char ch[] ,uint8_t num);

/*
 * ��  �ܣ�OLED�������꺯��
 * ��  ����
 *		x		--->��ʾλ�õĺ����꣺ȡֵ��Χ��0~127
 * 		y		--->��ʾλ�õ������꣺ȡֵ��Χ��0~7
 * ����ֵ����
 */
void OLED_SetPos(uint8_t x ,uint8_t y);

/*
 * ��  �ܣ���ʼ��OLED
 * ��  ������
 * ����ֵ����
 */
void Led_Init(void);

/*
 * ��  �ܣ�OLED��������
 * ��  ������
 * ����ֵ����
 */ 
void OLED_ClearLogin(void);

/*
 * ��  �ܣ�OLED��������
 * ��  ������
 * ����ֵ����
 */ 
void OLED_Clear(void);

/*
 * ��  �ܣ�OLED��MҳXY������
 * ��  ������
 * ����ֵ����
 */ 
void OLED_ClearXY(uint8_t x, uint8_t y, uint8_t M);

#endif
