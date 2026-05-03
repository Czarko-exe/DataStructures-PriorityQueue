#pragma once
#include <iostream>
//generalnie 75% takie samo jak w zwykłym DLLu który implementowaliśmy przedtem

struct DLLNode {        //nasze węzły
    int value;
    int priority;
    DLLNode* prev;
    DLLNode* next;

    DLLNode(int val, int prio) : value(val), priority(prio), next(nullptr), prev(nullptr) {}
    //konstruktor
};

class SortedDLL {
private:
    DLLNode* head;
    DLLNode* tail;
    int size;

public:
    SortedDLL();
    ~SortedDLL();

    void insertSDLL(int value, int priority);
    int findMax() const;
    int extractMax();
    bool modifyKey(int value, int newPriority);
    int getSize() const {return size;}
    bool isEmpty() const {return size == 0;}
    void clear();
    void print() const;
};