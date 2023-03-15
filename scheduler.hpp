//
// Created by os on 8/17/22.
//
#ifndef PROJECT_BASE_V1_1_SCHEDULER_HPP
#define PROJECT_BASE_V1_1_SCHEDULER_HPP
#include "../h/list.hpp"

class TCB;

class Scheduler
{
public:
    static List<TCB> readyThreadQueue;
    static int counter;
public:
    static TCB *getTh();
    static int counterBr(){return counter;}
    static void putTh(TCB* tcb);
    static TCB* returnFirst();

};





#endif //PROJECT_BASE_V1_1_SCHEDULER_HPP
