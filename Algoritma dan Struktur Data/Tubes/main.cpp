// =====================================================
// TUGAS BESAR  : Penerapan Multi-Linked List
//                dalam Program Penjualan
// Nama         : Satrio Nurcahya
// NIM          : 1303180078
// Kelas        : IT-42-01
// File         : main.cpp
// =====================================================

#include <iostream>
#include <string>
#include "barang.h"
#include "penjualan.h"
using namespace std;

ListKategori  LK;
ListPelanggan LP;

// =====================================================
// MENU KATEGORI
// =====================================================
void menuKategori() {
    int pilih;
    do {
        cout << "\n===== MENU KATEGORI =====\n";
        cout << "1. Tambah Kategori\n";
        cout << "2. Lihat Semua Kategori\n";
        cout << "3. Ubah Kategori\n";
        cout << "4. Hapus Kategori\n";
        cout << "5. Cari Kategori\n";
        cout << "0. Kembali\n";
        cout << "Pilihan : ";
        cin >> pilih; cin.ignore();

        switch (pilih) {
            case 1: {
                string kode, nama;
                cout << "Kode Kategori : "; getline(cin, kode);
                cout << "Nama Kategori : "; getline(cin, nama);
                insertKategori(LK, createKategori(kode, nama));
                break;
            }
            case 2: viewAllKategori(LK); break;
            case 3: {
                string kode, nama;
                cout << "Kode Kategori : "; getline(cin, kode);
                cout << "Nama Baru     : "; getline(cin, nama);
                updateKategori(LK, kode, nama);
                break;
            }
            case 4: {
                string kode;
                cout << "Kode Kategori : "; getline(cin, kode);
                deleteKategori(LK, kode);
                break;
            }
            case 5: {
                string kode;
                cout << "Kode Kategori : "; getline(cin, kode);
                Kategori* K = searchKategori(LK, kode);
                if (K == NULL) cout << "Kategori tidak ditemukan.\n";
                else cout << "Ditemukan: " << K->kodeKategori
                          << " - " << K->namaKategori
                          << " (" << countBarangDiKategori(K) << " barang)\n";
                break;
            }
        }
    } while (pilih != 0);
}

// =====================================================
// MENU BARANG
// =====================================================
void menuBarang() {
    int pilih;
    do {
        cout << "\n===== MENU BARANG =====\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Lihat Semua Barang\n";
        cout << "3. Lihat Barang per Kategori\n";
        cout << "4. Ubah Barang\n";
        cout << "5. Hapus Barang\n";
        cout << "6. Cari Barang\n";
        cout << "0. Kembali\n";
        cout << "Pilihan : ";
        cin >> pilih; cin.ignore();

        switch (pilih) {
            case 1: {
                string kode, nama, kodeKategori;
                double harga;
                int    stok;
                cout << "Kode Kategori : "; getline(cin, kodeKategori);
                cout << "Kode Barang   : "; getline(cin, kode);
                cout << "Nama Barang   : "; getline(cin, nama);
                cout << "Harga         : "; cin >> harga; cin.ignore();
                cout << "Stok          : "; cin >> stok;  cin.ignore();
                insertBarang(LK, kodeKategori,
                             createBarang(kode, nama, harga, stok));
                break;
            }
            case 2: viewAllBarang(LK); break;
            case 3: {
                string kodeKategori;
                cout << "Kode Kategori : "; getline(cin, kodeKategori);
                viewBarangByKategori(LK, kodeKategori);
                break;
            }
            case 4: {
                string kode, nama;
                double harga; int stok;
                cout << "Kode Barang : "; getline(cin, kode);
                cout << "Nama Baru   : "; getline(cin, nama);
                cout << "Harga Baru  : "; cin >> harga; cin.ignore();
                cout << "Stok Baru   : "; cin >> stok;  cin.ignore();
                updateBarang(LK, kode, nama, harga, stok);
                break;
            }
            case 5: {
                string kode;
                cout << "Kode Barang : "; getline(cin, kode);
                deleteBarang(LK, kode);
                break;
            }
            case 6: {
                string kode;
                cout << "Kode Barang : "; getline(cin, kode);
                Barang* B = searchBarang(LK, kode);
                if (B == NULL) cout << "Barang tidak ditemukan.\n";
                else cout << "Ditemukan: " << B->kodeBarang
                          << " - " << B->namaBarang
                          << " | Rp " << B->harga
                          << " | stok: " << B->stok << endl;
                break;
            }
        }
    } while (pilih != 0);
}

// =====================================================
// MENU PELANGGAN
// =====================================================
void menuPelanggan() {
    int pilih;
    do {
        cout << "\n===== MENU PELANGGAN =====\n";
        cout << "1. Tambah Pelanggan\n";
        cout << "2. Lihat Semua Pelanggan\n";
        cout << "3. Ubah Pelanggan\n";
        cout << "4. Hapus Pelanggan\n";
        cout << "5. Cari Pelanggan\n";
        cout << "0. Kembali\n";
        cout << "Pilihan : ";
        cin >> pilih; cin.ignore();

        switch (pilih) {
            case 1: {
                string id, nama, kontak;
                cout << "ID Pelanggan : "; getline(cin, id);
                cout << "Nama         : "; getline(cin, nama);
                cout << "Kontak       : "; getline(cin, kontak);
                insertPelanggan(LP, createPelanggan(id, nama, kontak));
                break;
            }
            case 2: viewAllPelanggan(LP); break;
            case 3: {
                string id, nama, kontak;
                cout << "ID Pelanggan : "; getline(cin, id);
                cout << "Nama Baru    : "; getline(cin, nama);
                cout << "Kontak Baru  : "; getline(cin, kontak);
                updatePelanggan(LP, id, nama, kontak);
                break;
            }
            case 4: {
                string id;
                cout << "ID Pelanggan : "; getline(cin, id);
                deletePelanggan(LP, id);
                break;
            }
            case 5: {
                string id;
                cout << "ID Pelanggan : "; getline(cin, id);
                Pelanggan* P = searchPelanggan(LP, id);
                if (P == NULL) cout << "Pelanggan tidak ditemukan.\n";
                else cout << "Ditemukan: " << P->idPelanggan
                          << " - " << P->nama
                          << " (" << P->kontak << ")\n";
                break;
            }
        }
    } while (pilih != 0);
}

// =====================================================
// MENU TRANSAKSI
// =====================================================
void menuTransaksi() {
    int pilih;
    do {
        cout << "\n===== MENU TRANSAKSI =====\n";
        cout << "1. Buat Transaksi Baru\n";
        cout << "2. Lihat Transaksi Pelanggan\n";
        cout << "3. Lihat Semua Transaksi\n";
        cout << "4. Laporan Penjualan\n";
        cout << "5. Laporan Barang Terjual\n";
        cout << "0. Kembali\n";
        cout << "Pilihan : ";
        cin >> pilih; cin.ignore();

        switch (pilih) {
            case 1: {
                if (isPelangganKosong(LP)) {
                    cout << "Belum ada pelanggan. Tambahkan dulu.\n";
                    break;
                }
                if (isKategoriKosong(LK)) {
                    cout << "Belum ada barang. Tambahkan dulu.\n";
                    break;
                }
                string id, kode, tanggal;
                cout << "ID Pelanggan    : "; getline(cin, id);
                cout << "Kode Transaksi  : "; getline(cin, kode);
                cout << "Tanggal (dd/mm) : "; getline(cin, tanggal);
                buatTransaksi(LP, LK, id, kode, tanggal);
                break;
            }
            case 2: {
                string id;
                cout << "ID Pelanggan : "; getline(cin, id);
                viewTransaksiPelanggan(LP, id);
                break;
            }
            case 3: viewAllTransaksi(LP);      break;
            case 4: laporanPenjualan(LP);      break;
            case 5: laporanBarangTerjual(LP);  break;
        }
    } while (pilih != 0);
}

// =====================================================
// MENU UTAMA
// =====================================================
void tampilMenuUtama() {
    cout << "\n=============================================\n";
    cout << "        PROGRAM PENJUALAN TOKO\n";
    cout << "       (Multi-Linked List ADT)\n";
    cout << "=============================================\n";
    cout << "1. Kelola Kategori\n";
    cout << "2. Kelola Barang\n";
    cout << "3. Kelola Pelanggan\n";
    cout << "4. Transaksi & Laporan Penjualan\n";
    cout << "5. Statistik Ringkas\n";
    cout << "0. Keluar\n";
    cout << "---------------------------------------------\n";
    cout << "Pilihan : ";
}

void tampilStatistik() {
    cout << "\n=== STATISTIK ===\n";
    cout << "Jumlah kategori       : " << countKategori(LK) << endl;
    cout << "Jumlah barang         : " << countTotalBarang(LK) << endl;
    cout << "Jumlah pelanggan      : " << countPelanggan(LP) << endl;
    cout << "Jumlah transaksi      : " << countAllTransaksi(LP) << endl;
    cout << "Total pendapatan      : Rp " << fixed << setprecision(0)
         << totalPendapatan(LP) << endl;
}

int main() {
    createListKategori(LK);
    createListPelanggan(LP);

    int pilih;
    do {
        tampilMenuUtama();
        cin >> pilih;
        cin.ignore();

        switch (pilih) {
            case 1: menuKategori();     break;
            case 2: menuBarang();       break;
            case 3: menuPelanggan();    break;
            case 4: menuTransaksi();    break;
            case 5: tampilStatistik();  break;
            case 0: cout << "Terima kasih!\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while (pilih != 0);

    // Bersihkan memori
    deleteAllPelanggan(LP);
    deleteAllKategori(LK);
    return 0;
}