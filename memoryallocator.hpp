//
// Created by os on 8/16/22.
//


#ifndef PROJECT_BASE_V1_1_MEMORYALLOCATOR_HPP
#define PROJECT_BASE_V1_1_MEMORYALLOCATOR_HPP
#include "../lib/console.h"
#include "../lib/hw.h"
struct MemBlock{
    uint64 size; //velicina bloka
    MemBlock* next;

};
class MemoryAllocator{
public:
    static MemBlock* head;
    static MemBlock* Freehead;
    static uint64 freespace;
    static void* mem_alloc(size_t size);
    static int mem_free(void*);
    static MemoryAllocator* getInstance(){
        if(instance==nullptr){
            MemoryAllocator memalloc;
            instance=&memalloc;
            return instance;
        }else{
            return instance;
        }
    }
private:
    static MemoryAllocator* instance;
    static MemoryAllocator* memalloc;
    MemoryAllocator(){
        freespace=((uint64)HEAP_END_ADDR-1 - (uint64)HEAP_START_ADDR);
        Freehead=(MemBlock*)HEAP_START_ADDR;
        Freehead->next= nullptr;
        Freehead->size=freespace;
        head= nullptr;

    }
};
#endif //PROJECT_BASE_V1_1_MEMORYALLOCATOR_HPP
