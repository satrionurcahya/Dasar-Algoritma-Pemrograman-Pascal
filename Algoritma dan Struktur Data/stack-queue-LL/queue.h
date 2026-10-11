// =====================================================
// File : queue.h
// =====================================================

#ifndef QUEUE_H
#define QUEUE_H

// Node Queue (berbasis Linked List)
struct QueueNode {
    char       info;
    QueueNode* next;
};

// ADT Queue dengan pointer Head dan Tail
struct Queue {
    QueueNode* head;
    QueueNode* tail;
};

// ---------- OPERASI QUEUE ----------
void createQueue(Queue &Q);
bool isEmptyQueue(Queue Q);
void enqueue(Queue &Q, char c);
char dequeue(Queue &Q);
char front(Queue Q);
void viewQueue(Queue Q);
void deleteQueue(Queue &Q);

#endif