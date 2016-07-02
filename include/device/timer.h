#ifndef __TIMER_H__
#define __TIMER_H__
unsigned int tm_cnt;
void timer_init();
uint32_t wakeupreg(void (*func)(uint32_t));
#endif
