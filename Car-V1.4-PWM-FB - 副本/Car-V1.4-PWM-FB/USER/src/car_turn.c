#include "car_turn.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//  文 件 名   : car_turn.c
//  版 本 号   : v2.1
//  作    者   : HuangFei
//  生成日期   : 2018-0403
//  最近修改   : 
//  功能描述   : 小车各转向演示例程(STM32F407VE系列SPI)
//              说明: 
//******************************************************************************/


void Car_go(void)
{	
	TIM_SetCompare1(TIM5, 0);	//前右   后
	TIM_SetCompare2(TIM5, 80);//前右   前
	
	TIM_SetCompare3(TIM5, 80);//前左   前
	TIM_SetCompare4(TIM5, 0);	//前左   后
				
	TIM_SetCompare1(TIM4, 80);//后左   前
	TIM_SetCompare2(TIM4, 0); //后左   后
	
	TIM_SetCompare3(TIM4, 80);//后右   前
	TIM_SetCompare4(TIM4, 0); //后右   后			
}

void Car_back(void)
{
	TIM_SetCompare1(TIM5, 80);	//前右   后
	TIM_SetCompare2(TIM5, 0);		//前右   前
	
	TIM_SetCompare3(TIM5, 0);		//前左   前
	TIM_SetCompare4(TIM5, 80);	//前左   后
				
	TIM_SetCompare1(TIM4, 0);		//后左   前
	TIM_SetCompare2(TIM4, 80); 	//后左   后
	
	TIM_SetCompare3(TIM4, 00);	//后右   前
	TIM_SetCompare4(TIM4, 80); 	//后右   后		
}

void Car_stop(void)
{
	TIM_SetCompare1(TIM5, 50);	//前右   后
	TIM_SetCompare2(TIM5, 50);	//前右   前
	
	TIM_SetCompare3(TIM5, 50);	//前左   前
	TIM_SetCompare4(TIM5, 50);	//前左   后
				
	TIM_SetCompare1(TIM4, 50);	//后左   前
	TIM_SetCompare2(TIM4, 50);  //后左   后
	
	TIM_SetCompare3(TIM4, 50);	//后右   前
	TIM_SetCompare4(TIM4, 50);  //后右   后		
}

void Car_go_left_turn(void)
{
	TIM_SetCompare1(TIM5, 100);	//前右   后
	TIM_SetCompare2(TIM5, 0);//前右   前
	
	TIM_SetCompare3(TIM5, 100);//前左   前
	TIM_SetCompare4(TIM5, 0);	//前左   后
				
	TIM_SetCompare1(TIM4, 0);//后左   前
	TIM_SetCompare2(TIM4, 100); //后左   后
	
	TIM_SetCompare3(TIM4, 80);//后右   前
	TIM_SetCompare4(TIM4, 0); //后右   后		

}

void Car_go_right_turn(void)
{
	TIM_SetCompare1(TIM5, 0);	//前右   后
	TIM_SetCompare2(TIM5, 100);//前右   前
	
	TIM_SetCompare3(TIM5, 0);//前左   前
	TIM_SetCompare4(TIM5, 100);	//前左   后
				
	TIM_SetCompare1(TIM4, 100);//后左   前
	TIM_SetCompare2(TIM4, 0); //后左   后
	
	TIM_SetCompare3(TIM4, 0);//后右   前
	TIM_SetCompare4(TIM4, 100); //后右   后		
}

