#include "oled.h"



void Led_Init()
{
	IIC_Init();
	
	Out_Oled(0xAE,MOC_Commend);//--AE��ʾ��AF��
	Out_Oled(0x00,MOC_Commend);//---ҳ��ַģʽ����������ʼ��ַ��λ(Set Lower Column Start Address For Page Addressing Mode)(00h~0Fh)
	Out_Oled(0x10,MOC_Commend);//---ҳ��ַģʽ����������ʼ��ַ��λ(Set Higher Column Start Address For Page Addressing Mode)(10h~1Fh)
	Out_Oled(0x40,MOC_Commend);//--���ÿ�ʼ�е�ַ  
	Out_Oled(0xB0,MOC_Commend);//--����ҳ���ַ
	Out_Oled(0x81,MOC_Commend);//���öԱȶ�
	Out_Oled(0xFF,MOC_Commend);//--128   
	Out_Oled(0xA1,MOC_Commend);//���ö���ӳ�� 
	Out_Oled(0xA6,MOC_Commend);//--A6����/A7����
	Out_Oled(0xA8,MOC_Commend);//--���ö�·������(1��64)
	Out_Oled(0x3F,MOC_Commend);//--1/32 duty
	Out_Oled(0xC8,MOC_Commend);//���������ɨ�跽��(Set COM Output Scan Direction)(C0h/C8h)
	Out_Oled(0xD3,MOC_Commend);//������ʾƫ��(Set Display Offset)(D3h)
	Out_Oled(0x00,MOC_Commend);//
	
	Out_Oled(0xD5,MOC_Commend);//������ʾʱ�ӷ�Ƶֵ/��Ƶ��
	Out_Oled(0x80,MOC_Commend);//
	
	Out_Oled(0xD8,MOC_Commend);//����������ɫģʽ(set area color mode off)
	Out_Oled(0x05,MOC_Commend);//
	
	Out_Oled(0xD9,MOC_Commend);//����Ԥ�������
	Out_Oled(0xF1,MOC_Commend);//
	 
	Out_Oled(0xDA,MOC_Commend);//����������Ӳ������(Set COM Pins Hardware Configuration)(DAh)
	Out_Oled(0x12,MOC_Commend);//
	
	Out_Oled(0xDB,MOC_Commend);//����VCOMH��ѹֵ(Set VCOMH Deselect Level)(DBh)
	Out_Oled(0x30,MOC_Commend);//
	
	Out_Oled(0x8D,MOC_Commend);//��ɱ��������ã�set charge pump enable��(8Dh)
	Out_Oled(0x14,MOC_Commend);//
	
	Out_Oled(0x26,MOC_Commend); //ˮƽ��������
	Out_Oled(0x00,MOC_Commend);
	Out_Oled(0x00,MOC_Commend);
	Out_Oled(0x07,MOC_Commend);
	Out_Oled(0x07,MOC_Commend);
	Out_Oled(0x00,MOC_Commend);
	Out_Oled(0xff,MOC_Commend);
	
	//Out_Oled(0x2F,MOC_Commend);//�������
	Out_Oled(0x2E,MOC_Commend);//�رչ���
	
	//Out_Oled(0xD6,MOC_Commend); //�Ŵ�
	//Out_Oled(0x00,MOC_Commend); 
	
	Out_Oled(0xD6,MOC_Commend); //�Ŵ��ֹ
	Out_Oled(0x00,MOC_Commend); 
	
	Out_Oled(0xAF,MOC_Commend);//����ʾ(turn on oled panel)(AFh)
	
}
									
/*
 * ��  �ܣ����һ���ֽڵ����ݵ�OLED
 * ��  ����
 *		MOC		--->����
 * 		data	--->����
 * ����ֵ����
 */
void Out_Oled(uint8_t data, uint8_t MOC )
{
	//��ʼ����
	IIC_Start();
	
	//����������ַ��д����
	IIC_WriteByte(0x78);
	if(IIC_WaitAck()){
		IIC_Stop();
		printf("����������ַʧ��...\r\n");
		return;
	}
	
	//��������
	IIC_WriteByte(MOC);
	if(IIC_WaitAck()){
		IIC_Stop();
		printf("�����ֵ�ַʧ��...\r\n");
		return;
	}
	
	//��������
	IIC_WriteByte(data);
	if(IIC_WaitAck()){
		IIC_Stop();
		printf("��������ʧ��...\r\n");
		return;
	}
	//ֹͣ
	IIC_Stop();
}

/*
 * ��  �ܣ�OLED��ʾ
 * ��  ����
 *		x		--->��ʾ�������Ͻ�x������
 *		y		--->��ʾ�������Ͻ�y������
 * 		ch	--->����
 * 		num	--->��ʾ���ָ���
 * ����ֵ����
 */
void Show_Zh(uint8_t x ,uint8_t y ,char ch[] ,uint8_t num)
{
	
	
	int i;
	OLED_SetPos(x, y);
	for(i = 0; i < 16 ; i++){
		Out_Oled(ch[i + (32*num)], MOC_Data );
	}
	
	OLED_SetPos(x, y+1);
	for(i = 0; i < 16; i++){
		Out_Oled(ch[i + 16 + (32*num)], MOC_Data );
	}
}

/*
 * ��  �ܣ�OLED��ʾ8*16λ
 * ��  ����
 *		x		--->��ʾ�������Ͻ�x������
 *		y		--->��ʾ�������Ͻ�y������
 * 		ch	--->����
 * 		num	--->��ʾ���ָ���
 * ����ֵ����
 */
void Show_Num(uint8_t x ,uint8_t y ,char ch[] ,uint8_t num)
{
	
	
	int i;
	OLED_SetPos(x, y);
	for(i = 0; i < 8 ; i++){
		Out_Oled(ch[i + (16*num)], MOC_Data );
	}
	
	OLED_SetPos(x, y+1);
	for(i = 0; i < 8; i++){
		Out_Oled(ch[i + 8 + (16*num)], MOC_Data );
	}
}

/*
 * ��  �ܣ�OLED��ʾ32λ
 * ��  ����
 *		x		--->��ʾ�������Ͻ�x������
 *		y		--->��ʾ�������Ͻ�y������
 * 		ch	--->����
 * 		num	--->��ʾ���ָ���
 * ����ֵ����
 */
void Show_Zh32(uint8_t x ,uint8_t y ,char ch[] ,uint8_t num)
{
	
	
	int i;
	OLED_SetPos(x, y);
	for(i = 0; i < 32 ; i++){
		Out_Oled(ch[i + (128*num)], MOC_Data );
	}
	
	OLED_SetPos(x, y+1);
	for(i = 0; i < 32; i++){
		Out_Oled(ch[i + 32 + (128*num)], MOC_Data );
	}
	
	OLED_SetPos(x, y+2);
	for(i = 0; i < 32; i++){
		Out_Oled(ch[i + 64 + (128*num)], MOC_Data );
	}
	
	OLED_SetPos(x, y+3);
	for(i = 0; i < 32; i++){
		Out_Oled(ch[i + 96 + (128*num)], MOC_Data );
	}
}

/*
 * ��  �ܣ�OLED�������꺯��
 * ��  ����
 *		x		--->��ʾλ�õĺ����꣺ȡֵ��Χ��0~127
 * 		y		--->��ʾλ�õ������꣺ȡֵ��Χ��0~7
 * ����ֵ����
 */
void OLED_SetPos(uint8_t x ,uint8_t y)
{ 	
	//1���������
//	if((x>127||x<0) || (y>7||y<0) )
//	{
//		return;
//	}
	
	//2������������
	Out_Oled(0xb0+y,MOC_Commend);
	
	//3�����ú�����
	Out_Oled(((x&0xf0)>>4)|0x10,MOC_Commend);
	Out_Oled((x&0x0f),MOC_Commend); 
}

/*
 * ��  �ܣ�OLED��������
 * ��  ������
 * ����ֵ����
 */ 
void OLED_ClearLogin(void)
{
	uint8_t i ,m;
	
	for(m=0;m<8;m++)
	{
		OLED_SetPos(0 ,m);  //ȷ��ҳ
		
		for(i=0;i<128;i++)
		{
			Out_Oled(0x00,MOC_Data);	
		}
	}
}

/*
 * ��  �ܣ�OLED��������
 * ��  ������
 * ����ֵ����
 */ 
void OLED_Clear(void)
{
	uint8_t i ,m;
	
	for(m=4;m<6;m++)
	{
		OLED_SetPos(0 ,m);  //ȷ��ҳ
		
		for(i=0;i<128;i++)
		{
			Out_Oled(0x00,MOC_Data);	
		}
	}
}

/*
 * ��  �ܣ�OLED��MҳXY������
 * ��  ������
 * ����ֵ����
 */ 
void OLED_ClearXY(uint8_t x, uint8_t y, uint8_t M)
{
	uint8_t i;
	OLED_SetPos(x ,M);  //ȷ��ҳ
	for(i=x;i<y;i++)
	{
		Out_Oled(0x00,MOC_Data);	
	}
}














