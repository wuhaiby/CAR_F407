#include "car.h"

//////////////////////////////////////////////////////////////////////////////////	 

//              ----------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////	


//���
void Car_go_(u8 number)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct; //TIM���Խṹ��
	TIM_OCInitTypeDef TIM_OCInitStructure;//����Ƚϲ����ṹ��
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//1.ʹ�ܶ�ʱ��5��GPIOE
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOA, ENABLE);
	
	//2����ʼ��IO��Ϊ���ù������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; 		//ѡ������GPIOE  14
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 	//��������Ϊ���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;  //�ٶ�ѡ�����100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 	//���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 	//����
	GPIO_Init(GPIOA,&GPIO_InitStructure); 	//��ʼ�� PE����װ����
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; 		//ѡ������GPIOE  14
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 	//��������Ϊ���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;  //�ٶ�ѡ�����100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 	//���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 	//����
	GPIO_Init(GPIOA,&GPIO_InitStructure); 	//��ʼ�� PE����װ����
	
	//����ʹ�õ�PE�ĸ��ù��ܣ����ÿ⺯��ʹ��������TIM14��ʱ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5); 
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM5); 
	
	//3����ʼ�� TIM14��ʱ��, ���� TIM14 ��װ�أ���Ƶ������ģʽ�ȵ�
	//arr*psc = 84000000�Կɣ������Ǵ�0��ʼ������Ҫ��1�����ߵ�ֵ������Ӱ��
	TIM_TimeBaseStruct.TIM_Period = 100-1;//�Զ���װ��ֵARR������Ƶ�ʣ�
	TIM_TimeBaseStruct.TIM_Prescaler =1680-1;//��ʱ����Ƶ��Ԥ��Ƶϵ��(һ�����ڶ��ٴ�)��100hz=100us
	TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;//�ٷ�Ƶ��/1�����ǲ��ٷ�Ƶ����˼
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStruct);//��ʼ����ʱ��1
	
	 //4��PWM1ģʽ���ã�ͨ��2*/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//ѡ��PWM��ģʽ��ѡ��PWMģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//���������ʹ��
	TIM_OCInitStructure.TIM_Pulse = number;//��ʼ�����ñȽϼĴ���(CCRx�Ƚ�ֵ)������ʱ��Խ�������Ⱦ�Խ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//����ļ��ԣ�����ѡ��ߵ�ƽ��Ч
	
	//5��TIM5ͨ��1��ʼ��
	TIM_OC1Init(TIM5, &TIM_OCInitStructure);
	TIM_OC2Init(TIM5, &TIM_OCInitStructure);
	TIM_OC3Init(TIM5, &TIM_OCInitStructure);
	TIM_OC4Init(TIM5, &TIM_OCInitStructure);
	
	//6�������Զ�����CCR1���Ƚϣ������ϲ���PWM����
	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);
	
	//7�������Զ���װ��ֵARR�����ϲ���PWM����
	TIM_ARRPreloadConfig(TIM5,ENABLE);


	TIM_Cmd(TIM5,ENABLE); //ʹ�ܶ�ʱ��14(�ܿ���)

	//9.ʹ��TIM1PWM���(�߼���ʱ��)(�ֿ���)
	//TIM_CtrlPWMOutputs(TIM1, ENABLE);
}


void Car_back_(u8 number)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct; //TIM���Խṹ��
	TIM_OCInitTypeDef TIM_OCInitStructure;//����Ƚϲ����ṹ��
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//1.ʹ�ܶ�ʱ��5��GPIOE
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOB, ENABLE);
	
	//2����ʼ��IO��Ϊ���ù������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9; 		//ѡ������GPIOE  14
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 	//��������Ϊ���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;  //�ٶ�ѡ�����100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 	//���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 	//����
	GPIO_Init(GPIOB,&GPIO_InitStructure); 	//��ʼ�� PE����װ����
	
	//����ʹ�õ�PE�ĸ��ù��ܣ����ÿ⺯��ʹ��������TIM14��ʱ��
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_TIM4); 
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_TIM4); 
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_TIM4); 
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_TIM4); 
	
	//3����ʼ�� TIM14��ʱ��, ���� TIM14 ��װ�أ���Ƶ������ģʽ�ȵ�
	//arr*psc = 84000000�Կɣ������Ǵ�0��ʼ������Ҫ��1�����ߵ�ֵ������Ӱ��
	TIM_TimeBaseStruct.TIM_Period = 100-1;//�Զ���װ��ֵARR������Ƶ�ʣ�
	TIM_TimeBaseStruct.TIM_Prescaler =1680-1;//��ʱ����Ƶ��Ԥ��Ƶϵ��(һ�����ڶ��ٴ�)��100hz=100us
	TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;//�ٷ�Ƶ��/1�����ǲ��ٷ�Ƶ����˼
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStruct);//��ʼ����ʱ��1
	
	 //4��PWM1ģʽ���ã�ͨ��2*/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//ѡ��PWM��ģʽ��ѡ��PWMģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//���������ʹ��
	TIM_OCInitStructure.TIM_Pulse = number;//��ʼ�����ñȽϼĴ���(CCRx�Ƚ�ֵ)������ʱ��Խ�������Ⱦ�Խ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//����ļ��ԣ�����ѡ��ߵ�ƽ��Ч
	
	//5��TIM5ͨ��1��ʼ��
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	
	//6�������Զ�����CCR1���Ƚϣ������ϲ���PWM����
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable); 
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable); 
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable); 
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable); 

	//7�������Զ���װ��ֵARR�����ϲ���PWM����
	TIM_ARRPreloadConfig(TIM4,ENABLE);

	TIM_Cmd(TIM4,ENABLE); //ʹ�ܶ�ʱ��14(�ܿ���)
}

