// =====================================================
// File : penjualan.h
// ADT Pelanggan, Transaksi, dan Detail Transaksi
// =====================================================

#ifndef PENJUALAN_H
#define PENJUALAN_H

#include <string>
#include "barang.h"
using namespace std;

// =====================================================
// ADT PELANGGAN, TRANSAKSI, DETAIL (Multi-Linked List)
// =====================================================

// Node Detail: menghubungkan transaksi ke barang
struct Detail {
    Barang* barang;     // pointer ke node barang (BUKAN copy)
    int     jumlah;
    double  subtotal;
    Detail* nextDetail;
};

// Node Transaksi
struct Transaksi {
    string   kodeTransaksi;
    string   tanggal;
    double   total;
    Detail*  firstDetail;
    Transaksi* nextTransaksi;
};

// Node Pelanggan
struct Pelanggan {
    string   idPelanggan;
    string   nama;
    string   kontak;
    Transaksi* firstTransaksi;
    Pelanggan* nextPelanggan;
};

// List Pelanggan
struct ListPelanggan {
    Pelanggan* firstPelanggan;
};

// ---------- OPERASI PELANGGAN ----------
void       createListPelanggan(ListPelanggan &LP);
Pelanggan* createPelanggan(string id, string nama, string kontak);
void       insertPelanggan(ListPelanggan &LP, Pelanggan* P);
Pelanggan* searchPelanggan(ListPelanggan LP, string id);
void       updatePelanggan(ListPelanggan &LP, string id,
                           string namaBaru, string kontakBaru);
void       deletePelanggan(ListPelanggan &LP, string id);
void       viewAllPelanggan(ListPelanggan LP);

// ---------- OPERASI TRANSAKSI ----------
Transaksi* createTransaksi(string kode, string tanggal);
Detail*    createDetail(Barang* B, int jumlah);
void       tambahDetail(Transaksi* T, Detail* D);
void       buatTransaksi(ListPelanggan &LP, ListKategori &LK,
                         string idPelanggan, string kodeTransaksi,
                         string tanggal);
void       viewTransaksiPelanggan(ListPelanggan LP, string idPelanggan);
void       viewAllTransaksi(ListPelanggan LP);
void       laporanPenjualan(ListPelanggan LP);
void       laporanBarangTerjual(ListPelanggan LP);

// ---------- UTIL ----------
bool       isPelangganKosong(ListPelanggan LP);
int        countPelanggan(ListPelanggan LP);
int        countTransaksiPelanggan(Pelanggan* P);
int        countAllTransaksi(ListPelanggan LP);
double     totalPendapatan(ListPelanggan LP);
void       deleteAllPelanggan(ListPelanggan &LP);

#endif