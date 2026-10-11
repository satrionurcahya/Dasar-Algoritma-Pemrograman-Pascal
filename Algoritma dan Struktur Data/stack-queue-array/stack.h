// =====================================================
// TUGAS 5      : Pengolahan Ekspresi Postfix
//                (Stack, Queue, Rekursif)
// Nama         : Satrio Nurcahya
// NIM          : 1303180078
// Kelas        : IT-42-01
// File         : stack.h
// =====================================================

#ifndef STACK_H
#define STACK_H

#include <string>
using namespace std;

const int MAX_STACK = 100;

struct Stack {
    string data[MAX_STACK];
    int    top;
};

void   createStack(Stack &S);
bool   isEmptyStack(Stack S);
bool   isFullStack(Stack S);
void   push(Stack &S, string token);
string pop(Stack &S);
string peek(Stack S);
void   viewStack(Stack S);

#endif