#ifndef __SCHEDULE_H__
#define __SCHEDULE_H_
uint32_t idle_no;
void schedule_init();
uint32_t allocate_slot();
void release_slot(uint32_t);
void sch_sleep(uint32_t,uint32_t);
uint32_t change_process(uint32_t);
void set_status(uint32_t,uint32_t);
void sch_pwait(uint32_t,uint32_t);
void idle();
#endif
