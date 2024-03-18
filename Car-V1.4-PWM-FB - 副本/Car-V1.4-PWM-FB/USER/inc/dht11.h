#ifndef _DHT11_H_
#define _DHT11_H_

#include <sys.h>

//����DHT11����Ϊ���ģʽ
void DHT11_SetOutputMode(void);


//����DHT11����Ϊ����ģʽ
void DHT11_SetInputMode(void);

void DHT11_Init(void);

//�������Ϳ�ʼ�ź�
void DHT11_SendStart(void);

//�����ȴ�DHT11��Ӧ
bool DHT11_IsACK(void);

//��ȡ1bit���� ����ֵ  ����0  --> 0000 000_0  or ����1  --> 0000 000_1
uint8_t DHT11_ReadBit(void);

//��ȡDHT11������������
bool DHT11_GetVal(void);

#endif

