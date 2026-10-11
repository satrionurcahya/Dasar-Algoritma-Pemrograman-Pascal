// =====================================================
// TUGAS 6      : Pemeriksa Palindrom
//                (Stack, Queue, Rekursif, DLL)
// Nama         : Satrio Nurcahya
// NIM          : 1303180078
// Kelas        : IT-42-01
// File         : stack.h
// =====================================================

#ifndef STACK_H
#define STACK_H

// Node Stack (berbasis Linked List)
struct StackNode {
    char       info;
    StackNode* next;
};

// ADT Stack
struct Stack {
    StackNode* top;
};

// ---------- OPERASI STACK ----------
void createStack(Stack &S);
bool isEmptyStack(Stack S);
void push(Stack &S, char c);
char pop(Stack &S);
char peek(Stack S);
void viewStack(Stack S);
void deleteStack(Stack &S);

#endif