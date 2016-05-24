#include "include/common/common.h"
#ifndef __PROCESS_H__
#define __PROCESS_H__

void exit();
void sleep(uint32_t time);//time
uint32_t open_semaphore();
void sem_wait(uint32_t);
void sem_post(uint32_t);


uint32_t fork();
uint32_t forkex();
void lock(int*);
void unlock(int*);
#endif
