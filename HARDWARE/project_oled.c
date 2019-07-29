#include "project_oled.h"


extern	char					temperature	[];		//�ⲿ��������ģ
extern	char							humidity[];
extern	char								state	[];
extern	char								config[];
extern	const unsigned char	 F8X16[];

//extern	int	 Read_DHT11(char *);				//�ⲿ�����ĺ���
extern int AT24C02_PageReadData(uint8_t addr ,uint8_t pBuf[] ,uint8_t length);
extern int AT24C02_PageWriteData(uint8_t addr ,uint8_t pBuf[] ,uint8_t length);
extern volatile	int Count_Pro;					//�ⲿ�����ı���
extern	volatile int light;

volatile int Temperature_Standard	= 30;	//�¶ȱȽ�ֵ
volatile int Humidity_Standard		= 31;	//ʪ�ȱȽ�ֵ
volatile int Temperature;								//�¶�
volatile int Humidity;									//ʪ��

/*
 * ��  �ܣ�������Ŀ
 * ��  ������
 * ����ֵ����
 */
void Start_Proj1()
{
	int i;
	int j = 1;
	int Temperature_Obj;
	int Humidity_Obj;
	
	
	//4,����2���ɼ���ӡ�¶� ʪ�� �ж�״̬
	/******************** ��ʾ�¶� *********************/
	for(i = 0; i < 5 && Count_Pro== 0; i++){
			Show_Zh( 16*i, 0, temperature, i);
	}
	
	Temperature_Obj = Temperature;
	j = 1;
	while(1){
		if(Temperature_Obj / 10 != 0){
			j *= 10;
			Temperature_Obj /= 10;
		}else{
			break;
		}
	}
	if(light != 1)return;
	
	/************ �ֲ����� ************/
	if(Temperature < 10){
		OLED_ClearXY(96, 128, 0);
		OLED_ClearXY(96, 128, 1);
	}else if(Temperature < 100){
		OLED_ClearXY(104, 128, 0);
		OLED_ClearXY(104, 128, 1);
	}else{
		OLED_ClearXY(112, 128, 0);
		OLED_ClearXY(112, 128, 1);
	}
	
	i = 0;
	Temperature_Obj = Temperature;
	while(Temperature_Obj != 0 || j != 0){
		Show_Num(72 + 8*i, 0, (char *)F8X16, (Temperature_Obj / j + 16));
		i++;
		Temperature_Obj = Temperature_Obj % j;
		j /= 10;
	}
	
	Show_Zh(72 + 8*i, 0, temperature, 5);			//��ӡ��C
	
	/********************* ��ʾʪ�� ****************************/
	for(i = 0; i < 5 && Count_Pro== 0; i++){
			Show_Zh( 16*i, 2, humidity, i);
	}
	
	Humidity_Obj = Humidity;
	j = 1;
	while(1){
		if(Humidity_Obj / 10 != 0){
			j *= 10;
			Humidity_Obj /= 10;
		}else{
			break;
		}
	}
	if(light != 1)return;
	
	/************ �ֲ����� ************/
	if(Humidity < 10){
		OLED_ClearXY(104, 128, 2);
		OLED_ClearXY(104, 128, 3);
	}else{
		OLED_ClearXY(112, 128, 2);
		OLED_ClearXY(112, 128, 3);
	}
	
	i = 0;
	Humidity_Obj = Humidity;
	while(Humidity_Obj != 0 || j != 0){
		Show_Num(72 + 8*i, 2, (char *)F8X16, (Humidity_Obj / j + 16));
		i++;
		Humidity_Obj %= j;
		j /= 10;
	}
	
	Show_Num(72 + 8*i, 2, (char *)F8X16, 5);			//��ӡ%RH
	i++;
	Show_Num(72 + 8*i, 2, (char *)F8X16, 50);
	i++;
	Show_Num(72 + 8*i, 2, (char *)F8X16, 40);
	if(light != 1)return;
	
	/************************* ��ʾ״̬ ***************************/
	for(i = 0; i < 5 && Count_Pro== 0; i++){
			Show_Zh( 16*i, 4, state, i);
	}
	if(Temperature_Standard > Temperature){
		Show_Zh( 16*5, 4, state, 5);
		Show_Zh( 16*6, 4, state, 6);

	}else{
		Show_Zh( 16*5, 4, state, 7);
		Show_Zh( 16*6, 4, state, 8);
	}
}

/*
 * ��  �ܣ���ȡ�¶�,ʪ��
 * ��  ������
 * ����ֵ����
 */
void Get_Data()
{
	char data[5];
	DHT11_Init();          				//
	Read_DHT11(data);
	Humidity		= (int)data[0];		//����ȫ�ֱ����洢
	Temperature	= (int)data[2];
}

/*
 * ��  �ܣ���ӭҳ
 * ��  ����
 *				name:��������
 *				role:����˵��
 * ����ֵ����
 */
void Login(char name[], char role[])
{
	/******* 1,����1����ʾ���� ���� ***********/
	int i;
	for(i = 0; i < 3; i++){
			Show_Zh32( 32*i, 0, name, i);
	}
	Show_Zh32( 32*i - 16, 0, name, i);
	
	for(i = 0; i < 7; i++){
			Show_Zh( 16*i, 4, role, i);
	}
	
	for(i = 7; i < 14; i++){
			Show_Zh( 16*(i - 7), 6, role, i);
	}
}

/*
 * ��  �ܣ������¶ȣ�ʪ�ȱȽ�ֵ
 * ��  ������
 * ����ֵ����
 */
void Set_Config()
{
	int i;
	int j = 0;
	int Temperature_Standard_Obj;
	int Humidity_Standard_Obj;
	
	
	//5,����3�������¶ȣ�ʪ�ȱȽ�ֵ
	/************** ��ʾ�¶ȱȽ�ֵ ******************/
	for(i = 0; i < 2 && Count_Pro == 0; i++){
			Show_Zh( 16*i, 0, config, i);
	}
	
	for(i = 4; i < 8 && Count_Pro == 0; i++){
			Show_Zh( 16*(i - 2), 0, config, i);
	}
	
	Temperature_Standard_Obj = Temperature_Standard;
	j = 1;
	while(1){
		if(Temperature_Standard_Obj / 10 != 0){
			j *= 10;
			Temperature_Standard_Obj /= 10;
		}else{
			break;
		}
	}
	
	i = 0;
	Temperature_Standard_Obj = Temperature_Standard;
	while(Temperature_Standard_Obj != 0 || j != 0){
		Show_Num(88 + 8*i, 0, (char *)F8X16, (Temperature_Standard_Obj / j + 16));
		i++;
		Temperature_Standard_Obj = Temperature_Standard_Obj % j;
		j /= 10;
	}
	
	//��ʾ��ͷ
	if(Count_Pro == 2 || Count_Pro == 0){
			OLED_ClearXY(104, 128, 2);
			OLED_ClearXY(104, 128, 3);
			Show_Zh(88 + 8*i , 0, config, 8);
	}
	if(light == 1)return;
	
	/**************** ��ʾʪ�ȱȽ�ֵ ********************/
	for(i = 2; i < 8 && Count_Pro == 0; i++){
			Show_Zh( 16*(i - 2), 2, config, i);
	}
	
	Humidity_Standard_Obj = Humidity_Standard;
	j = 1;
	while(1){
		if(Humidity_Standard_Obj / 10 != 0){
			j *= 10;
			Humidity_Standard_Obj /= 10;
		}else{
			break;
		}
	}
	
	i = 0;
	Humidity_Standard_Obj = Humidity_Standard;
	while(Humidity_Standard_Obj != 0 || j != 0){
		Show_Num(88 + 8*i, 2, (char *)F8X16, (Humidity_Standard_Obj / j + 16));
		i++;
		Humidity_Standard_Obj = Humidity_Standard_Obj % j;
		j /= 10;
	}
	
		//��ʾ��ͷ
	if(Count_Pro == 3){
			OLED_ClearXY(104, 128, 0);
			OLED_ClearXY(104, 128, 1);
			Show_Zh(88 + 8*i , 2, config, 8);
	}else{
		Count_Pro = 2;
	}
	
}

/*
 * ��  �ܣ��޸Ļ��ʼ��AT24C02
 * ��  ����
 *				�״ν��룺choose == 1
 *				�޸Ĳ�����choose == 0
 * ����ֵ����
 */
void Modify_TH(uint8_t choose)
{
	uint8_t pBuf[10] = {0};
	uint8_t fBuf[20];
	if(choose == 0){
			pBuf[0] = 'F';
			pBuf[1] = Temperature_Standard / 100 + '0';
			pBuf[2] = Temperature_Standard % 100 / 10 + '0';
			pBuf[3] = Temperature_Standard % 10 + '0';
			pBuf[4] = Humidity_Standard / 100 + '0';
			pBuf[5] = Humidity_Standard % 100 / 10 + '0';
			pBuf[6] = Humidity_Standard % 10 + '0';
			AT24C02_PageWriteData(0 ,pBuf,strlen((char *)pBuf));
	}else if(choose == 1){
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
			Modify_TH(0);
		}
	}
}










