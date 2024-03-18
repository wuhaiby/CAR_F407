#include "hc_sr04.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//  �� �� ��   : hc_sr04.c
//  �� �� ��   : v1.0
//  ��    ��   : ������Ƕͨ�ſƼ��ɷ����޹�˾
//  ��������   : 2018-06-03
//  ����޸�   : 
//  ��������   : ��������ʾ����(STM32F407)
//              ˵��: 
//              ----------------------------------------------------------------
//              GND  �ӵ�
//							VCC  ��5V
//							TRIG ��PB5
//							ECHO ��PE6
//              ----------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////


// ��ʼ��PE6�����룩 �� PB6�������
void init_sr04(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;

	//��GPIO�˿�ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOE, ENABLE);
	
	//����GPIO���ŵĲ���  PB6 -- TRIG
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT;			
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_5;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//����GPIO���ŵĲ���  PE6 -- TRIG
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN;			
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_6;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

#define HCSR04_TRIG(n)  n ? GPIO_SetBits(GPIOB,GPIO_Pin_5) : GPIO_ResetBits(GPIOB,GPIO_Pin_5)

#define HCSR04_ECHO		  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6)

int get_sr04_distance(void)
{
	
	uint32_t cnt = 0;
	//1.���ʹ����ź�
	HCSR04_TRIG(0);
	delay_ms(5);
	HCSR04_TRIG(1);
	delay_us(15);
	HCSR04_TRIG(0);
	
	//2.�ȴ�ECHO���ų��ָߵ�ƽ
	while( HCSR04_ECHO == RESET);
	
	//3.����ߵ�ƽ����ʱ��
	while(HCSR04_ECHO == SET)
	{
		delay_us(9);
		cnt++;	
	}
	
	//4.���ù�ʽ������벢����
	cnt /= 2;
	
	return (cnt * 3); // ���� = 9us * ��ྫ��
}





