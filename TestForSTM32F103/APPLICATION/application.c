#include "application.h"
#include "delay.h"
#include "beep.h"
void Task_Start(void)
{
	while(1)
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_5); //LED0�����
		OSTimeDelay(1500);
		GPIO_SetBits(GPIOB,GPIO_Pin_5);//LED0�����
		OSTimeDelay(400);
	}
}

void LEDlight(void)
{
	while(1)
	{
		GPIO_SetBits(GPIOE,GPIO_Pin_5);//LED1�����
		OSTimeDelay(300);
		GPIO_ResetBits(GPIOE,GPIO_Pin_5);//LED1�����
		OSTimeDelay(500);
	}
}

	void Beep(void)
{
	while(1)
	{
		BEEP=0;		  
		OSTimeDelay(500);//��ʱ300ms
		BEEP=1;  
		OSTimeDelay(200);//��ʱ300ms
	}
}
