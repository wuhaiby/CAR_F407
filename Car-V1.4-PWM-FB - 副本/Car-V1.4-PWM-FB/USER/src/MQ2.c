#include "stm32f4xx.h"                  // Device header

void mq2_init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//使能GPIOA时钟

  //GPIOF9,F10初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;//LED0和LED1对应IO口
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//无上下拉
  GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化GPIO
	
  //GPIO_SetBits(GPIOD,GPIO_Pin_5);//设置高，灯灭
    
}

uint8_t MQ2_Get(void)
{
	return GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_5);			//返回PB13输入寄存器的状态
}


