#include "stm32f4xx.h"  //必须包含
#include <stdbool.h>
#include <stdio.h>
#include "delay.h"
#include "dht11.h"

char dhtbuf[5] = {0}; //存储温湿度数据


#define BUFFERSIZE  256  				//接收缓冲区大小
uint8_t aRxBuffer [BUFFERSIZE];	//作为接收缓冲区
__IO uint8_t ubRxIndex = 0x00;  //作为接收缓冲区的计数器，相当于数组下标



//配置DHT11引脚为输出模式
void DHT11_SetOutputMode(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//打开GPIO端口时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT;			//输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_3;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_3); //引脚空闲为高电平
}


//配置DHT11引脚为输入模式
void DHT11_SetInputMode(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//打开GPIO端口时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN;			//输入模式
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_3;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void DHT11_Init(void)
{
	DHT11_SetOutputMode();
}


//主机发送开始信号
void DHT11_SendStart(void)
{
	//1.配置引脚为输出模式
	DHT11_SetOutputMode();
	
	//2.主机把引脚电平拉低,大于18ms
	GPIO_ResetBits(GPIOB,GPIO_Pin_3);
	delay_ms(20);
	
	//3.主机把引脚电平拉高，20us ~ 40us
	GPIO_SetBits(GPIOB,GPIO_Pin_3); 
	delay_us(30);
}


//主机等待DHT11响应
bool DHT11_IsACK(void)
{
	uint32_t i = 0;
	
	//1.配置DHT11引脚为输入模式
	DHT11_SetInputMode();
	
	//2.主机等待引脚被拉低 为了提高程序可靠性，所以添加超时处理 超时时间100us即可
	while( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3) == SET && i < 100 )
	{
		delay_us(1);
		i++;
	}
	
	if(i>=100)
	{
		return false; //说明未响应，原因是超时
	}
	
	//3.主机等待引脚被拉高 为了提高程序可靠性，所以添加超时处理 超时时间100us即可
	i= 0;
	while( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3) == RESET && i < 100 )
	{
		delay_us(1);
		i++;
	}
	if(i>=100)
	{
		return false; //说明未响应，原因是超时
	}
	else
		return true;  //说明已响应
}

//读取1bit数据 返回值  数字0  --> 0000 000_0  or 数字1  --> 0000 000_1
uint8_t DHT11_ReadBit(void)
{
	uint32_t i = 0;
	
	//1.主机等待低电平出现
	while( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3) == SET && i < 100 )
	{
		delay_us(1);
		i++;
	}
	
	//2.主机等待高电平出现
	i= 0;
	while( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3) == RESET && i < 100 )
	{
		delay_us(1);
		i++;
	}
	
	//3.延时一段时间 28us < x < 70us
	delay_us(40);
	
	//4.读取此时的引脚电平并直接返回
	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3);
}

//获取DHT11传感器的数据
bool DHT11_GetVal(void)
{
	int cnt = 0;
	int i = 0;

	//1.发送开始信号
	DHT11_SendStart();
	
	//2.等待DHT11响应
	if(DHT11_IsACK())
	{
		//3.循环读取40bit数据   8bit湿度整数 + 8bit湿度小数 + 8bit温度整数 + 8bit温度小数 + 8bit校验和   
		for(cnt=0;cnt<5;cnt++)
		{
			for(i=0;i<8;i++)
			{
					dhtbuf[cnt] <<= 1;
					dhtbuf[cnt] |= DHT11_ReadBit(); //MSB 高位先出  			
			}
		}
		//进行校验
		if(dhtbuf[0]+dhtbuf[1]+dhtbuf[2]+dhtbuf[3] != dhtbuf[4])
		{
			return false; //校验失败		
		}
	}
	else
	{
		return false; //没有响应
	}
	
	return true;
}