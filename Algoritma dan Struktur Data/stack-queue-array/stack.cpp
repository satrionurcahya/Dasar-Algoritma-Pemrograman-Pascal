// =====================================================
// File : stack.cpp
// =====================================================

#include <iostream>
#include "stack.h"
using namespace std;

void createStack(Stack &S) {
    S.top = -1;
}

bool isEmptyStack(Stack S) {
    return (S.top == -1);
}

bool isFullStack(Stack S) {
    return (S.top == MAX_STACK - 1);
}

void push(Stack &S, string token) {
    if (isFullStack(S)) {
        cout << "Stack penuh!\n";
        return;
    }
    S.top++;
    S.data[S.top] = token;
}

string pop(Stack &S) {
    if (isEmptyStack(S)) {
        cout << "Stack kosong, tidak bisa pop!\n";
        return "";
    }
    string token = S.data[S.top];
    S.top--;
    return token;
}

string peek(Stack S) {
    if (isEmptyStack(S)) return "";
    return S.data[S.top];
}

void viewStack(Stack S) {
    if (isEmptyStack(S)) {
        cout << "(kosong)";
        return;
    }
    cout << "[ ";
    for (int i = 0; i <= S.top; i++) {
        cout << S.data[i];
        if (i < S.top) cout << " | ";
    }
    cout << " ]";
}