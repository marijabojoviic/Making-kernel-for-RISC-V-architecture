//
// Created by os on 8/24/22.
//
#include "../h/_sem.hpp"
void _sem::CreateSem(sem_t *handle, unsigned int init) {
    _sem* sem=(_sem*) MemoryAllocator::mem_alloc(sizeof(_sem));
    *handle=sem;
    sem->count=init;
    sem->blocked= (List<TCB>*)MemoryAllocator::mem_alloc(sizeof(List<TCB>));
    sem->blocked->head= nullptr;
    sem->blocked->tail= nullptr;
}
int _sem::closeSem(sem_t handle){
    if(handle==nullptr) return -1;
    TCB* tcb=handle->blocked->removeFirst();
    while(tcb!=nullptr){
        Scheduler::putTh(tcb);
        (tcb)->kodizlaska=-1;
        tcb=handle->blocked->removeFirst();

    }
    return 0;
}

int _sem::wait(){
    if((--(count))<0) {
        TCB* old=TCB::running;
        blocked->addLast(old);
        TCB::running->blokirana=true;
        TCB::dispatch();
        TCB::running->blokirana=false;
    }
    return TCB::running->kodizlaska;

}
int _sem::signal(){
    if((++(count))<=0) {
        TCB* thread=blocked->removeFirst();
        if(thread){
            thread->blokirana=false;
            Scheduler::putTh(thread);}
    }
    return 0;
}
