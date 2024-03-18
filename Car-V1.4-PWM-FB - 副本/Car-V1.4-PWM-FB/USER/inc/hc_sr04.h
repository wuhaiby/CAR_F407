#ifndef __HC_SR04_H
#define __HC_SR04_H

#include "stm32f4xx.h" 
#include "sys.h" 
#include "delay.h"
#include "stdio.h"


//hc_sr04初始化函数的声明
void init_sr04(void);
int get_sr04_distance(void);

#endif
