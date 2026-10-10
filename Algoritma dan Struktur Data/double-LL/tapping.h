// =====================================================
// TUGAS 2      : ADT Sistem Tapping Kehadiran Pegawai
//                (Double Linked List)
// Nama         : Satrio Nurcahya
// NIM          : 1303180078
// Kelas        : IT-42-01
// File         : tapping.h
// =====================================================

#ifndef TAPPING_H
#define TAPPING_H

#include <string>
using namespace std;

// ---------- DEFINISI ADT ----------

// (a) Struct Tapping: data tapping pegawai
struct Tapping {
    string idPegawai;   // ID pegawai
    int    jam;         // jam tapping
    int    menit;       // menit tapping
    string status;      // "masuk" atau "keluar"
    int    count;       // jumlah tapping untuk kombinasi ID+status
};

// (b) Struct Node: data Tapping + pointer Prev & Next
struct Node {
    Tapping data;
    Node*   Prev;
    Node*   Next;
};

// (c) Struct List: pointer First dan Last
struct List {
    Node* First;
    Node* Last;
};

// ---------- DEKLARASI PROSEDUR ----------
void createList(List &L);
void insertElemen(List &L, Node* P);
void tampilData(List L);
void deleteAfter(List &L, Node* P);
void deleteAll(List &L);

// ---------- DEKLARASI FUNGSI ----------
bool    isNull(List L);
Node*   createData(string idPegawai, int jam, int menit);
int     countElemen(List L);
bool    searchPegawai(List L, string idCari);

#endif