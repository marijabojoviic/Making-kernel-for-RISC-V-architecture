//
// Created by os on 8/16/22.
//

#include "../h/riscv.hpp"
void Riscv::popSppSpie()
{
    __asm__ volatile("csrw sepc, ra");
    __asm__ volatile("sret");
}
void Riscv::handleSupervisorTrap() {

    uint64 volatile pc = r_sepc();
    uint64 volatile scause = r_scause();
    uint64 volatile proma4;// stack
    uint64 volatile proma3;// arg
    uint64 volatile proma2; //start routine
    uint64 volatile proma1; //handle
    uint64 volatile kod;

    __asm__ volatile  ("mv %0,a4":"=r" (proma4));
    __asm__ volatile  ("mv %0,a3":"=r" (proma3));
    __asm__ volatile  ("mv %0,a2":  "=r" (proma2));
    __asm__ volatile  ("mv %0,a1":"=r" (proma1));
    __asm__ volatile  ("mv %0,a0":"=r" (kod));

    if (scause == 0x0000000000000008UL || scause == 0x0000000000000009UL) {
        if (kod == 0x01) {
            void *volatile pointer = MemoryAllocator::mem_alloc(proma1);
            __asm__ volatile ("mv a0,%[x]": : [x] "r"(pointer));//size u a1, x nesto izmedju radi
            Riscv::w_sepc(pc + 4);


        } else if (kod == 0x02) {
            int cause = MemoryAllocator::mem_free((uint64 *) proma1);
            __asm__ volatile ("mv a0,%[x]": : [x] "r"(cause));//size u a1, x nesto izmedju radi
            Riscv::w_sepc(pc + 4);


        } else if (kod == 0x11) {
            TCB * volatile pointer = TCB::createThread((thread_t *) proma1, (TCB::Body) proma2, (void *) proma3, (void *) proma4);
            if (pointer == nullptr) {
                __asm__ volatile ("li a0,-1");
            } else {
                __asm__ volatile ("li a0,0");
            }
            Riscv::w_sepc(pc + 4);


        } else if (kod == 0x12) {
            uint64 volatile cause = TCB::deleteTCB_exit();
            if (cause < 0) {
                __asm__ volatile ("li a0,-1");

            } else {
                __asm__ volatile ("li a0,0");


            }
            Riscv::w_sepc(pc + 4);


        } else if (kod == 0x13) {
            TCB::dispatch();
            Riscv::w_sepc(pc + 4);
        } else if (kod == 0x21) {
            _sem::CreateSem((sem_t *) proma1, (unsigned) proma2);
            Riscv::w_sepc(pc + 4);
            if ((_sem *) proma3 != nullptr) {
                __asm__ volatile ("li a0,0");

            } else {
                __asm__ volatile ("li a0,-1");

            }

        } else if (kod == 0x22) {
            int kod = _sem::closeSem((sem_t) proma1);
            Riscv::w_sepc(pc + 4);
            __asm__ volatile ("mv a0,%[x]": : [x] "r"(kod));


        } else if (kod == 0x23) {
            int kod=((_sem*)proma1)->wait();
            Riscv::w_sepc(pc + 4);
            __asm__ volatile ("mv a0,%[x]": : [x] "r"(kod));

        } else if (kod == 0x24) {
          int kod=((_sem*)proma1)->signal();
            Riscv::w_sepc(pc + 4);
            __asm__ volatile ("mv a0,%[x]": : [x] "r"(kod));


        } else if (kod == 0x31) {
            int kod = TCB::thread_sleep((time_t) proma1);
            Riscv::w_sepc(pc + 4);
            __asm__ volatile ("mv a0,%[x]": : [x] "r"(kod));


        } else if (kod == 0x51) {
            Scheduler::putTh((TCB *) proma1);
            int kod = 0;
            Riscv::w_sepc(pc + 4);
            __asm__ volatile ("mv a0,%[x]": : [x] "r"(kod));

        } else if (kod == 0x52) {
            Riscv::mc_sstatus(SSTATUS_SPP);
            Riscv::w_sepc(pc + 4);


        } else if (kod == 0x41) {
            char c = __getc();
            Riscv::w_sepc(pc + 4);
            __asm__ volatile ("mv a0,%[x]": : [x] "r"((uint64)c));


        } else if (kod == 0x42) {
            __putc((char) proma1);
            Riscv::w_sepc(pc + 4);
        } else if (kod == 0x54) {
            TCB::createThread_nosch((thread_t *) proma1, (TCB::Body) proma2, (void *) proma3, (void *) proma4);
            int c = 0;
            Riscv::w_sepc(pc + 4);
            __asm__ volatile ("mv a0,%[x]": : [x] "r"(c));

        }else if(kod==0x55){
            TCB* volatile thread=(TCB*)proma1;
            thread->deleteThread();
            Riscv::w_sepc(pc + 4);


        }

    } else if (scause == 0x8000000000000001UL) {

        // interrupt: yes; cause code: supervisor software interrupt (CLINT; machine timer interrupt)

        TCB::timeSliceCounter++;
        if (TCB::timeSliceCounter >= TCB::running->getTimeSlice()) {
             //uint64 volatile sepc = r_sepc();
             uint64 volatile sstatus = r_sstatus();
             TCB::timeSliceCounter = 0;
             TCB::dispatch();
             w_sstatus(sstatus);
             w_sepc(pc);
         }
        mc_sip(SIP_SSIP);
    } else if (scause == 0x8000000000000009UL){
        console_handler();
       plic_complete(10);

    }
    else{
    }

}