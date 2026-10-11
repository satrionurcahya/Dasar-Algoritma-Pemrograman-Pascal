// =====================================================
// TUGAS 4      : Multi Linked List - Relasi N to M
//                (Mahasiswa dan Mata Kuliah)
// Nama         : Satrio Nurcahya
// NIM          : 1303180078
// Kelas        : IT-42-01
// File         : mahasiswa.h
// =====================================================

#ifndef MAHASISWA_H
#define MAHASISWA_H

#include <string>
using namespace std;

// ---------- DEFINISI ADT ----------

// Data mahasiswa
struct Mahasiswa {
    string nim;
    string namaMahasiswa;
};

// Data mata kuliah (N to M)
struct MataKuliahNM {
    string kodeMK;
    string namaMK;
    int    sks;
};

// Forward declaration
struct NodeMahasiswa;
struct NodeMK_NM;
struct NodeRelasi;

// Node mahasiswa (Double Linked List non-circular)
struct NodeMahasiswa {
    Mahasiswa data;
    NodeRelasi* firstRelasi;      // daftar MK yang diambil
    NodeMahasiswa* prevMahasiswa;
    NodeMahasiswa* nextMahasiswa;
};

// Node mata kuliah (Single Linked List circular)
struct NodeMK_NM {
    MataKuliahNM data;
    NodeMK_NM* nextMK;
};

// Node relasi (Single Linked List non-circular)
struct NodeRelasi {
    NodeMahasiswa* mahasiswa;
    NodeMK_NM*     mataKuliah;
    double         nilai;
    NodeRelasi*    nextRelasi;
};

// List mahasiswa
struct ListMahasiswa {
    NodeMahasiswa* firstMahasiswa;
    NodeMahasiswa* lastMahasiswa;
};

// List mata kuliah (circular)
struct ListMK {
    NodeMK_NM* firstMK;
};

// ---------- PROSEDUR ----------
void createListMahasiswa(ListMahasiswa &L);
void createListMK(ListMK &L);
void insertMahasiswa(ListMahasiswa &L, NodeMahasiswa* P);
void insertMK(ListMK &L, NodeMK_NM* Q);
void insertRelasi(ListMahasiswa &L, NodeMahasiswa* P, NodeMK_NM* Q);
void updateNilai(ListMahasiswa &L, string nim, string kodeMK, double nilaiBaru);
void viewAllMahasiswa(ListMahasiswa L);
void viewAllMK(ListMK L);
void viewMKMahasiswa(ListMahasiswa L, string nim);
void viewMahasiswaMK(ListMahasiswa L, string kodeMK);
void deleteRelasi(ListMahasiswa &L, string nim, string kodeMK);
void deleteMahasiswa(ListMahasiswa &L, string nim);
void deleteMK(ListMahasiswa &L, ListMK &LMK, string kodeMK);

// ---------- FUNGSI ----------
NodeMahasiswa* createMahasiswa(string nim, string nama);
NodeMK_NM*     createMK_NM(string kode, string nama, int sks);
NodeRelasi*    createRelasi(NodeMahasiswa* m, NodeMK_NM* mk);
NodeMahasiswa* searchMahasiswa(ListMahasiswa L, string nim);
NodeMK_NM*     searchMK(ListMK L, string kodeMK);
bool           searchRelasi(NodeMahasiswa* m, string kodeMK);
int            countMahasiswa(ListMahasiswa L);
int            countMK(ListMK L);
int            countMKMahasiswa(NodeMahasiswa* m);
int            countMahasiswaMK(ListMahasiswa L, string kodeMK);

#endif