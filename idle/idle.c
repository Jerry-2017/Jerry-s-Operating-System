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
	while (1)
	{
		sleep(1000);
		printkex("i'm alive\n");
	}
	return 0;
}
