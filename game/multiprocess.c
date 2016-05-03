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
	output_ex("init game pass\n");
	while (1)
	{
		sleep(500);
	}
	return 0;
}
