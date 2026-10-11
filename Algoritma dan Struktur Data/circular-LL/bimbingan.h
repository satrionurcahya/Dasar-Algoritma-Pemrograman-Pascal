// =====================================================
// TUGAS 3      : Sistem Pengelolaan Aktivitas Akademik
//                (Circular Single Linked List)
// Nama         : Satrio Nurcahya
// NIM          : 1303180078
// Kelas        : IT-42-01
// File         : bimbingan.h
// =====================================================

#ifndef BIMBINGAN_H
#define BIMBINGAN_H

#include <string>
using namespace std;

// ---------- DEFINISI ADT ----------

// Struct Mahasiswa: data antrean bimbingan
struct Mahasiswa {
    string nim;
    string nama;
    string keperluan;
    int    nomorAntrean;
};

// Struct Node: data Mahasiswa + pointer Next
struct NodeBimbingan {
    Mahasiswa data;
    NodeBimbingan* Next;
};

// Struct List: pointer First (circular)
struct ListBimbingan {
    NodeBimbingan* First;
};

// ---------- DEKLARASI PROSEDUR ----------
void createListBimbingan(ListBimbingan &L);
void insertLastBimbingan(ListBimbingan &L, NodeBimbingan* P);
void deleteFirstBimbingan(ListBimbingan &L);
void viewAllBimbingan(ListBimbingan L);

// ---------- DEKLARASI FUNGSI ----------
bool isNullBimbingan(ListBimbingan L);
NodeBimbingan* createDataBimbingan(string nim, string nama, string keperluan, int noAntrean);
bool searchNIM(ListBimbingan L, string nimCari);
int  countNodeBimbingan(ListBimbingan L);

#endif