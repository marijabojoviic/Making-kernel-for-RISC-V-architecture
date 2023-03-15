//
// Created by os on 8/17/22.
//

#ifndef PROJECT_BASE_V1_1_TCB_HPP
#define PROJECT_BASE_V1_1_TCB_HPP
#include "../lib/hw.h"
#include "../h/scheduler.hpp"
#include "../h/syscall_c.hpp"


// Thread Control Block
class TCB
{
public:
    static int deleteTCB_exit();
    static int brojac;
    static List<TCB> sleepingList;
     void deleteThread();
    ~TCB() {
        MemoryAllocator::mem_free(this->stack);
   }
    bool isFinished() const { return finished; }
    void setFinished(bool value) { finished = value; }
    uint64  getTimeSLice(){return timeSlice;}
    using Body = void (*)(void*);
    static TCB *createThread( thread_t* handle,Body body,void* arg,void*stack); //poziva thread_create
    static TCB *createThread_nosch( thread_t* handle,Body body,void* arg,void*stack); //poziva thread_create
    static TCB *running;
    int kodizlaska;
    bool uspavana;
    bool blokirana;
    static void dispatch(); //thread_dispatch ovo poziva
    static int thread_sleep(time_t time);


private:
    void *operator new(size_t size) {
        return MemoryAllocator::mem_alloc(size);
    }

    void operator delete(void *ptr){
        MemoryAllocator::mem_free(ptr);
    }
    struct Context
    {
        uint64 ra;
        uint64 sp;
    };
    TCB(Body body,void* arg,void*st)
    {   brojac++;
        this->body=body;
        this->stack=(this->body!=nullptr?(uint64*)st:nullptr);
        if(this->stack==nullptr){
            MemoryAllocator::mem_free(st);
        }
        this->context.ra=(uint64)&threadWrapper;
        this->context.sp=this->stack != nullptr ? (uint64) &this->stack[STACK_SIZE] : 0;
        this->finished=false;
        this->arg=arg;
        this->kodizlaska=0;
        this->timeSlice=TIME_SLICE;
        this->blokirana=false;
        this->uspavana=false;
    }
    static void setArgs(TCB* tcb,Body body,void* arg,void*st);
    Body body;
    uint64 *stack;
    void* arg;
    uint64 timeSlice;
    bool finished;
    time_t Sleepingtime;
    friend class Riscv;
    static void threadWrapper();
    static uint64 timeSliceCounter;
    static uint64 constexpr STACK_SIZE = 1024;
    static uint64 constexpr TIME_SLICE = 2;
    uint64 getTimeSlice() const { return timeSlice; }
    static void contextSwitch(Context *oldContext, Context *runningContext);
    Context context;





};



#endif //PROJECT_BASE_V1_1_TCB_HPP
