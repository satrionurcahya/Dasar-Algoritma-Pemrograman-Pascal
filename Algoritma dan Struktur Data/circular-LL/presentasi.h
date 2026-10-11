// =====================================================
// TUGAS 3      : Sistem Pengelolaan Aktivitas Akademik
//                (Circular Double Linked List)
// Nama         : Satrio Nurcahya
// NIM          : 1303180078
// Kelas        : IT-42-01
// File         : presentasi.h
// =====================================================

#ifndef PRESENTASI_H
#define PRESENTASI_H

#include <string>
using namespace std;

// ---------- DEFINISI ADT ----------

// Struct Kelompok: data kelompok presentasi
struct Kelompok {
    string kodeKelompok;
    string namaKetua;
    string topik;
    string status;      // "belum", "berlangsung", "selesai"
};

// Struct Node: data Kelompok + pointer Next & Prev
struct NodePresentasi {
    Kelompok data;
    NodePresentasi* Next;
    NodePresentasi* Prev;
};

// Struct List: pointer First dan Last
struct ListPresentasi {
    NodePresentasi* First;
    NodePresentasi* Last;
    NodePresentasi* Aktif;   // posisi kelompok yang sedang dipilih
};

// ---------- DEKLARASI PROSEDUR ----------
void createListPresentasi(ListPresentasi &L);
void insertFirstPresentasi(ListPresentasi &L, NodePresentasi* P);
void insertLastPresentasi(ListPresentasi &L, NodePresentasi* P);
void nextGroup(ListPresentasi &L);
void prevGroup(ListPresentasi &L);
void updateStatus(ListPresentasi &L, string kode, string statusBaru);
void deleteByKode(ListPresentasi &L, string kode);
void viewAllPresentasi(ListPresentasi L);

// ---------- DEKLARASI FUNGSI ----------
bool isNullPresentasi(ListPresentasi L);
NodePresentasi* createDataPresentasi(string kode, string ketua, string topik);
bool searchKelompok(ListPresentasi L, string kode);
int  countNodePresentasi(ListPresentasi L);

#endif