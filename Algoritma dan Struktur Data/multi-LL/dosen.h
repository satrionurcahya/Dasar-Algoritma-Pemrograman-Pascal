// =====================================================
// TUGAS 4      : Multi Linked List - Relasi 1 to N
//                (Dosen dan Mata Kuliah)
// Nama         : Satrio Nurcahya
// NIM          : 1303180078
// Kelas        : IT-42-01
// File         : dosen.h
// =====================================================

#ifndef DOSEN_H
#define DOSEN_H

#include <string>
using namespace std;

// ---------- DEFINISI ADT ----------

// Data dosen
struct Dosen {
    string nidn;
    string namaDosen;
};

// Data mata kuliah
struct MataKuliah1N {
    string kodeMK;
    string namaMK;
    int    sks;
};

// Node dosen (parent - single linked list non-circular)
struct NodeDosen {
    Dosen data;
    NodeDosen* nextDosen;
    struct NodeMK1N* firstMK;   // pointer ke MK pertama yang diampu
};

// Node mata kuliah (child - single linked list non-circular)
struct NodeMK1N {
    MataKuliah1N data;
    NodeMK1N* nextMK;
};

// List dosen
struct ListDosen {
    NodeDosen* firstDosen;
};

// ---------- PROSEDUR ----------
void createListDosen(ListDosen &L);
void insertDosen(ListDosen &L, NodeDosen* P);
void insertMK(ListDosen &L, string nidn, NodeMK1N* Q);
void viewAllDosen(ListDosen L);
void deleteMK(ListDosen &L, string nidn, string kodeMK);
void deleteDosen(ListDosen &L, string nidn);

// ---------- FUNGSI ----------
NodeDosen* createDosen(string nidn, string nama);
NodeMK1N*  createMK1N(string kode, string nama, int sks);
NodeDosen* searchDosen(ListDosen L, string nidn);
bool       searchMK(NodeDosen* d, string kodeMK);
int        countDosen(ListDosen L);
int        countMK(NodeDosen* d);

#endif