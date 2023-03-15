#include "../h/_sem.hpp"
extern void userMain();
void wrapper(void* arg){
    userMain();
}
int main() {
    MemoryAllocator* mem=MemoryAllocator::getInstance();
    if(mem){}
    Riscv::w_stvec((uint64) &Riscv::supervisorTrap);
    thread_t ruckaMain;
    thread_t userM;
    thread_create(&ruckaMain, nullptr, nullptr);
    thread_create(&userM, wrapper,nullptr);
    TCB::running = (TCB *) (ruckaMain);
     //Riscv::ms_sstatus(Riscv::SSTATUS_SIE);
    while(ruckaMain->isFinished()==false){
        thread_dispatch();

    }

    deleteThread(userM);
    deleteThread(ruckaMain);
    return 0;
}