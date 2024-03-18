#include "car_turn.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//  �� �� ��   : car_turn.c
//  �� �� ��   : v2.1
//  ��    ��   : HuangFei
//  ��������   : 2018-0403
//  ����޸�   : 
//  ��������   : С����ת����ʾ����(STM32F407VEϵ��SPI)
//              ˵��: 
//******************************************************************************/


void Car_go(void)
{	
	TIM_SetCompare1(TIM5, 0);	//ǰ��   ��
	TIM_SetCompare2(TIM5, 80);//ǰ��   ǰ
	
	TIM_SetCompare3(TIM5, 80);//ǰ��   ǰ
	TIM_SetCompare4(TIM5, 0);	//ǰ��   ��
				
	TIM_SetCompare1(TIM4, 80);//����   ǰ
	TIM_SetCompare2(TIM4, 0); //����   ��
	
	TIM_SetCompare3(TIM4, 80);//����   ǰ
	TIM_SetCompare4(TIM4, 0); //����   ��			
}

void Car_back(void)
{
	TIM_SetCompare1(TIM5, 80);	//ǰ��   ��
	TIM_SetCompare2(TIM5, 0);		//ǰ��   ǰ
	
	TIM_SetCompare3(TIM5, 0);		//ǰ��   ǰ
	TIM_SetCompare4(TIM5, 80);	//ǰ��   ��
				
	TIM_SetCompare1(TIM4, 0);		//����   ǰ
	TIM_SetCompare2(TIM4, 80); 	//����   ��
	
	TIM_SetCompare3(TIM4, 00);	//����   ǰ
	TIM_SetCompare4(TIM4, 80); 	//����   ��		
}

void Car_stop(void)
{
	TIM_SetCompare1(TIM5, 50);	//ǰ��   ��
	TIM_SetCompare2(TIM5, 50);	//ǰ��   ǰ
	
	TIM_SetCompare3(TIM5, 50);	//ǰ��   ǰ
	TIM_SetCompare4(TIM5, 50);	//ǰ��   ��
				
	TIM_SetCompare1(TIM4, 50);	//����   ǰ
	TIM_SetCompare2(TIM4, 50);  //����   ��
	
	TIM_SetCompare3(TIM4, 50);	//����   ǰ
	TIM_SetCompare4(TIM4, 50);  //����   ��		
}

void Car_go_left_turn(void)
{
	TIM_SetCompare1(TIM5, 100);	//ǰ��   ��
	TIM_SetCompare2(TIM5, 0);//ǰ��   ǰ
	
	TIM_SetCompare3(TIM5, 100);//ǰ��   ǰ
	TIM_SetCompare4(TIM5, 0);	//ǰ��   ��
				
	TIM_SetCompare1(TIM4, 0);//����   ǰ
	TIM_SetCompare2(TIM4, 100); //����   ��
	
	TIM_SetCompare3(TIM4, 80);//����   ǰ
	TIM_SetCompare4(TIM4, 0); //����   ��		

}

void Car_go_right_turn(void)
{
	TIM_SetCompare1(TIM5, 0);	//ǰ��   ��
	TIM_SetCompare2(TIM5, 100);//ǰ��   ǰ
	
	TIM_SetCompare3(TIM5, 0);//ǰ��   ǰ
	TIM_SetCompare4(TIM5, 100);	//ǰ��   ��
				
	TIM_SetCompare1(TIM4, 100);//����   ǰ
	TIM_SetCompare2(TIM4, 0); //����   ��
	
	TIM_SetCompare3(TIM4, 0);//����   ǰ
	TIM_SetCompare4(TIM4, 100); //����   ��		
}

