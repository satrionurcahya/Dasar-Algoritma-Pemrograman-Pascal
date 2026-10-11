// =====================================================
// File : palindrom.cpp
// =====================================================

#include <iostream>
#include <cctype>
#include "palindrom.h"
using namespace std;

// =====================================================
//                     SLL
// =====================================================
void createList(List &L) {
    L.First = NULL;
}

bool isNull(List L) {
    return (L.First == NULL);
}

NodeSLL* createNode(char c) {
    NodeSLL* node = new NodeSLL;
    node->info = c;
    node->next = NULL;
    return node;
}

void insertLast(List &L, char c) {
    NodeSLL* node = createNode(c);

    if (L.First == NULL) {
        L.First = node;
    } else {
        NodeSLL* p = L.First;
        while (p->next != NULL) p = p->next;
        p->next = node;
    }
}

// Bangun SLL dari teks: abaikan spasi, ubah ke huruf kecil
void buildList(List &L, string teks) {
    createList(L);
    for (int i = 0; i < (int)teks.length(); i++) {
        char c = teks[i];
        if (c == ' ' || c == '\t') continue;   // abaikan spasi
        c = tolower(c);                        // normalisasi
        insertLast(L, c);
    }
}

void viewList(List L) {
    if (isNull(L)) {
        cout << "(kosong)";
        return;
    }
    NodeSLL* p = L.First;
    while (p != NULL) {
        cout << p->info;
        if (p->next != NULL) cout << " -> ";
        p = p->next;
    }
    cout << " -> NULL";
}

int countNode(List L) {
    int hitung = 0;
    NodeSLL* p = L.First;
    while (p != NULL) {
        hitung++;
        p = p->next;
    }
    return hitung;
}

void deleteList(List &L) {
    NodeSLL* p = L.First;
    while (p != NULL) {
        NodeSLL* temp = p;
        p = p->next;
        delete temp;
    }
    L.First = NULL;
}

// =====================================================
//                     DLL
// =====================================================
void createListDLL(ListDLL &L) {
    L.First = NULL;
    L.Last  = NULL;
}

void insertLastDLL(ListDLL &L, char c) {
    NodeDLL* node = new NodeDLL;
    node->info = c;
    node->next = NULL;
    node->prev = NULL;

    if (L.First == NULL) {
        L.First = node;
        L.Last  = node;
    } else {
        node->prev     = L.Last;
        L.Last->next   = node;
        L.Last         = node;
    }
}

void buildListDLL(ListDLL &L, string teks) {
    createListDLL(L);
    for (int i = 0; i < (int)teks.length(); i++) {
        char c = teks[i];
        if (c == ' ' || c == '\t') continue;
        c = tolower(c);
        insertLastDLL(L, c);
    }
}

void viewForward(ListDLL L) {
    if (L.First == NULL) {
        cout << "(kosong)";
        return;
    }
    NodeDLL* p = L.First;
    while (p != NULL) {
        cout << p->info;
        if (p->next != NULL) cout << " <-> ";
        p = p->next;
    }
    cout << " <-> NULL";
}

void viewBackward(ListDLL L) {
    if (L.Last == NULL) {
        cout << "(kosong)";
        return;
    }
    NodeDLL* p = L.Last;
    while (p != NULL) {
        cout << p->info;
        if (p->prev != NULL) cout << " <-> ";
        p = p->prev;
    }
    cout << " <-> NULL";
}

void deleteListDLL(ListDLL &L) {
    NodeDLL* p = L.First;
    while (p != NULL) {
        NodeDLL* temp = p;
        p = p->next;
        delete temp;
    }
    L.First = NULL;
    L.Last  = NULL;
}

// =====================================================
//      METODE 1 : PALINDROM DENGAN STACK (LL)
// =====================================================
bool isPalindromeStack(List L) {
    if (isNull(L)) return true;   // teks kosong = palindrom

    Stack S;
    createStack(S);

    // Push semua karakter ke stack
    NodeSLL* p = L.First;
    while (p != NULL) {
        push(S, p->info);
        p = p->next;
    }

    // Bandingkan karakter asli dengan hasil pop (terbalik)
    p = L.First;
    while (p != NULL) {
        if (p->info != pop(S)) {
            deleteStack(S);
            return false;
        }
        p = p->next;
    }
    deleteStack(S);
    return true;
}

// =====================================================
//      METODE 2 : PALINDROM DENGAN QUEUE + STACK
// =====================================================
bool isPalindromeQueueStack(List L) {
    if (isNull(L)) return true;

    Queue Q;
    Stack S;
    createQueue(Q);
    createStack(S);

    // Masukkan semua karakter ke Queue (urutan asli)
    // dan ke Stack (urutan terbalik)
    NodeSLL* p = L.First;
    while (p != NULL) {
        enqueue(Q, p->info);
        push(S, p->info);
        p = p->next;
    }

    // Bandingkan dequeue (depan) vs pop (belakang)
    while (!isEmptyQueue(Q)) {
        char kiri  = dequeue(Q);
        char kanan = pop(S);
        if (kiri != kanan) {
            deleteQueue(Q);
            deleteStack(S);
            return false;
        }
    }
    deleteQueue(Q);
    deleteStack(S);
    return true;
}

// =====================================================
//      METODE 3 : PALINDROM DENGAN REKURSI
// =====================================================
// Strategi: pointer kiri maju satu langkah setiap kali
// satu node kanan selesai dibandingkan pada "jalan pulang"
// dari rekursi. Perbandingan hanya dilakukan untuk
// totalLen / 2 pasang pertama dari arah kanan.

static NodeSLL* g_leftPtr;
static int      g_totalLen;
static int      g_counter;   // hitungan node dari kanan

static bool recHelper(NodeSLL* right) {
    if (right == NULL) return true;

    // Turun dulu sampai ujung kanan
    if (!recHelper(right->next)) return false;

    // "Jalan pulang" - saatnya membandingkan
    g_counter++;

    // Hanya bandingkan sebanyak totalLen/2 pasang
    if (g_counter > g_totalLen / 2) return true;

    if (g_leftPtr->info != right->info) return false;

    g_leftPtr = g_leftPtr->next;
    return true;
}

bool isPalindromeRecursive(List L) {
    if (isNull(L)) return true;

    g_leftPtr  = L.First;
    g_totalLen = countNode(L);
    g_counter  = 0;

    return recHelper(L.First);
}

// =====================================================
//      METODE 4 : PALINDROM DENGAN DLL
// =====================================================
bool isPalindromeDLL(ListDLL L) {
    if (L.First == NULL) return true;

    NodeDLL* kiri  = L.First;
    NodeDLL* kanan = L.Last;

    // Berhenti ketika kedua pointer bertemu atau bersebelahan
    while (kiri != kanan && kiri->prev != kanan) {
        if (kiri->info != kanan->info) return false;
        kiri  = kiri->next;
        kanan = kanan->prev;
    }
    return true;
}