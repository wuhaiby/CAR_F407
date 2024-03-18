#include "stm32f4xx.h"                  // Device header

void mq2_init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//ʹ��GPIOAʱ��

  //GPIOF9,F10��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;//LED0��LED1��ӦIO��
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//��������
  GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��GPIO
	
  //GPIO_SetBits(GPIOD,GPIO_Pin_5);//���øߣ�����
    
}

uint8_t MQ2_Get(void)
{
	return GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_5);			//����PB13����Ĵ�����״̬
}


