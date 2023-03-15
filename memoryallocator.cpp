//
// Created by os on 8/16/22.
//
#include "../h/memoryallocator.hpp"
uint64 MemoryAllocator::freespace=((uint64)HEAP_END_ADDR -1 - (uint64)HEAP_START_ADDR);
MemoryAllocator* MemoryAllocator::instance=nullptr;
MemBlock* MemoryAllocator::Freehead=(MemBlock*)HEAP_START_ADDR;
MemBlock* MemoryAllocator::head=nullptr;

void* MemoryAllocator::mem_alloc(size_t size) {
    //uint64 brblk = size / MEM_BLOCK_SIZE;
    //if (size % MEM_BLOCK_SIZE != 0)brblk++;
    uint64 pom = sizeof(MemBlock) / MEM_BLOCK_SIZE;
    uint64 brblk=size;
    if (sizeof(MemBlock) % MEM_BLOCK_SIZE != 0)pom++;
    if (freespace < (brblk + pom) * MEM_BLOCK_SIZE)return nullptr;
    if (head == nullptr) {
        freespace -= (brblk + pom) * MEM_BLOCK_SIZE;
        Freehead = (MemBlock *) ((char* ) Freehead + (brblk + pom) * MEM_BLOCK_SIZE);
        Freehead->size = freespace;
        Freehead->next = nullptr;
        head = (MemBlock *) HEAP_START_ADDR;
        (head)->size = (brblk + pom) * MEM_BLOCK_SIZE;
        head->next = nullptr;
        return (MemBlock *) ((char* ) (head) + pom * MEM_BLOCK_SIZE);
    }
    else{

        MemBlock*tekFree=Freehead;
        MemBlock*prethodniFree=nullptr;
        while(tekFree!=nullptr){
            if(tekFree->size>(pom+brblk)*MEM_BLOCK_SIZE){
                break;
            }
            prethodniFree=tekFree;
            tekFree=tekFree->next;

        }

        MemBlock*tek=head;
        MemBlock*prethodni=nullptr;
        while(tek){
            prethodni=tek;
            tek=tek->next;
        }
        if(tekFree){

            freespace-=(brblk+pom)*MEM_BLOCK_SIZE;
            MemBlock* tekFreenxt=tekFree->next;
            uint64 tekFreesz=tekFree->size;
            (prethodni)->next = (tekFree);
            (prethodni)->next->size = (brblk+pom)*MEM_BLOCK_SIZE;
            prethodni->next->next=nullptr;
            tekFree=(MemBlock*)((char*)(tekFree)+MEM_BLOCK_SIZE*(brblk+pom));
            (tekFree)->size=tekFreesz-(brblk+pom)*MEM_BLOCK_SIZE;
            tekFree->next=tekFreenxt;
            if(prethodniFree){
                (prethodniFree)->next=tekFree;
            }else{
                Freehead=tekFree;

            }
            return (MemBlock*)((char*)((prethodni)->next)+pom*MEM_BLOCK_SIZE);
        }
    }


    return nullptr;


}


int MemoryAllocator::mem_free(void * pointer) {
    if(pointer==nullptr) return -1;
    pointer=(MemBlock*)pointer;
    uint64 vel=sizeof(MemBlock)/MEM_BLOCK_SIZE;
    if(sizeof (MemBlock)%MEM_BLOCK_SIZE!=0)vel++;
    pointer=(MemBlock*)((char*)pointer-vel*MEM_BLOCK_SIZE);
    if(pointer==nullptr) return -2;
    MemBlock* tek=head;
    MemBlock* pretOcc=nullptr;
   // MemBlock* poin=(MemBlock*)pointer;
    while(tek){
        if((char*)tek==(char*)(pointer)){
            break;
        }

        pretOcc=tek;
        tek=tek->next;
    }

    if(tek== nullptr) return -3;
    freespace+=tek->size;
    if(pretOcc){
        pretOcc->next=tek->next;
    }else{head=tek->next;}
    MemBlock* freeTek=Freehead;
    while(freeTek!=nullptr){
        if((char*)freeTek+freeTek->size==(char*)tek){
            freeTek->size=freeTek->size+tek->size;

            return 0;
        }
        freeTek=freeTek->next;
    }

    if(Freehead){
        tek->next=Freehead;
        Freehead=tek;
    }else{
        Freehead=tek;
        tek->next=nullptr;}
    return 0;}

