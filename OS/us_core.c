#include "includes.h"


TCB *TCBPrioTbl[LOWEST_PRIO + 1];
INT8U PrioCur;//��ǰ�������ȼ�
INT8U PrioHighRdy;//������ȼ�
INT8U Running;
TCB  *TCBHighRdy; //ָ��ǰ������ȼ���TCBָ�룬�������
//INT8U TCBRdyGrope;//TCB������
INT8U TCBSuspendGrope;//TCB�����
TCB  *TCBCur;//��ǰ���ȼ�����ĵ�ַ�����㱣��Ĵ�����Ϣ
STK TaskIdleStk[STARTUP_TASK_START_STK_SIZE];  //���������ջ
extern void StartHighRdy(void);

/******************��ʼ��TCB��*********************/
TCB TCBA;
TCB TCBB;
TCB TCBC;
TCB TCBD;
TCB TCBE;
TCB TCBF;
TCB TCBG;
TCB TCBH;


void  Init (void)//��ʼ������
{
	TCBinit();
	//���п���TCB��ʼ��
	TaskCreate(Task_IDLE,&TaskIdleStk[STARTUP_TASK_START_STK_SIZE-1],LOWEST_PRIO);//���ȼ���Ϊ������ȼ�
}

void TCBinit(void)
{
	/******************��ָ��ָ��TCB��*********************/
	TCBPrioTbl[0]=&TCBA;
	TCBPrioTbl[1]=&TCBB;
	TCBPrioTbl[2]=&TCBC;
	TCBPrioTbl[3]=&TCBD;
	TCBPrioTbl[4]=&TCBE;
	TCBPrioTbl[5]=&TCBF;
	TCBPrioTbl[6]=&TCBG;
	TCBPrioTbl[7]=&TCBH;
	
	/******************��TCB�鸳��ֵ*********************/
	TCBPrioTbl[0]->TCBStkPtr = (STK *)0; //TCBA  ��������
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

//��������
void Task_IDLE(void)
{
	while(1);
}

//�������ȼ� ��ջջ��ָ��  ջ��ָ��
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
			 SchedNew();//�ҵ�������ȼ�
			 PrioCur = PrioHighRdy;//������ȼ���ֵ����ǰ���ȼ�
			 TCBHighRdy = TCBPrioTbl[PrioHighRdy];//������ȼ���ַ��ֵ��TCBHighRdy
			 TCBCur = TCBHighRdy;
			 StartHighRdy();//���л����ȣ����Ĵ�����������ݷ��뵽CPU�н������У�
    }
}
//Ѱ��������ȼ�
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


