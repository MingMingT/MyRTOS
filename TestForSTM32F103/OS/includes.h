#ifndef  __INCLUDES_H__
#define  __INCLUDES_H__

/****************************************  ���� (���Ͷ���)*********************************************************/
typedef unsigned char  BOOLEAN;
typedef unsigned char  INT8U;                    /* Unsigned  8 bit quantity                           */
typedef signed   char  INT8S;                    /* Signed    8 bit quantity                           */
typedef unsigned short INT16U;                   /* Unsigned 16 bit quantity                           */
typedef signed   short INT16S;                   /* Signed   16 bit quantity                           */
typedef unsigned int   INT32U;                   /* Unsigned 32 bit quantity                           */
typedef signed   int   INT32S;                   /* Signed   32 bit quantity                           */
typedef float          FP32;                     /* Single precision floating point                    */
typedef double         FP64;                     /* Double precision floating point                    */
typedef unsigned char  uchar;
typedef unsigned short uint16;
typedef unsigned int   OS_STK;
typedef unsigned int   uint32;
typedef unsigned int   OS_STK;                   /* Each stack entry is 32-bit wide                    */
typedef unsigned int   OS_CPU_SR;                /* Define size of CPU status register (PSR = 32 bits) */
typedef unsigned char  BOOLEAN;
typedef unsigned char  INT8U; 
typedef unsigned short  INT16U; 
typedef unsigned int   INT32U;    
typedef unsigned int   STK;
#define   FALSE                                              0//����
#define   TURE                                               1//�ɹ�   
/****************************************************************************************************************/




/****************************************�����ٽ�������**********************************************************/
#define  OS_ENTER_CRITICAL()  {cpu_sr = OS_CPU_SR_Save();}  //�������ٽ���
#define  OS_EXIT_CRITICAL()   {OS_CPU_SR_Restore(cpu_sr);}  //����˳��ٽ���
OS_CPU_SR  OS_CPU_SR_Save(void);
void       OS_CPU_SR_Restore(OS_CPU_SR cpu_sr);
/****************************************************************************************************************/




/****************************************�����������**********************************************************/
#define  STARTUP_TASK_START_STK_SIZE                         80//��ջ��С��Ϊ80
#define  LOWEST_PRIO                                         7 //������ȼ�7
#define  MAX_TASK                                            8 //�����������    
#define  ARG_CHK_EN                                          1//�Ƿ�������ȼ���Ч���
/****************************************************************************************************************/

/***************************************************״̬��**********************************************************/
#define  STAT_RDY  0x00;//����̬
#define  STAT_SUSPEND 0x01//����
#define  STAT_WITE 0x02//�ȴ�
/****************************************************************************************************************/



/***************************************************TCB�鶨��**********************************************************/
typedef struct tcb
{
	STK        *TCBStkPtr;        //��ǰ��ջָ��
	INT8U       TCBStat;          //���������״̬��
	INT8U       TCBPrio;          //������������ȼ� 
	INT16U      TCBDly;           //������������ȴ�ʱ��������
	INT8U       TCBused;
}TCB;
/****************************************************************************************************************/


extern TCB *TCBPrioTbl[LOWEST_PRIO + 1];
extern INT8U PrioCur;//��ǰ�������ȼ�
extern INT8U PrioHighRdy;//������ȼ�
extern INT8U Running;  //ϵͳ���б�־
extern TCB  *TCBHighRdy; //ָ��ǰ������ȼ���TCBָ�룬�������
extern TCB  *TCBCur;//��ǰ���ȼ�����ĵ�ַ��
extern STK TaskIdleStk[80];  //���������ջ

///////////////////////////////////////////////////////////////////////
//core.c
void  Init (void);//��ʼ������
INT8U TCBInit(INT8U prio, STK *ptos, STK *pbos);
void  Start (void);
void SchedNew(void);
void Task_IDLE(void);
void TaskSwHook(void);
//task.c
INT8U TaskCreate(void (*task)(), STK *ptos, INT8U prio);
INT8U  TaskSuspend (INT8U prio);
void TCBinit(void);
void Sched(void);
//cpu.c
STK *TaskStkInit (void (*task)(),STK *ptos);

////////////////////////////////////////////////////////////////////////
#endif
