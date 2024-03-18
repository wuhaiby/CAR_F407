#ifndef _DHT11_H_
#define _DHT11_H_

#include <sys.h>

//配置DHT11引脚为输出模式
void DHT11_SetOutputMode(void);


//配置DHT11引脚为输入模式
void DHT11_SetInputMode(void);

void DHT11_Init(void);

//主机发送开始信号
void DHT11_SendStart(void);

//主机等待DHT11响应
bool DHT11_IsACK(void);

//读取1bit数据 返回值  数字0  --> 0000 000_0  or 数字1  --> 0000 000_1
uint8_t DHT11_ReadBit(void);

//获取DHT11传感器的数据
bool DHT11_GetVal(void);

#endif

