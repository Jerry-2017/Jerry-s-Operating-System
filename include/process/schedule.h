#ifndef __SCHEDULE_H__
#define __SCHEDULE_H__
void schedule_init();
uint32_t allocate_slot();
void release_slot(uint32_t);
void sch_sleep(uint32_t,uint32_t);
#endif
