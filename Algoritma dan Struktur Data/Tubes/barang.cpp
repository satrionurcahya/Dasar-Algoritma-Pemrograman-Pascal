// =====================================================
// File : barang.cpp
// =====================================================

#include <iostream>
#include <iomanip>
#include "barang.h"
using namespace std;

// =====================================================
//                 OPERASI KATEGORI
// =====================================================
void createListKategori(ListKategori &LK) {
    LK.firstKategori = NULL;
}

bool isKategoriKosong(ListKategori LK) {
    return (LK.firstKategori == NULL);
}

Kategori* createKategori(string kode, string nama) {
    Kategori* K = new Kategori;
    K->kodeKategori = kode;
    K->namaKategori = nama;
    K->firstBarang  = NULL;
    K->nextKategori = NULL;
    return K;
}

void insertKategori(ListKategori &LK, Kategori* K) {
    if (searchKategori(LK, K->kodeKategori) != NULL) {
        cout << "Kode kategori " << K->kodeKategori << " sudah terdaftar!\n";
        delete K;
        return;
    }
    if (LK.firstKategori == NULL) {
        LK.firstKategori = K;
    } else {
        Kategori* p = LK.firstKategori;
        while (p->nextKategori != NULL) p = p->nextKategori;
        p->nextKategori = K;
    }
    cout << "Kategori " << K->namaKategori << " berhasil ditambahkan.\n";
}

Kategori* searchKategori(ListKategori LK, string kode) {
    Kategori* p = LK.firstKategori;
    while (p != NULL) {
        if (p->kodeKategori == kode) return p;
        p = p->nextKategori;
    }
    return NULL;
}

void updateKategori(ListKategori &LK, string kode, string namaBaru) {
    Kategori* K = searchKategori(LK, kode);
    if (K == NULL) { cout << "Kategori tidak ditemukan.\n"; return; }
    K->namaKategori = namaBaru;
    cout << "Kategori berhasil diubah.\n";
}

void deleteKategori(ListKategori &LK, string kode) {
    Kategori* p    = LK.firstKategori;
    Kategori* prev = NULL;

    while (p != NULL && p->kodeKategori != kode) {
        prev = p;
        p    = p->nextKategori;
    }
    if (p == NULL) { cout << "Kategori tidak ditemukan.\n"; return; }

    // Hapus semua barang dalam kategori ini
    Barang* B = p->firstBarang;
    while (B != NULL) {
        Barang* temp = B;
        B = B->nextBarang;
        delete temp;
    }

    // Hapus kategori dari list
    if (prev == NULL) LK.firstKategori = p->nextKategori;
    else              prev->nextKategori = p->nextKategori;

    cout << "Kategori " << p->namaKategori << " dan seluruh barangnya dihapus.\n";
    delete p;
}

void viewAllKategori(ListKategori LK) {
    if (isKategoriKosong(LK)) {
        cout << "Belum ada data kategori.\n";
        return;
    }
    cout << "\n=== DAFTAR KATEGORI ===\n";
    Kategori* K = LK.firstKategori;
    while (K != NULL) {
        cout << "\n[" << K->kodeKategori << "] " << K->namaKategori << endl;
        if (K->firstBarang == NULL) {
            cout << "  (belum ada barang)\n";
        } else {
            Barang* B = K->firstBarang;
            while (B != NULL) {
                cout << "  - " << B->kodeBarang << " | "
                     << setw(20) << left << B->namaBarang
                     << " | Rp " << setw(10) << fixed << setprecision(0) << B->harga
                     << " | stok: " << B->stok << endl;
                B = B->nextBarang;
            }
        }
        K = K->nextKategori;
    }
}

// =====================================================
//                 OPERASI BARANG
// =====================================================
Barang* createBarang(string kode, string nama, double harga, int stok) {
    Barang* B = new Barang;
    B->kodeBarang = kode;
    B->namaBarang = nama;
    B->harga      = harga;
    B->stok       = stok;
    B->nextBarang = NULL;
    return B;
}

void insertBarang(ListKategori &LK, string kodeKategori, Barang* B) {
    Kategori* K = searchKategori(LK, kodeKategori);
    if (K == NULL) {
        cout << "Kategori " << kodeKategori << " tidak ditemukan!\n";
        delete B;
        return;
    }
    // Cek duplikat kode barang di seluruh kategori
    if (searchBarang(LK, B->kodeBarang) != NULL) {
        cout << "Kode barang " << B->kodeBarang << " sudah terdaftar!\n";
        delete B;
        return;
    }
    // Insert di akhir list barang kategori
    if (K->firstBarang == NULL) {
        K->firstBarang = B;
    } else {
        Barang* p = K->firstBarang;
        while (p->nextBarang != NULL) p = p->nextBarang;
        p->nextBarang = B;
    }
    cout << "Barang " << B->namaBarang << " berhasil ditambahkan ke kategori "
         << K->namaKategori << ".\n";
}

Barang* searchBarangDiKategori(Kategori* K, string kodeBarang) {
    if (K == NULL) return NULL;
    Barang* B = K->firstBarang;
    while (B != NULL) {
        if (B->kodeBarang == kodeBarang) return B;
        B = B->nextBarang;
    }
    return NULL;
}

Barang* searchBarang(ListKategori LK, string kodeBarang) {
    Kategori* K = LK.firstKategori;
    while (K != NULL) {
        Barang* B = searchBarangDiKategori(K, kodeBarang);
        if (B != NULL) return B;
        K = K->nextKategori;
    }
    return NULL;
}

void updateBarang(ListKategori &LK, string kodeBarang,
                  string namaBaru, double hargaBaru, int stokBaru) {
    Barang* B = searchBarang(LK, kodeBarang);
    if (B == NULL) { cout << "Barang tidak ditemukan.\n"; return; }
    B->namaBarang = namaBaru;
    B->harga      = hargaBaru;
    B->stok       = stokBaru;
    cout << "Data barang berhasil diubah.\n";
}

void deleteBarang(ListKategori &LK, string kodeBarang) {
    Kategori* K = LK.firstKategori;
    while (K != NULL) {
        Barang* B    = K->firstBarang;
        Barang* prev = NULL;
        while (B != NULL && B->kodeBarang != kodeBarang) {
            prev = B;
            B    = B->nextBarang;
        }
        if (B != NULL) {
            if (prev == NULL) K->firstBarang = B->nextBarang;
            else              prev->nextBarang = B->nextBarang;
            cout << "Barang " << B->namaBarang << " berhasil dihapus.\n";
            delete B;
            return;
        }
        K = K->nextKategori;
    }
    cout << "Barang tidak ditemukan.\n";
}

void viewAllBarang(ListKategori LK) {
    if (isKategoriKosong(LK)) {
        cout << "Belum ada data.\n";
        return;
    }
    cout << "\n=============================================================\n";
    cout << left << setw(10) << "Kode"
         << setw(25) << "Nama Barang"
         << setw(15) << "Harga"
         << setw(8)  << "Stok"
         << setw(10) << "Kategori" << endl;
    cout << "=============================================================\n";
    Kategori* K = LK.firstKategori;
    while (K != NULL) {
        Barang* B = K->firstBarang;
        while (B != NULL) {
            cout << left << setw(10) << B->kodeBarang
                 << setw(25) << B->namaBarang
                 << "Rp " << setw(12) << fixed << setprecision(0) << B->harga
                 << setw(8)  << B->stok
                 << setw(10) << K->namaKategori << endl;
            B = B->nextBarang;
        }
        K = K->nextKategori;
    }
    cout << "=============================================================\n";
}

void viewBarangByKategori(ListKategori LK, string kodeKategori) {
    Kategori* K = searchKategori(LK, kodeKategori);
    if (K == NULL) { cout << "Kategori tidak ditemukan.\n"; return; }

    cout << "\n=== Barang dalam kategori " << K->namaKategori << " ===\n";
    if (K->firstBarang == NULL) {
        cout << "(belum ada barang)\n";
        return;
    }
    Barang* B = K->firstBarang;
    while (B != NULL) {
        cout << "  " << B->kodeBarang << " | " << B->namaBarang
             << " | Rp " << fixed << setprecision(0) << B->harga
             << " | stok: " << B->stok << endl;
        B = B->nextBarang;
    }
}

// =====================================================
//                 UTIL
// =====================================================
int countKategori(ListKategori LK) {
    int c = 0;
    Kategori* K = LK.firstKategori;
    while (K != NULL) { c++; K = K->nextKategori; }
    return c;
}

int countBarangDiKategori(Kategori* K) {
    if (K == NULL) return 0;
    int c = 0;
    Barang* B = K->firstBarang;
    while (B != NULL) { c++; B = B->nextBarang; }
    return c;
}

int countTotalBarang(ListKategori LK) {
    int total = 0;
    Kategori* K = LK.firstKategori;
    while (K != NULL) {
        total += countBarangDiKategori(K);
        K = K->nextKategori;
    }
    return total;
}

void deleteAllKategori(ListKategori &LK) {
    Kategori* K = LK.firstKategori;
    while (K != NULL) {
        Kategori* tempK = K;
        Barang* B = K->firstBarang;
        while (B != NULL) {
            Barang* tempB = B;
            B = B->nextBarang;
            delete tempB;
        }
        K = K->nextKategori;
        delete tempK;
    }
    LK.firstKategori = NULL;
}