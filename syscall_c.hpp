//
// Created by os on 9/8/22.
//

#ifndef PROJECT_BASE_V1_1_SYSCALL_C_HPP
#define PROJECT_BASE_V1_1_SYSCALL_C_HPP
#include "../lib/hw.h"

class TCB;
class _sem;
typedef unsigned long time_t;
typedef _sem* sem_t;
typedef TCB* thread_t;
const int EOF=-1;
int sem_open (sem_t* handle,unsigned init);//ox21
int sem_close(sem_t handle);
int sem_signal(sem_t handle);
int sem_wait(sem_t handle);
void* mem_alloc (size_t size); //prima u bajtovima
int mem_free (void* pointer);
int time_sleep (time_t);
int thread_create (thread_t* handle,void(*start_routine)(void*),void* arg); //ox11
int thread_exit (); //ox12
void thread_dispatch ();//ox13
int thread_create_nosch(thread_t* handle,void(*start_routine)(void*),void*arg);
int thread_start(void*arg);
void change_sstatus();
char getc();
void putc(char);
void deleteThread(thread_t myhandle);
#endif //PROJECT_BASE_V1_1_SYSCALL_C_HPP
