#include "stm32f4xx.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "delay.h"
#include "sys.h"
#include "led.h"
#include "oled.h"
#include "hc_sr04.h"
#include "beep.h"
#include "car.h"
#include "key.h"
#include "car_turn.h"
#include "init_usart.h"
#include "MQ2.h"
#include "dht11.h"
#define MQ2 PDin(5)
void Car_Turn(void);
extern char dhtbuf[5]; //存储温湿度数据

int main(void)
{  
	DHT11_Init();		 //DHT11初始化
    
	u16 distance = 0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
		
	Systick_Init();//延时延时函数
	usart_init(115200);//串口1初始化	
	USART3_Init(9600);//串口3初始化	

	KEY_Init();	
	init_beep();
	init_sr04();


	   
	//前后同时初始化不动
	OLED_Init();			//初始化OLED  
	OLED_Clear(); 	   
	Oled_show();
    OLED_Clear(); 
    OLED_ShowString(0,4, "temp:");
    OLED_ShowString(0,6, "humi:");
    OLED_ShowString(0,0, "Derect:");
    OLED_ShowString(0,4, "temp:");
    OLED_ShowString(0,6, "humi:");
    OLED_ShowString(0,2, "MQ:");
    
    mq2_init();	
	Car_go_(50);    //TIM5 CH1 2 3 4
	Car_back_(50);  //TIM4 CH1 2 3 4
    delay_s(1);

           
		while(1)
		{
            DHT11_GetVal(); //获取一次温湿度数据
            printf("温度是 %d ℃，湿度是 %d %%RH\n",dhtbuf[2],dhtbuf[0]); //输出字符串
            //delay_ms(500);
            //delay_s(1);

            GPIO_ResetBits(GPIOA, GPIO_Pin_9);
            distance = get_sr04_distance()/10;
            printf("distance = %d cm\n",distance);
            
            OLED_ShowNum(70,0,distance,4,20);

            OLED_ShowNum(70,4,dhtbuf[2],4,20);
            OLED_ShowNum(70,6,dhtbuf[0],4,20);

            
            if(MQ2_Get() ==0 )
            {
                
                OLED_ShowString(70,2, "FLASE");
            }
            else if(MQ2_Get() ==1 ){
                OLED_ShowString(70,2, "TRUE");
            
            }
 
			//Car_Turn();
            if(data == 1)
            {
                Car_go();
                printf("GO\n");
            }
            else if(data == 2)
            {
                Car_back();
                printf("BACK\n");
            }
            else if(data == 3)
            {
                Car_go_left_turn();
                printf("LEFT\n");
            }
            else if(data == 4)
            {
                Car_go_right_turn();
                printf("RIGHT\n");
            }
            else if(data == 0)
            {
                Car_stop();
                printf("STOP\n");
            }
            
			else if(data == 8)
			{
				Car_go();
				
				if(distance <= 20 &&  distance > 5)
				{
                    
                    Car_go_left_turn();  
                    GPIO_SetBits(GPIOA, GPIO_Pin_9);
                    delay_ms(100);
//                     if(GPIO_ReadOutputDataBit(GPIOD,GPIO_Pin_5) == 1)
//                    {
//                        
//                        GPIO_SetBits(GPIOA, GPIO_Pin_9);
//                    }
				}
                else if(distance <= 5 &&  distance >= 0)
                {
                    Car_stop();
                
                }
                else
				{
                    Car_go();
                    //GPIO_ResetBits(GPIOA, GPIO_Pin_9);
                }
                

//                if(GPIO_ReadOutputDataBit(GPIOD,GPIO_Pin_5) == 1)
//                {
//                    GPIO_ResetBits(GPIOA, GPIO_Pin_9);
//                
//                }
		
            }
            
           //delay_ms(100);
        }
        
        
}
        

void Car_Turn(void)
{

}




