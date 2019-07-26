#ifndef _PROJECT_OLED_H_ 
#define _PROJECT_OLED_H_

/************************* ͷ�ļ� *********************/
#include "stm32f4xx.h"
#include "systick.h"
#include "oled.h"
#include "dht.h"

/************************ �������� *********************/
/*
 * ��  �ܣ�������Ŀ
 * ��  ����
 *				name:��������
 *				role:����˵��
 * ����ֵ����
 */
void Start_Proj1(void);

/*
 * ��  �ܣ���ȡ�¶ȣ�ʪ��
 * ��  ������
 * ����ֵ��int
 */
void Get_Data(void);


/*
 * ��  �ܣ���ӭҳ
 * ��  ����
 *				name:��������
 *				role:����˵��
 * ����ֵ����
 */
void Login(char name[], char role[]);

/*
 * ��  �ܣ������¶ȣ�ʪ�ȱȽ�ֵ
 * ��  ������
 * ����ֵ����
 */
void Set_Config(void);

#endif