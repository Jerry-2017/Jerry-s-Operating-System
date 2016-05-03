#include "include/common/common.h"
#include "include/common/printk.h"
#include "include/common/common.h"
#include "include/device/int.h"
#include "include/device/x86.h"
#define PORT_CH_0 0x40
#define PORT_CMD 0x43
#define PIT_FREQUENCE 1193182
#define HZ 100

#define MAX_WAKEUP 100
unsigned int tm_cnt=0;
bool test_serv=1;

static void (*wakeupstack [MAX_WAKEUP])(uint32_t);
static int wakeupl=0;
uint32_t wakeupreg(void (*func)(uint32_t))
{
	if (wakeupl>=MAX_WAKEUP)
	{
		printk("Error in src.sys.timer.c, Wakeup Overstack\n");
		return false;
	}
	wakeupstack[wakeupl++]=(void*)func;
	return true;
}

void wakeup()
{
	int i;
	for (i=0;i<wakeupl;i++)
		(*wakeupstack[i])(tm_cnt);
}

void timer_serv()
{
	if (test_serv)
	{
		printk("timer int recv\n");
		tm_cnt=0;
		test_serv=0;
	}
	wakeup();
	tm_cnt++;
}

union CmdByte {
  struct {
    uint8_t present_mode : 1;
    uint8_t operate_mode : 3;
    uint8_t access_mode  : 2;
    uint8_t channel      : 2;
  };
  uint8_t val;
};

union CmdByte mode = {
  .present_mode = 0,  // 16-bit binary
  .operate_mode = 2,  // rate generator, for more accuracy
  .access_mode  = 3,  // low byte / high byte, see below
  .channel      = 0,  // use channel 0
};
void timer_init()
{
	int counter = PIT_FREQUENCE / HZ;
	outb(PORT_CMD, mode.val);
	outb(PORT_CH_0, counter & 0xFF);         // access low byte
	outb(PORT_CH_0, (counter >> 8) & 0xFF);  // access high byte
	serv_addr((uint32_t)timer_serv,0x20);
}
