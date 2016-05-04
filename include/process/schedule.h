#ifndef __SCHEDULE_H__
#define __SCHEDULE_H_
bool monitor_flag;
void schedule_init();
uint32_t allocate_slot();
void release_slot(uint32_t);
void sch_sleep(uint32_t,uint32_t);
uint32_t change_process(uint32_t);
void start_process(uint32_t);
void monitor_call();
#endif
