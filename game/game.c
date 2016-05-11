#include "include/common/common.h"
#include "include/common/printkex.h"
#include "include/sys/display.h"
#include "include/common/rvgs.h"
#include "include/sys/input.h"
#include "include/sys/output.h"
#include "include/sys/process.h"
#include "include/process/pcb.h"

int main()
{
//	ioinit();
	output_ex("it's the start of Jerry's game, enjoy it\n");
	output_ex("gogo\n");
	printkex("init game pass\n");
	int i1,i2=0;
	int i=forkex();
	while (1)
	{
		lock(&i1);
		if (i==1)
		{
			lock(&i2);
			printkex("poduct\n");
			unlock(&i2);
		}
		else
		{
			lock(&i2);
			printkex("consumer\n");
			unlock(&i2);
		}
		unlock(&i1);
		unlock(&i);
	}
	return 0;
}
