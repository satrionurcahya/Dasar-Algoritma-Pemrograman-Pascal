// =====================================================
// File : stack.cpp
// =====================================================

#include <iostream>
#include "stack.h"
using namespace std;

// Inisialisasi stack kosong
void createStack(Stack &S) {
    S.top = NULL;
}

// Cek apakah stack kosong
bool isEmptyStack(Stack S) {
    return (S.top == NULL);
}

// Push: tambahkan node di atas stack
void push(Stack &S, char c) {
    StackNode* node = new StackNode;
    node->info = c;
    node->next = S.top;
    S.top     = node;
}

// Pop: ambil & hapus node teratas
char pop(Stack &S) {
    if (isEmptyStack(S)) return '\0';
    StackNode* temp = S.top;
    char c = temp->info;
    S.top = S.top->next;
    delete temp;
    return c;
}

// Peek: lihat node teratas tanpa hapus
char peek(Stack S) {
    if (isEmptyStack(S)) return '\0';
    return S.top->info;
}

// Tampilkan isi stack (dari top ke bawah)
void viewStack(Stack S) {
    if (isEmptyStack(S)) {
        cout << "(kosong)";
        return;
    }
    cout << "[ top -> ";
    StackNode* p = S.top;
    while (p != NULL) {
        cout << p->info;
        if (p->next != NULL) cout << " | ";
        p = p->next;
    }
    cout << " ]";
}

// Bersihkan seluruh isi stack
void deleteStack(Stack &S) {
    while (!isEmptyStack(S)) pop(S);
}