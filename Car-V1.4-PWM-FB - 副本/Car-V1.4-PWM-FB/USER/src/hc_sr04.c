#include "hc_sr04.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//  文 件 名   : hc_sr04.c
//  版 本 号   : v1.0
//  作    者   : 广州粤嵌通信科技股份有限公司
//  生成日期   : 2018-06-03
//  最近修改   : 
//  功能描述   : 超声波演示例程(STM32F407)
//              说明: 
//              ----------------------------------------------------------------
//              GND  接地
//							VCC  接5V
//							TRIG 接PB5
//							ECHO 接PE6
//              ----------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////


// 初始化PE6（输入） 和 PB6（输出）
void init_sr04(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;

	//打开GPIO端口时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOE, ENABLE);
	
	//配置GPIO引脚的参数  PB6 -- TRIG
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT;			
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_5;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//配置GPIO引脚的参数  PE6 -- TRIG
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN;			
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_6;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

#define HCSR04_TRIG(n)  n ? GPIO_SetBits(GPIOB,GPIO_Pin_5) : GPIO_ResetBits(GPIOB,GPIO_Pin_5)

#define HCSR04_ECHO		  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6)

int get_sr04_distance(void)
{
	
	uint32_t cnt = 0;
	//1.发送触发信号
	HCSR04_TRIG(0);
	delay_ms(5);
	HCSR04_TRIG(1);
	delay_us(15);
	HCSR04_TRIG(0);
	
	//2.等待ECHO引脚出现高电平
	while( HCSR04_ECHO == RESET);
	
	//3.计算高电平持续时间
	while(HCSR04_ECHO == SET)
	{
		delay_us(9);
		cnt++;	
	}
	
	//4.利用公式计算距离并返回
	cnt /= 2;
	
	return (cnt * 3); // 距离 = 9us * 测距精度
}





