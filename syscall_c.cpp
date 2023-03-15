#include "../h/syscall_c.hpp"
#include "../h/_sem.hpp"

void* mem_alloc(size_t size){
    size_t volatile blokovi=size/MEM_BLOCK_SIZE;
    if(size%MEM_BLOCK_SIZE!=0) blokovi++;
    __asm__ volatile ("mv a1,%[x]": : [x] "r" (blokovi));//size u a1, x nesto izmedju radi
    __asm__ volatile ("li a0,1");//kod sis poz, li neposredna vr u reg
    __asm__ volatile ("ecall"); // poziv prek rutine
    uint64 pointer;
    __asm__ volatile("mv a0,%[x]":  [x] "=r" (pointer));
    return (void*)pointer;

}
int mem_free (void* pointer){
    __asm__ volatile ("mv a1,%[x]": : [x] "r" (pointer));
    __asm__ volatile ("li a0,0x02");
    __asm__ volatile("ecall"); // poziv prek rutine
    uint64 kod;
    __asm__ volatile("mv %[x],a0":  [x] "=r" (kod));
    return (int)kod;
}
int thread_create (thread_t* handle,void(*start_routine)(void*),void* arg){
    void* volatile pointer= mem_alloc(DEFAULT_STACK_SIZE*sizeof(uint64));
    __asm__ volatile ("mv a4,%[u]": : [u] "r" (pointer));
    __asm__ volatile ("mv a3,%[h]": : [h] "r" (arg));
    __asm__ volatile ("mv a2,%[z]": : [z] "r" (start_routine));
    __asm__ volatile ("mv a1,%[y]": : [y] "r" (handle));
    __asm__ volatile ("li a0,0x11");
    __asm__ volatile("ecall"); // poziv prek rutine
    uint64 volatile kod;
    __asm__ volatile("mv %[x],a0":  [x] "=r" (kod));
   return (int)kod;

}


int thread_exit (){
    __asm__ volatile ("li a0,0x12");
    __asm__ volatile("ecall"); // poziv prek rutine
    uint64 kod;
    __asm__ volatile("mv %[x],a0":  [x] "=r" (kod));
    return (int)kod;
}
void thread_dispatch (){
    __asm__ volatile ("li a0,0x13");
    __asm__ volatile("ecall"); // poziv prek rutin
    return;
}
int sem_open (sem_t* handle,unsigned init){
    __asm__ volatile ("mv a2,%[z]": : [z] "r" (init));
    __asm__ volatile ("mv a1,%[y]": : [y] "r" (handle));
    __asm__ volatile ("li a0,0x21");
    __asm__ volatile("ecall"); // poziv prek rutine
    uint64 kod;
    __asm__ volatile("mv %[x],a0":  [x] "=r" (kod));
    return (int)kod;


}
int sem_close(sem_t handle){
    __asm__ volatile ("mv a1,%[y]": : [y] "r" (handle));
    __asm__ volatile ("li a0,0x22");
    __asm__ volatile("ecall"); // poziv prek rutine
    uint64 kod;
    __asm__ volatile("mv %[x],a0":  [x] "=r" (kod));
    return (int)kod;
}
int sem_signal(sem_t handle){
    __asm__ volatile ("mv a1,%[y]": : [y] "r" (handle));
    __asm__ volatile ("li a0,0x24");
    __asm__ volatile("ecall"); // poziv prek rutine
    uint64 kod;
    __asm__ volatile("mv %[x],a0":  [x] "=r" (kod));
    return (int)kod;
}
int sem_wait(sem_t handle){
    __asm__ volatile ("mv a1,%[y]": : [y] "r" (handle));
    __asm__ volatile ("li a0,0x23");
    __asm__ volatile("ecall"); // poziv prek rutine
    uint64 kod;
    __asm__ volatile("mv %[x],a0":  [x] "=r" (kod));
    return (int)kod;
}
int time_sleep(time_t time){
    __asm__ volatile ("mv a1,%[y]": : [y] "r" (time));
    __asm__ volatile ("li a0,0x31");
    __asm__ volatile("ecall"); // poziv prek rutine
    uint64 kod;
    __asm__ volatile("mv %[x],a0":  [x] "=r" (kod));
    return (int)kod;


}
int thread_create_nosch(thread_t* handle,void(*start_routine)(void*),void*arg){
    void* volatile pointer= mem_alloc(DEFAULT_STACK_SIZE*sizeof(uint64));
    __asm__ volatile ("mv a4,%[u]": : [u] "r" (pointer));
    __asm__ volatile ("mv a3,%[h]": : [h] "r" (arg));
    __asm__ volatile ("mv a2,%[z]": : [z] "r" (start_routine));
    __asm__ volatile ("mv a1,%[y]": : [y] "r" (handle));
    __asm__ volatile ("li a0,0x54");
    __asm__ volatile("ecall"); // poziv prek rutine
    uint64 kod;
    __asm__ volatile("mv %[x],a0":  [x] "=r" (kod));
    //__asm__ volatile("mv %[x],a1":  [x] "=r" (*handle));
    return (int)kod;

}
int thread_start(void*arg){
        __asm__ volatile ("mv a1,%[y]": : [y] "r" (arg));
        __asm__ volatile ("li a0,0x51");
        __asm__ volatile("ecall"); // poziv prek rutine
        uint64 kod;
         __asm__ volatile("mv %[x],a0":  [x] "=r" (kod));
        //__asm__ volatile("mv %[x],a1":  [x] "=r" (*handle));
        return (int)kod;

};
void change_sstatus(){

    __asm__ volatile ("li a0,0x52");
    __asm__ volatile("ecall"); // poziv prek rutine



}
char getc(){
    __asm__ volatile ("li a0,0x41");
    __asm__ volatile("ecall"); // poziv prek rutine
    char volatile kod;
    __asm__ volatile("mv %[x],a0":  [x] "=r" (kod));
    //__asm__ volatile("mv %[x],a1":  [x] "=r" (*handle));
    return (int)kod;

}
void putc(char c){

    __asm__ volatile ("mv a1,%[y]": : [y] "r" (c));
    __asm__ volatile ("li a0,0x42");
    __asm__ volatile("ecall"); // poziv prek rutine


}

void deleteThread(thread_t myhandle){
    __asm__ volatile ("mv a1,%[y]": : [y] "r" (myhandle));
    __asm__ volatile ("li a0,0x55");
    __asm__ volatile("ecall");


}
