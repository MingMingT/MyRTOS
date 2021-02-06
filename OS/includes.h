#ifndef  __INCLUDES_H__
#define  __INCLUDES_H__

/****************************************  方言 (类型定义)*********************************************************/
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
#define   FALSE                                              0//错误
#define   TURE                                               1//成功   
/****************************************************************************************************************/




/****************************************进出临界区代码**********************************************************/
#define  OS_ENTER_CRITICAL()  {cpu_sr = OS_CPU_SR_Save();}  //汇编进入临界区
#define  OS_EXIT_CRITICAL()   {OS_CPU_SR_Restore(cpu_sr);}  //汇编退出临界区
OS_CPU_SR  OS_CPU_SR_Save(void);
void       OS_CPU_SR_Restore(OS_CPU_SR cpu_sr);
/****************************************************************************************************************/




/****************************************任务情况定义**********************************************************/
#define  STARTUP_TASK_START_STK_SIZE                         80//堆栈大小定为80
#define  LOWEST_PRIO                                         7 //最低优先级7
#define  MAX_TASK                                            8 //最大任务数量    
#define  ARG_CHK_EN                                          1//是否进行优先级有效检查
/****************************************************************************************************************/

/***************************************************状态字**********************************************************/
#define  STAT_RDY  0x00;//就绪态
#define  STAT_SUSPEND 0x01//挂起
#define  STAT_WITE 0x02//等待
/****************************************************************************************************************/



/***************************************************TCB块定义**********************************************************/
typedef struct tcb
{
	STK        *TCBStkPtr;        //当前堆栈指针
	INT8U       TCBStat;          //定义任务的状态字
	INT8U       TCBPrio;          //定义任务的优先级 
	INT16U      TCBDly;           //定义允许任务等待时的最多节拍
	INT8U       TCBused;
}TCB;
/****************************************************************************************************************/


extern TCB *TCBPrioTbl[LOWEST_PRIO + 1];
extern INT8U PrioCur;//当前任务优先级
extern INT8U PrioHighRdy;//最高优先级
extern INT8U Running;  //系统运行标志
extern TCB  *TCBHighRdy; //指向当前最高优先级的TCB指针，方便调用
extern TCB  *TCBCur;//当前优先级任务的地址。
extern STK TaskIdleStk[80];  //空闲任务堆栈

///////////////////////////////////////////////////////////////////////
//core.c
void  Init (void);//初始化函数
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
