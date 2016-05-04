#include "include/process/pcb.h"
#include "include/device/timer.h"
#include "include/common/printk.h"
#include "include/common/common.h"
bool monitor_flag=false;
static int tp_slot=0;
static int free[MAX_PROC_NUM+2][2]; //0 prev 1 next
static int used[MAX_PROC_NUM+2][2]; //0 prev 1 next
static int status[MAX_PROC_NUM+2]; //0 running 1 sleeping 2 dead 3 waiting 4 free 5 sys
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
	}
	free[mx-1][1]=-1;
	free[0][0]=-1;
	for (i=1;i<mx;i++)
	{
		free[i][0]=i-1;
	}
	return;
}
uint32_t allocate_slot()
{
	int n=free[0][1];
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
	return n-1;
}

void release_slot(uint32_t slot)
{	
	slot+=1;
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
	if (ms<10000 && status[slot]==0)
	{
		status[slot]=1;
		sleepcnt[slot]=tm_cnt+ms;
	}
}

void start_process(uint32_t slot)
{
	status[slot]=0;
}

uint32_t change_process(uint32_t slot)
{
//	uint32_t tp1=0,tp2=0;
	tp_slot=slot;
	monitor_flag=true;
	asm("sti":::);
	while (monitor_flag);
	return tp_slot;
}

void monitor_call()
{
	int slot=used[tp_slot][1];
	if (status[slot]==3) 
		return;
	if (status[slot]==1)
	{
/*			if (tp1!=sleepcnt[slot] || tp2!=tm_cnt)
				printk("%d %d\n",sleepcnt[slot],tm_cnt);
			tp1=sleepcnt[slot];
			tp2=tm_cnt;*/
		printk("tm_cnt\n");
		if (sleepcnt[slot]<tm_cnt)
		{
			printk("sleep out\n");
			monitor_flag=false;
			status[slot]=0;
			return;	
		}
	}
	if (slot==-1) slot=0;
	tp_slot=slot;	
}
