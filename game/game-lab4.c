#include "include/common/common.h"
#include "include/common/printkex.h"
#include "include/sys/display.h"
#include "include/common/rvgs.h"
#include "include/sys/input.h"
#include "include/sys/output.h"
#include "include/sys/process.h"

int main()
{
//	ioinit();
	output_ex("it's the start of Jerry's game, enjoy it\n");
	output_ex("gogo\n");
	printkex("init game pass\n");
	uint32_t a=open_semaphore();
	uint32_t consumer=a;
	printkex("get lock %x a%x\n",consumer,a);
	uint32_t i=fork();
	printkex("i'm process %x",i);
//	uint32_t mutex=open_semaphore();
	
//	int i1,i2=0;
//	int i=forkex();
	while (1)
	{
//		sem_wait(mutex);
		//printkex("i'm alive %x lock %x a %x\n",i,consumer,a);
		if (i==1) {	 //consumer
			printkex("one consumer wait for product\n");
			sem_wait(consumer);
		}
		else
		{
			printkex("one product is produced\n");
			sem_post(consumer);
			sleep(1000);
		}
//		sem_post(mutex);
	}
	return 0;
}
