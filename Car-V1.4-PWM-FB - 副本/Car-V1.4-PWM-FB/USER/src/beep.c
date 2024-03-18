#include "beep.h"
#include "sys.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx.h"

//////////////////////////////////////////////////////////////////////////////////	 

//  功能描述   : 蜂鸣器演示例程(STM32F407)
//              说明: 
//              ----------------------------------------------------------------
//              GND  接地
//							VCC  接5V
//							I/O  接PE0
//              ----------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////

void init_beep(void)
{
	// 初始化BEER

	/*******************************************************************************/
	GPIO_InitTypeDef GPIO_InitStruct;
	//初始化时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	//设置GPIO参数
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9; // 
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;//设置为输出模式
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;//设置为推挽
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;//下拉
	GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed ;
	
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	//初始化完成后将输出置为0
	//GPIO_SetBits(A, GPIO_Pin_9; //1
	GPIO_ResetBits(GPIOA, GPIO_Pin_9); //0
	//PBout(8) = 0;
}


