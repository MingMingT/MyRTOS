#include "includes.h"

extern void CtxSw(void);

INT8U TaskCreate(void (*task)(), STK *ptos, INT8U prio)
{
	  STK    *psp;
    INT8U      err;
#if ARG_CHK_EN > 0
    if (prio > LOWEST_PRIO) {             /* Make sure priority is within allowable range*/           
        return (FALSE);
    }
#endif
		if (TCBPrioTbl[prio]->TCBused == 0) 
		{	 
			  TCBPrioTbl[prio]->TCBused=1;
		}
		else
		{
			return FALSE;
		}
		
		psp = TaskStkInit(task, ptos);
		err = TCBInit(prio, psp, (STK *)0);
		if(err == TURE)
		{
			 if (Running != FALSE) 
			{
				Sched();
			}
	  }
		return err;
}


//////////////////////////////////////

void Sched(void)
{
	SchedNew();
	if(PrioHighRdy != PrioCur) 
		{
			TCBHighRdy = TCBPrioTbl[PrioHighRdy];
			CtxSw();
		}
}




