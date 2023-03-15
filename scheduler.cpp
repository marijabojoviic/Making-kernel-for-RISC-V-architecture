//
// Created by os on 8/17/22.
//
#include "../h/scheduler.hpp"

List<TCB> Scheduler::readyThreadQueue;
int Scheduler::counter=0;

TCB *Scheduler::getTh()
{   if(readyThreadQueue.head!=nullptr){
    counter--;}

    return readyThreadQueue.removeFirst();
}
void Scheduler::putTh(TCB *tcb)
{   counter++;
    readyThreadQueue.addLast(tcb);
}
TCB* Scheduler::returnFirst(){
    if(readyThreadQueue.head){
    return readyThreadQueue.head->data;}
    else{return nullptr;}
}
