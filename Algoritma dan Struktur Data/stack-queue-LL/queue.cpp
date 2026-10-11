// =====================================================
// File : queue.cpp
// =====================================================

#include <iostream>
#include "queue.h"
using namespace std;

void createQueue(Queue &Q) {
    Q.head = NULL;
    Q.tail = NULL;
}

bool isEmptyQueue(Queue Q) {
    return (Q.head == NULL);
}

// Enqueue: tambahkan node di belakang queue
void enqueue(Queue &Q, char c) {
    QueueNode* node = new QueueNode;
    node->info = c;
    node->next = NULL;

    if (Q.head == NULL) {
        Q.head = node;
        Q.tail = node;
    } else {
        Q.tail->next = node;
        Q.tail       = node;
    }
}

// Dequeue: ambil & hapus node di depan queue
char dequeue(Queue &Q) {
    if (isEmptyQueue(Q)) return '\0';
    QueueNode* temp = Q.head;
    char c = temp->info;
    Q.head = Q.head->next;

    if (Q.head == NULL) Q.tail = NULL;   // queue jadi kosong
    delete temp;
    return c;
}

char front(Queue Q) {
    if (isEmptyQueue(Q)) return '\0';
    return Q.head->info;
}

void viewQueue(Queue Q) {
    if (isEmptyQueue(Q)) {
        cout << "(kosong)";
        return;
    }
    cout << "[ head -> ";
    QueueNode* p = Q.head;
    while (p != NULL) {
        cout << p->info;
        if (p->next != NULL) cout << " | ";
        p = p->next;
    }
    cout << " <- tail ]";
}

void deleteQueue(Queue &Q) {
    while (!isEmptyQueue(Q)) dequeue(Q);
}