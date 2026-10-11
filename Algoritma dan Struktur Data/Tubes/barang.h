// =====================================================
// TUGAS BESAR  : Penerapan Multi-Linked List
//                dalam Program Penjualan
// Nama         : Satrio Nurcahya
// NIM          : 1303180078
// Kelas        : IT-42-01
// File         : barang.h
// =====================================================

#ifndef BARANG_H
#define BARANG_H

#include <string>
using namespace std;

// =====================================================
// ADT BARANG dan KATEGORI
// =====================================================

// Node Barang (child dari Kategori)
struct Barang {
    string  kodeBarang;
    string  namaBarang;
    double  harga;
    int     stok;
    Barang* nextBarang;    // next barang dalam kategori yang sama
};

// Node Kategori (parent)
struct Kategori {
    string    kodeKategori;
    string    namaKategori;
    Barang*   firstBarang;    // list barang dalam kategori ini
    Kategori* nextKategori;
};

// List Kategori
struct ListKategori {
    Kategori* firstKategori;
};

// ---------- OPERASI KATEGORI ----------
void      createListKategori(ListKategori &LK);
Kategori* createKategori(string kode, string nama);
void      insertKategori(ListKategori &LK, Kategori* K);
Kategori* searchKategori(ListKategori LK, string kode);
void      updateKategori(ListKategori &LK, string kode, string namaBaru);
void      deleteKategori(ListKategori &LK, string kode);
void      viewAllKategori(ListKategori LK);

// ---------- OPERASI BARANG ----------
Barang*   createBarang(string kode, string nama, double harga, int stok);
void      insertBarang(ListKategori &LK, string kodeKategori, Barang* B);
Barang*   searchBarang(ListKategori LK, string kodeBarang);
Barang*   searchBarangDiKategori(Kategori* K, string kodeBarang);
void      updateBarang(ListKategori &LK, string kodeBarang,
                       string namaBaru, double hargaBaru, int stokBaru);
void      deleteBarang(ListKategori &LK, string kodeBarang);
void      viewAllBarang(ListKategori LK);
void      viewBarangByKategori(ListKategori LK, string kodeKategori);

// ---------- UTIL ----------
bool      isKategoriKosong(ListKategori LK);
int       countKategori(ListKategori LK);
int       countBarangDiKategori(Kategori* K);
int       countTotalBarang(ListKategori LK);
void      deleteAllKategori(ListKategori &LK);

#endif