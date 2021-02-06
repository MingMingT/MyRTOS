#include "includes.h"
#include "led.h"
#include "beep.h"
#include "delay.h"
#include "application.h"


static STK startup_task_stk[STARTUP_TASK_START_STK_SIZE];
static STK LEDlight_stk[80];
static STK Beep_stk[80];
int main()
{
  delay_init();     //ʱ�ӳ�ʼ��
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	BEEP_Init();
  Init();
	TaskCreate(Task_Start,&startup_task_stk[STARTUP_TASK_START_STK_SIZE-1],1);
	TaskCreate(LEDlight,&LEDlight_stk[80-1],2);
	TaskCreate(Beep,&Beep_stk[80-1],3);
	Start();
	return 0;
}
