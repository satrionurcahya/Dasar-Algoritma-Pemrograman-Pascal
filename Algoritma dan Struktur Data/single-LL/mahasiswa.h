// =====================================================
// TUGAS 1      : Single Linked List Data Mahasiswa
// Nama         : Satrio Nurcahya
// NIM          : 1303180078
// Kelas        : IT-42-01
// Ketentuan    : ADT Single Linked List
// File         : mahasiswa.h
// =====================================================

#ifndef MAHASISWA_H
#define MAHASISWA_H

#include <string>
using namespace std;

// ---------- DEFINISI ADT ----------

// (a) Struct Mahasiswa: menyimpan Nama, NIM, IPK
struct Mahasiswa {
    string nama;
    string nim;
    double ipk;
};

// (b) Struct Node: menyimpan data Mahasiswa + pointer Next
struct Node {
    Mahasiswa data;
    Node* next;
};

// (c) Struct List: menyimpan pointer First
struct List {
    Node* First;
};

// ---------- DEKLARASI PROSEDUR ----------
void createList(List &L);
void insertFirst(List &L, Mahasiswa mhs);
void deleteLast(List &L);
void viewAll(List L);
void deleteAll(List &L);

// ---------- DEKLARASI FUNGSI ----------
bool searchNIM(List L, string nimCari);
int  countNode(List L);

#endif