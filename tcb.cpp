//
// Created by os on 8/17/22.
//
#include "../h/tcb.hpp"

TCB *TCB::running = nullptr;
List<TCB> TCB::sleepingList;
uint64 TCB::timeSliceCounter = 0;
int TCB::brojac=0;



TCB *TCB::createThread(thread_t *handle,Body body,void* arg,void* stack)
{TCB* tcb=(TCB*)(MemoryAllocator::mem_alloc(sizeof(TCB)));
    if (body != nullptr) { Scheduler::putTh(tcb); }
    brojac++;
    setArgs(tcb,body,arg,stack);
    *handle=tcb;
    return tcb;
}
TCB *TCB::createThread_nosch(thread_t *handle, TCB::Body body, void *arg, void *stack) {
    TCB* tcb=(TCB*)(MemoryAllocator::mem_alloc(sizeof(TCB)));
    brojac++;
    setArgs(tcb,body,arg,stack);
    *handle=tcb;
    return tcb;
}
int TCB::deleteTCB_exit(){
   running->setFinished(true);
   dispatch();
   return 0;
}
void TCB::setArgs(TCB* tcb,Body body,void* arg,void*st){
    tcb->body=body;
    tcb->stack=(tcb->body!=nullptr?(uint64*)st:nullptr);
    if(tcb->stack==nullptr){
        MemoryAllocator::mem_free(st);
    }
    tcb->context.ra=(uint64)&threadWrapper;
    tcb->context.sp=tcb->stack != nullptr ? (uint64) &tcb->stack[STACK_SIZE] : 0;
    tcb->finished=false;
    tcb->arg=arg;
    tcb->kodizlaska=0;
    tcb->timeSlice=TIME_SLICE;
    tcb->blokirana=false;
    tcb->uspavana=false;
}
void TCB::dispatch()
{TCB *old = running;
    if (!old->isFinished()&&!old->blokirana&&!old->uspavana) Scheduler::putTh(old);
    running = Scheduler::getTh();
    if(brojac==1){
        running->finished=true;
    }
    TCB::contextSwitch(&old->context, &running->context);

}
void TCB::deleteThread() {
    MemoryAllocator::mem_free(stack);
}
void TCB::threadWrapper()
{change_sstatus();
    running->body(running->arg);
    running->setFinished(true);
    brojac--;
    thread_dispatch();

}
int TCB::thread_sleep(time_t time) {
    running->Sleepingtime=time;
    running->uspavana=true;
    sleepingList.addLast(TCB::running);
    dispatch();
    running->uspavana=false;
    return 0;

}

