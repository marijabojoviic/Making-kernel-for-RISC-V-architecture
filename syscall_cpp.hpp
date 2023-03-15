//
// Created by os on 9/8/22.
//

#ifndef PROJECT_BASE_V1_1_SYSCALL_CPP_HPP
#define PROJECT_BASE_V1_1_SYSCALL_CPP_HPP
#include "../h/syscall_c.hpp"

void *operator new(size_t size);
void operator delete(void *ptr);
void* operator new[](size_t size);
void operator delete[](void* ptr);

class Thread {
public:
    Thread(void (*body)(void *), void *arg);
    static void wrapper(void* arg);

    virtual ~Thread();

    int start();

    static void dispatch();

    static int sleep(time_t);

protected:
    Thread();

    virtual void run() {}

private:
    thread_t myHandle;
};
class Semaphore {
public:
    Semaphore (unsigned init = 1);
    virtual ~Semaphore ();
    int wait ();
    int signal ();
private:
    sem_t myHandle;
};
/*class PeriodicThread : public Thread {
protected:
    PeriodicThread (time_t period);
    virtual void periodicActivation () {}
};*/
class Console {
public:
    static char getc ();
    static void putc (char);
};

#endif //PROJECT_BASE_V1_1_SYSCALL_CPP_HPP
