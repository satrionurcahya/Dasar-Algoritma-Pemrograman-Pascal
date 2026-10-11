// =====================================================
// File : penjualan.cpp
// =====================================================

#include <iostream>
#include <iomanip>
#include "penjualan.h"
using namespace std;

// =====================================================
//                 OPERASI PELANGGAN
// =====================================================
void createListPelanggan(ListPelanggan &LP) {
    LP.firstPelanggan = NULL;
}

bool isPelangganKosong(ListPelanggan LP) {
    return (LP.firstPelanggan == NULL);
}

Pelanggan* createPelanggan(string id, string nama, string kontak) {
    Pelanggan* P = new Pelanggan;
    P->idPelanggan    = id;
    P->nama           = nama;
    P->kontak         = kontak;
    P->firstTransaksi = NULL;
    P->nextPelanggan  = NULL;
    return P;
}

void insertPelanggan(ListPelanggan &LP, Pelanggan* P) {
    if (searchPelanggan(LP, P->idPelanggan) != NULL) {
        cout << "ID pelanggan " << P->idPelanggan << " sudah terdaftar!\n";
        delete P;
        return;
    }
    if (LP.firstPelanggan == NULL) {
        LP.firstPelanggan = P;
    } else {
        Pelanggan* p = LP.firstPelanggan;
        while (p->nextPelanggan != NULL) p = p->nextPelanggan;
        p->nextPelanggan = P;
    }
    cout << "Pelanggan " << P->nama << " berhasil ditambahkan.\n";
}

Pelanggan* searchPelanggan(ListPelanggan LP, string id) {
    Pelanggan* p = LP.firstPelanggan;
    while (p != NULL) {
        if (p->idPelanggan == id) return p;
        p = p->nextPelanggan;
    }
    return NULL;
}

void updatePelanggan(ListPelanggan &LP, string id,
                     string namaBaru, string kontakBaru) {
    Pelanggan* P = searchPelanggan(LP, id);
    if (P == NULL) { cout << "Pelanggan tidak ditemukan.\n"; return; }
    P->nama   = namaBaru;
    P->kontak = kontakBaru;
    cout << "Data pelanggan berhasil diubah.\n";
}

void deletePelanggan(ListPelanggan &LP, string id) {
    Pelanggan* p    = LP.firstPelanggan;
    Pelanggan* prev = NULL;

    while (p != NULL && p->idPelanggan != id) {
        prev = p;
        p    = p->nextPelanggan;
    }
    if (p == NULL) { cout << "Pelanggan tidak ditemukan.\n"; return; }

    // Hapus semua transaksi pelanggan ini beserta detail-nya
    Transaksi* T = p->firstTransaksi;
    while (T != NULL) {
        Detail* D = T->firstDetail;
        while (D != NULL) {
            Detail* tempD = D;
            D = D->nextDetail;
            delete tempD;   // hanya hapus node Detail, BUKAN Barang-nya
        }
        Transaksi* tempT = T;
        T = T->nextTransaksi;
        delete tempT;
    }

    if (prev == NULL) LP.firstPelanggan = p->nextPelanggan;
    else              prev->nextPelanggan = p->nextPelanggan;

    cout << "Pelanggan " << p->nama << " beserta seluruh transaksinya dihapus.\n";
    delete p;
}

void viewAllPelanggan(ListPelanggan LP) {
    if (isPelangganKosong(LP)) {
        cout << "Belum ada data pelanggan.\n";
        return;
    }
    cout << "\n=== DAFTAR PELANGGAN ===\n";
    cout << "====================================================\n";
    cout << left << setw(10) << "ID"
         << setw(20) << "Nama"
         << setw(15) << "Kontak"
         << setw(10) << "Transaksi" << endl;
    cout << "====================================================\n";
    Pelanggan* P = LP.firstPelanggan;
    while (P != NULL) {
        cout << left << setw(10) << P->idPelanggan
             << setw(20) << P->nama
             << setw(15) << P->kontak
             << setw(10) << countTransaksiPelanggan(P) << endl;
        P = P->nextPelanggan;
    }
    cout << "====================================================\n";
}

// =====================================================
//                 OPERASI TRANSAKSI
// =====================================================
Transaksi* createTransaksi(string kode, string tanggal) {
    Transaksi* T = new Transaksi;
    T->kodeTransaksi = kode;
    T->tanggal       = tanggal;
    T->total         = 0;
    T->firstDetail   = NULL;
    T->nextTransaksi = NULL;
    return T;
}

Detail* createDetail(Barang* B, int jumlah) {
    Detail* D = new Detail;
    D->barang     = B;    // pointer ke Barang asli
    D->jumlah     = jumlah;
    D->subtotal   = B->harga * jumlah;
    D->nextDetail = NULL;
    return D;
}

void tambahDetail(Transaksi* T, Detail* D) {
    if (T->firstDetail == NULL) {
        T->firstDetail = D;
    } else {
        Detail* p = T->firstDetail;
        while (p->nextDetail != NULL) p = p->nextDetail;
        p->nextDetail = D;
    }
    T->total += D->subtotal;
}

// Prosedur buat transaksi lengkap (interaktif)
void buatTransaksi(ListPelanggan &LP, ListKategori &LK,
                   string idPelanggan, string kodeTransaksi,
                   string tanggal) {
    // Cek pelanggan
    Pelanggan* P = searchPelanggan(LP, idPelanggan);
    if (P == NULL) {
        cout << "Pelanggan dengan ID " << idPelanggan << " tidak ditemukan!\n";
        return;
    }

    Transaksi* T = createTransaksi(kodeTransaksi, tanggal);

    char lagi = 'y';
    while (lagi == 'y' || lagi == 'Y') {
        string kodeBarang;
        int    jumlah;

        cout << "\nKode barang yang dibeli : ";
        cin >> kodeBarang;
        cin.ignore();

        Barang* B = searchBarang(LK, kodeBarang);
        if (B == NULL) {
            cout << "Barang tidak ditemukan.\n";
        } else {
            cout << "Barang  : " << B->namaBarang << endl;
            cout << "Harga   : Rp " << fixed << setprecision(0) << B->harga << endl;
            cout << "Stok    : " << B->stok << endl;

            cout << "Jumlah beli : ";
            cin >> jumlah;
            cin.ignore();

            if (jumlah <= 0) {
                cout << "Jumlah tidak valid.\n";
            } else if (jumlah > B->stok) {
                cout << "Stok tidak mencukupi! Stok tersedia: " << B->stok << endl;
            } else {
                // Buat detail & kurangi stok
                Detail* D = createDetail(B, jumlah);
                tambahDetail(T, D);
                B->stok -= jumlah;
                cout << "Subtotal : Rp " << fixed << setprecision(0)
                     << D->subtotal << endl;
            }
        }

        cout << "Tambah barang lain? (y/t) : ";
        cin >> lagi;
        cin.ignore();
    }

    if (T->firstDetail == NULL) {
        cout << "Tidak ada barang yang dibeli. Transaksi dibatalkan.\n";
        delete T;
        return;
    }

    // Simpan transaksi ke list milik pelanggan
    if (P->firstTransaksi == NULL) {
        P->firstTransaksi = T;
    } else {
        Transaksi* t = P->firstTransaksi;
        while (t->nextTransaksi != NULL) t = t->nextTransaksi;
        t->nextTransaksi = T;
    }

    cout << "\n=== TRANSAKSI BERHASIL ===\n";
    cout << "Kode Transaksi : " << T->kodeTransaksi << endl;
    cout << "Tanggal        : " << T->tanggal << endl;
    cout << "Pelanggan      : " << P->nama << endl;
    cout << "Total Bayar    : Rp " << fixed << setprecision(0) << T->total << endl;
}

void viewTransaksiPelanggan(ListPelanggan LP, string idPelanggan) {
    Pelanggan* P = searchPelanggan(LP, idPelanggan);
    if (P == NULL) { cout << "Pelanggan tidak ditemukan.\n"; return; }

    cout << "\n=== RIWAYAT TRANSAKSI : " << P->nama
         << " (" << P->idPelanggan << ") ===\n";

    if (P->firstTransaksi == NULL) {
        cout << "(belum ada transaksi)\n";
        return;
    }

    Transaksi* T = P->firstTransaksi;
    while (T != NULL) {
        cout << "\nKode : " << T->kodeTransaksi
             << " | Tanggal : " << T->tanggal
             << " | Total : Rp " << fixed << setprecision(0) << T->total << endl;

        Detail* D = T->firstDetail;
        while (D != NULL) {
            cout << "   - " << D->barang->kodeBarang << " "
                 << D->barang->namaBarang
                 << " x " << D->jumlah
                 << " = Rp " << fixed << setprecision(0) << D->subtotal << endl;
            D = D->nextDetail;
        }
        T = T->nextTransaksi;
    }
}

void viewAllTransaksi(ListPelanggan LP) {
    if (isPelangganKosong(LP)) { cout << "Belum ada pelanggan.\n"; return; }
    if (countAllTransaksi(LP) == 0) {
        cout << "Belum ada transaksi tercatat.\n";
        return;
    }

    cout << "\n=== SELURUH TRANSAKSI ===\n";
    Pelanggan* P = LP.firstPelanggan;
    while (P != NULL) {
        Transaksi* T = P->firstTransaksi;
        while (T != NULL) {
            cout << T->kodeTransaksi << " | " << T->tanggal
                 << " | Pelanggan: " << P->nama
                 << " | Total: Rp " << fixed << setprecision(0) << T->total << endl;
            T = T->nextTransaksi;
        }
        P = P->nextPelanggan;
    }
}

void laporanPenjualan(ListPelanggan LP) {
    int    totalTransaksi = countAllTransaksi(LP);
    double pendapatan     = totalPendapatan(LP);

    cout << "\n=== LAPORAN PENJUALAN ===\n";
    cout << "Jumlah transaksi   : " << totalTransaksi << endl;
    cout << "Total pendapatan   : Rp " << fixed << setprecision(0)
         << pendapatan << endl;
    cout << "Rata-rata/transaksi: Rp ";
    if (totalTransaksi == 0) cout << 0;
    else                     cout << fixed << setprecision(0)
                                    << pendapatan / totalTransaksi;
    cout << endl;
}

// Laporan barang terjual - pakai pendekatan sederhana:
// kumpulkan kode barang unik, hitung total qty terjual
void laporanBarangTerjual(ListPelanggan LP) {
    if (isPelangganKosong(LP)) { cout << "Belum ada pelanggan.\n"; return; }

    // Kumpulkan kode barang unik + total qty terjual
    string kodeUnik[200];
    int    qtyJual[200];
    double totalRp[200];
    string namaUnik[200];
    int    n = 0;

    Pelanggan* P = LP.firstPelanggan;
    while (P != NULL) {
        Transaksi* T = P->firstTransaksi;
        while (T != NULL) {
            Detail* D = T->firstDetail;
            while (D != NULL) {
                // cari kode di list unik
                bool found = false;
                for (int i = 0; i < n; i++) {
                    if (kodeUnik[i] == D->barang->kodeBarang) {
                        qtyJual[i] += D->jumlah;
                        totalRp[i] += D->subtotal;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    kodeUnik[n]  = D->barang->kodeBarang;
                    namaUnik[n]  = D->barang->namaBarang;
                    qtyJual[n]   = D->jumlah;
                    totalRp[n]   = D->subtotal;
                    n++;
                }
                D = D->nextDetail;
            }
            T = T->nextTransaksi;
        }
        P = P->nextPelanggan;
    }

    if (n == 0) { cout << "Belum ada barang terjual.\n"; return; }

    cout << "\n=== LAPORAN BARANG TERJUAL ===\n";
    cout << "============================================================\n";
    cout << left << setw(10) << "Kode"
         << setw(25) << "Nama Barang"
         << setw(10) << "Terjual"
         << setw(15) << "Total (Rp)" << endl;
    cout << "============================================================\n";
    for (int i = 0; i < n; i++) {
        cout << left << setw(10) << kodeUnik[i]
             << setw(25) << namaUnik[i]
             << setw(10) << qtyJual[i]
             << setw(15) << fixed << setprecision(0) << totalRp[i] << endl;
    }
    cout << "============================================================\n";
}

// =====================================================
//                 UTIL
// =====================================================
int countPelanggan(ListPelanggan LP) {
    int c = 0;
    Pelanggan* P = LP.firstPelanggan;
    while (P != NULL) { c++; P = P->nextPelanggan; }
    return c;
}

int countTransaksiPelanggan(Pelanggan* P) {
    if (P == NULL) return 0;
    int c = 0;
    Transaksi* T = P->firstTransaksi;
    while (T != NULL) { c++; T = T->nextTransaksi; }
    return c;
}

int countAllTransaksi(ListPelanggan LP) {
    int total = 0;
    Pelanggan* P = LP.firstPelanggan;
    while (P != NULL) {
        total += countTransaksiPelanggan(P);
        P = P->nextPelanggan;
    }
    return total;
}

double totalPendapatan(ListPelanggan LP) {
    double total = 0;
    Pelanggan* P = LP.firstPelanggan;
    while (P != NULL) {
        Transaksi* T = P->firstTransaksi;
        while (T != NULL) {
            total += T->total;
            T = T->nextTransaksi;
        }
        P = P->nextPelanggan;
    }
    return total;
}

void deleteAllPelanggan(ListPelanggan &LP) {
    Pelanggan* P = LP.firstPelanggan;
    while (P != NULL) {
        Transaksi* T = P->firstTransaksi;
        while (T != NULL) {
            Detail* D = T->firstDetail;
            while (D != NULL) {
                Detail* tempD = D;
                D = D->nextDetail;
                delete tempD;
            }
            Transaksi* tempT = T;
            T = T->nextTransaksi;
            delete tempT;
        }
        Pelanggan* tempP = P;
        P = P->nextPelanggan;
        delete tempP;
    }
    LP.firstPelanggan = NULL;
}