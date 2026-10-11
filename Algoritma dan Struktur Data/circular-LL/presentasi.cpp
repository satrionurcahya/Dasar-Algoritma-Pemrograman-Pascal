// =====================================================
// TUGAS 3      : Sistem Pengelolaan Aktivitas Akademik
//                (Circular Double Linked List)
// Nama         : Satrio Nurcahya
// NIM          : 1303180078
// Kelas        : IT-42-01
// File         : presentasi.cpp
// =====================================================

#include <iostream>
#include <iomanip>
#include "presentasi.h"
using namespace std;

// =====================================================
// 1. CREATE LIST - Inisialisasi list kosong
// =====================================================
void createListPresentasi(ListPresentasi &L) {
    L.First = NULL;
    L.Last  = NULL;
    L.Aktif = NULL;
}

// =====================================================
// 2. IS NULL - Cek apakah list kosong
// =====================================================
bool isNullPresentasi(ListPresentasi L) {
    return (L.First == NULL);
}

// =====================================================
// 3. CREATE DATA - Buat node kelompok baru
// =====================================================
NodePresentasi* createDataPresentasi(string kode, string ketua, string topik) {
    NodePresentasi* newNode = new NodePresentasi;

    newNode->data.kodeKelompok = kode;
    newNode->data.namaKetua    = ketua;
    newNode->data.topik        = topik;
    newNode->data.status       = "belum";     // status awal

    newNode->Next = NULL;
    newNode->Prev = NULL;

    return newNode;
}

// =====================================================
// 4. INSERT FIRST - Tambah kelompok di awal
// =====================================================
void insertFirstPresentasi(ListPresentasi &L, NodePresentasi* P) {
    if (L.First == NULL) {
        // List kosong
        L.First = P;
        L.Last  = P;
        L.Aktif = P;
        P->Next = P;
        P->Prev = P;
    } else {
        // Sisipkan di depan
        P->Next        = L.First;
        P->Prev        = L.Last;
        L.First->Prev  = P;
        L.Last->Next   = P;
        L.First        = P;
    }
}

// =====================================================
// 5. INSERT LAST - Tambah kelompok di akhir
// =====================================================
void insertLastPresentasi(ListPresentasi &L, NodePresentasi* P) {
    if (L.First == NULL) {
        // List kosong
        L.First = P;
        L.Last  = P;
        L.Aktif = P;
        P->Next = P;
        P->Prev = P;
    } else {
        // Sisipkan di belakang
        P->Next        = L.First;
        P->Prev        = L.Last;
        L.Last->Next   = P;
        L.First->Prev  = P;
        L.Last         = P;
    }
}

// =====================================================
// 6. NEXT GROUP - Pindah ke kelompok berikutnya
// =====================================================
void nextGroup(ListPresentasi &L) {
    if (isNullPresentasi(L)) {
        cout << "Belum ada kelompok dalam jadwal.\n";
        return;
    }
    L.Aktif = L.Aktif->Next;
    cout << "Sekarang di kelompok: " << L.Aktif->data.kodeKelompok
         << " (" << L.Aktif->data.namaKetua << ")\n";
}

// =====================================================
// 7. PREV GROUP - Pindah ke kelompok sebelumnya
// =====================================================
void prevGroup(ListPresentasi &L) {
    if (isNullPresentasi(L)) {
        cout << "Belum ada kelompok dalam jadwal.\n";
        return;
    }
    L.Aktif = L.Aktif->Prev;
    cout << "Sekarang di kelompok: " << L.Aktif->data.kodeKelompok
         << " (" << L.Aktif->data.namaKetua << ")\n";
}

// =====================================================
// 8. SEARCH KELOMPOK - Sequential Search
// =====================================================
bool searchKelompok(ListPresentasi L, string kode) {
    if (L.First == NULL) return false;

    NodePresentasi* P = L.First;
    do {
        if (P->data.kodeKelompok == kode) return true;
        P = P->Next;
    } while (P != L.First);

    return false;
}

// =====================================================
// 9. UPDATE STATUS - Ubah status presentasi
// =====================================================
void updateStatus(ListPresentasi &L, string kode, string statusBaru) {
    if (isNullPresentasi(L)) {
        cout << "Belum ada kelompok dalam jadwal.\n";
        return;
    }

    NodePresentasi* P = L.First;
    bool ketemu = false;
    do {
        if (P->data.kodeKelompok == kode) {
            P->data.status = statusBaru;
            ketemu = true;
            cout << "Status kelompok " << kode
                 << " berhasil diubah menjadi \"" << statusBaru << "\".\n";
            break;
        }
        P = P->Next;
    } while (P != L.First);

    if (!ketemu)
        cout << "Kelompok dengan kode " << kode << " tidak ditemukan.\n";
}

// =====================================================
// 10. DELETE BY KODE - Hapus kelompok berdasarkan kode
// =====================================================
void deleteByKode(ListPresentasi &L, string kode) {
    if (isNullPresentasi(L)) {
        cout << "List kosong, tidak ada yang bisa dihapus.\n";
        return;
    }

    NodePresentasi* P = L.First;
    bool ketemu = false;

    do {
        if (P->data.kodeKelompok == kode) {
            ketemu = true;
            break;
        }
        P = P->Next;
    } while (P != L.First);

    if (!ketemu) {
        cout << "Kelompok dengan kode " << kode << " tidak ditemukan.\n";
        return;
    }

    // ---- Hapus node P ----
    if (P->Next == P) {
        // Hanya satu elemen
        L.First = NULL;
        L.Last  = NULL;
        L.Aktif = NULL;
    } else {
        P->Prev->Next = P->Next;
        P->Next->Prev = P->Prev;

        if (P == L.First) L.First = P->Next;
        if (P == L.Last)  L.Last  = P->Prev;
        if (P == L.Aktif) L.Aktif = P->Next;
    }

    cout << "Kelompok " << kode << " berhasil dihapus.\n";
    delete P;
}

// =====================================================
// 11. VIEW ALL - Tampilkan seluruh kelompok
// =====================================================
void viewAllPresentasi(ListPresentasi L) {
    if (L.First == NULL) {
        cout << "Belum ada kelompok dalam jadwal presentasi.\n";
        return;
    }

    cout << "\n=========================================================================\n";
    cout << left << setw(10) << "Kode"
         << setw(20) << "Ketua"
         << setw(25) << "Topik"
         << setw(15) << "Status" << endl;
    cout << "=========================================================================\n";

    NodePresentasi* P = L.First;
    do {
        cout << left << setw(10) << P->data.kodeKelompok
             << setw(20) << P->data.namaKetua
             << setw(25) << P->data.topik
             << setw(15) << P->data.status;
        if (P == L.Aktif) cout << "  <-- posisi aktif";
        cout << endl;
        P = P->Next;
    } while (P != L.First);

    cout << "=========================================================================\n";
}

// =====================================================
// 12. COUNT NODE - Hitung jumlah kelompok
// =====================================================
int countNodePresentasi(ListPresentasi L) {
    if (L.First == NULL) return 0;

    int hitung = 0;
    NodePresentasi* P = L.First;
    do {
        hitung++;
        P = P->Next;
    } while (P != L.First);

    return hitung;
}