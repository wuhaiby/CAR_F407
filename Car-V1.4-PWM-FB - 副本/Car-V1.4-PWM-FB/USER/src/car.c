#include "car.h"

//////////////////////////////////////////////////////////////////////////////////	 

//              ----------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////	


//电机
void Car_go_(u8 number)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct; //TIM属性结构体
	TIM_OCInitTypeDef TIM_OCInitStructure;//输出比较参数结构体
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//1.使能定时器5和GPIOE
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOA, ENABLE);
	
	//2、初始化IO口为复用功能输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; 		//选择引脚GPIOE  14
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 	//配置引脚为复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;  //速度选择最高100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 	//推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 	//上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); 	//初始化 PE，安装参数
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; 		//选择引脚GPIOE  14
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 	//配置引脚为复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;  //速度选择最高100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 	//推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 	//上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); 	//初始化 PE，安装参数
	
	//由于使用到PE的复用功能，利用库函数使其引脚与TIM14定时器
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5); 
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM5); 
	
	//3、初始化 TIM14定时器, 设置 TIM14 的装载，分频，计数模式等等
	//arr*psc = 84000000皆可，由于是从0开始，所以要减1，两者的值互换不影响
	TIM_TimeBaseStruct.TIM_Period = 100-1;//自动重装载值ARR（控制频率）
	TIM_TimeBaseStruct.TIM_Prescaler =1680-1;//定时器分频，预分频系数(一个周期多少次)，100hz=100us
	TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;//再分频，/1等于是不再分频的意思
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStruct);//初始化定时器1
	
	 //4、PWM1模式配置：通道2*/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//选择PWM的模式，选择PWM模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//开启输出的使能
	TIM_OCInitStructure.TIM_Pulse = number;//初始化配置比较寄存器(CCRx比较值)，持续时间越长，亮度就越亮
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//输出的极性，这里选择高电平有效
	
	//5、TIM5通道1初始化
	TIM_OC1Init(TIM5, &TIM_OCInitStructure);
	TIM_OC2Init(TIM5, &TIM_OCInitStructure);
	TIM_OC3Init(TIM5, &TIM_OCInitStructure);
	TIM_OC4Init(TIM5, &TIM_OCInitStructure);
	
	//6、设置自动重载CCR1（比较），不断产生PWM脉冲
	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);
	
	//7、设置自动重装载值ARR，不断产生PWM脉冲
	TIM_ARRPreloadConfig(TIM5,ENABLE);


	TIM_Cmd(TIM5,ENABLE); //使能定时器14(总开关)

	//9.使能TIM1PWM输出(高级定时器)(分开关)
	//TIM_CtrlPWMOutputs(TIM1, ENABLE);
}


void Car_back_(u8 number)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct; //TIM属性结构体
	TIM_OCInitTypeDef TIM_OCInitStructure;//输出比较参数结构体
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//1.使能定时器5和GPIOE
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOB, ENABLE);
	
	//2、初始化IO口为复用功能输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9; 		//选择引脚GPIOE  14
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 	//配置引脚为复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;  //速度选择最高100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 	//推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 	//上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure); 	//初始化 PE，安装参数
	
	//由于使用到PE的复用功能，利用库函数使其引脚与TIM14定时器
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_TIM4); 
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_TIM4); 
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_TIM4); 
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_TIM4); 
	
	//3、初始化 TIM14定时器, 设置 TIM14 的装载，分频，计数模式等等
	//arr*psc = 84000000皆可，由于是从0开始，所以要减1，两者的值互换不影响
	TIM_TimeBaseStruct.TIM_Period = 100-1;//自动重装载值ARR（控制频率）
	TIM_TimeBaseStruct.TIM_Prescaler =1680-1;//定时器分频，预分频系数(一个周期多少次)，100hz=100us
	TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;//再分频，/1等于是不再分频的意思
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStruct);//初始化定时器1
	
	 //4、PWM1模式配置：通道2*/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//选择PWM的模式，选择PWM模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//开启输出的使能
	TIM_OCInitStructure.TIM_Pulse = number;//初始化配置比较寄存器(CCRx比较值)，持续时间越长，亮度就越亮
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//输出的极性，这里选择高电平有效
	
	//5、TIM5通道1初始化
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	
	//6、设置自动重载CCR1（比较），不断产生PWM脉冲
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable); 
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable); 
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable); 
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable); 

	//7、设置自动重装载值ARR，不断产生PWM脉冲
	TIM_ARRPreloadConfig(TIM4,ENABLE);

	TIM_Cmd(TIM4,ENABLE); //使能定时器14(总开关)
}

