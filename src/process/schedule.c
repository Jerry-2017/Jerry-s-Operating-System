#include "include/process/pcb.h"
#include "include/device/timer.h"
#include "include/common/printk.h"
#include "include/common/common.h"
#include "include/common/printkex.h"
#include "include/sys/output.h"
#include "include/process/semaphore.h"

uint32_t idle_no;
static int tp_slot=0;

static int free[MAX_PROC_NUM+2][2]; //0 prev 1 next
static int used[MAX_PROC_NUM+2][2]; //0 prev 1 next
static int status[MAX_PROC_NUM+2]; //0 running 1 sleeping 2 dead 3 waiting 4 free 5 sys 6 waiting on p
static int waitsid[MAX_PROC_NUM+2];
static uint32_t sleepcnt[MAX_PROC_NUM+2];
void schedule_init()
{
	int i;
	int mx=MAX_PROC_NUM+2;
	status[0]=5;
	status[mx-1]=5;
	for (i=1;i<mx-1;i++)
		status[i]=4;
	for (i=0;i<mx-1;i++)
	{
		free[i][1]=i+1;
		waitsid[i]=-1;
	}
	free[mx-1][1]=-1;
	free[0][0]=-1;
	for (i=1;i<mx;i++)
	{
		free[i][0]=i-1;
	}
	used[0][1]=MAX_PROC_NUM+1;
	used[0][0]=-1;
	used[MAX_PROC_NUM+1][0]=0;
	used[MAX_PROC_NUM+1][1]=-1;
	return;
}
uint32_t allocate_slot()
{
	int n=free[0][1];
//	printk("allocate %d slot\n",n);
	int nn=free[n][1];
	int un=used[0][1];
	if (nn<0) return -1;
	else
	{
		status[nn]=3;
		free[0][1]=nn;
		free[nn][0]=0;
		used[0][1]=n;
		used[n][0]=0;
		used[un][0]=n;
		used[n][1]=un;
	}
	return n;
}

void idle ()
{
	int i=0,j;
	while (1)
	{
		i=0;
		j=0;
		for (;j<100;j++)
			for (i=0;i<100000;i++);
//		printkex("I'm in idle\n");
		//output_ex("idle gogo\n");
		asm ("push %%ebx\n\tmov $0x5,%%ebx\n\tint $0x80\n\tpop %%ebx\n\tnop\n\tnop\n\tnop":::);
//		output_ex("idle gogo\n");
	}
}

void release_slot(uint32_t slot)
{	
	if (slot>0 && slot<MAX_PROC_NUM+1)
	{
		status[slot]=4;
		int p=used[slot][0],n=used[slot][1];
		used[p][1]=n;
		used[n][0]=p;
		int fn=free[0][1];
		free[0][1]=slot;
		free[slot][0]=0;
		free[slot][1]=fn;
		free[fn][0]=slot;
	}
	return;	
}

void sch_sleep(uint32_t slot,uint32_t ms)
{
	if (ms<10000)
	{
		status[slot]=1;
		sleepcnt[slot]=tm_cnt+ms;
		printk("sleep set slot:%d time:%d\n",slot,ms);
	}
}

void sch_pwait(uint32_t slot,uint32_t sid)
{
	status[slot]=6;
	waitsid[slot]=sid;
	printk("pwait set slot:%d sid:%d\n",slot,sid);
}

void set_status(uint32_t slot,uint32_t type)
{
	status[slot]=type;
}

uint32_t change_process(uint32_t slot)
{
//	uint32_t tp1=0,tp2=0;
	tp_slot=slot;
	int pslot=slot;
	while (true)
	{
		slot=used[slot][1];
		if (slot==-1) slot=0;
	//	printk("monitor %d\n",slot);
		if ((status[slot]==1 && (sleepcnt[slot]<tm_cnt)) || status[slot]==3)
		{
			//printk("%x sleep out\n",slot);
	//		monitor_flag=false;
			tp_slot=slot;
			status[slot]=0;
			return tp_slot;	
		}
		else if (status[slot]==6 && p(waitsid[slot])==1)	
		{
			status[slot]=0;
			tp_slot=slot;
			return tp_slot;
		}
		if (slot==pslot)
		{
			return idle_no;
		}
	}
}
