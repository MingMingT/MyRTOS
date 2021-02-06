#include "includes.h"


TCB *TCBPrioTbl[LOWEST_PRIO + 1];
INT8U PrioCur;//当前任务优先级
INT8U PrioHighRdy;//最高优先级
INT8U Running;
TCB  *TCBHighRdy; //指向当前最高优先级的TCB指针，方便调用
//INT8U TCBRdyGrope;//TCB就绪表
INT8U TCBSuspendGrope;//TCB挂起表
TCB  *TCBCur;//当前优先级任务的地址，方便保存寄存器信息
STK TaskIdleStk[STARTUP_TASK_START_STK_SIZE];  //空闲任务堆栈
extern void StartHighRdy(void);

/******************初始化TCB块*********************/
TCB TCBA;
TCB TCBB;
TCB TCBC;
TCB TCBD;
TCB TCBE;
TCB TCBF;
TCB TCBG;
TCB TCBH;


void  Init (void)//初始化函数
{
	TCBinit();
	//进行空闲TCB初始化
	TaskCreate(Task_IDLE,&TaskIdleStk[STARTUP_TASK_START_STK_SIZE-1],LOWEST_PRIO);//优先级设为最低优先级
}

void TCBinit(void)
{
	/******************让指针指向TCB块*********************/
	TCBPrioTbl[0]=&TCBA;
	TCBPrioTbl[1]=&TCBB;
	TCBPrioTbl[2]=&TCBC;
	TCBPrioTbl[3]=&TCBD;
	TCBPrioTbl[4]=&TCBE;
	TCBPrioTbl[5]=&TCBF;
	TCBPrioTbl[6]=&TCBG;
	TCBPrioTbl[7]=&TCBH;
	
	/******************给TCB块赋初值*********************/
	TCBPrioTbl[0]->TCBStkPtr = (STK *)0; //TCBA  空闲任务
	TCBPrioTbl[0]->TCBPrio = 0;
	TCBPrioTbl[0]->TCBStat = 0;
	TCBPrioTbl[0]->TCBDly = 0;
	TCBPrioTbl[0]->TCBused = 0;
	
	TCBPrioTbl[1]->TCBStkPtr = (STK *)0; //TCBB
	TCBPrioTbl[1]->TCBPrio = 0;
	TCBPrioTbl[1]->TCBStat = 0;
	TCBPrioTbl[1]->TCBDly = 0;
	TCBPrioTbl[1]->TCBused = 0;
	
	TCBPrioTbl[2]->TCBStkPtr = (STK *)0; //TCBC
	TCBPrioTbl[2]->TCBPrio = 0;
	TCBPrioTbl[2]->TCBStat = 0;
	TCBPrioTbl[2]->TCBDly = 0;
	TCBPrioTbl[2]->TCBused = 0;
	
	TCBPrioTbl[3]->TCBStkPtr = (STK *)0; //TCBD
	TCBPrioTbl[3]->TCBPrio = 0;
	TCBPrioTbl[3]->TCBStat = 0;
	TCBPrioTbl[3]->TCBDly = 0;
	TCBPrioTbl[3]->TCBused = 0;
	
	TCBPrioTbl[4]->TCBStkPtr =(STK *) 0; //TCBE
	TCBPrioTbl[4]->TCBPrio = 0;
	TCBPrioTbl[4]->TCBStat = 0;
	TCBPrioTbl[4]->TCBDly = 0;
	TCBPrioTbl[4]->TCBused = 0;
	
	TCBPrioTbl[5]->TCBStkPtr = (STK *)0; //TCBF
	TCBPrioTbl[5]->TCBPrio = 0;
	TCBPrioTbl[5]->TCBStat = 0;
	TCBPrioTbl[5]->TCBDly = 0;
	TCBPrioTbl[5]->TCBused = 0;
	
	TCBPrioTbl[6]->TCBStkPtr = (STK *)0; //TCBG
	TCBPrioTbl[6]->TCBPrio = 0;
	TCBPrioTbl[6]->TCBStat = 0;
	TCBPrioTbl[6]->TCBDly = 0;
	TCBPrioTbl[6]->TCBused = 0;
	
	TCBPrioTbl[7]->TCBStkPtr = (STK *)0; //TCBH
	TCBPrioTbl[7]->TCBPrio = 0;
	TCBPrioTbl[7]->TCBStat = 0;
	TCBPrioTbl[7]->TCBDly = 0;
	TCBPrioTbl[7]->TCBused = 0;
}

//空闲任务
void Task_IDLE(void)
{
	while(1);
}

//任务优先级 堆栈栈顶指针  栈顶指针
INT8U TCBInit(INT8U prio, STK *ptos, STK *pbos)
{
	 TCBPrioTbl[prio]->TCBStkPtr = ptos;
	 TCBPrioTbl[prio]->TCBStat = STAT_RDY;
	 TCBPrioTbl[prio]->TCBPrio = prio;
	 TCBPrioTbl[prio]->TCBDly = 0x00;
	 TCBPrioTbl[prio]->TCBused = 1;
	 return TURE;
}


void  Start (void)
{
	  
    if (Running == FALSE) 
		{
			 SchedNew();//找到最高优先级
			 PrioCur = PrioHighRdy;//最高优先级赋值给当前优先级
			 TCBHighRdy = TCBPrioTbl[PrioHighRdy];//最高优先级地址赋值给TCBHighRdy
			 TCBCur = TCBHighRdy;
			 StartHighRdy();//进行汇编调度（将寄存器里面的内容放入到CPU中进行运行）
    }
}
//寻找最高优先级
void SchedNew(void)
{
	int i;
	for(i=0;i<8;i++)
	{
		if(TCBPrioTbl[i]->TCBused ==1 && TCBPrioTbl[i]->TCBStat == 0x00)
		{
			PrioHighRdy = i;
			break;
		}
	}
}



void TaskSwHook()
{
	
}


