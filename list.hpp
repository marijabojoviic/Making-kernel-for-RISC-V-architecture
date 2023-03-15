//
// Created by os on 8/17/22.
//


#ifndef PROJECT_BASE_V1_1_LIST_HPP
#define PROJECT_BASE_V1_1_LIST_HPP
//#include "/home/os/Desktop/project-base-v1.1/lib/mem.h"
#include "../h/memoryallocator.hpp"

template<typename T>
class List {
public:

    struct Elem {
        T *data;
        Elem *next;

        Elem(T *data, Elem *next) : data(data), next(next) {}
    };

    List() : head(0), tail(0) {}
    Elem *head, *tail;


    void addFirst(T *data) {

        Elem *elem = (Elem *) MemoryAllocator::mem_alloc(sizeof(Elem));
        elem->data = data;
        elem->next = head;
        head = elem;
        if (!tail) { tail = head; }
    }

    void addLast(T *data) {
        Elem *elem = (Elem *) MemoryAllocator::mem_alloc(sizeof(Elem));
        if (elem) {
            elem->data = data;
            elem->next = 0;
            if (tail!=nullptr) {
                tail->next = elem;
                tail = elem;
            } else {
                    head = tail = elem;
            }

        }
    }



    T *removeFirst()
    {
        if (!head) { return 0; }
        Elem *elem = head;
        head = head->next;
        if (!head) { tail = 0; }
        T *ret = elem->data;
        MemoryAllocator::mem_free(elem);
        return ret;
    }

    T *peekFirst()
    {
        if (!head) { return 0; }
        return head->data;
    }

    T *removeLast()
    {
        if (!head) { return 0; }

        Elem *prev = 0;
        for (Elem *curr = head; curr && curr != tail; curr = curr->next)
        {
            prev = curr;
        }

        Elem *elem = tail;
        if (prev) { prev->next = 0; }
        else { head = 0; }
        tail = prev;

        T *ret = elem->data;
   MemoryAllocator::mem_free(elem);
   //__mem_free(elem);
        //delete elem;
        return ret;
    }

    T *peekLast()
    {
        if (!tail) { return 0; }
        return tail->data;
    }
    void removeThis(T* mem){
        if(mem== nullptr)return;
        Elem* prev=nullptr;
        Elem* sl=head;
        while(sl!=nullptr&&sl->data!=mem){
            prev=sl;
            sl=sl->next;

        }
        if(sl!=nullptr) {
            if (prev) {
                prev->next = sl->next;
            } else {
                head = sl->next;
            }
            MemoryAllocator::mem_free(sl->data);
            MemoryAllocator::mem_free(sl);

        }

    }
    T* removeThisret(T* mem){
        if(mem== nullptr)return nullptr;
        Elem* prev=nullptr;
        Elem* sl=head;
        while(sl!=nullptr&&sl->data!=mem){
            prev=sl;
            sl=sl->next;

        }
        if(sl!=nullptr) {
            if (prev) {
                prev->next = sl->next;
            } else {
                head = sl->next;
            }
            T* ret=sl->data;
            MemoryAllocator::mem_free(sl);
            return ret;
        }
        return nullptr;

    }
    T* getNext(T* dat){
        if(dat==nullptr) return nullptr;
        Elem* sl=head;
        while(sl!=nullptr&&sl->data!=dat){
            sl=sl->next;

        }
        if(sl==nullptr)return nullptr;
        if(sl->next){
            return sl->next->data;
        }
        return nullptr;

    }



};

#endif //PROJECT_BASE_V1_1_LIST_HPP
