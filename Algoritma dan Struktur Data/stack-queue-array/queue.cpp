// =====================================================
// File : queue.cpp
// =====================================================

#include <iostream>
#include "queue.h"
using namespace std;

void createQueue(Queue &Q) {
    Q.head  = 0;
    Q.tail  = -1;
    Q.count = 0;
}

bool isEmptyQueue(Queue Q) {
    return (Q.count == 0);
}

bool isFullQueue(Queue Q) {
    return (Q.count == MAX_QUEUE);
}

void enqueue(Queue &Q, string token) {
    if (isFullQueue(Q)) {
        cout << "Queue penuh!\n";
        return;
    }
    Q.tail = (Q.tail + 1) % MAX_QUEUE;
    Q.data[Q.tail] = token;
    Q.count++;
}

string dequeue(Queue &Q) {
    if (isEmptyQueue(Q)) {
        cout << "Queue kosong, tidak bisa dequeue!\n";
        return "";
    }
    string token = Q.data[Q.head];
    Q.head = (Q.head + 1) % MAX_QUEUE;
    Q.count--;
    return token;
}

string frontQueue(Queue Q) {
    if (isEmptyQueue(Q)) return "";
    return Q.data[Q.head];
}

void viewQueue(Queue Q) {
    if (isEmptyQueue(Q)) {
        cout << "(kosong)";
        return;
    }
    cout << "[ ";
    for (int i = 0; i < Q.count; i++) {
        cout << Q.data[(Q.head + i) % MAX_QUEUE];
        if (i < Q.count - 1) cout << " | ";
    }
    cout << " ]";
}