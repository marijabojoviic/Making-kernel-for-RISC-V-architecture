//
// Created by os on 8/17/22.
//
#include "../h/syscall_cpp.hpp"

void *operator new(size_t size) {
    return mem_alloc(size);
}

void operator delete(void *ptr) {
    mem_free(ptr);
}
void *operator new[](size_t size) {
    return mem_alloc(size);
}

void operator delete[](void *ptr) {
    mem_free(ptr);
}
Thread::Thread(void (*body)(void *), void *arg) {
   thread_create_nosch(&myHandle,body,arg);

}

Thread::~Thread() {
    deleteThread(myHandle);
    mem_free(myHandle);
}

int Thread::sleep(time_t t) {
    return time_sleep(t);
}

void Thread::dispatch() {
    thread_dispatch();
}

Thread::Thread() {
    thread_create_nosch(&myHandle,wrapper,this);

}
void Thread::wrapper(void*arg){
    if(arg!=nullptr){
        ((Thread*)arg)->run();
    }
}

int Thread::start() {
    thread_start((TCB*)myHandle);
  return 0;
}


Semaphore::Semaphore(unsigned int init) {
    sem_open(&myHandle,init);
}

Semaphore::~Semaphore() {
    sem_close(myHandle);
}

int Semaphore::wait() {
    return sem_wait(myHandle);
}

int Semaphore::signal() {
    return sem_signal(myHandle);
}

char Console::getc() {
    return ::getc();
}

void Console::putc(char c) {
    ::putc(c);
}
