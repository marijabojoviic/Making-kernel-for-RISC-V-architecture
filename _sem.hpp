//
// Created by os on 8/24/22.
//

#ifndef PROJECT_BASE_V1_1__SEM_HPP
#define PROJECT_BASE_V1_1__SEM_HPP
#include "../h/syscall_c.hpp"
#include "../h/list.hpp"
#include "../h/tcb.hpp"
#include "../h/riscv.hpp"

class _sem{
private:
    List<TCB>* blocked;
    int count;
public:
    _sem(int count){
        this->count=count;
        this->blocked= (List<TCB>*)MemoryAllocator::mem_alloc(sizeof(List<TCB>));
        blocked->head= nullptr;
        blocked->tail= nullptr;
    }
    void *operator new(size_t size) {
        return MemoryAllocator::mem_alloc(size);
    }

    void operator delete(void *ptr){
        MemoryAllocator::mem_free(ptr);
    }
    static void CreateSem(sem_t* handle,unsigned init);
    static int closeSem(sem_t handle);
    int wait();
    int signal();

};

#endif //PROJECT_BASE_V1_1__SEM_HPP
