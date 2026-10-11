// =====================================================
// File : palindrom.h
// Berisi ADT SLL (untuk teks), ADT DLL (untuk metode E),
// dan deklarasi 4 metode pemeriksaan palindrom.
// =====================================================

#ifndef PALINDROM_H
#define PALINDROM_H

#include <string>
#include "stack.h"
#include "queue.h"
using namespace std;

// =====================================================
// ADT Single Linked List untuk menyimpan karakter teks
// =====================================================
struct NodeSLL {
    char     info;
    NodeSLL* next;
};

struct List {
    NodeSLL* First;
};

// =====================================================
// ADT Double Linked List untuk metode pemeriksaan DLL
// =====================================================
struct NodeDLL {
    char     info;
    NodeDLL* next;
    NodeDLL* prev;
};

struct ListDLL {
    NodeDLL* First;
    NodeDLL* Last;
};

// ---------- OPERASI SLL ----------
void createList(List &L);
bool isNull(List L);
NodeSLL* createNode(char c);
void insertLast(List &L, char c);
void buildList(List &L, string teks);
void viewList(List L);
int  countNode(List L);
void deleteList(List &L);

// ---------- OPERASI DLL ----------
void createListDLL(ListDLL &L);
void insertLastDLL(ListDLL &L, char c);
void buildListDLL(ListDLL &L, string teks);
void viewForward(ListDLL L);
void viewBackward(ListDLL L);
void deleteListDLL(ListDLL &L);

// ---------- PEMERIKSAAN PALINDROM ----------
bool isPalindromeStack(List L);           // pakai Stack LL
bool isPalindromeQueueStack(List L);      // pakai Queue + Stack LL
bool isPalindromeRecursive(List L);       // pakai rekursi
bool isPalindromeDLL(ListDLL L);          // pakai DLL

#endif