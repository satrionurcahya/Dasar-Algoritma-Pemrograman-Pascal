// =====================================================
// TUGAS 4      : Multi Linked List - Relasi 1 to N
//                (Dosen dan Mata Kuliah)
// Nama         : Satrio Nurcahya
// NIM          : 1303180078
// Kelas        : IT-42-01
// File         : dosen.cpp
// =====================================================

#include <iostream>
#include <iomanip>
#include "dosen.h"
using namespace std;

// =====================================================
// CREATE LIST DOSEN
// =====================================================
void createListDosen(ListDosen &L) {
    L.firstDosen = NULL;
}

// =====================================================
// CREATE DOSEN
// =====================================================
NodeDosen* createDosen(string nidn, string nama) {
    NodeDosen* newNode = new NodeDosen;
    newNode->data.nidn      = nidn;
    newNode->data.namaDosen = nama;
    newNode->nextDosen      = NULL;
    newNode->firstMK        = NULL;
    return newNode;
}

// =====================================================
// CREATE MATA KULIAH
// =====================================================
NodeMK1N* createMK1N(string kode, string nama, int sks) {
    NodeMK1N* newNode = new NodeMK1N;
    newNode->data.kodeMK = kode;
    newNode->data.namaMK = nama;
    newNode->data.sks    = sks;
    newNode->nextMK      = NULL;
    return newNode;
}

// =====================================================
// SEARCH DOSEN
// =====================================================
NodeDosen* searchDosen(ListDosen L, string nidn) {
    NodeDosen* P = L.firstDosen;
    while (P != NULL) {
        if (P->data.nidn == nidn) return P;
        P = P->nextDosen;
    }
    return NULL;
}

// =====================================================
// SEARCH MK pada dosen tertentu
// =====================================================
bool searchMK(NodeDosen* d, string kodeMK) {
    if (d == NULL) return false;
    NodeMK1N* P = d->firstMK;
    while (P != NULL) {
        if (P->data.kodeMK == kodeMK) return true;
        P = P->nextMK;
    }
    return false;
}

// =====================================================
// INSERT DOSEN (di akhir, NIDN tidak boleh duplikat)
// =====================================================
void insertDosen(ListDosen &L, NodeDosen* P) {
    if (searchDosen(L, P->data.nidn) != NULL) {
        cout << "NIDN " << P->data.nidn << " sudah terdaftar!\n";
        delete P;
        return;
    }

    if (L.firstDosen == NULL) {
        L.firstDosen = P;
    } else {
        NodeDosen* last = L.firstDosen;
        while (last->nextDosen != NULL)
            last = last->nextDosen;
        last->nextDosen = P;
    }
    cout << "Dosen " << P->data.namaDosen << " berhasil ditambahkan.\n";
}

// =====================================================
// INSERT MK ke dosen tertentu
// =====================================================
void insertMK(ListDosen &L, string nidn, NodeMK1N* Q) {
    NodeDosen* d = searchDosen(L, nidn);
    if (d == NULL) {
        cout << "Dosen dengan NIDN " << nidn << " tidak ditemukan!\n";
        delete Q;
        return;
    }
    if (searchMK(d, Q->data.kodeMK)) {
        cout << "MK " << Q->data.kodeMK << " sudah ada pada dosen ini!\n";
        delete Q;
        return;
    }

    if (d->firstMK == NULL) {
        d->firstMK = Q;
    } else {
        NodeMK1N* last = d->firstMK;
        while (last->nextMK != NULL)
            last = last->nextMK;
        last->nextMK = Q;
    }
    cout << "MK " << Q->data.namaMK << " berhasil ditambahkan ke "
         << d->data.namaDosen << ".\n";
}

// =====================================================
// VIEW ALL DOSEN + MK
// =====================================================
void viewAllDosen(ListDosen L) {
    if (L.firstDosen == NULL) {
        cout << "Belum ada data dosen.\n";
        return;
    }

    NodeDosen* P = L.firstDosen;
    while (P != NULL) {
        cout << "\nNIDN       : " << P->data.nidn << endl;
        cout << "Nama Dosen : " << P->data.namaDosen << endl;
        cout << "Mata Kuliah:" << endl;

        if (P->firstMK == NULL) {
            cout << "  (Belum ada mata kuliah yang diampu)\n";
        } else {
            NodeMK1N* Q = P->firstMK;
            while (Q != NULL) {
                cout << "  - " << Q->data.kodeMK << ", "
                     << Q->data.namaMK << ", "
                     << Q->data.sks << " SKS" << endl;
                Q = Q->nextMK;
            }
        }
        P = P->nextDosen;
    }
}

// =====================================================
// DELETE MK dari dosen tertentu
// =====================================================
void deleteMK(ListDosen &L, string nidn, string kodeMK) {
    NodeDosen* d = searchDosen(L, nidn);
    if (d == NULL) {
        cout << "Dosen tidak ditemukan.\n";
        return;
    }
    if (d->firstMK == NULL) {
        cout << "Dosen ini belum memiliki mata kuliah.\n";
        return;
    }

    NodeMK1N* P = d->firstMK;
    NodeMK1N* prev = NULL;

    while (P != NULL && P->data.kodeMK != kodeMK) {
        prev = P;
        P = P->nextMK;
    }

    if (P == NULL) {
        cout << "MK " << kodeMK << " tidak ditemukan pada dosen ini.\n";
        return;
    }

    if (prev == NULL)
        d->firstMK = P->nextMK;
    else
        prev->nextMK = P->nextMK;

    cout << "MK " << P->data.namaMK << " berhasil dihapus.\n";
    delete P;
}

// =====================================================
// DELETE DOSEN beserta seluruh MK-nya
// =====================================================
void deleteDosen(ListDosen &L, string nidn) {
    NodeDosen* P = L.firstDosen;
    NodeDosen* prev = NULL;

    while (P != NULL && P->data.nidn != nidn) {
        prev = P;
        P = P->nextDosen;
    }

    if (P == NULL) {
        cout << "Dosen dengan NIDN " << nidn << " tidak ditemukan.\n";
        return;
    }

    // Hapus seluruh MK-nya
    NodeMK1N* Q = P->firstMK;
    while (Q != NULL) {
        NodeMK1N* temp = Q;
        Q = Q->nextMK;
        delete temp;
    }

    // Hapus dosen dari list
    if (prev == NULL)
        L.firstDosen = P->nextDosen;
    else
        prev->nextDosen = P->nextDosen;

    cout << "Dosen " << P->data.namaDosen << " beserta seluruh MK berhasil dihapus.\n";
    delete P;
}

// =====================================================
// COUNT DOSEN
// =====================================================
int countDosen(ListDosen L) {
    int hitung = 0;
    NodeDosen* P = L.firstDosen;
    while (P != NULL) {
        hitung++;
        P = P->nextDosen;
    }
    return hitung;
}

// =====================================================
// COUNT MK pada dosen
// =====================================================
int countMK(NodeDosen* d) {
    if (d == NULL) return 0;
    int hitung = 0;
    NodeMK1N* P = d->firstMK;
    while (P != NULL) {
        hitung++;
        P = P->nextMK;
    }
    return hitung;
}