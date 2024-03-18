#include "stm32f4xx.h"  //�������
#include <stdbool.h>
#include <stdio.h>
#include "delay.h"
#include "dht11.h"

char dhtbuf[5] = {0}; //�洢��ʪ������


#define BUFFERSIZE  256  				//���ջ�������С
uint8_t aRxBuffer [BUFFERSIZE];	//��Ϊ���ջ�����
__IO uint8_t ubRxIndex = 0x00;  //��Ϊ���ջ������ļ��������൱�������±�



//����DHT11����Ϊ���ģʽ
void DHT11_SetOutputMode(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//��GPIO�˿�ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT;			//���ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_3;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_3); //���ſ���Ϊ�ߵ�ƽ
}


//����DHT11����Ϊ����ģʽ
void DHT11_SetInputMode(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//��GPIO�˿�ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN;			//����ģʽ
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_3;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void DHT11_Init(void)
{
	DHT11_SetOutputMode();
}


//�������Ϳ�ʼ�ź�
void DHT11_SendStart(void)
{
	//1.��������Ϊ���ģʽ
	DHT11_SetOutputMode();
	
	//2.���������ŵ�ƽ����,����18ms
	GPIO_ResetBits(GPIOB,GPIO_Pin_3);
	delay_ms(20);
	
	//3.���������ŵ�ƽ���ߣ�20us ~ 40us
	GPIO_SetBits(GPIOB,GPIO_Pin_3); 
	delay_us(30);
}


//�����ȴ�DHT11��Ӧ
bool DHT11_IsACK(void)
{
	uint32_t i = 0;
	
	//1.����DHT11����Ϊ����ģʽ
	DHT11_SetInputMode();
	
	//2.�����ȴ����ű����� Ϊ����߳���ɿ��ԣ�������ӳ�ʱ���� ��ʱʱ��100us����
	while( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3) == SET && i < 100 )
	{
		delay_us(1);
		i++;
	}
	
	if(i>=100)
	{
		return false; //˵��δ��Ӧ��ԭ���ǳ�ʱ
	}
	
	//3.�����ȴ����ű����� Ϊ����߳���ɿ��ԣ�������ӳ�ʱ���� ��ʱʱ��100us����
	i= 0;
	while( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3) == RESET && i < 100 )
	{
		delay_us(1);
		i++;
	}
	if(i>=100)
	{
		return false; //˵��δ��Ӧ��ԭ���ǳ�ʱ
	}
	else
		return true;  //˵������Ӧ
}

//��ȡ1bit���� ����ֵ  ����0  --> 0000 000_0  or ����1  --> 0000 000_1
uint8_t DHT11_ReadBit(void)
{
	uint32_t i = 0;
	
	//1.�����ȴ��͵�ƽ����
	while( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3) == SET && i < 100 )
	{
		delay_us(1);
		i++;
	}
	
	//2.�����ȴ��ߵ�ƽ����
	i= 0;
	while( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3) == RESET && i < 100 )
	{
		delay_us(1);
		i++;
	}
	
	//3.��ʱһ��ʱ�� 28us < x < 70us
	delay_us(40);
	
	//4.��ȡ��ʱ�����ŵ�ƽ��ֱ�ӷ���
	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3);
}

//��ȡDHT11������������
bool DHT11_GetVal(void)
{
	int cnt = 0;
	int i = 0;

	//1.���Ϳ�ʼ�ź�
	DHT11_SendStart();
	
	//2.�ȴ�DHT11��Ӧ
	if(DHT11_IsACK())
	{
		//3.ѭ����ȡ40bit����   8bitʪ������ + 8bitʪ��С�� + 8bit�¶����� + 8bit�¶�С�� + 8bitУ���   
		for(cnt=0;cnt<5;cnt++)
		{
			for(i=0;i<8;i++)
			{
					dhtbuf[cnt] <<= 1;
					dhtbuf[cnt] |= DHT11_ReadBit(); //MSB ��λ�ȳ�  			
			}
		}
		//����У��
		if(dhtbuf[0]+dhtbuf[1]+dhtbuf[2]+dhtbuf[3] != dhtbuf[4])
		{
			return false; //У��ʧ��		
		}
	}
	else
	{
		return false; //û����Ӧ
	}
	
	return true;
}