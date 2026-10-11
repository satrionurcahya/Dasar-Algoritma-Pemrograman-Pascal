// =====================================================
// File : queue.h
// =====================================================

#ifndef QUEUE_H
#define QUEUE_H

#include <string>
using namespace std;

const int MAX_QUEUE = 100;

struct Queue {
    string data[MAX_QUEUE];
    int    head;    // indeks depan
    int    tail;    // indeks belakang
    int    count;   // jumlah elemen
};

void   createQueue(Queue &Q);
bool   isEmptyQueue(Queue Q);
bool   isFullQueue(Queue Q);
void   enqueue(Queue &Q, string token);
string dequeue(Queue &Q);
string frontQueue(Queue Q);
void   viewQueue(Queue Q);

#endif